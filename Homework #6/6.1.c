#include <stdio.h>
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
		double f = pow(2, mantissaLength);
		f = (double)mantissa / f;
		int accuracy = 0;
		int zeros = (mantissa - 1) & (~mantissa);
		while (zeros & accuracy < 23) {
			accuracy++;
			zeros = zeros >> 1;
		}
		accuracy = mantissaLength - accuracy;
		int deg = exp - 127;
		printf("    %d   %d\n", sign, deg);
		printf("(-1) * 2", sign);
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
		printf("* %.*f\n", accuracy, 1.0 + f);
	}
}

void firstMethod(float f) {
	union {
		float fl;
		int i;
	} un;

	un.fl = f;
	int sign = (un.i >> 31) & 1;
	int exp = (un.i >> mantissaLength) & 0xff ;
	int mantissa = un.i & ((1 << mantissaLength) - 1);
	printFloat(sign, exp, mantissa);
}

void secondMethod(float f) {
	union {
		float fl;
		struct {
			unsigned int mantissa : 23;
			unsigned int exp : 8;
			unsigned int sign : 1;
		} s;
	} un;
	un.fl = f;
	printFloat(un.s.sign, un.s.exp, un.s.mantissa);
}

void thirdMethod(float f) {
	float *p = &f;
	int i = *((int *)p);

	int sign = (i >> 31) & 1;
	int exp = (i >> mantissaLength) & 0xff;
	int mantissa = i & ((1 << mantissaLength) - 1);
	printFloat(sign, exp, mantissa);
}

struct Method {
	char *description;
	void(*doAction)(float);
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
		printf("Please enter 2 numbers with floating point.\n");
		printf("Divident: ");
		scanf_s("%f", &f1);
		printf("Divisor:  ");
		scanf_s("%f", &f2);
		int meth;
		int methodsCount = sizeof(methods) / sizeof(struct Method);
		printf("Choose method of finding of quotient:\n");
		for (int i = 0; i < methodsCount; i++) {
			printf("%d. %s\n", i + 1, methods[i].description);
		}
		float f = f1 / f2;
		scanf_s("%d", &meth);
		methods[meth - 1].doAction(f);
	}
	else {
		printf("I don't know why, but the size of float is not 4 bytes on your system :(");
	}
}