#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct queue {
    int items[SIZE];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

struct node
{
    int vertex;
    struct node* next;
};

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int* level;
};

struct node* createNode(int);
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void bfs(struct Graph* graph, int startVertex);

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct queue* q) {
    if(q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue* q, int value){
    if(q->rear == SIZE-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct queue* q){
    int item;
    if(isEmpty(q)){
        printf("Queue is empty");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            q->front = q->rear = -1;
        }
    }
    return item;
}

struct node* createNode(int v)
{
   struct node* newNode = malloc(sizeof(struct node));
   newNode->vertex = v;
   newNode->next = NULL;
   return newNode;
}

struct Graph* createGraph(int vertices)
{
   struct Graph* graph = malloc(sizeof(struct Graph));
   graph->numVertices = vertices;

   graph->adjLists = malloc(vertices * sizeof(struct node*));
   graph->level = malloc(vertices * sizeof(int));


   int i;
   for (i = 0; i < vertices; i++) {
       graph->adjLists[i] = NULL;
       graph->level[i] = -1;
   }

   return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
   // Add edge from src to dest
   struct node* newNode = createNode(dest);
   newNode->next = graph->adjLists[src];
   graph->adjLists[src] = newNode;

   // Add edge from dest to src
   newNode = createNode(src);
   newNode->next = graph->adjLists[dest];
   graph->adjLists[dest] = newNode;
}

void bfs(struct Graph* graph, int startVertex) {
    struct queue* frontier = createQueue();
    struct queue* next_frontier = createQueue();

    graph->level[startVertex] = 0;
    int curr_level = 0;
    enqueue(frontier, startVertex);
    printf("BFS: %d ", startVertex);

    while(!isEmpty(frontier)){
       int currentVertex = dequeue(frontier);
       struct node* temp = graph->adjLists[currentVertex];

       while(temp) {
            int adjVertex = temp->vertex;
            if(graph->level[adjVertex] == -1){
                printf("%d ", adjVertex);

                graph->level[adjVertex] = curr_level+1;
                enqueue(next_frontier, adjVertex);
            }
            temp = temp->next;
       }
    frontier->front = next_frontier->front;
    frontier->rear = next_frontier->rear;
    for (int i = 0; i < sizeof(*next_frontier)/sizeof(next_frontier[0]); i++) {
        frontier[i] = next_frontier[i];
    }
    next_frontier = createQueue();
    curr_level += 1;
    }
}

// Print the queue
void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("Queue is empty");
  } else {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%d ", q->items[i]);
    }
  }
}

int main()
{
    struct Graph* graph = createGraph(100);
    
//     addEdge(graph, 0, 1);
//     addEdge(graph, 0, 2);
//     addEdge(graph, 1, 2);
//     addEdge(graph, 1, 4);
//     addEdge(graph, 1, 3);
//     addEdge(graph, 2, 4);
//     addEdge(graph, 3, 4);
    int num;
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            scanf("%d",&num);
            if(num==1){
                addEdge(graph, i, j);
            }
        }
    }
    

    bfs(graph, 0);

    return 0;
}
