
#include <stdio.h>

int sub_func2()
{
	printf( "sub_func1()\n" );
}

#ifdef MULTI_DEF
// #ifdef MULTI_DEF_EXTERN
// extern int sub_func1();
// #else
int sub_func1()
{
	printf( "sub_func1()\n" );
}
// #endif /* MULTI_DEF_EXTERN */
#endif /* MULTI_DEF */

