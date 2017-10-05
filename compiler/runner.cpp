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
  if ( argc < 2 )
  {
    std::cout << "Missing source file" << std::endl;
    return 1;
  }

  std::ifstream input(  argv[1]);
  std::ofstream output( "output.txt" );

  std::list<std::string> tokens;
  ASTNode* root = NULL;
  std::string insn = "";

  if ( !input.is_open() || !output.is_open() )
    return 1;

  appendStream( input );
  tokens = getTokens();

  root = generateStatement( tokens );

  insn = compile( root, std::list<std::pair<std::string, int> >(), 0, std::list<int>() );

  output << insn << "hlt\n";

  delete root;
  input.close();
  output.close();
  return 0;
}
