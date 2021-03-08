#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int edge1 = 0;
int edge2 = 0;
struct Node
{
    int dest;
    struct Node *next;
};
struct Adjlist
{
    struct Node *head;
};
struct Graph
{
    int v;
    struct Adjlist *arr;
};

struct Degree
{
    int degree;
    int vertex;
};
struct Node *newNode(int dest)
{
    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
struct Graph *Create_Graph(int v)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    // printf("Hello");
    graph->v = v;
    graph->arr = (struct Adjlist *)malloc(v * sizeof(struct Adjlist));
    for (int i = 0; i < v; i++)
    {
        graph->arr[i].head = NULL;
    }
    return graph;
}
struct Graph *InsertEdge(struct Graph *graph, int source, int dest, int id)
{
    struct Node *new_node = newNode(dest);
    new_node->next = graph->arr[source].head;
    graph->arr[source].head = new_node;
    new_node = newNode(source);
    new_node->next = graph->arr[dest].head;
    graph->arr[dest].head = new_node;
    if (id == 1)
        edge1++;
    else
        edge2++;
    return graph;
}

void display(struct Graph *graph)
{

    for (int i = 0; i < graph->v; i++)
    {
        struct Node *traverse = graph->arr[i].head;
        if (traverse)
        {
            printf("%d :: ", i);
            while (traverse->next)
            {
                printf("%d-->", traverse->dest);
                traverse = traverse->next;
            }
            if (traverse != NULL)
                printf("%d", traverse->dest);
            printf("\n");
        }
    }
}
void swap(struct Node *a, struct Node *b)
{
    int temp = a->dest;
    a->dest = b->dest;
    b->dest = temp;
}
void bubbleSort(struct Graph *graph)
{
    int swapped;
    struct Node *ptr1 = NULL;
    struct Node *ptr;
    for (int i = 0; i < graph->v; i++)
    {
        if (graph->arr[i].head == NULL)
        {
            continue;
        }
        else
        {
            ptr1 = NULL;
            swapped = 1;
            while (swapped)
            {
                swapped = 0;
                ptr = graph->arr[i].head;
                while (ptr->next != ptr1)
                {
                    if (ptr->dest > ptr->next->dest)
                    {
                        swap(ptr, ptr->next);
                        swapped = 1;
                    }
                    ptr = ptr->next;
                }
                ptr1 = ptr;
            }
        }
    }
}

void DegreeSort(struct Degree **dsog, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (dsog[j]->degree > dsog[j + 1]->degree)
            {
                int temp1 = dsog[j]->degree;
                int temp2 = dsog[j]->vertex;
                dsog[j]->degree = dsog[j + 1]->degree;
                dsog[j]->vertex = dsog[j + 1]->vertex;
                dsog[j + 1]->degree = temp1;
                dsog[j + 1]->vertex = temp2;
            }
        }
    }
}

