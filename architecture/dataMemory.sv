/* import definitions */
import definitions::*;

module dataMemory (
  /* write on positive clock edge */
  input                           _CLK,
  /* read signal */
  input                           _read,
  /* write signal */
  input                           _write,
  /* address where input will be written at */
  input        [DATA_WIDTH - 1:0] _address,
  /* value to be written into data memory */
  input        [DATA_WIDTH - 1:0] _valueIn,
  /* value read from data memory */
  output logic [DATA_WIDTH - 1:0] valueOut
  );
  
  /* stores all data memory */
  logic [DATA_WIDTH - 1:0] data [2**DATA_WIDTH];

  /* load the entire data memory */
  initial
    $readmemb( "data_memory.txt", data);

  /* if read signaled, read at specified address */
  always_comb
    if ( _read )
      valueOut = data[_address];
    else
      valueOut = 0;

  /* on positive edge and write signaled, write into data memory */
  always @ ( posedge _CLK )
    if ( _write )
    begin
      data[_address] = _valueIn;
      $writememb( "data_memory.txt", data );
    end

endmodule

