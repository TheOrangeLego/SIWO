import definitions::*;

module SIWO_tb;
  bit  _CLK;
  bit  _start;
  wire halt;

SIWO uut (
  ._CLK   ( _CLK ),
  ._start ( _start ),
  .halt   ( halt )
  );

initial
begin
  #00ns
    _CLK = 1;
    _start = 0;

  #10ns
    _start = 1;
end

always
begin
  #5ns
  _CLK = ~_CLK;

  if ( halt )
    $stop;

end

endmodule
