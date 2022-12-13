#include <stdio.h>
#include <stdlib.h>

int problemSolve(int *board, int *index, char *letters, int counter, int pocet,
                 int skok ) {
                  
  for (int i = 0; i < pocet; i++) {
    int z = skok;
    for (int g = 0; g < pocet; g++) {
      if (board[g] != 0)
        continue;
    }
    for (int y = i - 1; y > 0; y--) {
      for (int k = i; k < pocet; k++) {
        z -= board[k];
        if (z < 0)
          break;
      }
      z -= board[y - 1];
      if ((z == 0) && (board[y] == 1)) {
        index[counter] = i;
        letters[counter] = 'L';
        board[i] = 0;
        board[y] = 2;

        if (counter == (pocet / 2) - 1) {
          for (int t = 0; t < (pocet / 2) - 1; t++) {
            printf("%d%c,", index[t], letters[t]);
          }
          printf("%d%c", index[(pocet / 2) - 1], letters[(pocet / 2) - 1]);
          printf("\n");

        } else
          problemSolve(board, index, letters, counter + 1, pocet, skok);
        board[y] = 1;
        board[i] = 1;
      }
    }
    z = skok + 1;
    for (int y = i + 1; y < pocet; y++) {
      z -= board[y - 1];
      for (int l = i - 1; l > 0; l--) {
        for (int l = i; l < pocet; l++) {
          z -= board[l];
          if (z < 0)
            break;
        }
        if ((z == 0) && (board[y] == 1)) {
          index[counter] = i;
          letters[counter] = 'R';
          board[i] = 0;
          board[y] = 2;

          if (counter == (pocet / 2) - 1) {
            for (int t = 0; t < (pocet / 2) - 1; t++) {
              printf("%d%c,", index[t], letters[t]);
            }
            printf("%d%c", index[(pocet / 2) - 1], letters[(pocet / 2) - 1]);
            printf("\n");

          } else{
            problemSolve(board, index, letters, counter + 1, pocet, skok);
           
                board[y] = 1;
                board[i] = 1;
          }
        }
      }
    }
  }
  return 0;
}

int main() {

  int pocet, skok, a, b, counter;
  printf("Pocet sirek:\n");
  a = (scanf("%d", &pocet));
  if ((pocet <= 0) || (a != 1)) {
    printf("Nespravny vstup.\n");
    return 0;
  }

  printf("Velikost skoku:\n");
  b = (scanf("%d", &skok));
  if ((skok < 0) || (b != 1)) {
    printf("Nespravny vstup.\n");
    return 0;
  }
  if (pocet % 2 != 0) {
    printf("Celkem reseni: 0\n");
    return 0;
  }

  int *board = (int *)malloc(sizeof(int) * pocet);
  int *index = (int *)malloc(sizeof(int) * pocet / 2);
  char *letters = (char *)malloc(sizeof(char) * pocet / 2);
  for (int h = 0; h < pocet; h++) {
    board[h] = 1;
  }

  problemSolve(board, index, letters, counter = 0, pocet, skok);
  free(board);
  free(index);
  free(letters);
  
  return 0;
}
