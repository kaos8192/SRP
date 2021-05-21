#include "SRP.h"
#include <stdio.h>

int main(){
	mc_init();
	float r= 0;
	float s= 0;
	float p = 0;
	float times = 100000;
	for(int i = 0; i < times; ++i){
		mc_play('p');
		char c = mc_getPlay();
		if(c == 'p'){
			p += 1;
		}else if(c == 'r'){
			r += 1;
		}else{
			s += 1;
		}
	}
	printf("s:%f r:%f p:%f\n",s/times, r/times, p/times);
	mc_print();
	mc_destroy();
}
