#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_GRAY 256

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
  long int n_col, n_row, n_tot;
  char *io_fname, *ir_fname;
  int *io, *ir;
  FILE *io_file, *ir_file;

  unsigned char chi;
  char chaine[10];
  long int k = 3, s = 1, nbg;
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
  if ((io_file = fopen(io_fname, "rb")) == NULL)
  {
    printf("Error : can't open input file\n");
    return EXIT_FAILURE;
  }
  if ((ir_file = fopen(ir_fname, "wb+")) == NULL)
  {
    printf("Error : can't create output file\n");
    return EXIT_FAILURE;
  }

  // lecture entete pgm
  fscanf(io_file, "%s\n", chaine);
  fprintf(ir_file, "%s\n", chaine);

  r = 0;
  while (r < 1)
  {
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

  ///////////////////////////////////////////////////////////////////
  // TRAITEMENT

  /*
  // histogram init
  for (k = 0; k < N_GRAY; k++)
    hist[k] = 0;
  // histogram construction
  for (c = 0; c < n_col; c++)
    for (r = 0; r < n_row; r++)
      hist[io[c * n_col + r]]++;
  */

  int count = 0;
  for (r = 0; r < n_row; r++)
  {
    for (c = 0; c < n_col; c++)
    {
      ir[r * n_col + c] = io[r * n_col + c];
      count++;
    }
  }

  printf("elo %d\n", count);

  // FIN TRAITEMENT
  ///////////////////////////////////////////////////////////////////

  // Sauvegarde de l image r�sultat dans le fichier ir_file
  for (r = 0; r < n_row; r++)
  {
    for (c = 0; c < n_col; c++)
    {
      fputc((unsigned char)ir[r * n_col + c], ir_file);
    }
  }

  // lib�ration de de la m�moire des tableaux io et ir et fermeture des 2
  // fichiers io_file et ir_file
  free(io_fname);
  free(ir_fname);
  free(io);
  free(ir);
  fclose(io_file);
  fclose(ir_file);

  return EXIT_SUCCESS;
}
