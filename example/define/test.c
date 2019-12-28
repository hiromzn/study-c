/*
	string macro sample

	string macro : #name
*/

#include <stdio.h>

#define PR_VAR(n)	printf("name:%s, val=%ld\n", #n, (long)n)

typedef struct test_struct {
	char	cdata[3];
	double	ddata;
	int	idata;
} TestSTR;

#define PR_MEM_OFFSET( _s_, _m_ ) \
	printf("member:%s, size:%ld, offset=%ld=0x%lX\n", #_m_, sizeof(_s_._m_), \
		(void*)&(_s_._m_) - (void*)&_s_, \
		(void*)&(_s_._m_) - (void*)&_s_ )


int main()
{
	TestSTR str;

	int localint = 10;
	int locallong = 20;

	PR_VAR( localint );
	PR_VAR( locallong );
	PR_MEM_OFFSET( str, cdata );
	PR_MEM_OFFSET( str, ddata );
	PR_MEM_OFFSET( str, idata );
}
