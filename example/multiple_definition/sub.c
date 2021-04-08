
#include <stdio.h>

extern int main_func1();

int sub_func1()
{
	printf( "sub_func1() : START\n" );
	main_func1();
	printf( "sub_func1() : END\n" );
}
