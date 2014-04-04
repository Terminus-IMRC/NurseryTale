#include "def.h"

static struct coordsAndSteps coordsAndSteps[X*2+2];

void mod_coordsAndSteps_init()
{
	int ident;

	for(ident=0; ident<X*2+2; ident++)
		if(ident>=0 && ident<X){
			coordsAndSteps[ident].x_init=ident;
			coordsAndSteps[ident].y_init=0;
			coordsAndSteps[ident].x_step=0;
			coordsAndSteps[ident].y_step=1;
		}else if(ident<X*2){
			coordsAndSteps[ident].x_init=0;
			coordsAndSteps[ident].y_init=ident-X;
			coordsAndSteps[ident].x_step=1;
			coordsAndSteps[ident].y_step=0;
		}else
			switch(ident){
				case X*2:
					coordsAndSteps[ident].x_init=0;
					coordsAndSteps[ident].y_init=0;
					coordsAndSteps[ident].x_step=1;
					coordsAndSteps[ident].y_step=1;
					break;
				case X*2+1:
					coordsAndSteps[ident].x_init=X-1;
					coordsAndSteps[ident].y_init=0;
					coordsAndSteps[ident].x_step=-1;
					coordsAndSteps[ident].y_step=1;
					break;
				default:
					will_and_die("mod_coordsAndSteps_init: no way", 1);
			}

	return;
}

void mod_coordsAndSteps(struct coordsAndSteps *ret, int ident)
{
	memcpy(ret, &coordsAndSteps[ident], sizeof(struct coordsAndSteps));

	return;
}
