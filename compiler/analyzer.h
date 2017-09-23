#ifndef _ANALYZER
#define _ANALYZER

#include <string>
#include <list>
#include <stack>

enum ExpressionType { Identifier, Operator };

class Expression
{
  std::string token;
  ExpressionType type;

  Expression* left;
  Expression* right;

  public:
    Expression( std::string _token, ExpressionType _type );
    Expression( std::string _token, ExpressionType _type, Expression* _left, Expression* _right );
    ~Expression();

    void setLeftExpression( Expression* _expr );
    void setRightExpression( Expression* _expr );

    std::string getToken();
    ExpressionType getType();
    Expression& getLeftExpression();
    Expression& getRightExpression();
};

int precedence( const std::string _token );

bool lowerPrecedence( const std::string _tokenA, const std::string _tokenB );

Expression* generateAS( std::list<std::string> _tokens );

#endif
