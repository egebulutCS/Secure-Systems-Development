#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *read_file(char *filename) {
  // Open the file and declare local variables
  FILE *f = fopen(filename, "rb");
  size_t length;
  char *output;
  size_t i;

  // Find the length of the file and allocate
  // the required quantity of space on the heap
  fseek(f, 0, SEEK_END);
  length = ftell(f);
  fseek(f, 0, SEEK_SET);
  output = (char *)malloc(length + 1);

  // Populate the space on the heap
  for (i = 0; i < length; i++) {
    output[i] = fgetc(f);
  }

  output[i] = 0;

  // Close the file and return
  fclose(f);

  return output;
}

/*
 * This function is vulnerable to a
 * stack smashing attack!
 */
void func(char *string) {
  char buffer[80];
  int number;

  // This is just here to pause the
  // program while we attach the
  // debugger!
  getchar();
  strcpy(buffer, string);
}

int main() {
  char *buffer = read_file("hello");

  printf("%s\n", buffer);
  func(buffer);

  free(buffer);

  return 0;
}
