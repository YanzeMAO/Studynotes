/*
 * Problem 2 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: YANZE MAO
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define INITIAL_CAPACITY 4  
#define INF 100000


typedef struct path Path;
struct path {
  int weight;
  int prev;g
};


int min(int i, int j);


/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_2_a();
void problem_2_b();
void print_usage_and_exit(char **argv);

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage_and_exit(argv);
  }

  /* If the argument provided is "a" then run problem_2_a(),
   * run problem_2_b() for "b", and fail otherwise. */
  if (strcmp(argv[1], "a") == 0) {
    problem_2_a();
  } else if (strcmp(argv[1], "b") == 0) {
    problem_2_b();
  } else {
    print_usage_and_exit(argv);
  }

  return 0;
}

/* Print the usage information and exit the program. */
void print_usage_and_exit(char **argv) {
  fprintf(stderr, "usage: %s [ab]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

/* TODO: Implement your solution to Problem 2.a. in this function. */


void problem_2_a() {
  int numnode;
  scanf("%d\n", &numnode);
  int l, h, i, j,m,n;
  int dist[numnode][numnode];
  for (n=0; n<numnode; n++){
    for (m=0;m<numnode;m++){
      dist[n][m]=INF;
    }
  }
  for(i=0;i<numnode;i++){
    int outdegree;
    scanf("%d\n", &outdegree);

    for (j=0;j<outdegree;j++){
      int node2, weight;
      scanf("%d %d\n", &node2,&weight);
      dist[i][node2]=weight;
    }
  }
  Path shortest[numnode];
  for (l = 0; l < numnode; l++){ 
    Path p;
    p.weight=INF;
    p.prev=-1;
    shortest[l]=p;
  }
  shortest[0].weight=0;
  for (h=0; h<numnode; h++){
    //h is the start node
    int w;
    //printf("h%d\n", h);
    for (w=h+1;w<numnode;w++){
      //printf("h:%d  w%d  %d %d\n", h,w,shortest[w].weight, dist[h][w]);
      if (dist[h][w]!=INF && shortest[h].weight!=INF && shortest[h].weight + dist[h][w] < shortest[w].weight){
        shortest[w].weight = shortest[h].weight + dist[h][w]; 
        shortest[w].prev=h;
        //printf("change h:%d  w%d  %d %d\n", h,w,shortest[w].weight, shortest[w].prev);
      }
    }
  }

  if (shortest[numnode-1].prev==-1){
    printf("No Path");
  }else{

    int* path=malloc(numnode*sizeof(int));

    int length=0, end=numnode-1;
    path[length]=end;
    printf("%d\n", shortest[end].weight);
    while (end!=0){
      assert(shortest[end].prev!=-1);
      length+=1;
      end=shortest[end].prev;
      path[length]=end;
    }
    printf("%d\n", length);
    int u;
    for (u=length; u>=0; u--){
      printf("%d\n", path[u]);
    }
  }

}




int min(int i, int j){
  if (i<j)
    return i;
  return j;
}

/* TODO: Implement your solution to Problem 2.b. in this function. */
void problem_2_b() {
  int numnode, k, K, h, i, j, m, n, l;
  scanf("%d  %d\n", &numnode, &K);
  int dist[numnode][numnode];

  for (n=0; n<numnode; n++){
    for (m=0; m<numnode; m++){
      dist[n][m]=INF;
    }
  }

  for(i=0;i<numnode;i++){
    int outdegree;
    scanf("%d\n", &outdegree);
    for (j=0;j<outdegree;j++){
      int node2, weight;
      scanf("%d %d\n", &node2,&weight);
      dist[i][node2]=weight;
    }
  }
  k=K+1;
  Path shortest[k][numnode];
  for (j=0; j<k; j++){
    for (h=0; h<numnode; h++){
      Path p;
      p.weight=INF;
      p.prev=-1;
      shortest[j][h]=p;
    }

  }
  shortest[0][0].weight=0;
  //printf("%d\n", numnode);
  int final=0;
  for (l=1; l<k; l++){
    //printf("\nstage%d\n", l);
    int p,q,r; 
    //copy the collumn from prev
    for (r=0;r<numnode;r++){
      shortest[l][r]=shortest[l-1][r];
    }
    //check from 0 to numnode-1 
    for (p=0; p<numnode-1; p++) {
      for (q=p+1;q<numnode;q++){
        if (dist[p][q]!=INF && 
          shortest[l-1][p].weight!=INF){
          if(shortest[l-1][p].weight + dist[p][q] < shortest[l][q].weight) { 
            
            shortest[l][q].weight=shortest[l-1][p].weight + dist[p][q];
            shortest[l][q].prev=p;
            if (q==numnode-1){
              final=l;
            }
          }
        } 
      }
    }
  }
  
  
  if (shortest[k-1][numnode-1].prev==-1){
    printf("No Path");
  }else{
    int* path=malloc(numnode*sizeof(int));
    int length=0, end=numnode-1, prevstage=final;
    path[length]=end;
    //printf("%d  %d weight\n", prevstage, numnode-1);
    printf("%d\n", shortest[prevstage][numnode-1].weight);
    while (end!=0){
      assert(shortest[prevstage][end].prev!=-1);
      length+=1;
      end=shortest[prevstage][end].prev;
      path[length]=end;
      prevstage-=1;
    }
    printf("%d\n", length);
    int u;
    for (u=length; u>=0; u--){
      printf("%d\n", path[u]);
    }
  }
  
}
