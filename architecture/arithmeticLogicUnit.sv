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
    result     = 0;
    overflow   = 0;
    compareBit = 0;
    
    /* compute the result or comparison bit depending on the function code */
    case ( _funcCode[FUNC_WIDTH - 1:0] )
      FUNC_SET : result = _valA;
      FUNC_ADD : result = _valA + _valB;
      FUNC_SUB : result = _valA - _valB;
      FUNC_ULS : result = _valA << _valB;
      FUNC_URS : result = _valA >> _valB;
      FUNC_SLS : result = $signed( _valA ) <<< _valB;
      FUNC_SRS : result = $signed( _valA ) >>> _valB;
      FUNC_AND : result = _valA & _valB;
      FUNC_OR  : result = _valA | _valB;
      FUNC_XOR : result = _valA ^ _valB;
      FUNC_NOT : result = !_valA;
      FUNC_LSS : result = ( $signed( _valA ) < $signed( _valB ) )  ? 1 : 0;
      FUNC_EQL : result = ( $signed( _valA ) == $signed( _valB ) ) ? 1 : 0;
      FUNC_GRT : result = ( $signed( _valA ) > $signed( _valB ) )  ? 1 : 0;
      FUNC_ABS : result = ( _valA[DATA_WIDTH - 1] == 1 ) ? -_valA : _valA;
      default  : result = 0;
    endcase
    
    /* determine if overflow when adding */
    if ( _funcCode == FUNC_ADD && (
      ( $signed( result ) < 0 && $signed( _valA ) > 0 && $signed( _valB ) > 0 ) ||
      ( $signed( result ) > 0 && $signed( _valA ) < 0 && $signed( _valB ) < 0 ) ) )
      overflow = 1;

    /* determine if overflow when subtracting */
    if ( _funcCode == FUNC_SUB && (
      ( $signed( result ) < 0 && $signed( _valA ) > 0 && $signed( _valB ) < 0 ) ||
      ( $signed( result ) > 0 && $signed( _valA ) < 0 && $signed( _valB ) > 0 ) ) )
      overflow = 1;

    if ( _funcCode >= FUNC_NOT && _funcCode <= FUNC_GRT )
      compareBit = result[0];
  end

endmodule

