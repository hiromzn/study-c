/*
 * NON blocking connect()
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <errno.h>

/*
 * export of function
 */
char *connect_nonblock_get_error_message( int errid );
int connect_nonblock( int socket, struct sockaddr *address, int address_len, struct timeval timeout, int *error_id );

/*
 * DEBUG section
 */
#define _DEBUG_PRINTF(a,b,c)

/*
 * common definition
 *
 */
#define _ERROR_		(-1)

typedef struct error_code_str {
	int		code;
	char	*msg;
} ErrorCode;

static ErrorCode error_code[] = {
	{	0x001, "fcntl(GETFL) error" },
	{	0x002, "fcntl(SETFL NONBLOCK mode) error" },
	{	0x003, "connect(NONBLOCK, timeout) error" },
	{	0x004, "fcntl(SETFL BLOCK mode) error" },
	{	0x005, "select() no descriptor error" },
	{	0x006, "select() other error" },
};
#define ERROR_CODE_MAX		(sizeof(error_code)/sizeof(ErrorCode))

/*
 * get error message of error_id from connect_nonblock()
 *
 */
char *connect_nonblock_get_error_message( int errid )
{
	if ( errid <= ERROR_CODE_MAX ) {
		return( error_code[errid-1].msg );
	} else {
		return( NULL );
	}
}

/*
 * NON blocking connect()
 *
 *   arguments: ( first 3 arguments is equal to connect() arguments )
 *
 *     [IN]  socket : socket descriptor
 *     [IN]  address : address to connect
 *     [IN]  address_len : length of address data
 *
 *     [IN]  timeout : time out value
 *     [OUT] error_id : error code of this function
 *
 *   return value:
 *     0 : success
 *     -1 : error ( reason of error : check errno and error_id of argument )
 */
int connect_nonblock( int socket, struct sockaddr *address, int address_len, struct timeval timeout, int *error_id )
{
#define GET_ERR_MSG(a)		connect_nonblock_get_error_message(a)
#define _FCNTL_ERROR_	(-1)

	int		flags = 0;
	int		result = 0;
    fd_set	readFd, writeFd, errFd;

	*error_id = 0;

    /* set NON-blocking mode */
    flags = fcntl(socket, F_GETFL);
    if ( _FCNTL_ERROR_ == flags )
    {
		*error_id = 0x001;
		_DEBUG_PRINTF( "ERROR: %s : %d\n", GET_ERR_MSG(*error_id), errno );
        return _ERROR_;
    }
    result = fcntl(socket, F_SETFL, flags | O_NONBLOCK);
    if ( _FCNTL_ERROR_ == result )
    {
		*error_id = 0x002;
		_DEBUG_PRINTF( "ERROR: %s : %d\n", GET_ERR_MSG(*error_id), errno );
        return _ERROR_;
    }

    /* CONNECT */
    result = connect(socket, address, address_len);
    if ( result )
    {
        if ( EINPROGRESS == errno )
        {
            /*
				The socket is non-blocking and the connection cannot be completed immediately.
				It is possible to select(2) for completion by selecting the socket for writing.
			*/
            errno = 0;
        }
        else
        {
			*error_id = 0x003;
			/* Actual connect ERROR */
            /* Fail connect : return to blocking mode */
            fcntl(socket, F_SETFL, flags );
			_DEBUG_PRINTF( "ERROR: %s : %d\n", GET_ERR_MSG(*error_id), errno );
            return _ERROR_;
        }
    }

    /* return to blocking mode */
    result = fcntl(socket, F_SETFL, flags );
    if ( _FCNTL_ERROR_ == result  )
    {
		*error_id = 0x004;
		_DEBUG_PRINTF( "ERROR: %s : %d\n", GET_ERR_MSG(*error_id), errno );
        return _ERROR_;
    }

    /* wait by select */
    FD_ZERO(&readFd);
    FD_ZERO(&writeFd);
    FD_ZERO(&errFd);
    FD_SET(socket, &readFd);
    FD_SET(socket, &writeFd);
    FD_SET(socket, &errFd);
    int sockNum = select( socket + 1, &readFd, &writeFd, &errFd, &timeout );
    if ( 0 == sockNum )
    {
        /* time out */
		/*  no desctiptor that are contained anything */
		*error_id = 0x005;
		_DEBUG_PRINTF( "ERROR: %s : %d\n", GET_ERR_MSG(*error_id), errno );
        return _ERROR_;
    }
    else if ( FD_ISSET(socket, &readFd) || FD_ISSET(socket, &writeFd)  )
    {
        /*
		  SUCCESS
		    socket is available for read and write
		*/
    }
    else
    {
		*error_id = 0x006;
		_DEBUG_PRINTF( "ERROR: %s : %d\n", GET_ERR_MSG(*error_id), errno );
        return _ERROR_;
    }

	/*
	  check socket error
	    check any pending error on the socket and clears the error status.
	*/
    int optval = 0;
    socklen_t optlen = (socklen_t)sizeof(optval);
    errno = 0;
    result = getsockopt(socket, SOL_SOCKET, SO_ERROR, (void *)&optval, &optlen);
    if ( result < 0 )
    {
        /* ERROR case */
		// _DEBUG_PRINTF( "ERROR: getsockopt 1 : %d\n", errno );
    }
    else if ( 0 != optval )
    {
        /* ERROR case */
		// _DEBUG_PRINTF( "ERROR: getsockopt 2 : %d\n", errno );
    }

    return 0;
}

#ifdef TEST_MAKE
int main()
{
	int eid;

	eid = 1; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
	eid = 2; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
	eid = 3; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
	eid = 4; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
	eid = 5; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
	eid = 6; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
	eid = 7; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
	eid = 0; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
	eid = -1; printf( "TEST: get message :%d => %s\n", eid, connect_nonblock_get_error_message(eid) );
}
#endif /* TEST_MAKE */
