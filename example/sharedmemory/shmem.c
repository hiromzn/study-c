#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main( int argc, char **argv )
{
	void *retaddr;

	key_t key;
	size_t shm_size = 1;
	int shmflg = 0666;
	char *flgstr = "NULL";
	int shmid = 0;

	char *shmaddr = NULL;

#define PR_SHM	printf( "shmget( key:%d(0x%08X), ID:%d, shmaddr:%p, shm_size:%d, shmflg:%s:%06o(O) )\n", (int)key, (int)key, shmid, shmaddr, (int)shm_size, flgstr, shmflg )

	// if ( !argv[1] || !argv[2] ) {
	if (argc <= 3) {
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
		return 1;
	}

	key = atoi( argv[1] );

	switch( atoi(argv[2]) ) {
	case 1 :
		shmflg |= IPC_CREAT;
		flgstr = "IPC_CREAT";
		break;
	case 2 :
		shmflg |= IPC_EXCL;
		flgstr = "IPC_EXCL";
		break;
	case 3 :
		shmflg |= IPC_CREAT | IPC_EXCL;
		flgstr = "IPC_CREAT | IPC_EXCL";
		break;
	}
	shm_size = atoi( argv[3] );

	PR_SHM;

	shmid = shmget(key, shm_size, shmflg);
	printf( "return : shmid:%d\n", shmid);
	if ( shmid == -1 ) {
		printf( "ERROR : shmget() : errno:%d\n", errno );
		perror( "shmget" );
		return 1;
	}

	shmaddr=NULL;

	printf( "shmat( shmid:%d, address:%p, 0)\n", shmid, (void*)shmaddr );
	retaddr = shmat(shmid, shmaddr, 0);
	printf( "return address from shmat():%p\n", retaddr);

	if ( retaddr == (void*)-1 ) {
		printf( "ERROR errno:%d\n", errno );
		perror( "ERROR shmat\n" );
		return  1;
	}

	shmaddr = (char*)retaddr;
	PR_SHM;
	
	return 0;
}
