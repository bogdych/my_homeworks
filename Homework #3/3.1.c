#include <stdio.h>

int main() {
	union some {
		int i;
		short sh;
	};
	union some thing;
	thing.i = 1;
	printf("%s\n", thing.sh == 0 ? "big-endian" : "little-endian");
	return 0;
}
