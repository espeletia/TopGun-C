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
    int visited;
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList *array;
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
    struct QueueNode *next;
};

struct QueueNode *newQueueItem(int data)
{
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enQueue(struct QueueNode **head, int data)
{
    if (*head == NULL)
    {
        *head = newQueueItem(data);
        return;
    }
    while ((*head)->next != NULL)
    {
        *head = (*head)->next;
    }

    (*head)->next = newQueueItem(data);
}

void printQueue(struct QueueNode *head)
{
    if (head == NULL)
    {
        printf("queue is empty\n");
        return;
    }
    printf("Queue: %d", head->data);
    struct QueueNode* node = head;
    while (node->next != NULL)
    {
        printf(" -> %d", node->data);
        node = node->next;
    }
}

int deQueue(struct QueueNode **head)
{
    int retval = -1;
    struct QueueNode *next_node = NULL;

    if (*head == NULL)
    {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->data;
    free(*head);
    *head = next_node;

    return retval;
}

int isEmpty(struct QueueNode *head)
{
    if (head == NULL)
    {
        return 1;
    }
    return 0;
}

/* - - - BFS ALGORITHM - - - */
/*BFS stands for BIG F[redacted] SEARCH*/
int BFS(struct Graph *graph, int startNode, int endNode)
{
    if (startNode == endNode)
    {
        return 0;
    }
    struct QueueNode *head = NULL;
    enQueue(&head, startNode);
    while (!isEmpty(head))
    {
        int currentNode = deQueue(&head);
        if (currentNode == endNode)
        {
            printf("Found\n");
            return 0;
        }
        struct AdjListNode *node = graph->array[currentNode].head;
        if (graph->array[currentNode].visited)
        {
            continue;
        }
        while (node != NULL)
        {
            printQueue(head);
            graph->array[currentNode].visited = 1;
            enQueue(&head, node->dest);
            node = node->next;
        }
        printf("%d\n", !isEmpty(head));
    }
    printf("how????\n");
    return 0;
}

int main()
{
    int row = 0;
    int col = 0;
    int permaCol = 0;
    char str;
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
            printf("\n");
            continue;
        }
        if (row < 1)
        {
            permaCol++;
        }
        col++;
        printf("%c", str);
        graph->V++;
        graph->array = (struct AdjList *)realloc(graph->array, graph->V * sizeof(struct AdjList));
        graph->array[graph->V - 1].head = NULL;
        graph->array[graph->V - 1].type = 1;
        graph->array[graph->V - 1].visited = 0;
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

    printRelevantGraph(graph);

    int startX;
    int startY;
    int endX;
    int endY;
    int startNode;
    int endNode;
    while (scanf("%d %d %d %d", &startX, &startY, &endX, &endY) != EOF)
    {

        // printf("%d %d %d %d\n", startX, startY, endX, endY);
        startNode = startX + startY * permaCol;
        endNode = endX + endY * permaCol;
        // printf("%d, %d\n", startNode, endNode);
        BFS(graph, startNode, endNode);
        // printRelevantGraph(graph);
    }

    return 0;
}
