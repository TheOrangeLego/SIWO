import definitions::*;

module SIWO_tb;
  bit  _CLK;
  bit  _start;
  wire halt;

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
  _CLK = !_CLK;

  if ( halt )
    $stop;

end

endmodule
