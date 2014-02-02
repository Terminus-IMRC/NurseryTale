#include "def.h"

struct coordsAndSteps* mod_coordsAndSteps(int ident)
{
	struct coordsAndSteps *ret;
	ret=(struct coordsAndSteps*)malloc(sizeof(struct coordsAndSteps));

	if(ident>=0 && ident<X){
		ret->x_init=ident;
		ret->y_init=0;
		ret->x_step=0;
		ret->y_step=1;
	}else if(ident<X*2){
		ret->x_init=0;
		ret->y_init=ident-X;
		ret->x_step=1;
		ret->y_step=0;
	}else
		switch(ident){
			case X*2:
				ret->x_init=0;
				ret->y_init=0;
				ret->x_step=1;
				ret->y_step=1;
				break;
			case X*2+1:
				ret->x_init=X-1;
				ret->y_init=0;
				ret->x_step=-1;
				ret->y_step=1;
				break;
			default:
				will_and_die("mod_coordsAndSteps: passed unknown identifier", 1);
				/* Never returns */
		}

	return ret;
}
