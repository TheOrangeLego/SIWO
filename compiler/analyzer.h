#ifndef _ANALYZER
#define _ANALYZER

#include <string>
#include <list>

/* Class - Expression */
class Expression
{
  public:
    /* types of expressions available */
    enum ExpressionType { Constant, Identifier, Operator, Assign };

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
    
    Expression( std::string _token, ExpressionType _type, Expression* _left,
                Expression* _middle, Expression* _right );

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
     * Function     - getToken
     *
     * Parameters   - none
     *
     * Return Value - string representation of the token
     *
     * Description  - returns the string representation of the token
     */
    std::string getToken() const;

    /*
     * Function     - getType
     *
     * Parameters   - none
     *
     * Return Value - type of token
     *
     * Description  - returns the type of token
     */
    ExpressionType getType() const;

    /*
     * Function     - getLeftExpression
     *
     * Parameters   - none
     *
     * Return Value - pointer to the left child
     *
     * Description  - return pointer to the left child of expression
     */
    Expression* getLeftExpression() const;

    /*
     * Function     - getRightExpression
     *
     * Parameters   - none
     *
     * Return Value - pointer to the right child
     *
     * Description  - return pointer to the right child of expression
     */
    Expression* getRightExpression() const;

  private:
    /* string representation of token expression */
    std::string token;
    /* type of expression */
    ExpressionType type;
    /* left expression for binary operators */
    Expression* left;
    Expression* middle;
    /* right expression for binary operators */
    Expression* right;
};

/*
 * Function     - precedence
 *
 * Parameters   -
 *  - std::string - token of operator whose precedence will be checked
 *
 * Return Value - precedence value of operator token
 *
 * Description  - returns the precedence value of the provided operator token, -1 is
 *                returned if not a valid operator
 */
int precedence( const std::string _token );

/*
 * Function     - lowerPrecedence
 *
 * Parameters   -
 *  - std::string - token whose precedence will be checked to be lower
 *  - std::string - token whose precedence will be compare to the first token
 *
 * Return Value - true if the first precedence is lower or equal to the second token,
 *                false otherwise
 *
 * Description  - determines if the precedence of the first token is lower or equal to
 *                the precedence of the second token
 */
bool lowerPrecedence( const std::string _tokenA, const std::string _tokenB );

/*
 * Function     - orderTokens
 *
 * Parameters   -
 *  - std::list<std::string> - list of tokens
 *
 * Return Value - list of ordered tokens
 *
 * Description  - returns the list of provided tokens in order according to
 *                shutting-yard algorithm
 */
std::list<std::string> orderTokens( std::list<std::string> _tokens );

Expression* generateExpression( std::list<std::string>& _tokens );

Expression* generateStatement( std::list<std::string>& _tokens );

#endif
