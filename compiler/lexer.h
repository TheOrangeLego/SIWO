#ifndef _LEXER
#define _LEXER

/* white space */
const char CHAR_SPACE   = ' ';
const char CHAR_TAB     = '\t';
const char CHAR_NEWLINE = '\n';

/* special tokens */
const char CHAR_HYPHEN  = '-';
const char CHAR_US      = '_';
const char CHAR_NUL     = '\0';

/* keywords */
const char* const KEYWORD_LET   = "let";
const char* const KEYWORD_COLON = ":";

/* operators */
const char* const TOKEN_EQL = "=";
const char* const TOKEN_ADD = "+";
const char* const TOKEN_SUB = "-";
const char* const TOKEN_MUL = "*";
const char* const TOKEN_DIV = "/";
const char* const TOKEN_LPA = "(";
const char* const TOKEN_RPA = ")";

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
