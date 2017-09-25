#include <ctype.h>
#include <string.h>
#include "lexer.h"

/* Function - validInteger */
bool validInteger( const char* const _string )
{
  /* start at beginning of string */
  int index = 0;

  /* parse through all characters */
  while ( _string[index] != CHAR_NUL )
  {
    /* if the first character is not a negative sign and not digit then not an integer */
    if ( !index && _string[index] != CHAR_HYPHEN && !isdigit( _string[index] ) )
      return false;
    
    /* if it is not the first character and is not a digit then not an integer */
    if ( index && !isdigit( _string[index] ) )
      return false;

    /* check next character */
    index++;
  }
  
  /* default is an integer */
  return true;
}

/* Function - validIdentifier */
bool validIdentifier( const char* const _string )
{
  /* start at beginning of string */
  int index = 0;

  /* parse through all characters */
  while ( _string[index] != CHAR_NUL )
  {
    /* if first character is not underscore and alphabetical character */
    /* then not identifier */
    if ( !index && _string[index] != CHAR_US && !isalpha( _string[index] ) )
      return false;

    /* if not first character and neither alphabetical character or digit */
    /* then not identifier */
    if ( index && !isalpha( _string[index] ) && !isdigit( _string[index] ) )
      return false;

    /* check next character */
    index++;
  }

  /* default is identifier */
  return true;
}

/* Function - validOperator */
bool validOperator( const char* const _string )
{
  /* check non-empty operator */
  if ( _string[0] == CHAR_NUL )
    return false;

  /* check if it is any defined operator */
  if ( strcmp( _string, TOKEN_ADD ) && strcmp( _string, TOKEN_SUB ) &&
       strcmp( _string, TOKEN_MUL ) && strcmp( _string, TOKEN_DIV ) &&
       strcmp( _string, TOKEN_LPA ) && strcmp( _string, TOKEN_RPA ) &&
       strcmp( _string, TOKEN_EQL ) )
    return false;
  
  /* default is operator */
  return true;
}
