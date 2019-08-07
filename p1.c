/*
 * Problem 1 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: YANZE MAO
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define MAX 1000000
#define NEGINF -1000000





void insert(int* heap,int k);
void MaxHeapify(int* heap, int height, int size);
void swap(int *x, int *y);
int parent(int i);
int left(int i);
int right(int i);
void siftdown(int *heap, int i, int size);
void righthandheap(int* heap, int size);
/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_1_a();
void problem_1_b();
void print_usage_and_exit(char **argv);





int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage_and_exit(argv);
  }

  /* If the argument provided is "a" then run problem_1_a(),
   * run problem_1_b() for "b", and fail otherwise. */
  if (strcmp(argv[1], "a") == 0) {
    problem_1_a();
  } else if (strcmp(argv[1], "b") == 0) {
    problem_1_b();
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

/* TODO: Implement your solution to Problem 1.a. in this function. */
void problem_1_a() {
  int i,j,k,index=1,size;
  scanf("%d\n",&j);
  size=j;
  int *heap = malloc(j*sizeof(int));
  assert(heap);
  while (scanf("%d\n", &i)==1){
    heap[index]=i;
    index+=1;
  }
  //find height of th tree
  int height=0;
  while(j>0){
    height+=1;
    j=j/2;
  }
  MaxHeapify(heap, height, size);
  for (k=1;k<=size;k++){
    printf("%d\n", heap[k]);
  }
}


int parent(int i){
  return i/2;
}
int left(int i){
  return 2*i;
}
int right(int i){
  return 2*i+1;
}
 

void MaxHeapify(int* heap, int height, int size) 
{ 
  int m;
  m=pow(2, height-2);
  while (m > 0){
    int p;
    for (p=m; p<=(2*m-1); p++){
      siftdown(heap, p, size);
    } 
    m/=2;
  } 
} 

void siftdown(int *heap, int i, int size){
  int l, r;
  l=left(i);
  r=right(i);
  while (r <= size && (heap[i] < heap[r] || heap[i] < heap[l])){
    if(heap[l] < heap[r] && heap[i] < heap[r]){ 
      swap(&heap[i], &heap[r]);
      i=r;
      l=left(i);
      r=right(i);
    }else if(heap[l] >= heap[r] && heap[i] < heap[l]){
      swap(&heap[i], &heap[l]);
      i=l;
      l=left(i);
      r=right(i);
    }

  }
}

void swap(int *x, int *y) 
{ 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
} 

/* TODO: Implement your solution to Problem 1.b. in this function. */
void problem_1_b() {
  int i,j,k,index=1,size;
  scanf("%d\n",&j);
  size=j;
  int *heap = malloc(j*sizeof(int));
  assert(heap);
  while (scanf("%d\n", &i)==1){
    heap[index]=i;
    index+=1;
  }
  //find height of th tree
  int height=0;
  while(j>0){
    height+=1;
    j=j/2;
  }
  MaxHeapify(heap, height, size);
  righthandheap(heap, size);
  for (k=1;k<=size;k++){
    printf("%d\n", heap[k]);   
  }
}


void righthandheap(int* heap, int size){
  // Start from a heap
  int k,j;
  j=size/2;
  for (k=1;k<=j;k++){
    //make the heap correct
    //printf("head%d %d\n", k, harr[k]);
    if (heap[left(k)]>heap[right(k)]){
      swap(&heap[left(k)], &heap[right(k)]);
    }
    siftdown(heap, left(k), size);
  }

}
