#include <stdio.h>

int main() {
	union some {
		int i;
		short sh;
	};
	union some thing;
	thing.i = 1;
	if (thing.sh == 1) {
		printf("liltle endean\n");
	} else {
		printf("big endean");
	};
	return 0;
}
