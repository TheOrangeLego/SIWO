#include "assembler.h"

int main ( int argc, char* argv[] )
{
  /* if no parameters provided, exit with error message */
  if ( argc == 1 )
  {
    ( void ) printf( "%s%s\n", ERR_MISSING_SOURCE, MSG_GET_HELP );
    return 1;
  }

  /* open input and output file streams */
  std::ifstream sourceFile( argv[1] );
  std::ofstream binaryFile( OUTPUT_FILE );

  /* if input file fails to open, exit with error message */
  if ( !sourceFile.is_open() )
  {
    ( void ) printf( "%s\n", ERR_CANNOT_OPEN_SOURCE );
    return 2;
  }
  
  /* if output file fails to open, exit with error message */
  if ( !binaryFile.is_open() )
  {
    ( void ) printf( "%s\n", ERR_CANNOT_CREATE_BINARY );
    return 2;
  }

  /* generate the binary file given both input and output files */
  generateBinary( sourceFile, binaryFile );

  /* close input and output files */
  sourceFile.close();
  binaryFile.close();

  return 0;
}

/* Function - generateBinary */
void generateBinary( std::ifstream& _in, std::ofstream& _out )
{
  /* position where first endline character is found */
  std::size_t endlineChar;
  /* will contain input file content as string format */
  std::string contentString;
  /* will contain input file content as stringstream format */
  std::stringstream contentStream;
  
  /* read the contents in the file */
  contentStream << _in.rdbuf();
  /* convert contents into string format */
  contentString = contentStream.str();
  /* find first instance of endline character */
  endlineChar = contentString.find_first_of( "\n" );

  /* continue this process while there are lines in file */
  while ( endlineChar != std::string::npos )
  {
    /* contains the top line of assembly */
    std::string currentLine = contentString.substr( 0, endlineChar );

    /* remove the first line from remaining contents */
    contentString = contentString.substr( endlineChar + 1 );
    /* find the next first instance of newline character */
    endlineChar = contentString.find_first_of( "\n" );
    /* translate the top assembly line and write into output file */
    _out << translate( currentLine );
  }
}

/* Function - translate */
std::string translate( std::string _currentLine )
{
  /* if the line is empty, return an empty translation */
  if ( !_currentLine.size() )
    return "";
  
  /* if NOP instruction, translate into binary */
  if ( !_currentLine.compare( INSN_NOP ) )
    return FLAG_NOP;
  
  /* if HLT instruction, translate into binary */
  if ( !_currentLine.compare( INSN_HLT ) )
    return FLAG_HLT;
  
  /* will contain complete translated line */
  std::string translatedLine = ""; 
  /* extract the function / operation at the head of the assembly line */
  std::string header = _currentLine.substr( 0, _currentLine.find_first_of( " " ) );
  /* keep the remaining of the assembly line after the head */
  _currentLine = _currentLine.substr( _currentLine.find_first_of( " " ) + 1 );

  /* if function is SET */
  if ( header == INSN_SET )
  {
    /* extract register from line */
    std::string reg = _currentLine.substr( 1, _currentLine.find_first_of( "," ) );
    /* extract immediate value from line */
    std::string val = _currentLine.substr( _currentLine.find_first_of( "," ) + 2 );
    /* convert register into binary value */
    std::bitset<REGISTER_WIDTH> regBit( std::atoi( reg.c_str() ) );
    /* convert immediate into binary value */
    std::bitset<IMMEDIATE_WIDTH> valBit( std::atoi( val.c_str() ) );

    /* form the translated line */
    translatedLine = FLAG_SET + regBit.to_string() + valBit.to_string() + "\n";
  }
  /* if function is a branch or jump */
  else if ( header[0] == 'B' || header[0] == 'J' )
  {
    /* translate absolute branch */
    if ( header == INSN_BRANCH_A )
      translatedLine = FLAG_BRANCH_A;
    /* translate relative branch */
    else if ( header == INSN_BRANCH_R )
      translatedLine = FLAG_BRANCH_R;
    /* translate absolute jump */
    else if ( header == INSN_JUMP_A )
      translatedLine = FLAG_JUMP_A;
    /* translate relative jump */
    else
      translatedLine = FLAG_JUMP_R;

    /* convert immediate value to binary */
    std::bitset<IMMEDIATE_WIDTH> valBit( std::atoi( _currentLine.c_str() ) );
    /* form the translated line */
    translatedLine += valBit.to_string() + "\n";
  }
  /* if line is comment */
  else if ( header[0] == header[1] == '+' )
  { /* do nothing */ }
  /* for all other operations */
  else
  {
    /* extract register A from line */
    std::string regA = _currentLine.substr( 1, _currentLine.find_first_of( "," ) );
    /* extract register B from line */
    std::string regB = _currentLine.substr( _currentLine.find_first_of( "," ) + 3 );
    /* convert register A to binary representation */
    std::bitset<REGISTER_WIDTH> regBitA( std::atoi( regA.c_str() ) );
    /* convert register B to binary representation */
    std::bitset<REGISTER_WIDTH> regBitB( std::atoi( regB.c_str() ) );

    /* set front of translated line */
    translatedLine = FLAG_OPERATION + regBitA.to_string() + regBitB.to_string();

    /* translate operation into corresponding binary representation */
    /* note - this looks really disturbing */
    if ( header == INSN_ADD )
      translatedLine += FLAG_ADD;
    else if ( header == INSN_SUB )
      translatedLine += FLAG_SUB;
    else if ( header == INSN_ULS )
      translatedLine += FLAG_ULS;
    else if ( header == INSN_URS )
      translatedLine += FLAG_URS;
    else if ( header == INSN_SLS )
      translatedLine += FLAG_SLS;
    else if ( header == INSN_SRS )
      translatedLine += FLAG_SRS;
    else if ( header == INSN_AND )
      translatedLine += FLAG_AND;
    else if ( header == INSN_OR )
      translatedLine += FLAG_OR;
    else if ( header == INSN_XOR )
      translatedLine += FLAG_XOR;
    else if ( header == INSN_NOT )
      translatedLine += FLAG_NOT;
    else if ( header == INSN_LESS )
      translatedLine += FLAG_LESS;
    else if ( header == INSN_EQL )
      translatedLine += FLAG_EQL;
    else if ( header == INSN_GRT )
      translatedLine += FLAG_GRT;
    else if ( header == INSN_ABS )
      translatedLine += FLAG_ABS;
    else if ( header == INSN_LOAD )
      translatedLine += FLAG_LOAD;
    else if ( header == INSN_SAVE )
      translatedLine += FLAG_SAVE;
    else if ( header == INSN_MOVE )
      translatedLine += FLAG_MOVE;
    else
      return "";
  }

  /* return translated line */
  return translatedLine;
}

