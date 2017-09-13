#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <cstdlib>
#include "parser.h"

void generateBinary( std::ifstream&, std::ofstream& );
std::string translate( std::string );

int main ( int argc, char* argv[] )
{
  if ( argc == 1 )
  {
    ( void ) printf( "%s%s\n", ERR_MISSING_SOURCE, MSG_GET_HELP );
    return 1;
  }

  std::ifstream sourceFile( "source.a" );
  std::ofstream binaryFile( "source.b" );

  if ( !sourceFile.is_open() )
  {
    ( void ) printf( "%s\n", ERR_CANNOT_OPEN_SOURCE );
    return 2;
  }
  
  if ( !binaryFile.is_open() )
  {
    ( void ) printf( "%s\n", ERR_CANNOT_CREATE_BINARY );
    return 2;
  }

  generateBinary( sourceFile, binaryFile );

  sourceFile.close();
  binaryFile.close();

  return 0;
}

void generateBinary( std::ifstream& _in, std::ofstream& _out )
{
  std::size_t endlineChar;
  std::string contentString;
  std::stringstream contentStream;
  
  contentStream << _in.rdbuf();
  contentString = contentStream.str();

  endlineChar = contentString.find_first_of( "\n" );

  while ( endlineChar != std::string::npos )
  {
    std::string currentLine = contentString.substr( 0, endlineChar );

    contentString = contentString.substr( endlineChar + 1 );
    endlineChar = contentString.find_first_of( "\n" );
    _out << translate( contentString );
  }
}

std::string translate( std::string _currentLine )
{
  if ( !_currentLine.size() )
    return "";

  std::string translatedLine = "";
  std::string header = _currentLine.substr( 0, _currentLine.find_first_of( " " ) );
  _currentLine = _currentLine.substr( _currentLine.find_first_of( " " ) + 1 );

  if ( header == INSN_SET )
  {
    std::string reg = _currentLine.substr( 0, _currentLine.find_first_of( "," ) );
    std::string val = _currentLine.substr( _currentLine.find_first_of( "," ) + 2 );

    std::bitset<REGISTER_WIDTH> regBit( std::atoi( reg.c_str() ) );
    std::bitset<IMMEDIATE_WIDTH> valBit( std::atoi( val.c_str() ) );

    translatedLine = FLAG_SET + regBit.to_string() + valBit.to_string() + "\n";
  }
  else if ( header[0] == 'b' || header[0] == 'j' )
  {
    if ( header == INSN_BRANCH_A )
      translatedLine = FLAG_BRANCH_A;
    else if ( header == INSN_BRANCH_R )
      translatedLine = FLAG_BRANCH_R;
    else if ( header == INSN_JUMP_A )
      translatedLine = FLAG_JUMP_A;
    else
      translatedLine = FLAG_JUMP_R;

    std::bitset<IMMEDIATE_WIDTH> valBit( std::atoi( _currentLine.c_str() ) );
    translatedLine += valBit.to_string() + "\n";
  }
  else
  {
  }

  return translatedLine;
}

