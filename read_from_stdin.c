#include <stdio.h>
#include <string.h>

int main()
{
  char temp[100];

  while (fgets(temp, sizeof temp, stdin) != NULL)
  {
    printf("%s", temp);
  }

  return 0;
}
