#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WT 1

int main(int argc,char* argv[])
{
	if(argc!=1)
	{
		fprintf(2,"usage error\n");
	}
	int p1[2];
	int p2[2];
	pipe(p1);
	pipe(p2);
	
	int pid = fork();
	char send = 'A';
	if(pid<0)
	{
		fprintf(2,"fork() error!\n");
		exit(1);
	}
	else if (pid==0)
	{
		close(p1[WT]);
		close(p2[RD]);
		if(read(p1[RD],&send,sizeof(char)) != sizeof(char))
		{
			fprintf(2,"child read() error!\n");
			exit(1);
		}
		else
		{
			fprintf(1,"%d: received ping\n",getpid());
		}
		if(write(p2[WT],&send,sizeof(char))!=sizeof(char))
		{
			fprintf(2,"child write() error!\n");
			exit(1);
		}
		
		close(p1[RD]);
		close(p2[WT]);

		exit(0);
	}
	else
	{
		close(p1[RD]);
		close(p2[WT]);
                if(write(p1[WT],&send,sizeof(char))!=sizeof(char))
                {
                        fprintf(2,"parent write() error!\n");
                        exit(1);
                }
		if(read(p2[RD],&send,sizeof(char))!=sizeof(char))
		{
			fprintf(2,"parent read() error!\n");
			exit(1);
		}
		else
		{
			fprintf(1,"%d: received pong\n",getpid());
		}

		close(p1[WT]);
		close(p2[RD]);
		
		exit(0);
	}
}

