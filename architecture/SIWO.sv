import definitions::*;

module SIWO (
  input  _CLK,
  input  _start,
  output halt
  );

  logic [INSN_WIDTH - 1:0] insnCount = 'b0;

endmodule
