#ifndef _ANALYZER
#define _ANALYZER

#include <string>
#include <list>

/* types of expressions available */
enum ExpressionType { Constant, Identifier, Operator };

/* Class - Expression */
class Expression
{
  /* string representation of token expression */
  std::string token;
  /* type of expression */
  ExpressionType type;
  /* left expression for binary operators */
  Expression* left;
  /* right expression for binary operators */
  Expression* right;

  public:
    /*
     * Constructor  - Expression
     *
     * Parameters   -
     *  - std::string    - string representation of token
     *  - ExpressionType - type of token expression
     *
     * Return Value - none
     *
     * Description  - creates a token expression given its string representation and type
     *                and contains no left nor right child expression
     */
    Expression( std::string _token, ExpressionType _type );
    /*
     * Constructor  - Expression
     *
     * Parameters   -
     *  - std::string    - string representation of token
     *  - ExpressionType - type of token expression
     *  - Expression*    - left child expression
     *  - Expression*    - right child expression
     *
     * Return Value - none
     *
     * Description  - creates a token expression with both left and right child, used for
     *                binary operators
     */
    Expression( std::string _token, ExpressionType _type, Expression* _left,
                Expression* _right );
    /*
     * Destructor   - Expression
     *
     * Parameters   - none
     *
     * Return Value - none
     *
     * Description  - destructor for Expression type objects
     */
    ~Expression();
    /*
     * Function     - setLeftExpression
     *
     * Parameters   -
     *  - Expression* - expression that will be assigned as the left child expression
     *
     * Return Value - none
     *
     * Description  - sets the left child of the current expression to the provided
     *                expression
     */
    void setLeftExpression( Expression* _expr );
    /*
     * Function     - setRightExpression
     *
     * Parameters   -
     *  - Expression* - expression that will be assigned as the right child expression
     *
     * Return Value - none
     *
     * Description  - sets the right child of the current expression to the provided
     *                expression
     */
    void setRightExpression( Expression* _expr );
    /*
     * Function     - getToken
     *
     * Parameters   - none
     *
     * Return Value - string representation of the token
     *
     * Description  - returns the string representation of the token
     */
    const std::string getToken();
    /*
     * Function     - getType
     *
     * Parameters   - none
     *
     * Return Value - type of token
     *
     * Description  - returns the type of token
     */
    const ExpressionType getType();
    /*
     * Function     - getLeftExpression
     *
     * Parameters   - none
     *
     * Return Value - pointer to the left child
     *
     * Description  - return pointer to the left child of expression
     */
    const Expression* getLeftExpression();
    /*
     * Function     - getRightExpression
     *
     * Parameters   - none
     *
     * Return Value - pointer to the right child
     *
     * Description  - return pointer to the right child of expression
     */
    const Expression* getRightExpression();
};
/*
int precedence( const std::string _token );

bool lowerPrecedence( const std::string _tokenA, const std::string _tokenB );

Expression* generateAS( std::list<std::string> _tokens );*/

#endif
