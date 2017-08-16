/* import definitions */
import definitions::*;

module registerFile (
  /* write on positive clock edge */
  input                     _CLK,
  /* bit flag to determine if need to write */
  input                     _regWrite,
  /* address of output register A */
  input  [REG_WIDTH - 1:0]  _regSrcA,
  /* address of output register B */
  input  [REG_WIDTH - 1:0]  _regSrcB,
  /* address of register to be written at */
  input  [REG_WIDTH - 1:0]  _regDest,
  /* value to write into destination register */
  input  [DATA_WIDTH - 1:0] _writeVal,
  /* value read from register A */
  output [DATA_WIDTH - 1:0] valueA,
  /* value read from register B */
  output [DATA_WIDTH - 1:0] valueB
  );

  /* all registers */
  logic [DATA_WIDTH - 1:0] registers[2**REG_WIDTH];

  /* load the values from specified registers */
  assign valueA = registers[_regSrcA];
  assign valueB = registers[_regSrcB];

  /* on positive edge, write to destination register if writing enabled */
  always @ ( posedge _CLK )
    if ( _regWrite )
      registers[_regDest] = _writeVal;

endmodule

