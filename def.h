#ifndef __DEF_INSIDE__
#define __DEF_INSIDE__

#include <stdio.h>
#include <stdlib.h>

	struct coordsAndSteps{
		int x_init, y_init;
		int x_step, y_step;
	};

	void mod_coordsAndSteps(struct coordsAndSteps *ret, int ident);
	void will_and_die(const char *str, const int exitno);
#endif
