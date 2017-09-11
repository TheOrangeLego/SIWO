/* import definitions */
import definitions::*;

module controlUnit (
  /* instruction fetched from ROM */
  input        [INSN_WIDTH - 1:0] _instruction,
  /* halt signal for instruction fetch */
  output logic                    halt,
  /* branch signal for instruction fetch */
  output logic                    branch,
  /* jump signal for instruction fetch */
  output logic                    jump,
  /* relative branch or jump for instruction fetch */
  output logic                    relative,
  /* destination address for instruction fetch */
  output logic [DATA_WIDTH - 1:0] destBranchJump,
  /* register A for register file */
  output logic [REG_WIDTH - 1:0]  regA,
  /* register B for register file */
  output logic [REG_WIDTH - 1:0]  regB,
  /* write signal for register file */
  output logic                    regWrite,
  /* mux signal choosing between register A data or immediate value */
  output logic                    muxRI,
  /* immediate value for ALU */
  output logic [DATA_WIDTH - 1:0] immediateValue,
  /* function code for ALU */
  output logic [FUNC_WIDTH - 1:0] funcCode,
  
  output logic                    overflow,
  
  output logic                    compare,
  /* read signal for data memory */
  output logic                    memoryRead,
  /* write signal for data memory */
  output logic                    memoryWrite,
  /* mux signal choosing between data memory or ALU output */
  output logic                    muxMA
  );

  always_comb
  begin
    /* default values for output logic */
    halt           = 0;
    branch         = 0;
    jump           = 0;
    relative       = 0;
    destBranchJump = 0;
    regA           = 0;
    regB           = 0;
    regWrite       = 0;
    muxRI          = 0;
    immediateValue = 0;
    funcCode       = 0;
    overflow       = 0;
    compare        = 0;
    memoryRead     = 0;
    memoryWrite    = 0;
    muxMA          = 0;

    case ( _instruction[INSN_WIDTH - 1:INSN_WIDTH - FLAG_WIDTH] )
      /* for set instructions */
      FLAG_SET : begin
          /* set the appropriate destination register */
          regA           = _instruction[INSN_SET_REG_S:INSN_SET_REG_E];
	  /* write the data into the register file */
          regWrite       = 1;
	  /* choose immediate value */
	  muxRI          = 1;
	  /* set the immediate value */
          immediateValue = _instruction[INSN_SET_IMMD:0];
	  /* ALU function code */
          funcCode       = FUNC_SET;
	  /* choose result from ALU */
          muxMA          = 1;
        end
      /* for branch or jump instructions */
      FLAG_BRANCH_JUMP : begin
          /* mark for branch or jump depending on branch/jump bit */
          if ( _instruction[INSN_BRANCH_BIT] == 0 )
	    branch = 1;
	  else
	    jump = 1;
	  /* set relative bit */
	  relative = _instruction[INSN_RELATIVE_BIT];
	  /* set destination address */
	  destBranchJump = _instruction[INSN_BRANCH_IMMD:0];
        end
      /* for operation instructions */
      FLAG_OPERATION : begin
          /* choose depending on function code */
          case ( _instruction[INSN_OP_FUNC:0] )
	    /* comparison functions only need to write comparison bit */
	    FUNC_LSS : compare = 1;
	    FUNC_EQL : compare = 1;
	    FUNC_GRT : compare = 1;
	    /* on load, write to register file and read from data memory */
	    FUNC_LD  : begin
		regWrite = 1;
		memoryRead = 1;
	      end
	    /* on save, write to memory */
	    FUNC_SV  : memoryWrite = 1;
	    /* for other function codes, write to register file */
	    /* and choose output of ALU */
	    default  : begin
	        regWrite = 1;
	        overflow = 1;
	        muxMA = 1;
	      end
	  endcase

	  /* set source A, source B, and destination registers */
          regA = _instruction[INSN_REG_A_S:INSN_REG_A_E];
          regB = _instruction[INSN_REG_B_S:INSN_REG_B_E];
	  /* set ALU function code */
	  funcCode = _instruction[FUNC_WIDTH - 1:0];
        end
      default : begin
          /* if halt instruction issued, send halt signal */
          if ( _instruction == INSN_HLT )
	    halt = 1;
        end
    endcase
  end

endmodule

