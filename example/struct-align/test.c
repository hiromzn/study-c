#include <stdio.h>

typedef	struct	my_time {
	char	timestr[5];
} Time;

typedef struct my_date {
	char	datestr[11];
} Date;	

typedef struct test_struct {
	char	c3[3];
	double	d1;
	double	d2;
	double	d3;
	double	d4;
	double	d5;
	double	d6;
	double	d7;
	double	d8;
	char	c1;
	char	c4[4];
	Date	date1;
	Time	time;
	double	d9;
} TestSTR;

#define PR_MEM_ADR( _s_, _m_ )		printf("%s:%p\n", #_m_, &(_s_._m_) )

#define PR_MEM_OFFSET( _s_, _m_ ) \
	printf("member:%s, size:%ld, offset=%ld=0x%lX\n", \
		#_m_, \
		(long int)sizeof(_s_._m_), \
		(long int)((void*)&(_s_._m_) - (void*)&_s_), \
		(long unsigned int)((void*)&(_s_._m_) - (void*)&_s_) )

int main()
{
	TestSTR str;

	PR_MEM_OFFSET( str, c3 );
	PR_MEM_OFFSET( str, d1 );
	PR_MEM_OFFSET( str, d2 );
	PR_MEM_OFFSET( str, d3 );
	PR_MEM_OFFSET( str, d4 );
	PR_MEM_OFFSET( str, d5 );
	PR_MEM_OFFSET( str, d6 );
	PR_MEM_OFFSET( str, d7 );
	PR_MEM_OFFSET( str, d8 );
	PR_MEM_OFFSET( str, c1 );
	PR_MEM_OFFSET( str, c4 );
	PR_MEM_OFFSET( str, date1 );
	PR_MEM_OFFSET( str, time );
	PR_MEM_OFFSET( str, d9 );
}
