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
#define MAX 10000
#define NEGINF -1000000



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
   
typedef struct node Node;
struct node 
{ 
    int key; 
    Node *left, *right; 
}; 


void swap(int *x, int *y) ;
Node *newNode();
int inorder(int* sort, int index, int i);
Node* insert(Node* node, int key);
int depth(Node *node);
Node* make(int* sort, int size);
void freetree();
void print_usage_and_exit(char **argv);
int maxDepth(Node* node);
void makebalance(int* sort, int head, int tail, int* bst, int index, int total);


/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_3();







int main(int argc, char **argv) {
  problem_3();
  return 0;
}




/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

/* TODO: Implement your solution to Problem 1.a. in this function. */
void problem_3() {
  int size, i;
  Node* root=newNode();
  scanf("%d\n", &size);
  int index=0,b,c,d,e;
  int* sort=(int*)malloc(size*sizeof(int));
  while (scanf("%d\n", &i)==1){
    
    b=inorder(sort,index, i);
    if (b==1){
      index++;
      root=insert(root, i);
    }
  }
  printf("%d\n", index);
  /*
  for (e=0;e<index;e++){
    printf("inorder%d\n", sort[e]);
  }*/
  int odepth;
  odepth=maxDepth(root);
  printf("%d\n", odepth-1);
  int height=0, j=index, total=1;
  while(j>0){
    height+=1;
    j=j/2;
  }
  for (e=0;e<height;e++){
    total*=2;
  }

  int *Bst=(int*)malloc(total*sizeof(int));
  assert(Bst);
  for (b=0;b<total;b++){
    Bst[b]=-1;
  }
  makebalance(sort, 0, index-1, Bst, 1, total);
  d=total-1;
  while (Bst[d]==-1){
    d--;
  }
  printf("%d\n",d);
  for (c=1;c<=d;c++){
    printf("%d\n", Bst[c]);
  }
  free(Bst);
  free(sort);
  freetree(root);
  
}

/* Print the usage information and exit the program. */
void print_usage_and_exit(char **argv) {
  fprintf(stderr, "usage: %s [ab]\n", argv[0]);
  exit(EXIT_FAILURE);
}

// create a new BST node 
Node *newNode() 
{ 
  Node *temp =  (Node*)malloc(sizeof(Node)); 
  temp->left = temp->right = NULL; 
  return temp; 
} 

void swap(int *x, int *y) 
{ 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
} 

int inorder(int *sort, int index, int i) { 
  int flag=1, l,k,j=index;
  for (k=0;k<index;k++){
    if (sort[k]==i){
      flag=0;
      return flag;
    }
    else if (sort[k]>i){
      //printf("k%d i%d\n", sort[k], i);
      //printf("sort%d index%d\n", sort[k], k);
      j=k;
      break;
    }

  }
  //printf("%d\n", j);
  for (l=index; l>j;l--){
    swap(sort+l, sort+l-1);
  }
  sort[j]=i;
  return flag;
} 


Node* insert(Node *node, int key) { 
  if (node==NULL){
    Node *new=newNode();
    new->key=key;
    return new;
    //printf("  %d\n  ", (node==NULL));
    
  }
  else if (key < node->key){
    node->left=insert(node->left, key);
    //printf("1 %d\n", key);
  }
  else if (key > node->key){
  
    node->right=insert(node->right, key);
    //printf("2%d\n", key);
  }
  return node;
} 

int maxDepth(Node* node){ 
  if (node==NULL) { 
    return 0; 
  }else{ 

    int lDepth = maxDepth(node->left); 
    int rDepth = maxDepth(node->right); 

    if (lDepth > rDepth){
      return(lDepth+1); 
    }else {
      return(rDepth+1); 
    }
  } 
}  

void freetree(Node* node){
  if (node == NULL){
    return;
  }
  //now onto the recursion
  freetree(node->left );
  freetree(node->right );

  free(node);
}
void makebalance(int* sort, int head, int tail, int* bst, int index, int total){
  //printf("h  %d   t%d     i%d\n", head, tail,index);
  //printf("sorthead%d sorttail%d\n", sort[head], sort[tail]);
  if (head>tail){
    return;
  }else if (head ==tail){
    bst[index]=sort[head];
  }else{  
    int middle;
    middle = (head+tail+1)/2;
    bst[index]=sort[middle];
    //printf("  i%d   bsti%d   m%d\n\n", index, bst[index], middle);
    makebalance(sort, head, middle-1, bst, index*2, total);
    makebalance(sort, middle+1, tail, bst, index*2+1, total);
  }
  return;
}







