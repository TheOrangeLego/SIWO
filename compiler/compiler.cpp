#include <iostream>
#include "lexer.h"
#include "parser.h"

int main ( int argc, char* argv[] )
{
  std::ifstream inputFile( "input.txt" );
  std::list<std::string> tokens;
  std::list<std::string> newTokens;

  if ( !inputFile.is_open() )
    return 1;

  appendStream( inputFile );

  while ( !streamEmpty() )
  {
    newTokens = getNextTokens();
    tokens.merge( newTokens );
  }

  validTokens( tokens );

  inputFile.close();

  return 0;
}
