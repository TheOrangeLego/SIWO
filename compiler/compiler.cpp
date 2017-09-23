#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "analyzer.h"

int main ( int argc, char* argv[] )
{
  std::ifstream inputFile( "input.txt" );
  std::list<std::string> tokens;

  if ( !inputFile.is_open() )
    return 1;

  appendStream( inputFile );
  tokens = getNextTokens();
  validTokens( tokens );

  ( void ) generateAS( tokens );

  inputFile.close();

  return 0;
}
