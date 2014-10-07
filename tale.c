#include "def.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

static tale_t tale;
static tale_t tale_def_0dim, *tale_def_1dim, **tale_def;
static _Bool ident_used[X*2+2];
static FILE *tale_output_fp;

void tale_init(int max_level)
{
	int i;
	char errmsg[0xffff];

	tale=tale_alloc();
	tale_clean(tale);
	tale_output_fp=stdout;

	tale_def_0dim=(tale_t)malloc(2*max_level*(X*X)*sizeof(tale_element_t));
	if(!tale_def_0dim){
		sprintf(errmsg, "tale_init: malloc: %s", strerror(errno));
		will_and_die(errmsg, 1);
	}

	tale_def_1dim=(tale_t*)malloc(2*max_level*sizeof(tale_t));
	if(!tale_def_1dim){
		sprintf(errmsg, "tale_init: malloc: %s", strerror(errno));
		will_and_die(errmsg, 1);
	}

	tale_def=(tale_t**)malloc(2*sizeof(tale_t*));
	if(!tale_def){
		sprintf(errmsg, "tale_init: malloc: %s", strerror(errno));
		will_and_die(errmsg, 1);
	}

	for(i=0; i<2*max_level; i++)
		tale_def_1dim[i]=tale_def_0dim+i*(X*X);

	for(i=0; i<2; i++)
		tale_def[i]=tale_def_1dim+i*max_level;

	for(i=0; i<X*2+2; i++)
		ident_used[i]=0;

	return;
}

void tale_finalize()
{
	tale_destroy(tale);

	free(tale_def);
	free(tale_def_1dim);
	free(tale_def_0dim);

	return;
}

void tell_me_a_nursery_tale(int level, int max_level, enum nt_from nf)
{
	int i;
	int nfe;
	int add;
	_Bool ident_used_already_used=0;
	uint64_t no;

	switch(nf){
		case NT_FROM_MAIN:
			nfe=0;
			break;
		case NT_FROM_ME:
			nfe=1;
			break;
		default:
			will_and_die("invalid nf value", 1);
			break;
	}

	/*printf("nt(%d):entering nt:%s\n", level, nf==NT_FROM_MAIN?"MAIN":"ME");*/

	tale_cp(tale_def[nfe][level], tale);

	switch(nfe){
		case 0:
			add=1;
			break;
		case 1:
			add=-1;
			break;
	}

	for(i=0; i<X*2+2; i++){
		if(nfe==0){
			if(ident_used[i])
				ident_used_already_used=!0;
			ident_used[i]=!0;
		}else{
			if(ident_used[i])
				continue;
		}

		/*printf("nt(%d):adopting i:%d\n", level, i);*/
		tale_adopt_line_by_identifier(tale, i, add);

		if(level!=max_level-1)
			tell_me_a_nursery_tale(level+1, max_level, nf);
		else
			switch(nfe){
				case 0:
					tell_me_a_nursery_tale(0, max_level, NT_FROM_ME);
					break;
				case 1:
					no=tale_to_searched_index_no(tale);
					if(!searched_index_if_index_searched(no))
						tale_output(tale);
					searched_index_set_index_searched(no);
					break;
			}

		if((nfe==0)&&(!ident_used_already_used))
			ident_used[i]=0;

		tale_cp(tale, tale_def[nfe][level]);
	}

	return;
}

tale_t tale_alloc()
{
	tale_t t;
	char errmsg[0xffff];

	t=(tale_t)malloc((X*X)*sizeof(tale_element_t));
	if(!t){
		sprintf(errmsg, "tale_alloc: malloc: %s", strerror(errno));
		will_and_die(errmsg, 1);
	}

	return t;
}

void tale_destroy(tale_t t)
{
	free(t);

	return;
}

void tale_cp(tale_t dst, tale_t src)
{
	memcpy(dst, src, (X*X)*sizeof(tale_element_t));

	return;
}

void tale_clean(tale_t t)
{
	memset(t, (int8_t)0, (X*X)*sizeof(tale_element_t));

	return;
}

void tale_adopt_line_by_identifier(tale_t t, int ident, int add)
{
	int i;
	struct coordsAndSteps cas;

	mod_coordsAndSteps(&cas, ident);

	for(t+=cas.xy_init, i=0; i<X; t+=cas.xy_step, i++)
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
