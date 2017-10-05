#include <iostream>
#include <string.h>
#include <stack>
#include "lexer.h"
#include "parser.h"
#include "analyzer.h"

/* Constructor - Expression */
Expression::Expression( std::string _token, Expression::ExpressionType _type )
{
  /* set token string and type according to parameters */
  token = _token;
  type = _type;
  /* expression has not left and right child, i.e. constant or identifier */
  left = middle = right = NULL;
}

/* Constructor - Expression */
Expression::Expression( std::string _token, Expression::ExpressionType _type, 
                        Expression* _left, Expression* _right )
{
  /* set token string, type, left, and right child expression */
  token = _token;
  type = _type;
  left = _left;
  middle = NULL;
  right = _right;
}

Expression::Expression( std::string _token, Expression::ExpressionType _type,
                        Expression* _left, Expression* _middle, Expression* _right )
{
  token = _token;
  type = _type;
  left = _left;
  middle = _middle;
  right = _right;
}

/* Destructor - Expression */
Expression::~Expression()
{
  /* if left child exists, delete it */
  if ( left != NULL )
    delete left;
  
  /* if right child exists, delete it */
  if ( right != NULL )
    delete right;
}

/* Function - getToken */
std::string Expression::getToken() const
{
  /* return token string representation */
  return token;
}

/* Function - getType */
Expression::ExpressionType Expression::getType() const
{
  /* return type of token */
  return type;
}

/* Function - getLeftExpression */
Expression* Expression::getLeftExpression() const
{
  /* return pointer to the left child */
  return left;
}

/* Function - getRightExpression */
Expression* Expression::getRightExpression() const
{
  /* return pointer to the right child */
  return right;
}

/* Function - precedence */
int precedence( const std::string _token )
{
  /* precedence 0 - '(' : ')' */
  if ( !strcmp( _token.c_str(), TOKEN_LPA ) || !strcmp( _token.c_str(), TOKEN_RPA ) )
    return 0;
  /* precedence 1 - '*' : '/' */
  else if ( !strcmp( _token.c_str(), TOKEN_MUL ) || !strcmp( _token.c_str(), TOKEN_DIV ) )
    return 1;
  /* precedence 2 - '+' : '-' */
  else if ( !strcmp( _token.c_str(), TOKEN_ADD ) || !strcmp( _token.c_str(), TOKEN_SUB ) )
    return 2;
  else if ( !strcmp( _token.c_str(), TOKEN_EQL ) )
    return 3;
  /* not recognized tokens return -1 */
  else
    return -1;
}

/* Function - lowerPrecedence */
bool lowerPrecedence( const std::string _tokenA, const std::string _tokenB )
{
  /* if precendence of first token is less or equal to second token return true */
  if ( precedence( _tokenA ) <= precedence( _tokenB ) )
    return true;
  /* otherwise return false */
  else
    return false;
}

