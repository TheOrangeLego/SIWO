import definitions::*;

module arithmeticLogicUnit_tb;

  bit  [DATA_WIDTH - 1:0] _valA;
  bit  [DATA_WIDTH - 1:0] _valB;
  bit  [FUNC_WIDTH - 1:0] _funcCode;
  wire [DATA_WIDTH - 1:0] result;
  wire                    overflow;
  wire                    compareBit;

arithmeticLogicUnit uut (
  ._valA      ( _valA ),
  ._valB      ( _valB ),
  ._funcCode  ( _funcCode ),
  .result     ( result ),
  .overflow   ( overflow ),
  .compareBit ( compareBit )
  );

initial
begin
  /* testing set function */
  #10ns
    _valA = 10;
    _valB = 11;
    _funcCode = FUNC_SET;

  #10ns
    _valA = 15;
    _valB = 4;

  #10ns
    _valA = -12;

  #10ns
    _valA = 0;

  /* testing add function */
  #10ns
    _valA = 2;
    _valB = 5;
    _funcCode = FUNC_ADD;

  #10ns
    _valA = 0;
    _valB = 55;

  #10ns
    _valA = -12;
    _valB = -1;

  #10ns
    _valA = 16'h7fff;
    _valB = 1;

  #10ns
    _valA = -44;
    _valB = 67;

  #10ns
    _valA = 16'h8001;
    _valB = -2;

  #10ns
    _valA = 33;
    _valB = -13;

  /* testing subtract function */
  #10ns
    _valA = 2;
    _valB = 5;
    _funcCode = FUNC_SUB;

  #10ns
    _valA = 0;
    _valB = 55;

  #10ns
    _valA = -12;
    _valB = -1;

  #10ns
    _valA = 16'h8001;
    _valB = 3;

  #10ns
    _valA = 16'hffff;
    _valB = -1;

  #10ns
    _valA = 16'h7fff;
    _valB = -7;

  #10ns
    _valA = 33;
    _valB = -13;

  /* testing logical left shift function */
  #10ns
    _valA = 2;
    _valB = 3;
    _funcCode = FUNC_ULS;

  /* testing logical right shift function */
  #10ns
    _valA = -1;
    _valB = 2;
    _funcCode = FUNC_URS;

  /* testing arithmetic left shift function */
  #10ns
    _valA = 3;
    _valB = 1;
    _funcCode = FUNC_SLS;

  /* testing arithmetic right shift function */
  #10ns
    _valA = -3;
    _valB = 4;
    _funcCode = FUNC_SRS;

  /* testing and function */
  #10ns
    _valA = 16'habcd;
    _valB = 0;
    _funcCode = FUNC_AND;

  #10ns
    _valA = 16'habcd;
    _valB = 16'haaaa;

  /* testing or function */
  #10ns
    _valA = 3;
    _valB = 22;
    _funcCode = FUNC_OR;

  #10ns
    _valA = 3;
    _valB = 0;

  /* testing xor function */
  #10ns
    _valA = 16'habcd;
    _valB = 16'h24a3;
    _funcCode = FUNC_XOR;

  #10ns
    _valA = 16'haaaa;
    _valB = 16'h5555;

  /* testing not function */
  #10ns
    _valA = 7;
    _funcCode = FUNC_NOT;

  #10ns
    _valA = 0;
  
  /* testing less function */
  #10ns
    _valA = 3;
    _valB = -7;
    _funcCode = FUNC_LSS;

  #10ns
    _valA = -14;
    _valB = -14;

  #10ns
    _valA = -1;
    _valB = 0;

  /* testing equal function */
  #10ns
    _valA = 3;
    _valB = -7;
    _funcCode = FUNC_EQL;

  #10ns
    _valA = -14;
    _valB = -14;

  #10ns
    _valA = -1;
    _valB = 0;

  /* testing greater function */
  #10ns
    _valA = 3;
    _valB = -7;
    _funcCode = FUNC_GRT;

  #10ns
    _valA = -14;
    _valB = -14;

  #10ns
    _valA = -1;
    _valB = 0;

  /* testing absolute function */
  #10ns
    _valA = 15;
    _funcCode = FUNC_ABS;

  #10ns
    _valA = -212;

  #10ns
    _valA = 0;

  #10ns
    $stop;
end

endmodule
