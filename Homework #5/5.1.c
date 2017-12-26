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
	return !(~((x >> 31) ^ (y >> 31)) & ((x >> 31) ^ (x + y >> 31)));
}

int bang(int x) {
	return ~((~x + 1 | x) >> 31) & 1 ;
}

int conditional(int x, int y, int z) {
	return y + ((z + 1 + ~y) & ((~(!x) + 1) >> 1));
}

int isPower2(int x) {
	return !!x & !(x >> 31) & !(x & (~0 + x));
}

int main() {
	return 0;
}