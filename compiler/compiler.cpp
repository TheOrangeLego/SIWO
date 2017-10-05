#include <string.h>
#include "lexer.h"
#include "compiler.h"

int findEnv( std::list<std::string> _env, std::string _var )
{
  for ( std::list<std::string>::iterator it = _env.begin(); it != _env.end(); it++ )
    if ( !strcmp( ( *it ).c_str(), _var.c_str() ) )
      return 0;

  return -1;
}

std::string insnConstant( std::string _value, int _registerIndex )
{
  std::string insn = "set r" + std::to_string( _registerIndex ) + ", " + _value + "\n";
  return insn;
}

std::string insnIdentifier( int _register, int _registerIndex )
{
  std::string insn = "ld r" + std::to_string( _registerIndex ) + ", r" +
                     std::to_string( _register ) + "\n";
  return insn;
}

std::string compile( Expression* _expr, std::list<std::string> _env, int _registerIndex,
                     std::list<int> _errorList )
{
  std::string instruction = "................";

  if ( _expr -> getType() == Expression::Constant )
    instruction = insnConstant( _expr -> getToken(), _registerIndex );

  if ( _expr -> getType() == Expression::Identifier )
  {
    int identifier = findEnv( _env, _expr -> getToken() );

    if ( identifier == -1 )
      return "........////";

    instruction = insnIdentifier( identifier, _registerIndex );
  }

  if ( _expr -> getType() == Expression::Operator )
  {
    std::string leftInsn = compile( _expr -> getLeftExpression(), _env,
                                    _registerIndex, _errorList );
    std::string rightInsn = compile( _expr -> getRightExpression(), _env,
                                    _registerIndex + 1, _errorList );
  }

  return instruction;
  
}
