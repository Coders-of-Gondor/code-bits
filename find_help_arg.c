#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		printf("%d. arg = %s\n", i, argv[i]);
		if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
		{
			printf("Print help\n");
		}
	}
	return 0;
}
