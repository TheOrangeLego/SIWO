#include <string.h>
#include <stack>
#include "lexer.h"
#include "analyzer.h"

ASTNode::ASTNode( std::string _token, ASTNodeType _type )
{
  token = _token;
  type = _type;
}

ASTNode::ASTNode( std::string _token, ASTNode::ASTNodeType _type, ASTNode* _left,
                  ASTNode* _right )
{
  token = _token;
  type = _type;
  left = left;
  right = right;
}

ASTNode::ASTNode( std::string _token, ASTNode::ASTNodeType _type, ASTNode* _left,
                  ASTNode* _middle, ASTNode* _right )
{
  token = _token;
  type = _type;
  left = _left;
  middle = _middle;
  right = _right;
}

ASTNode::~ASTNode()
{
  if ( left != NULL )
    delete left;

  if ( middle != NULL )
    delete middle;

  if ( right != NULL )
    delete right;
}

std::string ASTNode::getToken() const
{
  return token;
}

ASTNode::ASTNodeType ASTNode::getType() const
{
  return type;
}

ASTNode* ASTNode::getLeftNode() const
{
  return left;
}

ASTNode* ASTNode::getMiddleNode() const
{
  return middle;
}

ASTNode* ASTNode::getRightNode() const
{
  return right;
}

int precedence( std::string _token ) 
{
  if ( !strcmp( _token.c_str(), TOKEN_LPA ) || !strcmp( _token.c_str(), TOKEN_RPA ) )
    return 0;
  
  if ( !strcmp( _token.c_str(), TOKEN_MUL ) || !strcmp( _token.c_str(), TOKEN_DIV ) )
    return 1;
  
  if ( !strcmp( _token.c_str(), TOKEN_ADD ) || !strcmp( _token.c_str(), TOKEN_SUB ) )
    return 2;
}

bool greaterPrecedence( std::string _tokenA, std::string _tokenB ) 
{
  if ( precedence( _tokenA ) > precedence( _tokenB ) )
    return true;

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
	while ( !operators.empty() && !greaterPrecedence( topOperator, currentToken ) &&
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

ASTNode* generateExpression( std::list<std::string>& _tokens )
{
  if ( _tokens.empty() )
    return NULL;

  std::string backToken = _tokens.back();
  _tokens.pop_back();

  ASTNode* currentNode = NULL;

  if ( validInteger( backToken.c_str() ) )
    currentNode = new ASTNode( backToken, ASTNode::Constant );

  if ( validIdentifier( backToken.c_str() ) )
    currentNode = new ASTNode( backToken, ASTNode::Identifier );

  if ( validOperator( backToken.c_str() ) )
  {
    ASTNode* rightExpr = generateExpression( _tokens );
    ASTNode* leftExpr  = generateExpression( _tokens );

    /*
    if ( !strcmp( backToken.c_str(), TOKEN_SUB ) ||
         !strcmp( backToken.c_str(), TOKEN_DIV ) )
    {
      rightExpr = generateAS( _tokens );
      leftExpr = generateAS( _tokens );
    }
    else
    {
      leftExpr = generateAS( _tokens );
      rightExpr = generateAS( _tokens );
    }
    */

    currentNode = new ASTNode( backToken, ASTNode::Operator, leftExpr, rightExpr );
  }

  return currentNode;
}

ASTNode* generateStatement( std::list<std::string>& _tokens )
{
  ASTNode* currentNode = NULL;

  while ( !_tokens.empty() )
  {
    std::string frontToken = _tokens.front();
    _tokens.pop_front();

    if ( !strcmp( frontToken.c_str(), KEYWORD_LET ) )
    {
      std::string variable = _tokens.front();
      _tokens.pop_front();

      std::list<std::string> varExpression;
      std::list<std::string> boundExpression;

      varExpression.push_back( variable );

      frontToken = _tokens.front();
      _tokens.pop_front();

      while ( strcmp( frontToken.c_str(), KEYWORD_COLON ) )
      {
        boundExpression.push_back( frontToken );
	frontToken = _tokens.front();
	_tokens.pop_front();
      }

      boundExpression = orderTokens( boundExpression );

      ASTNode* letVar   = generateExpression( varExpression );
      ASTNode* letBound = generateExpression( boundExpression );
      ASTNode* letBody  = generateStatement( _tokens );
      
      currentNode = new ASTNode( KEYWORD_LET, ASTNode::Assign, letVar, letBound,
                                 letBody );
    }
  }

  return currentNode;
}
