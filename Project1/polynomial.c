#include <stdio.h>

#pragma warning(disable : 4996)

#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX 100

void padd_h(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
void attach(int coefficient, int exponent);

typedef struct
{
	int coef;
	int expon;
} Polynomial_term;

typedef struct
{
	int degree;
	int coef[MAX + 1];
} Polynomial_coef;

Polynomial_term terms[MAX];
Polynomial_coef B;

int avail = 0;

int main()
{
	int i, nA;
	int startA, finishA, startB, finishB, startD, finishD;
	int zero_1 = 0, zero_2 = 0;

	printf("Enter A(x):\n\n");

	printf("계수가 0이 아닌 항의 수?: ");
	scanf("%d", &nA);

	startA = 0;
	finishA = nA - 1;

	for (i = startA; i <= finishA; i++)
	{
		printf("계수?: ");
		scanf("%d", &terms[i].coef);

		printf("지수?: ");
		scanf("%d", &terms[i].expon);
	}

	printf("\n");

	printf("Enter B(x):\n\n");

	printf("최고차 항의 지수는?: ");
	scanf("%d", &B.degree);

	startB = nA;
	finishB = startB + B.degree;

	int B_degree = B.degree;

	for (i = startB; i <= finishB; i++)
	{
		printf("%d번째 항의 계수?: ", zero_1);
		scanf("%d", &B.coef[zero_1]);

		zero_1 = zero_1 + 1;
	}

	printf("\n");

	printf("A(x) : ");

	for (i = startA; i <= finishA; i++)
	{
		if (terms[i].expon == 0)
		{
			printf("%d", terms[i].coef);
			break;
		}
		else
			printf("%dx^%d + ", terms[i].coef, terms[i].expon);
	}

	printf("\n\n");

	printf("B(x) : ");

	for (i = startB; i <= finishB; i++)
	{
		if (B_degree == 0)
		{
			printf("%d", B.coef[zero_2]);
		}
		else
			printf("%dx^%d + ", B.coef[zero_2], B_degree);

		B_degree = B_degree - 1;
		zero_2 = zero_2 + 1;
	}

	printf("\n\n");

	avail = finishB + 1;

	padd_h(startA, finishA, startB, finishB, &startD, &finishD);

	printf("다항식 A(x) + B(x) = ");

	for (i = startD; i <= finishD; i++)
	{
		if (terms[i].expon == 0)
			printf("%d", terms[i].coef);
		else
			printf("%dx^%d + ", terms[i].coef, terms[i].expon);
	}

	printf("\n");
}

void padd_h(int startA, int finishA, int startB, int finishB, int* startD, int* finishD)
{
	int coefficient;
	int zero_3 = 0, zero_4 = 0;

	*startD = avail;

	while (startA <= finishA && B.degree >= 0)
	{
		switch (COMPARE(terms[startA].expon, B.degree))
		{
		case -1:
			attach(B.coef[zero_3], B.degree);

			B.degree = B.degree - 1;
			zero_3 = zero_3 + 1;

			break;

		case 0:
			coefficient = terms[startA].coef + B.coef[zero_3];

			if (coefficient)
				attach(coefficient, terms[startA].expon);

			startA++;

			B.degree = B.degree - 1;
			zero_3 = zero_3 + 1;

			break;

		case 1:
			attach(terms[startA].coef, terms[startA].expon);

			startA++;
		}
	}

	*finishD = avail - 1;
}

void attach(int coefficient, int exponent)
{
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}