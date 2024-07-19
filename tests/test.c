#include <stdio.h>

int main()
{
  char **array = {"Aiman", "Shehab", "hellow!!!!"};

  printf("%s - %d - %d", **(array), sizeof(*array), sizeof(**array));
  return 0;
}