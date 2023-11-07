#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// #define PR_SHM	printf( "shmget( key:%d(0x%08X), ID:%d, shmaddr:%p, shm_size:%d, shmflg:%s:%06o(O) )\n", (int)key, (int)key, shmid, shmaddr, (int)shm_size, flgstr, shmflg )
//
#define PR_SHM(a)	printf( "shmget( key:%d(0x%08X), ID:%d, shmaddr:%p, shm_size:%d, shmflg:%06o(O) )\n", (int)(a)->key, (int)(a)->key, (a)->id, (a)->addr, (int)(a)->size, (a)->flag )

typedef struct _shm_info_ {
	key_t	key;
	int		id;
	size_t	size;
	int		flag;
	void	*addr;
} ShmInfo;

void usage(char **argv);
int setup_shmem( ShmInfo *pShmInfo, int key, int flag, int size );

int main( int argc, char **argv )
{
	ShmInfo	sShmInfo;
	ShmInfo	*pShmInfo;
	int		shmflg = 0666;

	pShmInfo = &sShmInfo;

	// if ( !argv[1] || !argv[2] ) {
	if (argc <= 3) {
		usage(argv);
		exit( 1 );
	}


	switch( atoi(argv[2]) ) {
	case 1 :
		shmflg |= IPC_CREAT;
		break;
	case 2 :
		shmflg |= IPC_EXCL;
		break;
	case 3 :
		shmflg |= IPC_CREAT | IPC_EXCL;
		break;
	}

	if ( setup_shmem( pShmInfo, atoi( argv[1] ), shmflg, atoi( argv[3] ) ) ) {
		printf( "ERROR : setup_shmem()\n" );
		exit( 1 );
	}

	return( 0 );
}

int setup_shmem( ShmInfo *pShmInfo, int key, int flag, int size )
{
	void	*retaddr;

	pShmInfo->key = key;
	pShmInfo->flag = flag;

	pShmInfo->size = size;

	PR_SHM(pShmInfo);

	pShmInfo->id = shmget(pShmInfo->key, pShmInfo->size, pShmInfo->flag);
	printf( "return : shmid:%d\n", pShmInfo->id);
	if ( pShmInfo->id == -1 ) {
		printf( "ERROR : shmget() : errno:%d\n", errno );
		perror( "shmget" );
		return 1;
	}

	pShmInfo->addr=NULL;

	printf( "shmat( shmid:%d, address:%p, 0)\n", pShmInfo->id, (void*)pShmInfo->addr );
	retaddr = shmat(pShmInfo->id, pShmInfo->addr, 0);
	printf( "return address from shmat():%p\n", retaddr);

	if ( retaddr == (void*)-1 ) {
		printf( "ERROR errno:%d\n", errno );
		perror( "ERROR shmat\n" );
		return  1;
	}

	pShmInfo->addr = (char*)retaddr;
	PR_SHM(pShmInfo);

	return 0;
}

void usage( char **argv )
{
		printf( "\n\
usage : %s key flag size\n\
\n\
  key : shmem key (integer number)\n\
\n\
  flag :\n\
	1 : IPC_CREAT\n\
	2 : IPC_EXCL\n\
	3 : IPC_CREAT | IPC_EXCL\n\
\n\
  size : shared memory size (byte)\n\
\n", argv[0] );
}
