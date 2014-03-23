#include "def.h"
#include <assert.h>
#include <stdio.h>

tale_t tale;
FILE *tale_output_fp;

void tale_init()
{
	tale=tale_alloc();
	tale_clean(tale);
	tale_output_fp=stdout;

	return;
}

void tale_finalize()
{
	tale_destroy(tale);

	return;
}

void tell_me_a_nursery_tale(int level, int max_level, enum nt_from nf)
{
	int i;
	int add;
	tale_t tale_def;
	uint64_t no;

	/*printf("nt(%d):entering nt:%s\n", level, nf==NT_FROM_MAIN?"MAIN":"ME");*/

	tale_def=tale_alloc();
	tale_cp(tale_def, tale);

	switch(nf){
		case NT_FROM_MAIN:
			add=1;
			break;
		case NT_FROM_ME:
			add=-1;
			break;
		default:
			will_and_die("invalid nf value", 1);
			break;
	}

	for(i=0; i<X*2+2; i++){
		/*printf("nt(%d):adopting i:%d\n", level, i);*/
		tale_adopt_line_by_identifier(tale, i, add);

		if(level!=max_level-1)
			tell_me_a_nursery_tale(level+1, max_level, nf);
		else
			switch(nf){
				case NT_FROM_MAIN:
					tell_me_a_nursery_tale(0, max_level, NT_FROM_ME);
					break;
				case NT_FROM_ME:
					no=tale_to_searched_index_no(tale);
					if(!searched_index_if_index_searched(no))
						tale_output(tale);
					searched_index_set_index_searched(no);
					break;
				default:
					will_and_die("someone changed nf value", 1);
					break;
			}

		/* TODO: use tale_disadopt_line_by_identifier() for speed-up */
		tale_cp(tale, tale_def);
	}

	tale_destroy(tale_def);

	return;
}

tale_t tale_alloc()
{
	tale_t t;

	t=(tale_t)malloc((X*X)*sizeof(tale_element_t));
	assert(t);

	return t;
}

void tale_destroy(tale_t t)
{
	free(t);

	return;
}

void tale_cp(tale_t dst, tale_t src)
{
	int i;

	for(i=0; i<X*X; i++)
		dst[i]=src[i];

	return;
}

void tale_clean(tale_t t)
{
	int i;

	for(i=0; i<X*X; i++)
		t[i]=0;

	return;
}

void tale_adopt_line_by_identifier(tale_t t, int ident, int add)
{
	int i;
	struct coordsAndSteps cas;

	mod_coordsAndSteps(&cas, ident);

	for(t+=cas.x_init+cas.y_init*X, i=0; i<X; t+=cas.x_step+cas.y_step*X, i++)
		*t+=add;

	return;
}

void tale_set_output_fp(FILE *fp)
{
	tale_output_fp=fp;

	return;
}

void tale_output(tale_t t)
{
	int i;

	for(i=0; i<X*X; i++)
		fprintf(tale_output_fp, "%d%c", t[i], i!=X*X-1?' ':'\n');

	return;
}
