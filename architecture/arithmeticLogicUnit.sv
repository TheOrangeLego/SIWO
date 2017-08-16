/* import definitions */
import definitions::*;

module arithmeticLogicUnit (
  /* value from source A */
  input        [DATA_WIDTH - 1:0] _valA,
  /* value from source B */
  input        [DATA_WIDTH - 1:0] _valB,
  /* operation function code */
  input        [FUNC_WIDTH - 1:0] _funcCode,
  /* result */
  output logic [DATA_WIDTH - 1:0] result,
  /* overflow bit */
  output logic                    overflow,
  /* comparison bit */
  output logic                    compareBit
  );

  /* compute result when source values change */
  always_comb
  begin
    /* set default values */
    result     = 16'h0;
    overflow   = 1'b0;
    compareBit = 1'b0;
    
    /* compute the result or comparison bit depending on the function code */
    case ( _funcCode[FUNC_WIDTH - 1:0] )
      FUNC_SET : result = _valA;
      FUNC_ADD : result = _valA + _valB;
      FUNC_SUB : result = _valA - _valB;
      FUNC_ULS : result = { ( _valA << _valB ), _valB{0} };
      FUNC_URS : result = { _valB{0}, ( _valA >> _valB ) };
      FUNC_SLS : result = { ( _valA << _valB ), _valB{ _valA[0] } };
      FUNC_SRS : result = { _valB{ _valA[DATA_WIDTH - 1] }, ( _valA >> _valB ) };
      FUNC_AND : result = _valA & _valB;
      FUNC_OR  : result = _valA | _valB;
      FUNC_XOR : result = _valA ^ _valB;
      FUNC_NOT : result = !_valA;
      FUNC_LSS : compareBit = ( $signed( _valA ) < $signed( _valB ) ) ? 1'b1 : 1'b0;
      FUNC_EQL : compareBit = ( $signed( _valA ) == $signed( _valB ) ) ? 1'b1 : 1'b0;
      FUNC_GRT : compareBit = ( $signed( _valA ) > $signed( _valB ) ) ? 1'b1 : 1'b0;
      FUNC_ABS : result = ( _valA[DATA_WIDTH - 1] == 1'b1 ) ? -_valA : _valA
    endcase
    
    /* determine if overflow when adding */
    if ( _funcCode == FUNC_ADD && $signed( result ) < $signed( _valA ) )
      overflow = 1'b1;
    /* determine if overflow when subtracting */
    if ( _funcCode == FUNC_SUB && $signed( result ) > $signed( _valA ) )
      overflow = 1'b1;
  end

endmodule

