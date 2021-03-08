#include <stdio.h>
#include <stdlib.h>

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

struct Graph *InsertEdge(struct Graph *graph, int source, int dest)
{
    struct Node *new_node = newNode(dest);
    new_node->next = graph->arr[source].head;
    graph->arr[source].head = new_node;
    new_node = newNode(source);
    new_node->next = graph->arr[dest].head;
    graph->arr[dest].head = new_node;
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

struct Graph *Union(struct Graph *graph1, struct Graph *graph2)
{
    // printf("HII");
    struct Graph *graph = Create_Graph(graph1->v > graph2->v ? graph1->v : graph2->v);
    for (int i = 0; i < graph->v; i++)
    {
        struct Node *t1, *t2;
        if (i > graph1->v - 1)
        {
            t1 = NULL;
            t2 = graph2->arr[i].head;
        }
        else if (i > graph2->v - 1)
        {
            t1 = graph1->arr[i].head;
            t2 = NULL;
        }
        else
        {
            t1 = graph1->arr[i].head;
            t2 = graph2->arr[i].head;
        }
        while (t1 != NULL && t2 != NULL)
        {
            if (t1->dest < t2->dest)
            {
                struct Node *new_node = newNode(t1->dest);
                new_node->next = graph->arr[i].head;
                graph->arr[i].head = new_node;
                t1 = t1->next;
            }
            else if (t1->dest > t2->dest)
            {
                struct Node *new_node = newNode(t2->dest);
                new_node->next = graph->arr[i].head;
                graph->arr[i].head = new_node;
                t2 = t2->next;
            }
            else
            {
                struct Node *new_node = newNode(t2->dest);
                new_node->next = graph->arr[i].head;
                graph->arr[i].head = new_node;
                t1 = t1->next;
                t2 = t2->next;
            }
        }
        while (t1 != NULL)
        {
            struct Node *new_node = newNode(t1->dest);
            new_node->next = graph->arr[i].head;
            graph->arr[i].head = new_node;
            t1 = t1->next;
        }
        while (t2 != NULL)
        {
            struct Node *new_node = newNode(t2->dest);
            new_node->next = graph->arr[i].head;
            graph->arr[i].head = new_node;
            t2 = t2->next;
        }
    }
    bubbleSort(graph);
    return graph;
}
struct Graph *Intersection(struct Graph *graph1, struct Graph *graph2)
{
    struct Graph *graph = Create_Graph(graph1->v > graph2->v ? graph1->v : graph2->v);
    for (int i = 0; i < graph->v; i++)
    {
        struct Node *t1 = graph1->arr[i].head;
        struct Node *t2 = graph2->arr[i].head;
        while (t1 != NULL && t2 != NULL)
        {
            if (t1->dest > t2->dest)
                t2 = t2->next;
            else if (t1->dest < t2->dest)
                t1 = t1->next;
            else
            {
                struct Node *new_node = newNode(t2->dest);
                new_node->next = graph->arr[i].head;
                graph->arr[i].head = new_node;
                t1 = t1->next;
                t2 = t2->next;
            }
        }
    }
    bubbleSort(graph);
    return graph;
}

struct Graph *Complement(struct Graph *graph1, int n, int array[])
{
    struct Graph *graph = Create_Graph(graph1->v);
    for (int i = 0; i < graph->v; i++)
    {
        struct Node *t = graph1->arr[i].head;
        if (t != NULL)
        {
            int temp = 0;
            while (t != NULL)
            {
                if (t->dest < temp)
                    t = t->next;
                else if (t->dest > temp)
                {
                    for (int j = temp; j < t->dest; j++)
                    {
                        for (int jj = 0; jj < n; jj++)
                        {
                            if (array[jj] == j)
                            {
                                struct Node *new_Node = newNode(j);
                                new_Node->next = graph->arr[i].head;
                                graph->arr[i].head = new_Node;
                            }
                        }
                    }
                    temp = t->dest + 1;
                    t = t->next;
                }
                else
                {
                    t = t->next;
                    temp++;
                }
            }
            while (temp < graph1->v)
            {
                for (int jj = 0; jj < n; jj++)
                {
                    if (array[jj] == temp)
                    {
                        struct Node *new_Node = newNode(temp);
                        new_Node->next = graph->arr[i].head;
                        graph->arr[i].head = new_Node;
                    }
                }
                temp++;
            }
        }
        else
        {
            for (int jj = 0; jj < n; jj++)
            {
                if (array[jj] == i)
                {
                    for (int ii = 0; ii < n; ii++)
                    {
                        if (ii != array[jj])
                        {
                            struct Node *new_Node = newNode(ii);
                            new_Node->next = graph->arr[jj].head;
                            graph->arr[jj].head = new_Node;
                        }
                    }
                }
            }
        }
    }
    bubbleSort(graph);
    return graph;
}

struct Graph *Diffrence(struct Graph *graph1, struct Graph *graph2)
{
    // struct Graph *compgraph2 = Complement(graph2);
    // struct Graph *ans = graph1;

