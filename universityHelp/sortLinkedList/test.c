#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem *m_Next;
  char *m_Name;
  char m_Secret[24];
} TITEM;

int cmpName(const TITEM *a, const TITEM *b)
{
  return strcmp(a->m_Name, b->m_Name);
}

int cmpNameInsensitive(const TITEM *a, const TITEM *b)
{
  return strcasecmp(a->m_Name, b->m_Name);
}

int cmpNameLen(const TITEM *a, const TITEM *b)
{
  size_t la = strlen(a->m_Name), lb = strlen(b->m_Name);
  return (lb < la) - (la < lb);
}
#endif /* __PROGTEST__ */

// Here's where the merge sort starts
TITEM *SortedMerge(TITEM *a, TITEM *b, int ascending, int (*cmpFn)(const TITEM *, const TITEM *));
void Split(TITEM *source, TITEM **front, TITEM **back);

void MergeSort(TITEM **head, int ascending, int (*cmpFn)(const TITEM *, const TITEM *))
{
  TITEM *headRef = (*head);
  TITEM *a;
  TITEM *b;

  if (headRef == NULL || headRef->m_Next == NULL)
  {
    return;
  }

  Split(headRef, &a, &b);

  MergeSort(&a, ascending, cmpFn);
  MergeSort(&b, ascending, cmpFn);

  *head = SortedMerge(a, b, ascending, cmpFn);
}

// merging two sorted lists
TITEM *SortedMerge(TITEM *a, TITEM *b, int ascending, int (*cmpFn)(const TITEM *, const TITEM *))
{
  TITEM *result = NULL;

  if (a == NULL)
    return (b);
  else if (b == NULL)
    return (a);

  if (ascending)
  {
    if (cmpFn(a, b) <= 0)
    {
      result = a;
      result->m_Next = SortedMerge(a->m_Next, b, ascending, cmpFn);
    }
    else
    {
      result = b;
      result->m_Next = SortedMerge(a, b->m_Next, ascending, cmpFn);
    }
  }
  else
  {
    if (cmpFn(a, b) >= 0)
    {
      result = a;
      result->m_Next = SortedMerge(a->m_Next, b, ascending, cmpFn);
    }
    else
    {
      result = b;
      result->m_Next = SortedMerge(a, b->m_Next, ascending, cmpFn);
    }
  }
  return (result);
}

// splitting the list using a quick and a slow pointer to find the middle
void Split(TITEM *source, TITEM **front, TITEM **back)
{
  TITEM *fast;
  TITEM *slow;
  slow = source;
  fast = source->m_Next;

  while (fast != NULL)
  {
    fast = fast->m_Next;
    if (fast != NULL)
    {
      slow = slow->m_Next;
      fast = fast->m_Next;
    }
  }

  *front = source;
  *back = slow->m_Next;
  slow->m_Next = NULL;
}

TITEM *newItem(const char *name, TITEM *next)
{
  TITEM *newNode = (TITEM *)malloc(sizeof(TITEM));
  char *tmp = strdup(name);
  newNode->m_Name = tmp;
  newNode->m_Next = next;
  for (int i = 0; i < 24; i++)
  {
    newNode->m_Secret[i] = '\0';
  }
  return newNode;
}
TITEM *sortListCmp(TITEM *l, int ascending, int (*cmpFn)(const TITEM *, const TITEM *))
{
  MergeSort(&l, ascending, cmpFn);
  return l;
}
void freeList(TITEM *src)
{
  TITEM *node;
  while (src != NULL)
  {
    node = src;
    src = src->m_Next;
    free(node->m_Name);
    free(node);
  }
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  TITEM *l;
  char tmp[50];

  assert(sizeof(TITEM) == sizeof(TITEM *) + sizeof(char *) + 24 * sizeof(char));
  l = NULL;
  l = newItem("BI-PA1", l);
  l = newItem("BIE-PA2", l);
  l = newItem("NI-PAR", l);
  l = newItem("lin", l);
  l = newItem("AG1", l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpName);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameInsensitive);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = newItem("AAG.3", l);
  assert(l && !strcmp(l->m_Name, "AAG.3"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 0, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "BIE-PA2"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  l = NULL;
  strncpy(tmp, "BI-PA1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "BIE-PA2", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "NI-PAR", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "lin", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "AG1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpName);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameInsensitive);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  strncpy(tmp, "AAG.3", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AAG.3"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 0, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "BIE-PA2"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
