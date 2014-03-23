#include "def.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

void fill_fd_with_zero(int fd, uint64_t size)
{
	uint64_t i;
	uint8_t zero=0;
	char errmsg[0xffff];

	for(i=0; i<size; i++)
		if(write(fd, &zero, 1)==-1){
			sprintf(errmsg, "fill_fd_zero: write: %s", strerror(errno));
			will_and_die(errmsg, 1);
		}

	return;
}