    // struct Graph *graph = Intersection(graph1, compgraph2);
    // for (int i = 0; i < graph->v; i++)
    // {
    //     if (graph2->arr[i].head == NULL && graph1->arr[i].head != NULL)
    //     {
    //         graph->arr[i].head = graph1->arr[i].head;
    //     }
    // }
    struct Graph *graph = Create_Graph(graph1->v > graph2->v ? graph1->v : graph2->v);

    for (int i = 0; i < graph->v; i++)
    {
        struct Node *t1 = graph1->arr[i].head, *t2 = graph2->arr[i].head;
        // printf("HII");
        if (t1)
        {
            while (t1 && t2)
            {
                if (t1->dest > t2->dest)
                {
                    t2 = t2->next;
                }

                else if (t1->dest < t2->dest)
                {

                    struct Node *new_Node = newNode(t1->dest);
                    new_Node->next = graph->arr[i].head;
                    graph->arr[i].head = new_Node;
                    t1 = t1->next;
                }

                else
                {
                    t1 = t1->next;
                    t2 = t2->next;
                }
            }

            while (t1)
            {
                struct Node *new_Node = newNode(t1->dest);
                new_Node->next = graph->arr[i].head;
                graph->arr[i].head = new_Node;
                t1 = t1->next;
            }
        }
    }
    bubbleSort(graph);
    return graph;
}

struct Graph *RingSum(struct Graph *graph1, struct Graph *graph2)
{
    struct Graph *g1Ug2 = Union(graph1, graph2);
    struct Graph *g1Ig2 = Intersection(graph1, graph2);
    struct Graph *graph = Diffrence(g1Ug2, g1Ig2);
    return graph;
}
void main()
{
    // printf("Enter The Number of Vertices : ");
    // // printf("Hello");
    // printf("Enter The Number of Vertices : ");
    // printf("Hello");
    int v1 = 5;

    struct Graph *graph1 = Create_Graph(v1);
    // printf("Hello");
    graph1 = InsertEdge(graph1, 1, 2);
    graph1 = InsertEdge(graph1, 1, 3);
    graph1 = InsertEdge(graph1, 1, 4);
    graph1 = InsertEdge(graph1, 2, 3);
    graph1 = InsertEdge(graph1, 2, 4);
    graph1 = InsertEdge(graph1, 3, 4);
    printf("adjacency List for Graph 1 :\n");
    bubbleSort(graph1);
    display(graph1);
    // printf("Hello");
    int v2 = 5;
    struct Graph *graph2 = Create_Graph(v2);
    graph2 = InsertEdge(graph2, 0, 1);
    graph2 = InsertEdge(graph2, 0, 2);
    graph2 = InsertEdge(graph2, 1, 2);
    graph2 = InsertEdge(graph2, 1, 4);
    graph2 = InsertEdge(graph2, 2, 3);
    graph2 = InsertEdge(graph2, 3, 4);
    printf("adjacency List for Graph 2 :\n");
    bubbleSort(graph2);
    display(graph2);

    // For Union
    printf("\nUnion Of Graph 1 and 2 : \n");
    struct Graph *graph3 = Union(graph1, graph2);
    display(graph3);
    printf("\nIntersection Of the Graph1 and Graph2 : \n");
    struct Graph *graph4 = Intersection(graph1, graph2);
    display(graph4);
    printf("Complement of Graph 1 is : \n");
    int array1[] = {0, 1, 2, 3, 4};
    int array2[] = {0, 1, 2, 3, 4};
    int n1 = sizeof(array1) / sizeof(array1[0]);
    int n2 = sizeof(array2) / sizeof(array2[0]);

    struct Graph *compgraph1 = Complement(graph1, n1, array1);
    display(compgraph1);
    printf("Complement Of Graph 2 is : \n");
    struct Graph *compgraph2 = Complement(graph2, n2, array2);
    display(compgraph2);
    printf("G1-G2 : \n");
    struct Graph *g1g2 = Diffrence(graph1, graph2);
    display(g1g2);
    printf("G2-G1 : \n");
    struct Graph *g2g1 = Diffrence(graph2, graph1);
    display(g2g1);
    printf("RingSum of Two Graph : \n");
    struct Graph *g1Sg2 = RingSum(graph1, graph2);
    display(g1Sg2);

    printf("****************************************************");
    printf("Graph 3:\n");
    struct Graph *g1 = Create_Graph(7);
    g1 = InsertEdge(g1, 1, 2);
    g1 = InsertEdge(g1, 2, 3);
    g1 = InsertEdge(g1, 1, 3);
    g1 = InsertEdge(g1, 2, 4);
    g1 = InsertEdge(g1, 3, 5);
    g1 = InsertEdge(g1, 4, 5);
    printf("adjacency List for Graph 3 :\n");
    bubbleSort(g1);
    display(g1);

    struct Graph *g2 = Create_Graph(7);
    g2 = InsertEdge(g2, 1, 2);
    g2 = InsertEdge(g2, 2, 3);
    g2 = InsertEdge(g2, 1, 3);
    g2 = InsertEdge(g2, 1, 6);
    g2 = InsertEdge(g2, 3, 6);
    g2 = InsertEdge(g2, 5, 6);
    printf("adjacency List for Graph 4 :\n");
    bubbleSort(g2);
    display(g2);
    printf("\nUnion Of Graph 3 and 4 : \n");
    struct Graph *g3 = Union(g1, g2);
    display(g3);
    printf("\nIntersection Of the Graph3 and Graph4 : \n");
    struct Graph *g4 = Intersection(g1, g2);
    display(g4);
    printf("Complement of Graph 3 is : \n");
    int a1[] = {1, 2, 3, 4, 5};
    int a2[] = {1, 2, 3, 5, 6};
    n1 = sizeof(a1) / sizeof(a1[0]);
    n2 = sizeof(a2) / sizeof(a2[0]);

    struct Graph *compg1 = Complement(g1, n1, a1);
    display(compg1);
    printf("Complement Of Graph 4 is : \n");
    struct Graph *compg2 = Complement(g2, n2, a2);
    display(compg2);
    printf("G3-G4 : \n");
    struct Graph *g1_g2 = Diffrence(g1, g2);
    display(g1_g2);
    printf("G4-G3 : \n");
    struct Graph *g2_g1 = Diffrence(g2, g1);
    display(g2_g1);
    printf("RingSum of Two Graph : \n");
    struct Graph *g1_S_g2 = RingSum(g1, g2);
    display(g1_S_g2);

    // printf("How many edges Do you Want to Include :");
}
