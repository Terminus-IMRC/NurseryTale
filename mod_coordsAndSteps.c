#include "def.h"

static struct coordsAndSteps coordsAndSteps[X*2+2];

void mod_coordsAndSteps_init()
{
	int ident;

	for(ident=0; ident<X*2+2; ident++)
		if(ident>=0 && ident<X){
			coordsAndSteps[ident].xy_init=ident;
			coordsAndSteps[ident].xy_step=X;
		}else if(ident<X*2){
			coordsAndSteps[ident].xy_init=(ident-X)*X;
			coordsAndSteps[ident].xy_step=1;
		}else
			switch(ident){
				case X*2:
					coordsAndSteps[ident].xy_init=0;
					coordsAndSteps[ident].xy_step=1+X;
					break;
				case X*2+1:
					coordsAndSteps[ident].xy_init=X-1;
					coordsAndSteps[ident].xy_step=-1+X;
					break;
				default:
					will_and_die("mod_coordsAndSteps_init: no way", 1);
			}

	return;
}

void mod_coordsAndSteps(struct coordsAndSteps *ret, int ident)
{
	*ret=coordsAndSteps[ident];

	return;
}
