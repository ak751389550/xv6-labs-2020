#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WT 1

void transmit(int pipe[2],int p[2],int first)
{
	int data;
	while(read(pipe[RD],&data,sizeof(int))==sizeof(int))
	{
		if(data%first != 0)
		{
			write(p[WT],&data,sizeof(int));
		}
	}
	close(pipe[RD]);
	close(p[WT]);
}

void primes(int pipe2[2])
{
	close(pipe2[WT]);
	int first;
	if(read(pipe2[RD],&first,sizeof(int)) == sizeof(int))
	{
		printf("prime %d\n",first);
		int p[2];
		pipe(p);
		transmit(pipe2,p,first);

		if(fork()==0)
		{
			primes(p);
		}
		else
		{
			close(p[RD]);
			wait(0);
		}
	}
}

int main(int argc,char * argv[])
{
	if(argc!=1)
	{
		fprintf(2,"usage error!");
	}
	int p[2];
	pipe(p);

	for(int i=2;i<35;i++)
	{
		write(p[WT],&i,sizeof(int));
	}

	if(fork()==0)
	{
		primes(p);
	}
	else
	{
		close(p[WT]);
		close(p[RD]);
		wait(0);
	}
	exit(0);
}
