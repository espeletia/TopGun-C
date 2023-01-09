#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *scanc(char x, char *y)
{
  int i = 0;
  int boolx = 0;
  while (1)
  {

    scanf("%c", &x);
    if (x == '-')
    {
      scanf("%c", &x);
      return y;
    }
    if (x == '#' || x == '.')
    {
      y = realloc(y, i + 1);
      y[i++] = x;
      y[i] = '\0';
    }

    if (boolx == 0 && x == '\n')
    {
      boolx = 1;
      y = realloc(y, i + 1);
      y[i++] = x;
      y[i] = '\0';
    }
  }
}

typedef struct node
{
  int val;
  struct node *next;
} node_t;

void print_list(node_t *head)
{
  node_t *current = head;

  while (current != NULL)
  {
    printf("%d\n", current->val);
    current = current->next;
  }
}

bool search(node_t *head, int x)
{
  // Base case
  if (head == NULL)
    return false;

  // If key is present in current node, return true
  if (head->val == x)
    return true;

  // Recur for remaining list
  return search(head->next, x);
}

int sirka = 0;
bool s;

void push(node_t *head, int val)
{
  node_t *current = head;
  while (current->next != NULL)
  {
    current = current->next;
  }

  /* now we can add a new variable */
  current->next = (node_t *)malloc(sizeof(node_t));
  current->next->val = val;
  current->next->next = NULL;
}

int main()
{

  char *chartabulka;

  chartabulka = (char *)malloc(1 * sizeof(char));

  chartabulka = scanc(' ', malloc(1));

  //    printf("%s\n", chartabulka);
  for (int i = 0; i < strlen(chartabulka); i++)
  {
    if (chartabulka[i] == '\n')
    {
      sirka = i;
      break;
    }
  }
  //  printf("%d\n", sirka);

  memmove(&chartabulka[sirka], &chartabulka[sirka + 1], strlen(chartabulka) - sirka);

  // printf("ff");

  int cislo1, cislo2, cislo3, cislo4;

  while (scanf("%d %d %d %d\n", &cislo1, &cislo2, &cislo3, &cislo4) != EOF)
  {

    //   printf("d");

    int PQqueue = 1;
    int Squeue = 0;
    int pocetsekund = 0;
    int finalnicas = -1;

    int pozice = cislo1 * sirka + cislo2;
    int cilovapozice = cislo3 * sirka + cislo4;

    node_t *head = NULL;
    head = (node_t *)malloc(sizeof(node_t));
    if (head == NULL)
    {
      return 1;
    }

    head->val = pozice;
    head->next = NULL;

    while (head != NULL)
    {
      pozice = head->val;

      if (pozice + 1 % sirka != 0 && chartabulka[pozice + 1] == '.')
      {
        if (search(head, pozice + 1) == false)
        {
          push(head, pozice + 1);
          ++Squeue;
        }
        if (pozice + 1 == cilovapozice)
        {
          ++pocetsekund;
          finalnicas = pocetsekund;
          break;
        }
      }

      if (pozice + sirka < strlen(chartabulka) && chartabulka[pozice + sirka] == '.')
      {
        if (search(head, pozice + sirka) == false)
        {
          push(head, pozice + sirka);
          ++Squeue;
        }

        if (pozice + sirka == cilovapozice)
        {
          ++pocetsekund;
          finalnicas = pocetsekund;
          break;
        }
      }

      if (pozice / sirka != 0 && chartabulka[pozice - 1] == '.')
      {
        if (search(head, pozice - 1) == false)
        {
          push(head, pozice - 1);
          ++Squeue;
        }

        if (pozice - 1 == cilovapozice)
        {
          ++pocetsekund;
          finalnicas = pocetsekund;
          break;
        }
      }

      if (pozice - sirka > 0 && chartabulka[pozice - sirka] == '.')
      {
        if (search(head, pozice - sirka) == false)
        {
          push(head, pozice - sirka);
          ++Squeue;
        }

        if (pozice - sirka == cilovapozice)
        {
          ++pocetsekund;
          finalnicas = pocetsekund;
          break;
        }
      }

      --PQqueue;
      if (PQqueue == 0)
      {
        ++pocetsekund;
      }
      PQqueue = Squeue;
      Squeue = 0;

      head = head->next;
    }

    printf("%d\n", finalnicas);
  }

  return 0;
}
