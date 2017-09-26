#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "lexer.h"
#include "parser.h"
#include "analyzer.h"
#include "compiler.h"

int main ( int argc, char* argv[] )
{
  std::ifstream input( "input.txt" );
  std::ofstream output( "output.txt" );

  std::list<std::string> tokens;
  Expression* root = NULL;
  std::string insn = "";

  if ( !input.is_open() || !output.is_open() )
    return 1;

  appendStream( input );
  tokens = getNextTokens();

  if ( !validTokens( tokens ) )
    return 2;

  tokens = orderTokens( tokens );
  root = generateAS( tokens );

  insn = compile( root, std::list<std::string>(), 0, std::list<int>() );

  output << insn << "hlt\n";

  delete root;
  input.close();
  output.close();
  return 0;
}
