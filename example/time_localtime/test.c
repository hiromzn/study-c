#include <stdio.h>
#include <time.h>

#define DATETIME_STR_SIZE	40

char *get_datetime_string( char *datetime_str, int str_size )
{
#define DATETIME_STR_FMT	"%04d-%02d%02d-%02d%02d-%02d"

    time_t current_time;
    struct tm time_info;
    struct tm *ret;

	if ( !datetime_str || str_size < 1 ) {
		return( NULL );
	}

    time(&current_time);
    ret = localtime_r(&current_time, &time_info);

	if ( ret )
	{
		snprintf(
			datetime_str
			, str_size
			, DATETIME_STR_FMT
			, time_info.tm_year + 1900
			, time_info.tm_mon + 1
			, time_info.tm_mday
			, time_info.tm_hour
			, time_info.tm_min
			, time_info.tm_sec
		);
		return( datetime_str );
	}
	// ERROR
	return( NULL );
}

void DO_TEST( char *buf, int size )
{
	printf( "TEST:%p, %d\n", buf, size );
	char *ret;
	ret = get_datetime_string( buf, size );
	if (ret) {
		printf( "OK: %p : %s\n", ret, ret );
	} else {
		printf( "NG: %p\n", ret );
	}
}

int main()
{
    char datetime_str[DATETIME_STR_SIZE];

	DO_TEST( datetime_str, DATETIME_STR_SIZE );
	DO_TEST( datetime_str, 10 );
	DO_TEST( datetime_str, 0 );
	DO_TEST( NULL, 20 );
}
