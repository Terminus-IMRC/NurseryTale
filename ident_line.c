#include "def.h"

tale_t ident_line[X*2+2];

void ident_line_init()
{
	int ident, i, j;
	struct coordsAndSteps cas;

	for(ident=0; ident<X*2+2; ident++){
		ident_line[ident]=tale_alloc();
		mod_coordsAndSteps(&cas, ident);

		for(i=cas.x_init+cas.y_init*X, j=0; j<X; i+=cas.x_step+cas.y_step*X, j++)
			ident_line[ident][i]=1;
	}

	return;
}

void ident_line_finalize()
{
	int i;

	for(i=0; i<X*2+2; i++)
		tale_destroy(ident_line[i]);

	return;
}
