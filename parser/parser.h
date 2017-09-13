const char* MSG_HELP = "\n  help message\n";

const char* MSG_GET_HELP = "\n  for help run the program with the parameter \'-h\', such as--\n\t ./parse -h\n";

const char* ERR_MISSING_SOURCE       = "\n  missing source file for parsing\n";
const char* ERR_CANNOT_OPEN_SOURCE   = "\n  error when opening source file\n";
const char* ERR_CANNOT_CREATE_BINARY = "\n  error when creating binary file\n";

const char* INSN_SET      = "set";
const char* INSN_BRANCH_A = "ba";
const char* INSN_BRANCH_R = "br";
const char* INSN_JUMP_A   = "ja";
const char* INSN_JUMP_R   = "jr";
const char* INSN_ADD      = "add";
const char* INSN_SUB      = "sub";
const char* INSN_ULS      = "lsu";
const char* INSN_URS      = "rsu";
const char* INSN_SLS      = "lss";
const char* INSN_SRS      = "rss";
const char* INSN_AND      = "and";
const char* INSN_OR       = "or";
const char* INSN_XOR      = "xor";
const char* INSN_NOT      = "not";
const char* INSN_LESS     = "lss";
const char* INSN_EQL      = "eql";
const char* INSN_GRT      = "grt";
const char* INSN_ABS      = "abs";
const char* INSN_LOAD     = "ld";
const char* INSN_SAVE     = "sv";
const char* INSN_NOP      = "nop";
const char* INSN_HLT      = "hlt";

const char* FLAG_SET      = "1";
const char* FLAG_BRANCH_A = "0100";
const char* FLAG_BRANCH_R = "0101";
const char* FLAG_JUMP_A   = "0110";
const char* FLAG_JUMP_R   = "0111";

const int REGISTER_WIDTH  = 4;
const int IMMEDIATE_WIDTH = 11;
