#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_STR_LENGTH 30
#define N_GRAY 256
#define IO_DEFAULT_FILENAME "images/Tour_Eiffel_Japon"
#define IR_DEFAULT_FILENAME "images/out"
#define I_EXT ".pgm"

int main(int argc, char *argv[]) {
  long int n_col, n_row, n_tot;
  int *io, *ir;
  FILE *io_f, *ir_f;
  char *io_fname, *ir_fname;
  size_t io_fname_size, ir_fname_size;

  unsigned char chi;
  char chaine[10];
  long int k = 3, s = 1, nbg;
  register long int r, c;

  long int hist[N_GRAY], histc[N_GRAY];
  int LUT[N_GRAY];

  // default values for io_fname and ir_fname
  io_fname_size = strlen(IO_DEFAULT_FILENAME) + strlen(I_EXT) + 1;
  io_fname = (char *)malloc(io_fname_size);
  strcpy(io_fname, IO_DEFAULT_FILENAME);
  strcat(io_fname, I_EXT);

  ir_fname_size = strlen(IR_DEFAULT_FILENAME) + strlen(I_EXT) + 1;
  ir_fname = (char *)malloc(ir_fname_size);
  strcpy(ir_fname, IR_DEFAULT_FILENAME);
  strcat(ir_fname, I_EXT);

  // strncpy(ir_fname, IR_DEFAULT_FILENAME, strlen(IR_DEFAULT_FILENAME));

  /*
  if (argc > 1) {
    if (argc == 2) {
      strncpy(io_fname, argv[1], strlen(argv[1]));
      // io_fname[FILENAME_STR_LENGTH - 1] = '\0';
    }
    if (argc == 3) {
    }
    if (argc > 3) {
      printf("Error : number of args invalid \n");
      return EXIT_FAILURE;
    }
  }
  */
  // strcat(io_fname, ".pgm");
  // strcat(ir_fname, ".pgm");

  printf("io_fname : %s \n", io_fname);
  if ((io_f = fopen(io_fname, "rb")) == NULL) {
    printf("Error : can't open input file\n");
    return EXIT_FAILURE;
  }
  printf("ir_fname : %s \n", ir_fname);
  if ((ir_f = fopen(ir_fname, "wb+")) == NULL) {
    printf("Error : can't create output file\n");
    return EXIT_FAILURE;
  }

  // lecture entete pgm
  fscanf(io_f, "%s\n", chaine);
  fprintf(ir_f, "%s\n", chaine);

  r = 0;
  while (r < 1) {
    chi = fgetc(io_f);
    fputc(chi, ir_f);
    if (chi == '\n')
      r++;
  }

  fscanf(io_f, "%ld %ld\n", &n_col, &n_row);
  fprintf(ir_f, "%ld %ld\n", n_col, n_row);

  fscanf(io_f, "%ld\n", &nbg);
  fprintf(ir_f, "%ld\n", nbg);

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

  // FIN TRAITEMENT
  ///////////////////////////////////////////////////////////////////

  // Sauvegarde de l image r�sultat dans le fichier ir_f
  for (r = 0; r < n_row; r++)
    for (c = 0; c < n_col; c++)
      fputc((unsigned char)ir[r * n_col + c], ir_f);

  // lib�ration de de la m�moire des tableaux io et ir et fermeture des 2
  // fichiers io_f et ir_f
  free(io_fname);
  free(ir_fname);
  free(io);
  free(ir);
  fclose(io_f);
  fclose(ir_f);

  return EXIT_SUCCESS;
}
