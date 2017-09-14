import definitions::*;

module SIWO (
  input  _CLK,
  input  _start,
  output halt
  );

  logic [INSN_WIDTH - 1:0] insnCount = 'b0;

  /* miscellaneous wires */
  wire                    branchJump;
  wire [DATA_WIDTH - 1:0] writeValue;
  wire [DATA_WIDTH - 1:0] valueMUXA;
  wire [DATA_WIDTH - 1:0] valueMUXB;
  
  /* wire outputs from instruction fetch module */
  wire [INSN_WIDTH - 1:0] instruction;
  
  /* wire outputs from control unit module */
  wire                    branch;
  wire                    jump;
  wire                    relative;
  wire [DATA_WIDTH - 1:0] destBranchJump;
  wire [REG_WIDTH - 1:0]  regA;
  wire [REG_WIDTH - 1:0]  regB;
  wire                    regWrite;
  wire                    muxRI;
  wire [DATA_WIDTH - 1:0] immediateValue;
  wire [FUNC_WIDTH - 1:0] funcCode;
  wire                    overflow;
  wire                    compare;
  wire                    memoryRead;
  wire                    memoryWrite;
  wire                    muxMA;

  /* wire outputs from register file module */
  wire [DATA_WIDTH - 1:0] valueRegA;
  wire [DATA_WIDTH - 1:0] valueRegB;

  /* wire outputs from arithmetic logic unit module */
  wire [DATA_WIDTH - 1:0] result;
  wire                    overflowBit;
  wire                    compareBit;

  /* wire outputs from data memory module */
  wire [DATA_WIDTH - 1:0] valueData;

  /* miscellaneous wire assignments */
  assign branchJump = ( branch && ( ( overflow && overflowBit ) ||
		      ( compare && compareBit ) ) ) || jump;
  assign valueMUXA  = ( muxRI == 0 ) ? valueRegA : immediateValue;
  assign valueMUXB  = valueRegB;
  assign writeValue = ( muxMA == 0 ) ? valueData : result;

  always_ff @( posedge _CLK )
    insnCount <= insnCount + 1;

  /* module implementations */

  instructionFetch instructionFetch_module (
    ._CLK            ( _CLK ),
    ._run            ( _start ),
    ._reset          ( ~_start ),
    ._halt           ( halt ),
    ._branchJump     ( branchJump ),
    ._relative       ( relative ),
    ._destBranchJump ( destBranchJump ),
    .instruction     ( instruction )
    );

  controlUnit controlUnit_module (
    ._instruction   ( instruction ),
    .halt           ( halt ),
    .branch         ( branch ),
    .jump           ( jump ),
    .relative       ( relative ),
    .destBranchJump ( destBranchJump ),
    .regA           ( regA ),
    .regB           ( regB ),
    .regWrite       ( regWrite ),
    .muxRI          ( muxRI ),
    .immediateValue ( immediateValue ),
    .funcCode       ( funcCode ),
    .overflow       ( overflow ),
    .compare        ( compare ),
    .memoryRead     ( memoryRead ),
    .memoryWrite    ( memoryWrite ),
    .muxMA          ( muxMA )
    );

  registerFile registerFile_module (
    ._CLK      ( _CLK ),
    ._regWrite ( regWrite ),
    ._regSrcA  ( regA ),
    ._regSrcB  ( regB ),
    ._regDest  ( regA ),
    ._writeVal ( writeValue ),
    .valueA    ( valueRegA ),
    .valueB    ( valueRegB )
    );

  arithmeticLogicUnit arithmeticLogicUnit_module (
    ._valA      ( valueMUXA ),
    ._valB      ( valueMUXB ),
    ._funcCode  ( funcCode ),
    .result     ( result ),
    .overflow   ( overflowBit ),
    .compareBit ( compareBit )
    );

  dataMemory dataMemory_module (
    ._CLK     ( _CLK ),
    ._read    ( memoryRead ),
    ._write   ( memoryWrite ),
    ._address ( valueMUXB ),
    ._valueIn ( result ),
    .valueOut ( valueData )
    );

endmodule
