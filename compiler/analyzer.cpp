#include "analyzer.h"
#include "lexer.h"
#include "parser.h"
#include <iostream>

Expression::Expression( std::string _token, ExpressionType _type )
{
  token = _token;
  type = _type;
  left = right = NULL;
}

Expression::Expression( std::string _token, ExpressionType _type, Expression* _left, Expression* _right )
{
  token = _token;
  type = _type;
  left = _left;
  right = _right;
}

Expression::~Expression()
{
  if ( left != NULL )
    delete left;

  if ( right != NULL )
    delete right;
}

void Expression::setLeftExpression( Expression* _expr )
{
  left = _expr;
}

void Expression::setRightExpression( Expression* _expr )
{
  right = _expr;
}

std::string Expression::getToken()
{
  return token;
}

ExpressionType Expression::getType()
{
  return type;
}
Expression& Expression::getLeftExpression()
{
  return *left;
}

Expression& Expression::getRightExpression()
{
  return *right;
}

int precedence( const std::string _token )
{
  if ( !_token.compare( std::string( 1, TOKEN_LPA ) ) || !_token.compare( std::string( 1, TOKEN_RPA ) ) )
    return 0;
  else if ( !_token.compare( std::string( 1, TOKEN_DIV ) ) || !_token.compare( std::string( 1, TOKEN_MUL ) ) )
    return 1;
  else if ( !_token.compare( std::string( 1, TOKEN_ADD ) ) || !_token.compare( std::string( 1, TOKEN_SUB ) ) )
    return 2;
  else
    return -1;
}

bool lowerPrecedence( const std::string _tokenA, const std::string _tokenB )
{
  if ( precedence( _tokenA ) <= precedence( _tokenB ) )
    return true;
  else
    return false;
}

Expression* generateAS( std::list<std::string> _tokens )
{
  std::list<std::string> orderedTokens;
  std::stack<std::string> operators;

  while ( !_tokens.empty() )
  {
    std::string currentToken = _tokens.front();
    _tokens.pop_front();

    if ( !currentToken.compare( std::string( 1, TOKEN_LPA ) ) )
      operators.push( currentToken );
    else if ( !currentToken.compare( std::string( 1, TOKEN_RPA ) ) )
    {
      if ( operators.empty() )
        return NULL;
      
      std::string topOperator = operators.top();
      operators.pop();

      while ( topOperator.compare( std::string( 1, TOKEN_LPA ) ) )
      {
        orderedTokens.push_back( topOperator );

	if ( operators.empty() )
	  return NULL;

	topOperator = operators.top();
	operators.pop();
      }
    }
    else if ( validOperator( currentToken.c_str() ) )
    {
      if ( operators.empty() )
        operators.push( currentToken );
      else
      {
        std::string topOperator = operators.top();

	while ( !operators.empty() && lowerPrecedence( topOperator, currentToken ) && precedence( topOperator ) )
	{
	  operators.pop();
	  orderedTokens.push_back( topOperator );

	  if ( !operators.empty() )
	    topOperator = operators.top();
	}

	operators.push( currentToken );
      }
    }
    else
      orderedTokens.push_back( currentToken );
  }

  while ( !operators.empty() )
  {
   orderedTokens.push_back( operators.top() );
   operators.pop();
  }

  std::cout << "Ordered tokens:";

  for ( std::list<std::string>::const_iterator it = orderedTokens.begin(); it != orderedTokens.end(); it++ )
    std::cout << " " << *it;

  std::cout << std::endl;

  return NULL;
}
