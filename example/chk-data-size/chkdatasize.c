#include <stdio.h>
#include <stdlib.h>

#define PRINT_DATA_SIZE(t) {printf( "%10s:%d\n", #t, sizeof(t) );}

void main( int argc, char **argv )
{
	PRINT_DATA_SIZE( short );
	PRINT_DATA_SIZE( int );
	PRINT_DATA_SIZE( long );
	PRINT_DATA_SIZE( void* );
	PRINT_DATA_SIZE( float );
	PRINT_DATA_SIZE( double );
}
