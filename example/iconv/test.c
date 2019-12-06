#include <stdio.h>
#include <iconv.h>

#define  BUFSIZE  1024

char outbuf[BUFSIZE];

int convert(char const *src,
            char const *dest,
            char const *text,
            char *buf,
            size_t bufsize);

main(void)
{
    int ret;

    ret = convert("SHIFT-JIS", "UTF-8",
                  "日本語テストメッセージおはよう",
                  outbuf, sizeof(outbuf));
    if (ret) {
        printf("%s\n", outbuf);
    }
    else {
        printf("Oops!\n");
    }
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

    cd = iconv_open(dest, src);
    if (cd == (iconv_t)-1) {
        perror("iconv open");
        return 0;
    }

    srclen = strlen(text);
    destlen = bufsize - 1;
    memset(buf, '\0', bufsize);

    ret = iconv(cd, &text, &srclen, &buf, &destlen);
    if (ret == -1) {
        perror("iconv");
        return 0;
    }

    iconv_close(cd);
    return 1;
}
