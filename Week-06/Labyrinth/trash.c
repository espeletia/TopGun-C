#include <stdio.h>
#include <stdlib.h>

struct Coords {
	int x;
	int y;
};

struct ListNode {
	struct Coords position;
	struct ListNode* next;
};

struct List {
	struct Coords id;
    struct ListNode* head;
};

struct Graph {
	int V;
    struct List* array;
};


struct ListNode* newListNode(struct Coords pos){
    struct ListNode* Node = (struct ListNode*) malloc(sizeof(struct ListNode));
    Node->position = pos;
    Node->next = NULL;
    return Node;
}

struct Coords CreateCoords(int x, int y){
	struct Coords xy;
	xy.x = x;
	xy.y = y;
	return xy; 
}

void addEdge(struct Graph* graph, int srcIndex, int destIndex, struct Coords src, struct Coords dest)
{
	struct ListNode* check = NULL;
	struct ListNode* newNode = newListNode(dest);

	if (graph->array[srcIndex].head == NULL) {
		newNode->next = graph->array[srcIndex].head;
		graph->array[srcIndex].head = newNode;
	}
	else {

		check = graph->array[srcIndex].head;
		while (check->next != NULL) {
			check = check->next;
		}
		check->next = newNode;
	}

	newNode = newListNode(src);
	if (graph->array[destIndex].head == NULL) {
		newNode->next = graph->array[destIndex].head;
		graph->array[destIndex].head = newNode;
	}
	else {
		check = graph->array[destIndex].head;
		while (check->next != NULL) {
			check = check->next;
		}
		check->next = newNode;	}

}




void printList(struct ListNode* head){
    printf("(%d, %d)", head->position.x, head->position.y);
    if(head->next == NULL)return;
    printList(head);
}

void printGraph(struct Graph* graph)
{
	int v;
	for (v = 0; v < graph->V; ++v) {
		struct ListNode* pCrawl = graph->array[v].head;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl) {
			printf("-> %d, %d", pCrawl->position.x, pCrawl->position.y);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}

int main(){
   int* array = (int*) malloc(sizeof(int));
   int size = 0;
   while(1){
		size++;
		array =(int*) realloc(array, sizeof(int) * size);
   }
   free(array);
}