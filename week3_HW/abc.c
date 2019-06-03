#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>


#define DEVFILE "/dev/test" 

int open_file(char *filename)
{
	int fd;

	fd=open(filename, O_RDWR);
	if(fd == -1){
		perror("open");
	}
	return (fd);

}
void close_file(int fd)
{
	if(close(fd)!=0){
		perror("close");
	}
}

void read_file(int fd)
{
	char *buf ;
	ssize_t ret;

	ret=read(fd,buf,sizeof(buf));
	
	printf("%s",buf);
	
	perror("read");

	printf("\n");
}
void write_file(int fd,char *val)
{
	ssize_t ret;
	ret=write(fd,val,sizeof(val));
	printf("you enter:%s\n",val);
	
	if(ret <= 0)
	{
		perror("write");
	}
}
int main(void)
{	int i;
	int fd;
	int mode;
	char *s;
		printf("1=read from device\n");
		printf("2=write to device\n");
		printf("chose mode:");
		scanf("%d",&mode);
		fd=open_file(DEVFILE);
		switch(mode)
		{
  		case 1:
			read_file(fd);
			break;
		case 2:		
			printf("enter:");
			scanf("%s",s);
			write_file(fd, s);
			break;
		default:
			printf("enter error");
		
	}

	return 0;
}
