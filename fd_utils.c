#define _BSD_SOURCE
#include "def.h"
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

void fill_fd_with_zero(int fd, uint64_t size)
{
	char errmsg[0xffff];

	if(ftruncate(fd, size)==-1){
		sprintf(errmsg, "fill_fd_with_zero: ftruncate: %s\n", strerror(errno));
		will_and_die(errmsg, 1);
	}

	return;
}
