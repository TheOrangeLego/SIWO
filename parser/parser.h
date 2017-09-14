#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <cstdlib>

const char* OUTPUT_FILE = "instructionROM.b";

/* regular messages */
const char* MSG_HELP     = "\n  help message\n";
const char* MSG_GET_HELP = "\n  for help run the program with the parameter \'-h\', such as--\n\t ./parse -h\n";

/* errors messages */
const char* ERR_MISSING_SOURCE       = "\n  missing source file for parsing\n";
const char* ERR_CANNOT_OPEN_SOURCE   = "\n  error when opening source file\n";
const char* ERR_CANNOT_CREATE_BINARY = "\n  error when creating binary file\n";

/* functions and operations of instructions */
const char* INSN_SET      = "SET";
const char* INSN_BRANCH_A = "BA";
const char* INSN_BRANCH_R = "BR";
const char* INSN_JUMP_A   = "JA";
const char* INSN_JUMP_R   = "JR";
const char* INSN_ADD      = "ADD";
const char* INSN_SUB      = "SUB";
const char* INSN_ULS      = "ULS";
const char* INSN_URS      = "URS";
const char* INSN_SLS      = "SLS";
const char* INSN_SRS      = "SRS";
const char* INSN_AND      = "AND";
const char* INSN_OR       = "OR";
const char* INSN_XOR      = "XOR";
const char* INSN_NOT      = "NOT";
const char* INSN_LESS     = "LSS";
const char* INSN_EQL      = "EQL";
const char* INSN_GRT      = "GRT";
const char* INSN_ABS      = "ABS";
const char* INSN_LOAD     = "LD";
const char* INSN_SAVE     = "SV";
const char* INSN_NOP      = "NOP";
const char* INSN_HLT      = "HLT";

/* binary translations of functions and operations */
const char* FLAG_SET       = "1";
const char* FLAG_BRANCH_A  = "0100";
const char* FLAG_BRANCH_R  = "0101";
const char* FLAG_JUMP_A    = "0110";
const char* FLAG_JUMP_R    = "0111";
const char* FLAG_OPERATION = "001";
const char* FLAG_ADD       = "00001\n";
const char* FLAG_SUB       = "00010\n";
const char* FLAG_ULS       = "00011\n";
const char* FLAG_URS       = "00100\n";
const char* FLAG_SLS       = "00101\n";
const char* FLAG_SRS       = "00110\n";
const char* FLAG_AND       = "00111\n";
const char* FLAG_OR        = "01000\n";
const char* FLAG_XOR       = "01001\n";
const char* FLAG_NOT       = "01010\n";
const char* FLAG_LESS      = "01011\n";
const char* FLAG_EQL       = "01100\n";
const char* FLAG_GRT       = "01101\n";
const char* FLAG_ABS       = "01110\n";
const char* FLAG_LOAD      = "01111\n";
const char* FLAG_SAVE      = "10000\n";
const char* FLAG_NOP       = "0000000000000001\n";
const char* FLAG_HLT       = "0000000000000000\n";

/* constant widths */
const int REGISTER_WIDTH    = 4;
const int IMMEDIATE_WIDTH   = 11;
const int INSTRUCTION_WIDTH = 16;

/*
 * Function     - generateBinary
 *
 * Parameters   -
 *  - std::ifstream& - reference to input file that contains assembly code
 *  - std::ofstream& - reference to output file where binary code will be written to
 *
 * Return Value - none
 *
 * Description  - generates the binary code from the assembly input file and writes it to
 *                 output file
 */
void generateBinary( std::ifstream&, std::ofstream& );

/*
 * Function     - translate
 *
 * Parameters   -
 *  - std::string - line of assembly to be translated
 *
 * Return Value - string containing binary representation of assembly line
 *
 * Description  - translates the provided assembly line into binary
 */
std::string translate( std::string );
