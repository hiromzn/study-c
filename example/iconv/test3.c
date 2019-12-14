#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

#define  BUFSIZE  1024

char outbuf[BUFSIZE];

int convert(char const *src,
            char const *dest,
            char const *text,
            char *buf,
            size_t bufsize);

int main( int argc, char **argv )
{
    int ret;

    // OK: ret = convert("UTF-8", "EUCJP",
    // OK: ret = convert("UTF-8", "SJIS",
    // OK: ret = convert("UTF-8", "eucJP",
    ret = convert("eucJP", "SJIS",
                  // "日本語テストメッセージおはよう",
                  "Abcdef Xyzze",
                  outbuf, sizeof(outbuf));
    if (!ret) {
        printf("%s\n", outbuf);
    }
    else {
        printf("Oops!\n");
    }
	return( ret );
}

int call_iconv( 
			   iconv_t cd,
			   int	slen,
			   int	dlen,
			   char*	sbuf,
			   char*	dbuf )
{
  int ret;

  printf( "before : iconv_open( dest:%s:%d <- src:%s:%d );\n", dbuf, dlen, sbuf, slen );
  ret = iconv(cd, &sbuf, &slen, &dbuf, &dlen);
  printf( "before : iconv_open( dest:%s:%d <- src:%s:%d );\n", dbuf, dlen, sbuf, slen );

  if (ret == -1) {
	perror("ERROR:(iconv):");
	return 1;
  }
  return 0;
}

int convert(char const *src,
            char const *dest,
            char const *text,
            char *buf,
            size_t bufsize)
{
    iconv_t cd;
    size_t srclen, destlen;
    size_t ret;

	printf( "iconv_open( dest:%s <- src:%s );\n", dest, src );
    cd = iconv_open(dest, src);
    if (cd == (iconv_t)-1) {
        perror("iconv open");
        return 1;
    }

    srclen = strlen(text) + 1;
    destlen = bufsize - 1;
    memset(buf, '\0', bufsize);

    ret = call_iconv(cd, srclen, destlen, text, buf );

	iconv_close(cd);

	return( ret );
}
