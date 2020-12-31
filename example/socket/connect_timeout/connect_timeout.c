#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <errno.h>

#define _ERROR_		(-1)

int connect_nonblock(int socket, struct sockaddr * name, int namelen, struct timeval timeout )
{
#define _FCNTL_ERROR_	(-1)

	int		flags = 0;
	int		result = 0;
    fd_set	readFd, writeFd, errFd;

    /* set NON-blocking mode */
    flags = fcntl(socket, F_GETFL);
    if ( _FCNTL_ERROR_ == flags )
    {
        return _ERROR_;
    }
    result = fcntl(socket, F_SETFL, flags | O_NONBLOCK);
    if ( _FCNTL_ERROR_ == result )
    {
        return _ERROR_;
    }

    /* CONNECT */
    result = connect(socket, name, namelen);
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
			/* Actual connect ERROR */
            /* Fail connect : return to blocking mode */
            fcntl(socket, F_SETFL, flags );
            return _ERROR_;
        }
    }

    /* return to blocking mode */
    result = fcntl(socket, F_SETFL, flags );
    if ( _FCNTL_ERROR_ == result  )
    {
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
        return _ERROR_;
        return -1;
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
    }
    else if ( 0 != optval )
    {
        /* ERROR case */
    }

    return 0;
}
