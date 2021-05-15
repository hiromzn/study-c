#include <stdio.h>

typedef struct _mystr_ {
        int             idata;
        char    char1[5];
        char    char2;
} MYSTR_1;

#pragma pack(push)
#pragma pack(2)
typedef struct _mystr_2_ {
        int             idata;
        char    char1[5];
        char    char2;
} MYSTR_2;
#pragma pack(pop)

#define memi(a)         &a.idata
#define memc1(a)        &a.char1
#define memc2(a)        &a.char2

int main()
{
        MYSTR_1         str1;
        MYSTR_2         str2;
        MYSTR_2         str3[4];

        printf( "str1 %p : size:%d\n", & str1, sizeof(str1) );
        printf( " int %p\n", memi(str1) );
        printf( " char1 %p\n", memc1(str1) );
        printf( " char2 %p\n", memc2(str1) );
        printf( "\n" );

        printf( "str2 %p : size:%d\n", & str2, sizeof(str2) );
        printf( " int %p\n", memi(str2) );
        printf( " char1 %p\n", memc1(str2) );
        printf( " char2 %p\n", memc2(str2) );
        printf( "\n" );

        printf( "str3 %p : size:%d\n", & str3[0], sizeof(str3) );
        printf( "str3 %p : size:%d\n", & str3[1], sizeof(str3) );
        printf( "str3 %p : size:%d\n", & str3[2], sizeof(str3) );
        printf( "str3 %p : size:%d\n", & str3[3], sizeof(str3) );
}
