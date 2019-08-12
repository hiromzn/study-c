#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

/*
DEFINITON:
      char *
	  inet_ntoa(struct in_addr in);

STRUCTURE:

<bits/socket.h>
  struct sockaddr
  {
    __SOCKADDR_COMMON (sa_);
    char sa_data[14];
  };

<netinet/in.h>

  struct sockaddr_in
  {
    __SOCKADDR_COMMON (sin_);
    in_port_t sin_port;
    struct in_addr sin_addr;

    // Pad to size of `struct sockaddr'.
	// ...
  };


  typedef uint32_t in_addr_t;
  struct in_addr
  {
    in_addr_t s_addr;
  };

*/
 
int main() {
  int sockfd;
  int client_sockfd;
  struct sockaddr_in addr;

  socklen_t len = sizeof( struct sockaddr_in );
  struct sockaddr_in from_addr;
 
  char buf[1024];
	
  // initialize buffer
  memset( buf, 0, sizeof( buf ) );
    
  // create socket
  if( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
	printf( "errno:%d\n", errno );
    perror( "socket" );
  }
    
  // listen port 
  addr.sin_family = AF_INET;
  addr.sin_port = htons( 1234 );
  addr.sin_addr.s_addr = INADDR_ANY;

  char addrstr[1024];
  char *str = inet_ntoa( addr.sin_addr );
  if ( str ) {
	strcpy( addrstr, str );
  } else {
	perror( "inet_ntoa" );
  }
  printf( "address : %s\n", addrstr );
  printf( "port : %d\n", ntohs( addr.sin_port ) );

  // bind
  if( bind( sockfd, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 ) {
	printf( "errno:%d\n", errno );
	perror( "bind" );
  }
   
  // listen
  if( listen( sockfd, SOMAXCONN ) < 0 ) {
	printf( "errno:%d\n", errno );
	perror( "listen" );
  }
   
  // accept
  if( ( client_sockfd = accept( sockfd, (struct sockaddr *)&from_addr, &len ) ) < 0 )
	{
	  printf( "errno:%d\n", errno );
	  perror( "accept" );
  }
   
  // receive
  int rsize;
  while( 1 ) {
	rsize = recv( client_sockfd, buf, sizeof( buf ), 0 );
   
	if ( rsize == 0 ) {
	  break;
	} else if ( rsize == -1 ) {
	  printf( "errno:%d\n", errno );
	  perror( "recv" );
	} else {
	  printf( "receive:%s\n", buf );
	  sleep( 1 );
  
	  // responce
	  printf( "send:%s\n", buf );
	  write( client_sockfd, buf, rsize );
	}
  }
 
  // close
  close( client_sockfd );
  close( sockfd );
 
  return 0;
}
