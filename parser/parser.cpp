#include <iostream>
#include <fstream>

const char* MSG_HELP = "\n  help message\n";

const char* MSG_GET_HELP = "\n  for help run the program with the parameter \'-h\', such as--\n\t ./parse -h\n";

const char* ERR_MISSING_SOURCE       = "\n  missing source file for parsing\n";
const char* ERR_CANNOT_OPEN_SOURCE   = "\n  error when opening source file\n";
const char* ERR_CANNOT_CREATE_BINARY = "\n  error when creating binary file\n";

int main ( int argc, char* argv[] )
{
  if ( argc == 1 )
  {
    ( void ) printf( "%s%s\n", ERR_MISSING_SOURCE_FILE, MSG_GET_HELP );
    return 1;
  }

  std::ifstream sourceFile( "source.a" );
  std::ofstream binaryFile( "source.b" );

  if ( !sourceFile.is_open() )
  {
    ( void ) printf( "%s\n", ERR_CANNOT_OPEN_SOURCE );
    return 2;
  }
  
  if ( !binaryFile.is_open() )
  {
    ( void ) printf( "%s\n", ERR_CANNOT_CREATE_BINARY );
    return 2;
  }

  sourceFile.close();
  binaryfile.close();

  return 0;
}
