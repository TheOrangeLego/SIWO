#ifndef _LEXER
#define _LEXER

/* white space */
const char TOKEN_SPACE   = ' ';
const char TOKEN_NEWLINE = '\n';

/* keywords */
const char* const KEYWORD_LET = "let";

/* operators */
const char TOKEN_ADD = '+';
const char TOKEN_SUB = '-';
const char TOKEN_MUL = '*';
const char TOKEN_DIV = '/';
const char TOKEN_LPA = '(';
const char TOKEN_RPA = ')';

/* error messages */
const char* const ERR_BAD_TOKEN = "\n  ERR - invalid token %s\n";

/*
 * Function     - validInteger
 *
 * Parameters   -
 *  - const char* const - input string to be checked
 *
 * Return Value - true if the input string is a valid integer, false otherwise
 *
 * Description  - checks if the provided string is a valid integer
 */
bool validInteger( const char* const _string );

/*
 * Function     - validIdentifier
 *
 * Parameters   -
 *  - const char* const - input string to be checked
 *
 * Return Value - true if the input string is a valid identifier, false otherwise
 *
 * Description  - checks if the provided string is a valid identifier
 */
bool validIdentifier( const char* const _string );

/*
 * Function     - validOperator
 *
 * Parameters   -
 *  - const char* const - input string to be checked
 *
 * Return Value - true if the input string is a valid operator, false otherwise
 *
 * Description  - checks if the provided string is a valid operator
 */
bool validOperator( const char* const _string );

#endif
