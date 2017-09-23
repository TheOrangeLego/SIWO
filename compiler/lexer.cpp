#include <ctype.h>
#include "lexer.h"

/* Function - validInteger */
bool validInteger( const char* const _string )
{
  /* start at beginning of string */
  int index = 0;

  /* parse througn all characters */
  while ( _string[index] != '\0' )
  {
    /* if the first character is not a negative sign and not a digit then not an integer */
    if ( !index && _string[index] != '-' && !isdigit( _string[index] ) )
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
  int index = 0;

  while ( _string[index] != '\0' )
  {
    if ( !index && _string[index] != '_' && !isalpha( _string[index] ) )
      return false;

    if ( index && !isalpha( _string[index] ) && !isdigit( _string[index] ) )
      return false;

    index++;
  }

  return true;
}

/* Function - validOperator */
bool validOperator( const char* const _string )
{
  if ( _string[0] == '\0' )
    return false;

  if ( _string[1] != '\0' )
    return false;

  if ( _string[0] != TOKEN_ADD && _string[0] != TOKEN_SUB && _string[0] != TOKEN_MUL &&
       _string[0] != TOKEN_DIV && _string[0] != TOKEN_LPA && _string[0] != TOKEN_RPA )
    return false;

  return true;
}
