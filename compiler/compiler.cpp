#include <string.h>
#include "lexer.h"
#include "compiler.h"

#include <iostream>

int findEnv( std::list<std::pair<std::string, int> > _env, std::string _var )
{

  for ( std::list<std::pair<std::string, int> >::iterator it = _env.begin();
       it != _env.end(); it++ )
    if ( !strcmp( ( it -> first ).c_str(), _var.c_str() ) )
      return it -> second;

  return -1;
}

std::string insnConstant( std::string _value, int _registerIndex )
{
  std::string insn = "set r" + std::to_string( _registerIndex ) + ", " + _value + "\n";
  return insn;
}

std::string insnIdentifier( int _register, int _registerIndex )
{
  std::string insn = "mov r" + std::to_string( _registerIndex ) + ", r" +
                     std::to_string( _register ) + "\n";
  return insn;
}

std::string insnOperator( int _registerIndex, std::string _operator )
{
  std::string insn = _operator + " r" + std::to_string( _registerIndex ) + ", r" + 
                     std::to_string( _registerIndex + 1 ) + "\n";
  return insn;
}

std::string compile( ASTNode* _node, std::list<std::pair<std::string, int> > _env,
                     int _registerIndex, std::list<int> _errorList )
{
  std::string instruction;

  if ( _node -> getType() == ASTNode::Constant )
    instruction = insnConstant( _node -> getToken(), _registerIndex );

  if ( _node-> getType() == ASTNode::Identifier )
  {
    int identifier = findEnv( _env, _node -> getToken() );

    if ( identifier == -1 )
      return "................";

    instruction = insnIdentifier( identifier,  _registerIndex );
  }

  if ( _node -> getType() == ASTNode::Operator )
  {
    std::string leftInsn = compile( _node -> getLeftNode(), _env, _registerIndex,
                                    _errorList );

    std::string rightInsn = compile( _node -> getRightNode(), _env, _registerIndex + 1,
                                     _errorList );

    instruction = leftInsn + rightInsn;

    if ( !strcmp( _node -> getToken().c_str(), TOKEN_ADD ) )
      instruction += insnOperator( _registerIndex, "add" );

    if ( !strcmp( _node -> getToken().c_str(), TOKEN_SUB ) )
      instruction += insnOperator( _registerIndex, "sub" );
  }

  if ( _node -> getType() == ASTNode::Assign )
  {
    std::string variable = _node -> getLeftNode() -> getToken();

    if ( findEnv( _env, variable ) != -1 )
      return "................";

    instruction = compile( _node -> getMiddleNode(), _env, _registerIndex, _errorList );

    _env.push_back( std::pair<std::string, int>( variable, _registerIndex ) );

    instruction += compile( _node -> getRightNode(), _env, _registerIndex + 1,
                            _errorList );
  }

  return instruction;
  
}
