#include "def.h"

int main()
{
	int max_level;

	tale_init();
	for(max_level=0; max_level<X*X+2 /* NOTICE */; max_level++)
		tell_me_a_nursery_tale(0, max_level+1, NT_FROM_MAIN);

	return 0;
}
