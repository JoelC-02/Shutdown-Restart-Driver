#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256
static char receive[BUFFER_LENGTH];

int main() {
	int fd=open("/dev/shutdown", O_RDWR);
	char buf[100];
	while(1) {
		memset(buf, 0, 256);
		printf(" 1: Shut down\n 2: Restart\n 3: Quit\n Enter option: ");
		scanf("%s", buf);
		if(!strcmp(buf, "3")) break;
		write(fd, buf, strlen(buf));
		read(fd, buf, sizeof(100));
        	printf("Read: %s\n",buf);
        }
        close(fd);
	return 0;
}
