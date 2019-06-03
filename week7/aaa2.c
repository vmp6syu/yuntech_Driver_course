#include<stdio.h>
#include<string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
int main(int argc , char *argv[])
{
	int fd;
	fd_set rfds;
	struct timeval tv;

	char buf[11];
	int ret;
	
	int retval;


	while(1)
	{
		
		do {
			FD_ZERO(&rfds);
			FD_SET(fd, &rfds);
			tv.tv_sec = 5;
			tv.tv_usec = 0;
			printf("select()...\n");
       	
			retval = select(fd + 1, &rfds, NULL, NULL, &tv);
			

			            
			
			if (retval==-1) {
				perror("poll");
				break;
			}

			if (retval) {
				break;
			}
			memset((void *)buf,0,11);

			 ret =read(fd,(void * )buf,10);

			if(ret!=-1)
			{
				printf("ret=%d\n",ret);
                            if (ret != -1)
                            {
                                 printf("buf=%s\n",buf);
                            }

			}
			else
			{
		           printf("timeout\n");
			}


		} while (retval == 0);   /* timeout elapsed */
	
	}

	return 0;
}
