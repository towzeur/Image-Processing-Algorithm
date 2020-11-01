#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_GRAY 256

#define IO_DEFAULT_FILENAME "images/Tour_Eiffel_Japon"
#define IR_DEFAULT_FILENAME "out/sobel"
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

void exitError(const char *message) {
  printf("Error : %s\n", message);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  // file related var
  long int n_col, n_row, nbg, n_tot;
  char *io_fname, *ir_fname;
  FILE *io_file, *ir_file;
  int *io, *ir;

  unsigned char chi;
  char string[10];
  register long int r, c;

  int hx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int hy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
  int dr, dc, sumy, sumx, mmax;

  // ==========================================================================
  // open input and output files
  // ==========================================================================

  // default values for io_fname and ir_fname
  io_fname = getFilename((argc > 1) ? argv[1] : IO_DEFAULT_FILENAME);
  if (io_fname == NULL)
    exitError("io_fname malloc failed");
  ir_fname = getFilename((argc > 2) ? argv[2] : IR_DEFAULT_FILENAME);
  if (ir_fname == NULL)
    exitError("ir_fname malloc failed");

  printf("io_fname : %s\n", io_fname);
  printf("ir_fname : %s\n", ir_fname);

  // open FILE descriptor
  if ((io_file = fopen(io_fname, "rb")) == NULL)
    exitError("can't open input file");
  if ((ir_file = fopen(ir_fname, "wb+")) == NULL)
    exitError("can't create output file");

  // ==========================================================================
  // read pgm header from io and write it to ir
  // ==========================================================================

  // read magic value
  fscanf(io_file, "%s\n", string);
  if (strcmp(string, "P5") != 0)
    exitError("magic value different from 'P5' or 'P2' : not a pgm file !");
  fprintf(ir_file, "%s\n", string);

  // read comment (line starts with '#')
  do {
    chi = fgetc(io_file);
    fputc(chi, ir_file);
  } while (chi != '\n');

  // read and paste n_col and n_row
  fscanf(io_file, "%ld %ld\n", &n_col, &n_row);
  fprintf(ir_file, "%ld %ld\n", n_col, n_row);

  // read and paste nbg
  fscanf(io_file, "%ld\n", &nbg);
  fprintf(ir_file, "%ld\n", nbg);
  if (nbg != N_GRAY - 1)
    exitError("io color depth different from N_GRAY - 1");

  n_tot = n_col * n_row;
  printf("n_col=%ld n_row=%ld nbg=%ld n_tot=%ld\n", n_col, n_row, nbg, n_tot);

  // ==========================================================================
  // prepare io and ir array
  // ==========================================================================

  // dynamic allocation of io and ir array
  io = (int *)malloc(n_col * n_row * sizeof(int));
  ir = (int *)malloc(n_col * n_row * sizeof(int));
  if (io == NULL || ir == NULL)
    exitError("malloc failed");

  // copy io_file pixels to io
  for (r = 0; r < n_row; r++) {
    for (c = 0; c < n_col; c++) {
      chi = (unsigned char)fgetc(io_file);
      io[r * n_col + c] = (int)chi;
      ir[r * n_col + c] = 0;
    }
  }

  // ==========================================================================
  // Processing
  // ==========================================================================

  // convolve with the 3×3 kernels to calculate approximations of the
  // derivatives
  for (r = 1; r < n_row - 1; r++) {
    for (c = 1; c < n_col - 1; c++) {
      sumx = 0;
      sumy = 0;
      for (dr = -1; dr < 2; dr++) {
        for (dc = -1; dc < 2; dc++) {
          sumx = sumx + hx[dr + 1][dc + 1] * io[(r + dr) * n_col + (c + dc)];
          sumy = sumy + hy[dr + 1][dc + 1] * io[(r + dr) * n_col + (c + dc)];
        }
      }
      ir[r * n_col + c] = abs(sumx) + abs(sumy); // L1 norm
      // ir[r * n_col + c] = (int)sqrt(sumx * sumx + sumy * sumy);
    }
  }

  // find ir global (2d) max
  mmax = ir[0];
  for (r = 1; r < n_row - 1; r++) {
    for (c = 1; c < n_col - 1; c++) {
      if (ir[r * n_col + c] > mmax)
        mmax = ir[r * n_col + c];
    }
  }

  // normalization
  for (r = 1; r < n_row - 1; r++) {
    for (c = 1; c < n_col - 1; c++) {
      ir[r * n_col + c] =
          (int)((((long int)ir[r * n_col + c]) * N_GRAY) / mmax);
    }
  }

  // ==========================================================================
  // Processing
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