/* Function - orderTokens */
std::list<std::string> orderTokens( std::list<std::string> _tokens )
{
  /* contain all tokens in order */
  std::list<std::string> orderedTokens;
  /* stack of operators used for shutting-yard algorithm */
  std::stack<std::string> operators;

  /* parse through all tokens */
  while ( !_tokens.empty() )
  {
    /* obtain the first token from the provided list of tokens */
    std::string currentToken = _tokens.front();
    /* remove token from list */
    _tokens.pop_front();

    /* if left parantheses, push it into operator stack */
    if ( !strcmp( currentToken.c_str(), TOKEN_LPA ) )
      operators.push( currentToken );
    /* if right parantheses */
    else if ( !strcmp( currentToken.c_str(), TOKEN_RPA ) )
    {
      /* if there are no operators in stack, mismatch of parantheses */
      if ( operators.empty() )
        return std::list<std::string>();
      
      /* obtain top operator in stack */
      std::string topOperator = operators.top();
      /* remove operator from stack */
      operators.pop();

      /* continue to parse through operator stack until finding left parantheses */
      while ( strcmp( topOperator.c_str(), TOKEN_LPA ) )
      {
        /* push the top operator into the ordered tokens */
        orderedTokens.push_back( topOperator );

	/* if there are no more operators, mismatch of parantheses */
	if ( operators.empty() )
	  return std::list<std::string>();
	
	/* obtain the top operator on operator stack */
	topOperator = operators.top();
	/* remove top operator on operator stack */
	operators.pop();
      }
    }
    /* if it is another operator */
    else if ( validOperator( currentToken.c_str() ) )
    {
      /* if there are no other operators insert the current token to the stack */
      if ( operators.empty() )
        operators.push( currentToken );
      else
      {
        /* get the top operator */
        std::string topOperator = operators.top();

	/* continue to parse through operators while the operator stack is not empty, */
	/* the precendence of stack operator is lower than current token operator,    */
	/* and is not operator of precedence 0 */
	while ( !operators.empty() && lowerPrecedence( topOperator, currentToken ) &&
	        precedence( topOperator ) )
	{
	  /* remove top operator from stack */
	  operators.pop();
	  /* add top operator to ordered token list */
	  orderedTokens.push_back( topOperator );

	  /* if the operator list is not empty, obtain new top operator */
	  if ( !operators.empty() )
	    topOperator = operators.top();
	}

	/* once done push current token operator into stack */
	operators.push( currentToken );
      }
    }
    /* for all other tokens push them directly into ordered token list */
    else
      orderedTokens.push_back( currentToken );
  }

  /* push any remaining operators in operator stack */
  while ( !operators.empty() )
  {
   orderedTokens.push_back( operators.top() );
   operators.pop();
  }

  return orderedTokens;
}

Expression* generateExpression( std::list<std::string>& _tokens )
{
  if ( _tokens.empty() )
    return NULL;

  Expression* currentNode = NULL;
  std::string backToken = _tokens.back();
  _tokens.pop_back();

  if ( validInteger( backToken.c_str() ) )
    currentNode = new Expression( backToken, Expression::Constant );

  if ( validIdentifier( backToken.c_str() ) )
    currentNode = new Expression( backToken, Expression::Identifier );

  if ( validOperator( backToken.c_str() ) )
  {
    Expression* leftExpr = NULL;
    Expression* rightExpr = NULL;

    if ( !strcmp( backToken.c_str(), TOKEN_SUB ) ||
         !strcmp( backToken.c_str(), TOKEN_DIV ) ||
	 !strcmp( backToken.c_str(), TOKEN_EQL ) )
    {
      rightExpr = generateAS( _tokens );
      leftExpr = generateAS( _tokens );
    }
    else
    {
      leftExpr = generateAS( _tokens );
      rightExpr = generateAS( _tokens );
    }

    currentNode = new Expression( backToken, Expression::Operator, leftExpr, rightExpr );
  }

  return currentNode;
}

Expression* generateStatement( std::list<std::string>& _tokens )
{
  Expression* root = NULL;

  while ( !_tokens.empty() )
  {
    std::string frontToken = _tokens.front();
    _tokens.pop_front();

    if ( !strcmp( frontToken.c_str(), KEYWORD_LET ) )
    {
      std::list<std::string> boundTokens;

      frontToken = _tokens.front();
      _tokens.pop_front();

      while ( strcmp( frontToken.c_str(), KEYWORD_COLON ) )
      {
        boundTokens.push_back( frontToken );
	frontToken = _tokens.front();
	_tokens.pop_front();
      }

      if ( boundTokens.empty() )
      { /* error msg */ }

      boundTokens = orderTokens( boundTokens );

      Expression* boundExpression = generateExpression( boundTokens );
      Expression* bodyExpression  = generateStatement( _tokens );

      root = new Expression( KEYWORD_LET, Expression::Assign, boundExpression,
                             bodyExpression );
    }
    else
    {}
  }

  return root;
}
