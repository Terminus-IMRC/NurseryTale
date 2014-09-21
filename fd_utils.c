#define _BSD_SOURCE
#include "def.h"
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

void fill_fd_with_zero(int fd, uint64_t size)
{
	ftruncate(fd, size);
	return;
}
