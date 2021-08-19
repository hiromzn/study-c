#include <stdio.h>
#include <signal.h>

void handler(int sig)
{
        char buffer[1000];
        sprintf( buffer, "pstack %d >>/tmp/stack_trace \n", getpid() );
        system( buffer );
        printf("hadler last\n");
        exit(1);
}

int main()
{
        signal(SIGTERM, handler);
        kill(0, SIGTERM);
        printf("main last\n");
}
