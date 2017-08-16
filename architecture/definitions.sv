package definitions;
  /* count and width constants */
  localparam INSN_WIDTH = 16;
  localparam DATA_WIDTH = 16;
  localparam REG_WIDTH  = 4;
  localparam FLAG_WIDTH = 3;
  localparam FUNC_WIDTH = 5;

  /* significant addresses */
  const logic [DATA_WIDTH - 1:0] START_ADDRESS = 16'h0;

  /* instruction type flags */
  const logic [FLAG_WIDTH - 1:0] FLAG_SET         = 3'b1??;
  const logic [FLAG_WIDTH - 1:0] FLAG_BRANCH_JUMP = 3'b01?;
  const logic [FLAG_WIDTH - 1:0] FLAG_OPERATION   = 3'b001;

  /* operation function codes */
  const logic [FUNC_WIDTH - 1:0] FUNC_SET = 5'b00000;
  const logic [FUNC_WIDTH - 1:0] FUNC_ADD = 5'b00001;
  const logic [FUNC_WIDTH - 1:0] FUNC_SUB = 5'b00010;
  const logic [FUNC_WIDTH - 1:0] FUNC_ULS = 5'b00011;
  const logic [FUNC_WIDTH - 1:0] FUNC_URS = 5'b00100;
  const logic [FUNC_WIDTH - 1:0] FUNC_SLS = 5'b00101;
  const logic [FUNC_WIDTH - 1:0] FUNC_SRS = 5'b00110;
  const logic [FUNC_WIDTH - 1:0] FUNC_AND = 5'b00111;
  const logic [FUNC_WIDTH - 1:0] FUNC_OR  = 5'b01000;
  const logic [FUNC_WIDTH - 1:0] FUNC_XOR = 5'b01001;
  const logic [FUNC_WIDTH - 1:0] FUNC_NOT = 5'b01010;
  const logic [FUNC_WIDTH - 1:0] FUNC_LSS = 5'b01011;
  const logic [FUNC_WIDTH - 1:0] FUNC_EQL = 5'b01100;
  const logic [FUNC_WIDTH - 1:0] FUNC_GRT = 5'b01101;
  const logic [FUNC_WIDTH - 1:0] FUNC_ABS = 5'b01110;

  /* reserved instructions */
  const logic [INSN_WIDTH - 1:0] INSN_NOP = 16'h1;
  const logic [INSN_WIDTH - 1:0] INSN_HLT = 16'h0;
endpackage

