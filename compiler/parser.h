#ifndef _PARSER
#define _PARSER

#include <fstream>
#include <sstream>
#include <string>
#include <list>

/* stream buffer that holds file content */
static std::stringstream buffer;

/*
 * Function     - streamEmpty
 *
 * Parameters   - none
 *
 * Return Value - true if the stream is currently empty, false otherwise
 *
 * Description  - checks if the stream is currently empty
 */
bool streamEmpty();

/*
 * Function     - getTokens
 *
 * Parameters   - none
 *
 * Return Value - list of string tokens from the buffer. Return list will be empty if the
 *                buffer is empty too
 *
 * Description  - returns list of string tokens from the buffer
 */
std::list<std::string> getTokens();

/*
 * Function     - appendStream
 *
 * Parameters   -
 *  - std::ifstream& - reference to input stream whose content will be appended to buffer
 *
 * Return Value - none
 *
 * Description  - reads content of the file and appends them into the buffer. The file
 *                must be open before this function is called, else will result in error
 */
void appendStream( const std::ifstream& _inputFile );

/*
 * Function     - clearStream
 *
 * Parameters   - none
 *
 * Return Value - none
 *
 * Description  - clears the content of the buffer
 */
void clearStream();

/*
 * Function     - validTokens
 *
 * Parameters   -
 *  - std::list<std::string> - list of tokens to be checked
 *
 * Return Value - true if the list of tokens are valid, false otherwise
 *
 * Description  - checks if all tokens are valid, displays error message if a token
 *                is found to be invalid
 */
bool validTokens( const std::list<std::string> _list );

#endif
