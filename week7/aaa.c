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
	char buf[11];
	int ret;
	
	struct pollfd fds;
	int retval;

	while(1)
	{
		
		do {
			fds.fd = fd;
			fds.events = POLLIN;

		
			retval = poll(&fds, 1, 5 * 1000);
			printf("retval:%d\n",retval);
			if (retval == -1) {
				perror("poll");
				printf("123");
				break;
			}

			if (retval) {
				  memset((void *)buf,0,11);
                		ret =read(fd,(void * )buf,10);
        	       		 printf("ret=%d\n",ret);
	                	if (ret != -1)
              			  {
                        		printf("buf=%s\n",buf);
             			   }		

				break;
			}

			printf("timeout!!!\n");

		} while (retval == 0);   /* timeout elapsed */


	
	}

	return 0;
}
