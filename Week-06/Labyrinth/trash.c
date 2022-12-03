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
   struct Graph* arr = (struct Graph*) malloc(sizeof(struct Graph));
   arr->V = 4; 
   arr->array = (struct List*) malloc(sizeof(struct List) * arr->V);
   for (int i = 0; i < 4; i++)
   {
		arr->array[i].id = CreateCoords(i, 0);
    	arr->array[i].head = NULL;
   }
   addEdge(arr,0,1,CreateCoords(0,0), CreateCoords(1,0));
   addEdge(arr,0,3,CreateCoords(0,0), CreateCoords(1,1));
   addEdge(arr,0,2,CreateCoords(0,0), CreateCoords(0,1));
   addEdge(arr,1,3,CreateCoords(1,0), CreateCoords(1,1));
   addEdge(arr,2,3,CreateCoords(0,1), CreateCoords(1,1));
   
   printGraph(arr);
   return 0;
}