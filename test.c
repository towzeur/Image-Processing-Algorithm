#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IO_DEFAULT_FILENAME "images/Tour_Eiffel_Japon"
#define IR_DEFAULT_FILENAME "images/out"
#define I_EXT ".pgm"

char *getFilename(const char *filename)
{
  size_t f_name_len = strlen(filename) + strlen(I_EXT) + (size_t)1;
  char *file_ext = calloc(f_name_len, sizeof(char));
  strcat(file_ext, filename);
  strcat(file_ext, I_EXT);
  return file_ext;
}

int main(int argc, char *argv[])
{
  printf("argc : %d\n", argc);
  char *io_fname = getFilename((argc > 1) ? argv[1] : IO_DEFAULT_FILENAME);
  char *ir_fname = getFilename((argc > 2) ? argv[2] : IR_DEFAULT_FILENAME);

  printf("name : %s\n", ir_fname);
  printf("\n");
  free(io_fname);
  return EXIT_SUCCESS;
}
