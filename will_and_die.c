#include "def.h"
#include <stdlib.h>

void will_and_die(const char *str, const int exitno)
{
	fprintf(stderr, "In the nursery tale, Terminus said following:\n%s\n", str);
	exit(exitno);
}
