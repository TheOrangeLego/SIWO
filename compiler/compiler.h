#ifndef _COMPILER
#define _COMPILER

#include <string>
#include <list>
#include "analyzer.h"

int findEnv( std::list<std::string> _env, std::string _var );

std::string insnConstant( std::string _value, int _registerIndex );

std::string insnIdentifier( int _register, int _registerIndex );

std::string compile( ASTNode* _node, std::list<std::string> _env, int _registerIndex,
                     std::list<int> _errorList );

#endif
