#include <stdio.h>
#include <pthread.h>

void main( int argc, char **argv )
{
	pthread_attr_t	attr;
	struct sched_param param;
	int ret;

	ret = pthread_attr_init( &attr );
	printf( "ret:%d\n", ret );

	param.__sched_priority = 3;
	ret = pthread_attr_setschedparam( &attr, &param );
	printf( "ret:%d\n", ret );
}

