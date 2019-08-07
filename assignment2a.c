/* Solution to comp10002 Assignment 2, 2018 semester 2.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Yanze Mao
   Dated:     10/10/2018

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX 52
#define LEN 7
/* type definitions ----------------------------------------------------------*/

typedef int data_t;

typedef struct node node_t;

struct node {
	data_t data;
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

typedef struct {
	char end1, end2;
	int length;
} side_t;

typedef struct{
	char vertex;
	int sides;
} point_t;

typedef struct{
	char point1;
	char point2;
}twopoint_t;

/* end type definitions ------------------------------------------------------*/

/* function prototypes -------------------------------------------------------*/

// list operations
list_t *make_empty_list(void);
int    is_empty_list(list_t*);
void   free_list(list_t*);
list_t *insert_at_head(list_t*, data_t);
list_t *insert_at_foot(list_t *list, data_t value);
data_t get_head(list_t *list);
list_t *get_tail(list_t *list);

//Get input data
int mygetchar();

int find_point_side(char F[MAX], side_t data);
void get_sides(side_t data[MAX], char F[MAX][LEN], int len);
//int scenic(list_t list);
int read_string_array(char F[][LEN]);

/* end function prototypes ---------------------------------------------------*/


/*------------------------------------------------------------------------------
   Code that follows is written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
------------------------------------------------------------------------------*/
/*
list_t
*make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

int
is_empty_list(list_t *list) {
	assert(list!=NULL);
	return list->head==NULL;
}

void
free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}

list_t
*insert_at_head(list_t *list, data_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = list->head;
	list->head = new;
	if (list->foot==NULL) {
		// this is the first insertion into the list 
		list->foot = new;
	}
	return list;
}

list_t
*insert_at_foot(list_t *list, data_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = NULL;
	if (list->foot==NULL) {
		// this is the first insertion into the list 
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

data_t
get_head(list_t *list) {
	assert(list!=NULL && list->head!=NULL);
	return list->head->data;
}

list_t
*get_tail(list_t *list) {
	node_t *oldhead;
	assert(list!=NULL && list->head!=NULL);
	oldhead = list->head;
	list->head = list->head->next;
	if (list->head==NULL) {
		// the only list node just got deleted 
		list->foot = NULL;
	}
	free(oldhead);
	return list;
}
*/

int main(int argc, char* argv[]){

	char File[MAX][LEN];
	//In stage 0, reading the input file
	//Get the number of fragment after reading the input file 
	int len, i;
	len = read_string_array(File);
	printf("len %d\n", len);
	side_t *data;
	data=(side_t*)malloc(len*sizeof(side_t));
	get_sides(data, File, len);
	for (i=0; i<len; i++){
		//printf("%d\n", data[i].length);
		printf("%s\n", File[i]);
	}

	//stage1(data);
	//stage2(data);
	free(data);
	data=NULL;
	return 0;
}

int mygetchar(){
	//Scan the next input character
	int nextchar;
	while ((nextchar=getchar()) == '\r') {
	}
	return nextchar;
}

int read_string_array(char F[][LEN]){
	//Reading the input into the array
	int c, i = 0, j = 0, k = 0;
	//Reading the characters one by one
    while((c = mygetchar()) != EOF){
    	if(c=='\n'){
    		//The current string is finished, start a new one
    		F[i][j] = '\0';
    		i++;
    		j = 0;
    	}
    	else{
    		//Keep reading characters in string
    		F[i][j] = c;
    		j++;
    		k++;
    	}
	}
	return i;
}

void get_sides(side_t *data, char F[][LEN], int len){
	//Read the side data from the array of characters
	int i;
	printf("%c\n", F[0][2]);
	//Loop around get the points one by one
	for (i=0; i<len; i++){
		char end1, end2;
		int m;
		end1=F[i][0];
		
		end2=F[i][2];
		data[i].end1 = end1;
		data[i].end2 = end2;
		printf("%d\n", F[i][4]);
		
		if (strlen(F[i])==5){
			m = F[i][4] - 48;
			data[i].length = m;
			
		}
		else if(strlen(F[i])==6){
			m = 10*(F[i][4] - 48)+F[i][5]-48;
			data[i].length = m;
		}
		
	}

}

/*
void stage1(data){
	int i, j, k, l, h, len, vertex, p, sum = 0;
	//Make array to assert which array has been processed

	len=sizeof(data)/sizeof(side_t);
	int processed[MAX];
	for (p=0; p<len; p++){
		*(processed+p)=0;
	}
	side_t a;
	//Find vertex and the sides
	point_t P[MAX]
	vertex=find_point_side(data, P);
	//Find mininum length
	minside=minlength(data, processed);
	minlength=minside->length;
	maxlength=find_max(data);

	//Find total length
	for (j=0; j<len; j++){
		int sidelength = data[j] -> length;
		sum+=sidelength;
	}

	//Find odd points
	odd=find_odd(P);

	//Find even points
	even=find_even(P);

	//Find the start point
	if (odd==0)
		startpoint = startpoint0(data);
	else if(odd==1){
		char point= odd1(P);
		startpoint= startpoint1(data, point);
	}else if (odd=2){
		char point1, point2;
		twopoint_t two;
		two= odd2(P);
		startpoint=startpoint2(data, point1, point2);
	}


	printf("S0: Map is composed of %d vertices and %d edges\n", vertex, len);
	printf("S0: Min. edge value: %d\n", minlength);
	printf("S0: Max. edge value: %d\n", maxlength);
	printf("S0: Total value of edges: %d\n", sum);
	printf("S0: Route starts at \"%c\"", startpoint);
	printf("S0: Number of vertices with odd degree: %d", odd);
	printf("S0: Number of vertices with even degree: %d", even);
	if (odd>2){
		exit(EXIT_FAILURE);
	}else if (even==2){
		printf("S0: Multigraph is traversable");
	}else{
		printf("S0: Multigraph is Eulerian");
	}

	//Get head
	char point;
	point = find_start(data, minlength(data), odd);

	list_t route=make_empty_list();
	//Find the best pathway and append in list
	//Find the pathway of each points
	for (k=0; k<MAX; k++){
		point_t A;
		A = F[k];
		if (isodd(A->sides)){
			point = A;
			break;
		}
	}

	//Append the point in list
	for (j=0; j<len; j++){

		for (i=0; i<len; i++){
			a=*(data+i);
			if (a->end1 == point){
				insert_at_foot(route, a);
				point=a->end2;
				processed[i]=1;
				break;
			}
			else if (a->end2 == point){
				point= a->end1;
				processed[i]=1;
				break;
			}
		}
		if (point==startpoint){
			break;
		}
	}
	
	l=scenic(data);
	printf("S1: Scenic route value is %d", l);

	//Find the route and display
	printf("S1: %c", startpoint);
	char current=startpoint;
	for (j=0; j<len; j++){
		side_t q;
		q=get_head(route);
		char next;
		if (q->end1==current){
			next=q->end2;
		}else{
			next=q->end1;
		}
		printf("-%d->%c", q->length, next);
		//move the loccation to next element
		route=get_tail(route);
	}
	
}

void find_point_side(F[MAX], data){
	//Find total number of sides each point contains
	int i, j, len, num=0;
	len=sizeof(data)/sizeof(side_t);
	//Loop around each sides
	for (i=0; i<len; i++){

		side_t a;
		a=*(data+i);
		//Loop around each points 
		for (j=0; j<MAX; j++){
			//If the end already exist in the list
			if (F[j]->point == a->end1){
				F[j]->sides+=1;
				break;
			}
			//Create a new point
			if (j==MAX-1){
				point_t A;
				A->point=a->end1;
				A->sides=1;
				F[num]=A;
				num+=1;
			}
		}
	}

}


char startpoint0(side_t *data){
	int i, min=0;
	char vertex;
	for (i=0; i<MAX; i++){
		if (data->length > min){
			vertex=data->end1;
			min=data->length;
		}
	}

	return vertex;
}

char startpoint1(side_t *data, char point){
	int i, min=0;
	for (i=0; i<MAX; i++){
		if (data->length > min){
			if (data->end1==point){
				vertex=data->end1;
				min=data->length;
			} else if (data->end2==point){
				vertex=data->end1;
				min=data->length;
			}
		}
	}

}

char startpoint2(side_t *data, char point1, char point2){
	int i, min=0;
	for (i=0; i<MAX; i++){
		if  (data->length > min){
			if (data->end1==point1 || data->end1==point2){
				vertex=data->end1;
				min=data->length;
			}else if(data->end2==point1 || data->end2==point1){
				vertex=data->end2;
				min=data->length;
			}
		}
	}

}


int scenic(list){
	int i=1, total=0;
	while (list->foot!=NULL){
		side_t a;
		a= get_head(list);
		int s;
		s=a->length;
		s*=i;
		i+=1;
		total+=s;
		list = get_tail(list);
	}
	return total;
}
*/