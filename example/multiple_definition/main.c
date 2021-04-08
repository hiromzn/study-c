
#include <stdio.h>

extern int sub_func1();
extern int sub_func2();

int main_func1()
{
	printf( "main_func1()\n" );
}

int main()
{
	main_func1();
	sub_func1();
	sub_func2();
}
