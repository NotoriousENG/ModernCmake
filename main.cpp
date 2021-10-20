#include <adder.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("Hello cmake\n");

	printf("%f\n", add(42.12f, 3.f));

	return 0;
}
