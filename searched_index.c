#include "def.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define SEARCHED_INDEX_FILE_NAME "index.db"

static int fd;
static uint8_t *searched_index;
static size_t size;

void searched_index_init()
{
	uint64_t i;
	char errmsg[0xffff];

	size=1;
	for(i=0; i<X*X; i++)
		size*=2;
	/* searched indexes are stored in bits */
	size/=8;
	/*TODO:check if size<SIZE_MAX*/

	fd=open(SEARCHED_INDEX_FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd==-1){
		sprintf(errmsg, "searched_index_init: open: %s", strerror(errno));
		will_and_die(errmsg, 1);
	}

	fill_fd_with_zero(fd, size);

	searched_index=mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(searched_index==MAP_FAILED){
		sprintf(errmsg, "searched_index_init: mmap: %s", strerror(errno));
		will_and_die(errmsg, 1);
	}

	return;
}

void searched_index_finalize()
{
	char errmsg[0xffff];

	if(munmap(searched_index, size)==-1){
		sprintf(errmsg, "searched_index_finalize: munmap: %s", strerror(errno));
		will_and_die(errmsg, 1);
	}

	if(close(fd)==-1){
		sprintf(errmsg, "searched_index_finalize: close: %s", strerror(errno));
		will_and_die(errmsg, 1);
	}

	return;
}

uint64_t tale_to_searched_index_no(tale_t tale)
{
	int i;
	uint64_t no=0;

	for(i=0; i<X*X; i++){
		no<<=1;
		if(tale[i])
			no|=(uint64_t)1;
	}

	return no;
}

_Bool searched_index_if_index_searched(uint64_t no)
{
	return searched_index[no/8] & ((uint8_t)1 << no%8);
}

void searched_index_set_index_searched(uint64_t no)
{
	searched_index[no/8]|=(uint8_t)1 << no%8;
	return;
}
