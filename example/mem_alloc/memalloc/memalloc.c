#include <stdio.h>
#include <stdlib.h>

#define BLOCKS_DEF 10
#define DELTA 100

void access_mem( char *buf, unsigned long size )
{
	char data=0;
	char *top = buf;
	unsigned long i = 0;
	for ( i=0; i<size; i += DELTA ) {
		*buf = data++;
		buf += DELTA;
	}
}

int main(int argc, char **argv)
{
	unsigned long blocks = 10;
	unsigned long size;
	char *buf;
	int c;
	int time_out = 10;

	if ( argc > 1 ) {
		blocks = atoi( argv[1] );
	}
	if ( blocks <= 0  ) {
		blocks = BLOCKS_DEF;
	}
	size = blocks * 100 * 1024 * 1024; /* blocks x 100MB */
	printf( "now allocating memory %.3f Gbyte\n", (float)blocks / 10 );
	buf = malloc( size );
	if (!buf) {
		perror( "ERROR: can NOT malloc memory" );
		exit(1);
	}
	printf( "allocated memory %.3f Gbyte : address:%p\n", (float)blocks / 10, buf );
	fflush( stdout );
	while (1) {
		printf( "accessing memory %.3f Gbyte\n", (float)blocks / 10 );
		fflush( stdout );
		access_mem( buf, size );
		fflush( stdout );
		sleep( 1 );
	}
}
