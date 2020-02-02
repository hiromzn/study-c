#include <stdio.h>

#define MAP_FOO_IN(a) foo ## a ## _in,foo ## a ## _in(),#a,a
#define MAP_FOO_OUT(a) foo ## a ## _out,foo ## a ## _out(),#a,a

int foo100_in() { return 100; }
int foo100_out() { return 150; }
int foo200_in() { return 200; }
int foo200_out() { return 250; }

int main()
{
	printf( "in  :funcp:%p  ret:%d  expect:%s:%d\n", MAP_FOO_IN(100) );
	printf( "out :funcp:%p  ret:%d  expect:%s:%d\n", MAP_FOO_OUT(100) );
	printf( "in  :funcp:%p  ret:%d  expect:%s:%d\n", MAP_FOO_IN(200) );
	printf( "out :funcp:%p  ret:%d  expect:%s:%d\n", MAP_FOO_OUT(200) );
}
