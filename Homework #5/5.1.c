#include <stdio.h>

int bitAnd(int x, int y) {
	return (~(~x | ~y));
};

int bitXor(int x, int y) {
	return (~(~(~x & y) & ~(x & ~y)));
}

int thirdBits() {
	return (((36 << 8) + 146 << 8) + 73 << 8) + 36;
}
	
int fitsBits(int x, int n) {
	return !(((x << (~n + 33)) >> (~n + 33)) ^ x);
}

int sign(int x) {
	return ((x >> 31) | (!!x));
}

int getByte(int x, int n) {
	return (x >> (n << 3)) & 255;
}

int logicalShift(int x, int n) {
	return (x >> n) & (~(~1 << ~(~31 + n)));
}

int addOK(int x, int y) {
	return !((((x >> 24) & 255) + ((y >> 24) & 255) + (((x & ~(255 << 24)) + (y & ~(255 << 24))) >> 24)) >> 8);

}

int bang(int x) {
	return (((~x) + 1) | x) + 1;
}

int conditional(int x, int y, int z) {
	return y + ((z + 1 + ~y) & ((~(!x) + 1) >> 1));
}

int isPower2(int x) {
	return !!x & !(x >> 31) & !(x & (~0 + x));
}

int main() {
/*
	printf("\n\tПримеры реализаций функций:\n\n");
	
	printf("bitAnd(6, 5):\t\t\t%d\n\n", bitAnd(6, 5));
	
	printf("bitXor(4, 5):\t\t\t%d\n\n", bitXor(4, 5));
	
	printf("thirdBits:\t\t\t%d\n\n", thirdBits());
	
	printf("fitsBits(5, 3):\t\t\t%d\n", fitsBits(5, 3));
	printf("fitsBits(-4, 3):\t\t%d\n\n", fitsBits(-4, 3));
	
	printf("sign(130):\t\t\t%d\n", sign(130));
	printf("sign(-23):\t\t\t%d\n", sign(-23));
	printf("sign(0):\t\t\t%d\n\n", sign(0));
	
	printf("getByte(0x12345678, 1):\t\t0x%x\n\n", getByte(0x12345678, 1));
	
	printf("logicalShift(0x87654321, 4):\t0x%x\n\n", logicalShift(0x87654321, 4));
	
	printf("addOK(0x80000000,0x80000000)\t%d\n", addOK(0x80000000,0x80000000));
	printf("addOK(0x80000000,0x70000000)\t%d\n\n", addOK(0x80000000,0x70000000));
	
	printf("bang(3):\t\t\t%d\n", bang(3));
	printf("bang(0):\t\t\t%d\n\n", bang(0));
	
	printf("conditional(2, 4, 5):\t\t%d\n", conditional(2, 4, 5));
	printf("conditional(0, 4, 5):\t\t%d\n\n", conditional(0, 4, 5));
	
	printf("isPower2(5):\t\t\t%d\n", isPower2(5));
	printf("isPower2(8):\t\t\t%d\n", isPower2(8));
	printf("isPower2(0):\t\t\t%d\n\n", isPower2(0));
	
	printf("\n");
*/
	return 0;
};
