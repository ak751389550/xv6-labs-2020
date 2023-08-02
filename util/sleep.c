#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char* argv[])
{
	if(argc != 2)
	{
	fprintf(2,"usage error\n");
	exit(1);
	}
	int clock = atoi(argv[1]);
	sleep(clock);
	exit(0);	
}


