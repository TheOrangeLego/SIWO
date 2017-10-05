#ifndef _COMPILER
#define _COMPILER

#include <string>
#include <list>
#include <utility>
#include "analyzer.h"

int findEnv( std::list<std::pair<std::string, int> > _env, std::string _var );

std::string insnConstant( std::string _value, int _registerIndex );

std::string insnIdentifier( int _register, int _registerIndex );

std::string insnOperator( int _registerIndex, std::string _operator );

std::string compile( ASTNode* _node, std::list<std::pair<std::string, int> > _env,
                     int _registerIndex, std::list<int> _errorList );

#endif