void OnetoOne(struct Degree **dsog1, struct Degree **dsog2, int n)
{
    printf("One To One Relation B/w Two Graph are Given Below :\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d-->%d (%d)\n", dsog1[i]->vertex, dsog2[i]->vertex, dsog1[i]->degree);
    }
}
void computeDegree(struct Graph *graph, struct Degree **dsog)
{
    for (int i = 0; i < graph->v; i++)
    {
        struct Node *temp = graph->arr[i].head;
        struct Degree *t = (struct Degree *)malloc(sizeof(struct Degree));
        t->vertex = i;
        t->degree = 0;

        while (temp)
        {
            t->degree++;
            temp = temp->next;
        }
        dsog[i] = t;
        // printf("%d\n", dsog[i]->vertex);
    }
    DegreeSort(dsog, graph->v);
}
void Check_Isomorphism(struct Graph *graph1, struct Graph *graph2)
{
    //for checking equal number of vertice
    int checkv1 = 0, checkv2 = 0;
    for (int i = 0; i < graph1->v; i++)
    {
        if (graph1->arr[i].head != NULL)
        {
            checkv1++;
        }
    }

    for (int i = 0; i < graph2->v; i++)
    {
        if (graph2->arr[i].head != NULL)
        {
            checkv2++;
        }
    }

    if (checkv1 != checkv2)
    {
        printf("Both the Graphs are not isomorphic");
    }
    else if (edge1 != edge2)
    {
        printf("Both the Graphs are not isomorphic");
    }
    else
    {
        int n1 = graph1->v;
        int n2 = graph2->v;
        // printf("%d", n1);
        struct Degree **dsog1 = (struct Degree **)malloc(n1 * sizeof(struct Degree));
        struct Degree **dsog2 = (struct Degree **)malloc(n2 * sizeof(struct Degree));
        computeDegree(graph1, dsog1);
        computeDegree(graph2, dsog2);
        int flag = 0;
        for (int i = 0; i < graph1->v; i++)
        {
            if (dsog1[i]->degree != dsog2[i]->degree)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            printf("Both the Graphs are not isomorphic\n");
        }
        else
        {
            printf("\n***************Both the Graphs are Isomorphic*************\n");
            OnetoOne(dsog1, dsog2, n1);
        }
    }
}
void main()
{
    struct Graph *graph1 = Create_Graph(5);
    int id = 1;
    graph1 = InsertEdge(graph1, 0, 1, id);
    graph1 = InsertEdge(graph1, 0, 2, id);
    graph1 = InsertEdge(graph1, 1, 3, id);
    graph1 = InsertEdge(graph1, 2, 4, id);
    graph1 = InsertEdge(graph1, 3, 4, id);
    printf("adjacency List for Graph 1 :\n");
    bubbleSort(graph1);
    display(graph1);

    struct Graph *graph2 = Create_Graph(5);
    id = 2;
    graph2 = InsertEdge(graph2, 0, 3, id);
    graph2 = InsertEdge(graph2, 0, 4, id);
    graph2 = InsertEdge(graph2, 1, 2, id);
    graph2 = InsertEdge(graph2, 1, 4, id);
    graph2 = InsertEdge(graph2, 2, 3, id);

    printf("adjacency List for Graph 2 :\n");
    bubbleSort(graph2);
    display(graph2);
    Check_Isomorphism(graph1, graph2);

    printf("\n**************************>>>>>>>Second Pair<<<<<<************************************\n");
    edge1 = 0;
    edge2 = 0;
    graph1 = Create_Graph(8);
    id = 1;
    graph1 = InsertEdge(graph1, 0, 1, id);
    graph1 = InsertEdge(graph1, 0, 3, id);
    graph1 = InsertEdge(graph1, 0, 4, id);
    graph1 = InsertEdge(graph1, 1, 5, id);
    graph1 = InsertEdge(graph1, 1, 2, id);
    graph1 = InsertEdge(graph1, 2, 6, id);
    graph1 = InsertEdge(graph1, 2, 3, id);
    graph1 = InsertEdge(graph1, 3, 7, id);
    graph1 = InsertEdge(graph1, 4, 5, id);
    graph1 = InsertEdge(graph1, 4, 7, id);
    graph1 = InsertEdge(graph1, 5, 6, id);
    graph1 = InsertEdge(graph1, 6, 7, id);

    printf("Adjacency List for Graph 1 :\n");
    bubbleSort(graph1);
    display(graph1);

    graph2 = Create_Graph(8);
    id = 2;
    graph2 = InsertEdge(graph2, 0, 4, id);
    graph2 = InsertEdge(graph2, 0, 5, id);
    graph2 = InsertEdge(graph2, 0, 6, id);
    graph2 = InsertEdge(graph2, 1, 4, id);
    graph2 = InsertEdge(graph2, 1, 5, id);
    graph2 = InsertEdge(graph2, 1, 7, id);
    graph2 = InsertEdge(graph2, 2, 4, id);
    graph2 = InsertEdge(graph2, 2, 6, id);
    graph2 = InsertEdge(graph2, 2, 7, id);
    graph2 = InsertEdge(graph2, 3, 5, id);
    graph2 = InsertEdge(graph2, 3, 6, id);
    graph2 = InsertEdge(graph2, 3, 7, id);

    printf("adjacency List for Graph 2 :\n");
    bubbleSort(graph2);
    display(graph2);
    Check_Isomorphism(graph1, graph2);

    printf("\n**************************>>>>>>>Third Pair<<<<<<************************************\n");
    edge1 = 0;
    edge2 = 0;
    graph1 = Create_Graph(5);
    id = 1;
    graph1 = InsertEdge(graph1, 0, 1, id);
    graph1 = InsertEdge(graph1, 0, 2, id);
    graph1 = InsertEdge(graph1, 0, 3, id);
    graph1 = InsertEdge(graph1, 1, 2, id);
    graph1 = InsertEdge(graph1, 2, 3, id);
    graph1 = InsertEdge(graph1, 3, 4, id);
    printf("Adjacency List for Graph 1 :\n");
    bubbleSort(graph1);
    display(graph1);

    graph2 = Create_Graph(5);
    id = 2;
    graph2 = InsertEdge(graph2, 0, 1, id);
    graph2 = InsertEdge(graph2, 1, 2, id);
    graph2 = InsertEdge(graph2, 1, 4, id);
    graph2 = InsertEdge(graph2, 2, 4, id);
    graph2 = InsertEdge(graph2, 2, 3, id);
    graph2 = InsertEdge(graph2, 3, 4, id);
    printf("adjacency List for Graph 2 :\n");
    bubbleSort(graph2);
    display(graph2);
    Check_Isomorphism(graph1, graph2);
}
