#include "def.h"

int main()
{
	int max_level;

	tale_init();
	searched_index_init();
	for(max_level=0; max_level<(X*2+2)/2; max_level++)
		tell_me_a_nursery_tale(0, max_level+1, NT_FROM_MAIN);

	searched_index_finalize();

	return 0;
}
