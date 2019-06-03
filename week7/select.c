#include <stdio.h>
#include <errno.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h> 
 
int main()
{
		//int fds; 
		int ret;
		char buf[100];
		int timecount;
		int maxfd;
		
		fd_set rfds;//set listen 
		struct timeval tv;//set wating time，0不等待，NULL一直等待。
				
  
		FD_ZERO(&rfds);//清空集合

 
		timecount = 0;
		while(1)
		{
		        FD_SET(STDIN_FILENO, &rfds);//put keyboard input in 
         	        maxfd = STDIN_FILENO + 1;
	
			tv.tv_sec = 5;
			tv.tv_usec = 0;//set wait time
			ret = select(maxfd, &rfds, NULL, NULL, &tv);
			if(ret<0)
			{
				printf("select error, process will eixt\n");
				exit(0);
			}
			else if(FD_ISSET(STDIN_FILENO, &rfds))//test if have data
			{
					fgets(buf, 100, stdin);
					printf("You input is %s\n",buf);
				
			}
			else
			{
			
				timecount++;
				printf("\ntime out: %d\n", timecount);
			
			}
		}
		return 0;
}
