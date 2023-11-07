#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void func_b(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf( "func_b:" );
	vprintf( fmt, args);
	va_end(args);
}

void func_a(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf( "func_a:" );
	printf( ", %s:", fmt );
	vprintf( fmt, args);
	func_b(fmt, args);
	va_end(args);
}

int main( int argc, char **argv )
{
	printf( "data:%d\n", 123 );
	func_a( "data:%d\n", 123 );
}
