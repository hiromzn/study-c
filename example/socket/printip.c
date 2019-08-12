#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
DEFINITON:
      char *
	  inet_ntoa(struct in_addr in);

	  char *
	  inet_ntoa_r(struct in_addr in, char *buf, socklen_t size);
*/

#define BUFLEN  100

int main(int argc, char *argv[]) {
  unsigned long long_addr = 2085852108ul;
  struct in_addr inaddr = { htonl(long_addr) };

  char *addrstr = inet_ntoa( inaddr );

  if ( addrstr ) {
	printf ("%s\n", addrstr );
  } else {
	// can not get address
  }
  return 0;
}
