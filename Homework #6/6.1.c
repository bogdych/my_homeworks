#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int mantissaLength = 23;

void printFloat(int sign, int exp, int mantissa) {
	if ((exp == 255) && (mantissa == 0)) {
		if (sign) {
			printf("-Inf");
		}
		else {
			printf("+Inf");
		}
	}
	else if ((exp == 255) && (((mantissa + 1) >> mantissaLength == 1) || (mantissa >> (mantissaLength - 1) == 1))) {
		printf("NaN");
	}
	else {
		int deg = exp - 127;
		printf("    %d   %d\n", sign, deg);
		printf("(-1) * 2");
		int leng = 1;
		if (deg < 0) {
			leng++;
		};
		deg = abs(deg);
		while (deg != 0) {
			deg = deg / 10;
			leng++;
		}
		for (int i = 0; i < leng; i++) {
			printf(" ");
		}
		float s = 1;
		float t = 1;
		for (int i = 0; i <= 22; i++) 
		{
			int current = mantissa & (1 << 22);
			current = (current>> 22) & 1;
			mantissa = mantissa << 1;
			t = t / 2;
			s += t * current;
		}
		printf(" * %g\n", s);
	}
}


void firstMethod(int *sign, int *exp, int *mantissa, float f) {
	union {
		float fl;
		int i;
	} un;

	un.fl = f;
	*sign = (un.i >> 31) & 1;
	*exp = (un.i >> mantissaLength) & 0xff ;
	*mantissa = un.i & ((1 << mantissaLength) - 1);
}

void secondMethod(int *sign, int *exp, int *mantissa, float f) {
	union {
		float fl;
		struct {
			unsigned int mantissa : 23;
			unsigned int exp : 8;
			unsigned int sign : 1;
		} s;
	} un;
	un.fl = f;
	*sign = un.s.sign;
	*exp = un.s.exp;
	*mantissa = un.s.mantissa;
}

void thirdMethod(int *sign, int *exp, int *mantissa, float f) {
	float *p = &f;
	int i = *((int *)p);

	*sign = (i >> 31) & 1;
	*exp = (i >> mantissaLength) & 0xff;
	*mantissa = i & ((1 << mantissaLength) - 1);
}

struct Method {
	char *description;
	void(*doAction)(int *, int *, int *, float);
};

const struct Method methods[] = {
	{ .description = "Union with int and bit operations",.doAction = firstMethod },
	{ .description = "Union with struct with bit fields",.doAction = secondMethod },
	{ .description = "Taking an address and dereferencing a pointer",.doAction = thirdMethod },
};

void main() {
	if (sizeof(float) == 4) {
		float f1;
		float f2;
		int sign = 0;
		int exp = 0;
		int mantissa = 0;
		printf("Please enter 2 numbers with floating point.\n");
		printf("Divident: ");
		scanf("%f", &f1);
		printf("Divisor:  ");
		scanf("%f", &f2);
		int meth;
		int methodsCount = sizeof(methods) / sizeof(struct Method);
		printf("Choose method of finding of quotient:\n");
		for (int i = 0; i < methodsCount; i++) {
			printf("%d. %s\n", i + 1, methods[i].description);
		}
		printf("0. Exit\n");
		float f = f1 / f2;
		scanf("%d", &meth);
		while (!(meth >= 0 && meth <= 3)) {
			printf("Wrong input. Try again: ");
		}
		if (meth) {
			methods[meth - 1].doAction(&sign, &exp, &mantissa, f);
			printFloat(sign, exp, mantissa);
		}
		else {
			exit(0);
		}
	}
	else {
		printf("I don't know why, but the size of float is not 4 bytes on your system :(");
	}
}