#include <stdio.h>

void main()
{
	union {
		unsigned int data;
		struct {
			unsigned int a:16;
			unsigned int b:16;
			unsigned int c:16;
			unsigned int d:8;
			unsigned int e:8;
		} sd;
	} ud;

	ud.sd.a=1;
	ud.sd.b=2;
	ud.sd.c=3;
	ud.sd.d=4;
	ud.sd.e=5;

	printf( "size: data:%d\n", sizeof( ud.data ) );
	printf( "size: sd:%d\n", sizeof( ud.sd ) );
	printf( "%016X\n", ud.sd );
	printf( "%016X\n", ud.data );
}
