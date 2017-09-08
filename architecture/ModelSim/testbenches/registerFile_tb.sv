import definitions::*;

module registerFile_tb;
  bit                     _CLK;
  bit                     _regWrite;
  bit  [REG_WIDTH - 1:0]  _regSrcA;
  bit  [REG_WIDTH - 1:0]  _regSrcB;
  bit  [REG_WIDTH - 1:0]  _regDest;
  bit  [DATA_WIDTH - 1:0] _writeVal;
  wire [DATA_WIDTH - 1:0] valueA;
  wire [DATA_WIDTH - 1:0] valueB;

registerFile uut (
  ._CLK      ( _CLK ),
  ._regWrite ( _regWrite ),
  ._regSrcA  ( _regSrcA ),
  ._regSrcB  ( _regSrcB ),
  ._regDest  ( _regDest ),
  ._writeVal ( _writeVal ),
  .valueA    ( valueA ),
  .valueB    ( valueB )
  );

initial
begin
  /* set default input values */
  #00ns
    _CLK = 1;
    _regWrite = 0;
    _regSrcA = 0;
    _regSrcB = 0;
    _regDest = 0;
    _writeVal = 0;

  /* write value into register */
  #10ns
    _regWrite = 1;
    _regDest = 0;
    _writeVal = 10;

  /* write value into another register */
  #10ns
    _regWrite = 1;
    _regDest = 2;
    _writeVal = 7;

  /* change source register */
  #10ns
    _regWrite = 0;
    _regSrcA = 2;
    _regSrcB = 0;

  /* update register value */
  #10ns
    _regSrcB = 5;
    _regDest = 2;
    _writeVal = 11;

  /* update register value */
  #10ns
    _regWrite = 1;
    _regDest = 2;
    _writeVal = 55;

  /* test register writing without write signal */
  #10ns
    _regWrite = 0;
    _writeVal = 14;

  #10ns
    $stop;
end

always
begin
  #5ns
    _CLK = ~_CLK;
end

endmodule
