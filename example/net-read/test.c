#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

typedef struct mystr {
  unsigned int a;
  unsigned int b;
  unsigned int c;
  unsigned int d;
  char data[4];
} MYDATA;

void pr_mydata( MYDATA *p )
{
  printf( "a:%08X(x):%d(d)\n", p->a, p->a );
  printf( "b:%08X(x):%d(d)\n", p->b, p->b );
  printf( "c:%08X(x):%d(d)\n", p->c, p->c );
  printf( "d:%08X(x):%d(d)\n", p->d, p->d );
}

void dump( unsigned char *p, int size )
{
  unsigned int outn = 0;
  while ( outn < size ) {
	if ( ( outn & 0xfffffff0 ) == outn ) {
	  printf( "\n%08X:%04X:", p, outn );
	}
	printf( " %02X", *p );
	if ( ( outn & 7 ) == 7 ) {
	  printf( " :" );
	}
	outn ++;
	p ++;
  }
  printf( "\n", *(unsigned int*)p );
}
 
int main() {
 
  MYDATA hdata;
  MYDATA ndata;

  MYDATA cpdata;
  MYDATA okdata;

  int size = sizeof( MYDATA );

  hdata.a = 100;
  hdata.b = 296;
  hdata.c = 85000;
  hdata.d = 1;
  
  dump( &hdata, size );

  ndata.a = htonl( 100 );
  ndata.b = htonl( 296 );
  ndata.c = htonl( 85000 );
  ndata.d = htonl( 1 );

  dump( &ndata, size );
  pr_mydata( &ndata );

  memcpy( &cpdata, &ndata, size );
  dump( &cpdata, size );
  pr_mydata( &cpdata );

  okdata.a = ntohl( ndata.a );
  okdata.b = ntohl( ndata.b );
  okdata.c = ntohl( ndata.c );
  okdata.d = ntohl( ndata.d );
  pr_mydata( &okdata );

}
