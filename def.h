#ifndef __DEF_INSIDE__
#define __DEF_INSIDE__

#include <stdio.h>
#include <stdlib.h>

	struct coordsAndSteps{
		int x_init, y_init;
		int x_step, y_step;
	};

	enum nt_from{
		NT_FROM_MAIN, NT_FROM_ME
	};

	typedef int tale_element_t;
	typedef tale_element_t* tale_t;

	void mod_coordsAndSteps(struct coordsAndSteps *ret, int ident);
	void will_and_die(const char *str, const int exitno);
	void tale_init();
	void tell_me_a_nursery_tale(int level, int max_level, enum nt_from nf);
	tale_t tale_alloc();
	void tale_destroy(tale_t t);
	void tale_cp(tale_t dst, tale_t src);
	void tale_clean(tale_t t);
	void tale_adopt_line_by_identifier(tale_t t, int ident, int add);
	void tale_set_output_fp(FILE *fp);
	void tale_output(tale_t t);
#endif
