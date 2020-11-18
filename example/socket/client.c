#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
int main( int argc, char **argv )
{
    int sockfd;
    struct sockaddr_in addr;
	int i;
	int ret;
	char *adr_str = "127.0.0.1";
	int port;
 
	if (argc < 2) {
		fprintf( stderr, "usage: %s ip_address port_number\n", *argv );
		return(1);
	}
	adr_str = argv[1];
	port = atoi( argv[2] );
    // ソケット生成
    if( (sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 ) {
        perror( "socket" );
    }
 
    // 送信先アドレス・ポート番号設定
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );
    addr.sin_addr.s_addr = inet_addr( adr_str );
 
    // サーバ接続
	printf( "connect( %s, %d )\n", adr_str, port );
    ret = connect( sockfd, (struct sockaddr *)&addr, sizeof( struct sockaddr_in ) );
	if ( ret < 0 ) {
		fprintf( stderr, "ERROR: connect() errno:%d\n", errno );
		return(1);
	}
 
    // データ送信
    char send_str[10];
    char receive_str[10];
    for ( i = 0; i < 10; i++ ){
        sprintf( send_str, "%d", i );
        printf( "send:%d\n", i );
        if( send( sockfd, send_str, 10, 0 ) < 0 ) {
            perror( "send" );
        } else {
            recv( sockfd, receive_str, 10, 0 );
            printf( "receive:%s\n", receive_str );
        }
        sleep( 1 );
    }
 
    // ソケットクローズ
    close( sockfd );
 
    return 0;
}
