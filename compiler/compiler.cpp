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

  tokens = orderTokens( tokens );
  Expression* root = generateAS( tokens );
  printAS( root );

  std::cout << std::endl;

  inputFile.close();

  return 0;
}
