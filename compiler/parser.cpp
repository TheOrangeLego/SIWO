#include "parser.h"
#include "lexer.h"

/* Function - streamEmpty */
bool streamEmpty()
{
  /* check if there are any contents in the buffer */
  return !buffer.rdbuf()->in_avail();
}

/* Function - appendStream */
void appendStream( const std::ifstream& _inputFile )
{
  /* append the content of the input file into the buffer */
  buffer << _inputFile.rdbuf();
}

/* Function - getNextTokens */
std::list<std::string> getNextTokens()
{
  /* contents of the current line of buffer */
  std::string currentLine;
  /* list of string representation of each token */
  std::list<std::string> tokenList;

  /* if the stream is empty, return an empty list */
  if ( streamEmpty() )
    return std::list<std::string>();

  /* get the top line of the buffer */
  std::getline( buffer, currentLine );
  
  /* read all contents of the current line */
  while ( currentLine.length() )
  {
    /* skip any whitespace at the front of the line */
    if ( currentLine[0] == ' ' || currentLine[0] == '\t' )
      currentLine = currentLine.substr( 1 );
    else
    {
      /* find the first space */
      std::size_t spaceChar = currentLine.find_first_of( " " );
      /* extract the first word of the current line */
      std::string currentString = currentLine.substr( 0, spaceChar );
    
      /* add first word into token list */
      tokenList.push_back( currentString );

      /* if there are no more words, line will be empty */
      if ( spaceChar == std::string::npos )
        currentLine = "";
      /* else remove the first word and space from the current line for next parsing */
      else
        currentLine = currentLine.substr( spaceChar + 1 );
    }
  }
  
  /* if the line is empty extract from next line in buffer */
  if ( tokenList.empty() )
    return getNextTokens();
  
  /* return token list */
  return tokenList;
}

/* Function - clearStream */
void clearStream()
{
  /* flush the content of buffer */
  buffer.flush();
}

/* Function - validTokens */
bool validTokens( const std::list<std::string> _list )
{
  /* iterate through the provided token list */
  for ( std::list<std::string>::const_iterator listIt = _list.begin();
        listIt != _list.end(); listIt++ )
  {
    /* if the token is not recognized by the lexer print error message */
    if ( !validInteger( ( *listIt ).c_str() ) &&
         !validIdentifier( ( *listIt ).c_str() ) &&
	 !validOperator( ( *listIt ).c_str() ) )
      ( void ) printf( ERR_BAD_TOKEN, ( *listIt ).c_str() );
  }
}
