#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_GRAY 256

#define IO_DEFAULT_FILENAME "images/Tour_Eiffel_Japon"
#define IR_DEFAULT_FILENAME "images/out"
#define I_EXT ".pgm"

char *getFilename(const char *filename) {
  size_t f_name_len = strlen(filename) + strlen(I_EXT) + (size_t)1;
  char *file_ext = calloc(f_name_len, sizeof(char));
  if (file_ext != NULL) {
    strcat(file_ext, filename);
    strcat(file_ext, I_EXT);
  }
  return file_ext;
}

int main(int argc, char *argv[]) {
  // file related var
  long int n_col, n_row, n_tot;
  char *io_fname, *ir_fname;
  FILE *io_file, *ir_file;
  int *io, *ir;
  // stack var
  unsigned char chi;
  char string[10];
  long int k, nbg;
  register long int r, c;

  long int hist[N_GRAY], histc[N_GRAY];
  int LUT[N_GRAY];

  // default values for io_fname and ir_fname
  io_fname = getFilename((argc > 1) ? argv[1] : IO_DEFAULT_FILENAME);
  if (io_fname == NULL)
    return EXIT_FAILURE;
  ir_fname = getFilename((argc > 2) ? argv[2] : IR_DEFAULT_FILENAME);
  if (ir_fname == NULL)
    return EXIT_FAILURE;

  printf("io_fname : %s \n", io_fname);
  printf("ir_fname : %s \n", ir_fname);

  // prepare files
  if ((io_file = fopen(io_fname, "rb")) == NULL) {
    printf("Error : can't open input file\n");
    return EXIT_FAILURE;
  }
  if ((ir_file = fopen(ir_fname, "wb+")) == NULL) {
    printf("Error : can't create output file\n");
    return EXIT_FAILURE;
  }

  // lecture entete pgm
  fscanf(io_file, "%s\n", string);
  fprintf(ir_file, "%s\n", string);

  r = 0;
  while (r < 1) {
    chi = fgetc(io_file);
    fputc(chi, ir_file);
    if (chi == '\n')
      r++;
  }

  fscanf(io_file, "%ld %ld\n", &n_col, &n_row);
  fprintf(ir_file, "%ld %ld\n", n_col, n_row);

  fscanf(io_file, "%ld\n", &nbg);
  fprintf(ir_file, "%ld\n", nbg);

  n_tot = n_col * n_row;
  printf("n_col=%ld n_row=%ld nbg=%ld n_tot=%ld\n", n_col, n_row, nbg, n_tot);

  // allocation dynamique de m�moire des images io et ir
  io = (int *)malloc(n_col * n_row * sizeof(int));
  ir = (int *)malloc(n_col * n_row * sizeof(int));
  if (io == NULL || ir == NULL)
    printf("Error : malloc failed \n");

  // read i0 pixels
  for (r = 0; r < n_row; r++) {
    for (c = 0; c < n_col; c++) {
      chi = (unsigned char)fgetc(io_file);
      io[r * n_col + c] = (int)chi;
    }
  }

  // ==========================================================================
  // Processing
  // ==========================================================================

  // histogram init
  for (k = 0; k < N_GRAY; k++)
    hist[k] = 0;

  // histogram construction
  for (r = 0; r < n_row; r++) {
    for (c = 0; c < n_col; c++) {
      hist[io[r * n_col + c]]++;
    }
  }

  // cumulated histogram construction
  histc[0] = hist[0];
  for (k = 1; k < N_GRAY; k++)
    histc[k] = histc[k - 1] + hist[k];

  // Histogram equalization
  for (k = 0; k < N_GRAY; k++)
    LUT[k] = (int)((histc[k] * (long int)(N_GRAY - 1)) / n_tot);

  for (r = 0; r < n_row; r++) {
    for (c = 0; c < n_col; c++) {
      ir[r * n_col + c] = LUT[io[r * n_col + c]];
    }
  }

  // ==========================================================================

  // paste ir to ir_file
  for (r = 0; r < n_row; r++) {
    for (c = 0; c < n_col; c++) {
      fputc((unsigned char)ir[r * n_col + c], ir_file);
    }
  }

  // free
  free(io_fname);
  free(ir_fname);
  free(io);
  free(ir);
  fclose(io_file);
  fclose(ir_file);

  return EXIT_SUCCESS;
}
