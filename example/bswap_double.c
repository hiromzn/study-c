#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <byteswap.h>

static double bswap_double_p( double* src )
{
        uint64_t uint64;

        memcpy( &uint64, src, sizeof(double) );
        uint64 = bswap_64( uint64 );
        memcpy( src, &uint64, sizeof(uint64) );
        return *src;
}

static double bswap_double( double src )
{
        double ret;
        uint64_t uint64;

        memcpy( &uint64, &src, sizeof(src) );
        uint64 = bswap_64( uint64 );
        memcpy( &ret, &uint64, sizeof(uint64) );
        return ret;
}

int main()
{
        double da = 1.23e23;

        printf( "sizeof(double):%d\n", sizeof(double) );
        printf( "bswap_double_p(): da:%e\n", da );
        bswap_double_p( &da );
        printf( "bswap_double_p(): da:%e\n", da );
        da = bswap_double_p( &da );
        printf( "bswap_double_p(): da:%e\n", da );

        printf( "bswap_double(): da:%e\n", da );
        da = bswap_double( da );
        printf( "bswap_double(): da:%e\n", da );
        da = bswap_double( da );
        printf( "bswap_double(): da:%e\n", da );
}
