#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main( int argc, char **argv )
{
	int ret;

	key_t key;
	int nsems = 1;
	int semflg = 0666;
	char *flgstr = "NULL";
	int semid;

	struct sembuf	sb;

	if ( !argv[1] || !argv[2] ) {
		printf( "\n\
usage : %s key flag ........... create / attach\n\
usage : %s key flag lock ...... lock/unlock\n\
\n\
  key : semaphore key (integer number)\n\
\n\
  flag :\n\
	1 : IPC_CREAT\n\
	2 : IPC_EXCL\n\
	3 : IPC_CREAT | IPC_EXCL\n\
\n\
  lock :\n\
	-1 : lock\n\
	1  : unlock\n\
	0  : wait until 0\n", argv[0], argv[0] );
		return 1;
	}

	key = atoi( argv[1] );

	switch( atoi(argv[2]) ) {
	case 1 :
		semflg |= IPC_CREAT;
		flgstr = "IPC_CREAT";
		break;
	case 2 :
		semflg |= IPC_EXCL;
		flgstr = "IPC_EXCL";
		break;
	case 3 :
		semflg |= IPC_CREAT | IPC_EXCL;
		flgstr = "IPC_CREAT | IPC_EXCL";
		break;
	}
	printf( "semget( key:%d, nsems:%d, semflg:%s:%06o(O) )\n", key, nsems, flgstr, semflg );

	semid = semget(key, nsems, semflg);
	printf( "return : semid:%d\n", semid);
	if ( semid == -1 ) {
		printf( "ERROR errno:%d\n", errno );
		perror( "ERROR semget\n" );
		return 1;
	}
	if ( !argv[3] ) {
		return 1;
	}

	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	sb.sem_op = atoi(argv[3]);

	printf( "semop( semid:%d, lock:%d, 1 )\n", semid, sb.sem_op );

	ret = semop(semid, &sb, 1);
	printf( "return : semop():%d\n", ret);
	if ( ret == -1 ) {
		printf( "ERROR errno:%d\n", errno );
		perror( "ERROR semop\n" );
		return  1;
	}
	
	return 0;
}
