/* import definitions */
import definitions::*;

module instructionFetch (
  /* update the program counter per positive clock edge */
  input                     _CLK,
  /* flag determines if running */
  input                     _run,
  /* flag determines resetting address */
  input                     _reset,
  /* flag determines if halting */
  input                     _halt,
  /* flag determines if branching or jumping */
  input                     _branchJump,
  /* flag determines if the branching or jumping is relative */
  input                     _relative,
  /* address that will be relatively or absolutely set by branch or jump */
  input  [DATA_WIDTH - 1:0] _destBranchJump,
  /* instruction read from the instruction ROM */
  output [INSN_WIDTH - 1:0] instruction
  );

  /* currenet program counter */
  logic [DATA_WIDTH - 1:0] programCounter;
  /* store all instructions in ROM */
  logic [INSN_WIDTH - 1:0] instructionROM [2**DATA_WIDTH];

  /* load all instructions in ROM */
  initial
    $readmemb( "instructionROM.txt", instructionROM );
  
  /* on positive edge */
  always_ff @ ( posedge _CLK )
  begin
    /* if module running and not signaled to halt, load instruction */
    if ( _run && !_halt )
      instruction <= instructionROM[programCounter];
    
    /* if module running, increase the program counter */
    if ( _run )
      programCounter <= programCounter + 1;
    /* if signaled to reset, set program counter to default address */
    else if ( _reset )
      programCounter <= START_ADDRESS;
    /* if signaled to branch or jump */
    else if ( _branchJump )
    begin
      /* if the branch or jump is relative, signed addition of program */
      /* counter with the destination address value, else set absolutely */
      if ( _relative )
        programCounter <= programCounter + $signed( _destBranchJump );
      else
        programCounter <= _destBranchJump;
    end
    /* else keep program counter the same */
    else
      programCounter <= programCounter;
  end
endmodule

