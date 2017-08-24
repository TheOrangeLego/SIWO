import definitions::*;

module controlUnit_tb;

  bit  [INSN_WIDTH - 1:0] _instruction;
  wire                    halt;
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
  wire                    overflowWrite;
  wire                    compareWrite;
  wire                    memoryRead;
  wire                    memoryWrite;
  wire                    muxMA;

controlUnit uut (
  ._instruction   ( _instruction ),
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
  .overflowWrite  ( overflowWrite ),
  .compareWrite   ( compareWrite ),
  .memoryRead     ( memoryRead ),
  .memoryWrite    ( memoryWrite ),
  .muxMA          ( muxMA )
  );

initial
begin
  #10ns
    $stop;
end

endmodule
