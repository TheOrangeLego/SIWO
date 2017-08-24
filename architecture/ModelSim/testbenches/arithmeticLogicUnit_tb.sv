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
  #10ns
    $stop;
end

endmodule
