#include <stdio.h>
#include <stdlib.h>

/* - - - GRAPH LOGIC - - -*/
struct AdjListNode
{
    int dest;
    struct AdjListNode *next;
};

struct AdjList
{
    int type;
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList *array;
    // int *visited;
};

struct AdjListNode *newAdjListNode(int dest)
{
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));
    // graph->visited = (int *)malloc(V * sizeof(int));

    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    struct AdjListNode *check = NULL;
    struct AdjListNode *newNode = newAdjListNode(dest);

    if (graph->array[src].head == NULL)
    {
        newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;
    }
    else
    {

        check = graph->array[src].head;
        while (check->next != NULL)
        {
            check = check->next;
        }
        check->next = newNode;
    }

    newNode = newAdjListNode(src);
    if (graph->array[dest].head == NULL)
    {
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
    }
    else
    {
        check = graph->array[dest].head;
        while (check->next != NULL)
        {
            check = check->next;
        }
        check->next = newNode;
    }
}

void printGraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode *pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n of type %d head ", v, graph->array[v].type);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void printRelevantGraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        if (!graph->array[v].type)
        {
            struct AdjListNode *pCrawl = graph->array[v].head;
            printf("\n Adjacency list of vertex %d\n of type %d head ", v, graph->array[v].type);
            while (pCrawl)
            {
                printf("-> %d", pCrawl->dest);
                pCrawl = pCrawl->next;
            }
            printf("\n");
        }
    }
}

/* - - - QUEUE LOGIC - - - */
struct QueueNode
{
    int data;
    int steps;
    struct QueueNode *next;
};

struct QueueNode *newQueueItem(int data, int steps)
{
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->steps = steps;
    newNode->next = NULL;
    return newNode;
}

void enQueue(struct QueueNode **head, struct QueueNode **end, int data, int steps)
{
    if (*head == NULL)
    {
        *head = newQueueItem(data, steps);
        *end = *head;
        return;
    }
    struct QueueNode* temp = (*end);
    temp->next = newQueueItem(data, steps);
    (*end) = temp->next;
}

void printQueue(struct QueueNode *head)
{
    if (head == NULL)
    {
        printf("queue is empty\n");
        return;
    }
    printf("Queue: %d", head->data);
    struct QueueNode *node = head->next;
    while (node != NULL)
    {
        printf(" -> %d", node->data);
        node = node->next;
    }
    printf("\n");
}

struct QueueNode deQueue(struct QueueNode **head)
{
    struct QueueNode *next_node = NULL;
    struct QueueNode retVal;
    if (*head == NULL)
    {
        return retVal;
    }

    next_node = (*head)->next;
    retVal.data = (*head)->data;
    retVal.steps = (*head)->steps;
    retVal.next = NULL;
    free(*head);
    *head = next_node;

    return retVal;
}

int isEmpty(struct QueueNode *head)
{
    if (head == NULL)
    {
        return 1;
    }
    return 0;
}

int inArray(int *arr, int num, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == num)
            return 1;
    }
    return 0;
}

void resetArray(int **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        (*arr)[i] = 0;
    }
}
/* - - - BFS ALGORITHM - - - */
/*BFS stands for BIG F[redacted] SEARCH*/
int BFS(struct Graph *graph, int startNode, int endNode)
{
    int* visited = (int*) malloc(sizeof(int) * graph->V);
    for (int i = 0; i < graph->V; i++)
    {
        visited[i] = 0;
    }
    
    struct QueueNode *head = NULL;
    visited[startNode] = 1;
    struct QueueNode *end = NULL;
    enQueue(&head, &end, startNode, 0);
    while (!isEmpty(head))
    { 
        // printQueue(head);
        struct QueueNode currentNode = deQueue(&head);
        // printf("EXPLORTING CURRENT NODE: %d\n", currentNode.data);
        if (currentNode.data == endNode)
        {
            free(visited);
            printf("%d\n", currentNode.steps);
            return currentNode.steps;
        }
        struct AdjListNode *node = graph->array[currentNode.data].head;
        while (node != NULL)
        {
            if (visited[node->dest] != 1)
            {
                visited[node->dest] = 1;
                enQueue(&head, &end, node->dest, currentNode.steps + 1);
            }
            node = node->next;
        }
        visited[currentNode.data] = 1;
        // printf("%d\n", !isEmpty(head));
    }
    free(visited);
    printf("-1\n");
    return -1;
}

int main()
{
    int row = 0;
    int col = 0;
    int permaCol = 0;
    char str;
    int size = 1;
    struct Graph *graph = createGraph(0);
    ///////////////////////////////
    /////////READING GRAPH/////////
    ///////////////////////////////
    while (scanf("%c", &str) != EOF && str != '-')
    {
        if (str == ' ')
        {
            continue;
        }
        if (str == '\n')
        {
            row++;
            continue;
        }
        if (row < 1)
        {
            permaCol++;
        }
        col++;
        graph->V++;
        if(graph->V == size){
            size = size * 2;
            graph->array = (struct AdjList *)realloc(graph->array, size * sizeof(struct AdjList));
        }
        // graph->visited = (int *)realloc(graph->visited, graph->V * sizeof(int));
        graph->array[graph->V - 1].head = NULL;
        graph->array[graph->V - 1].type = 1;
        // graph->visited[graph->V - 1] = 0;
        if (str == '.')
        {
            graph->array[graph->V - 1].type = 0;
        }
        if (row > 0)
        {
            if (graph->array[graph->V - 1 - permaCol].type == 0 && graph->array[graph->V - 1].type == 0)
            {
                // printf("\nChar: %c, Index up: %d, Type up: %d, Index: %d, Type: %d\n", str, graph->V -1 - permaCol, graph->array[graph->V -1 - permaCol].type, graph->V -1, graph->array[graph->V -1].type);
                addEdge(graph, graph->V - 1 - permaCol, graph->V - 1);
            }
        }
        if (col > 0)
        {
            if (graph->array[graph->V - 2].type == 0 && graph->array[graph->V - 1].type == 0)
            {
                addEdge(graph, graph->V - 2, graph->V - 1);
            }
        }
    }

    // printRelevantGraph(graph);

    int startX;
    int startY;
    int endX;
    int endY;
    int startNode;
    int endNode;
    while (scanf("%d %d %d %d", &startY, &startX, &endY, &endX) != EOF)
    {

        // printf("%d %d %d %d\n", startY, startX, endY, endX);
        startNode = startX + (startY * permaCol);
        endNode = endX + (endY * permaCol);
        // printf("CALLING BFS FROM NODE: %d, TO NODE: %d\n", startNode, endNode);
        BFS(graph, startNode, endNode);
        // printRelevantGraph(graph);
        
    }

    return 0;
}
