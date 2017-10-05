#ifndef _ANALYZER
#define _ANALYZER

#include <string>
#include <list>

class ASTNode
{
  public:
    enum ASTNodeType { Constant, Identifier, Operator, Assign };

    ASTNode( std::string _token, ASTNodeType _type );

    ASTNode( std::string _token, ASTNodeType _type, ASTNode* _left, ASTNode* _right );

    ASTNode( std::string _token, ASTNodeType _type, ASTNode* _left, ASTNode* _middle,
             ASTNode* _right );

    ~ASTNode();

    std::string getToken() const;

    ASTNodeType getType() const;

    ASTNode* getLeftNode() const;

    ASTNode* getMiddleNode() const;

    ASTNode* getRightNode() const;

  private:
    std::string token;
    ASTNodeType type;
    ASTNode* left;
    ASTNode* middle;
    ASTNode* right;
};

int precedence( std::string _token );

bool greaterPrecedence( std::string _tokenA, std::string _tokenB );

std::list<std::string> orderTokens( std::list<std::string> _tokens );

ASTNode* generateExpression( std::list<std::string>& _tokens );

ASTNode* generateStatement( std::list<std::string>& _tokens );

#endif
