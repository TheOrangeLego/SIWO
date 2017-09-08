import definitions::*;

module instructionFetch_tb;
  bit                     _CLK;
  bit                     _run;
  bit                     _reset;
  bit                     _halt;
  bit                     _branchJump;
  bit                     _relative;
  bit  [DATA_WIDTH - 1:0] _destBranchJump;
  wire [INSN_WIDTH - 1:0] instruction;

instructionFetch uut (
  ._CLK            ( _CLK ),
  ._run            ( _run ),
  ._reset          ( _reset ),
  ._halt           ( _halt ),
  ._branchJump     ( _branchJump ),
  ._relative       ( _relative ),
  ._destBranchJump ( _destBranchJump ),
  .instruction     ( instruction )
  );

initial
begin
  #00ns
    _CLK = 1;
    _run = 0;
    _reset = 1;
    _halt = 0;
    _branchJump = 0;
    _relative = 0;
    _destBranchJump = 0;

  #10ns
    _run = 1;
    _reset = 0;
  
  #10ns
    _relative = 1;
    _destBranchJump = 20;

  #10ns
    _branchJump = 1;
    _destBranchJump = 5;

  #10ns
    _branchJump = 0;
    _relative = 0;
    _destBranchJump = 0;

  #10ns
    _branchJump = 1;
    _relative = 1;
    _destBranchJump = -3;

  #10ns
    _branchJump = 1;
    _relative = 0;
    _destBranchJump = 0;

  #10ns
    _branchJump = 1;
    _destBranchJump = 14;
  
  #10ns
    _branchJump = 0;
    _destBranchJump = 0;

  #10ns
    _halt = 1;

  #10ns
    _reset = 1;

  #10ns
    $stop;
end

always
begin
  #5ns
    _CLK = ~_CLK;
end

endmodule
