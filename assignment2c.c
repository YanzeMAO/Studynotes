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
#define LEN 5
/* type definitions ----------------------------------------------------------*/

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


typedef struct node node_t;

struct node {
	side_t data;
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
	int length;
} list_t;


/* end type definitions ------------------------------------------------------*/

/* function prototypes -------------------------------------------------------*/

// list operations
list_t *make_empty_list(void);
int    is_empty_list(list_t* list);
void   free_list(list_t* list);
list_t *insert_at_head(list_t*, side_t value);
list_t *insert_at_foot(list_t *list, side_t value);
side_t get_head(list_t *list);
list_t *get_tail(list_t *list);

//Get input data
int is_int(char a);
int find_point_side(point_t P[MAX], side_t *data, int len);
int get_sides(side_t *data);
void stage0(side_t *data, int len, char startpoint);
void stage1(side_t *data, int len, char startpoint);
void stage2(side_t *data, int len, char startpoint);
int minlen(side_t *data, int len);
int maxlen(side_t *data, int len);
int num_odd(point_t P[MAX], int vertex);
int num_even(point_t P[MAX], int vertex);
int allprocessed(int *processed, int len);
void add_circuit(list_t *circuits, int *processed, int len, side_t *data, char startpoint);
int find_route(side_t *data, point_t *P, int len, int vertex);
void join(list_t *list1, char start1, list_t *list2, char start2);
char startpoint0(int *processed, int len, side_t *data, char startpoint, char availablepoints[MAX], int av);
int scenic(list_t *list);
void read_list(list_t *route,  char startpoint);
int newpoint(char availablepoints[MAX], char new, int av);
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

list_t
*make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	list->length=0;
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
*insert_at_head(list_t *list, side_t value) {
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
	list->length+=1;
	return list;
}

list_t
*insert_at_foot(list_t *list, side_t value) {
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
	list->length+=1;
	return list;
}

side_t
get_head(list_t *list) {
	assert(list!=NULL && list->head!=NULL);
	return list->head->data;
}

list_t
*remove_head(list_t *list) {
	node_t *oldhead;
	assert(list!=NULL && list->head!=NULL);
	oldhead = list->head;
	list->head = list->head->next;
	if (list->head==NULL) {
		// the only list node just got deleted 
		list->foot = NULL;
	}
	list->length-=1;
	free(oldhead);
	return list;
}
/*
int
read(side_t *data) {
	word_t one_word;
	char **all_words;
	size_t current_size=INITIAL;
	int numdistinct=0, totwords=0, i, found;
	all_words = (char**)malloc(INITIAL*sizeof(*all_words));
	exit_if_null(all_words, "initial allocation");
	while (getword(one_word, MAXCHARS) != EOF) {
		totwords = totwords+1;
		linear search in array of previous words... 
		found = 0;
		for (i=0; i<numdistinct && !found; i++) {
			found = (strcmp(one_word, all_words[i]) == 0);
		}
		if (!found) {
			 a new word exists, but is there space? 
			if (numdistinct == current_size) {
				current_size *= 2;
				all_words = realloc(all_words, 
					current_size*sizeof(*all_words));
				exit_if_null(all_words, "reallocation");
			}
			ok, there is definitely space in array 
			all_words[numdistinct] =
				(char*)malloc(1+strlen(one_word));
			exit_if_null(all_words[numdistinct],
				"string malloc");
			 and there is also a space for the new word 
			strcpy(all_words[numdistinct], one_word);
			numdistinct += 1;
		}
	}
}

*/


int main(int argc, char* argv[]){
	//In stage 0, reading the input file
	//Get the number of fragment after reading the input file 
	int len;
	side_t *data;
	data=(side_t*)malloc(LEN*sizeof(side_t));
	char startpoint=argv[1][0];
	len = get_sides(data);
	stage0(data, len, startpoint);
	stage1(data, len, startpoint);
	//stage2(data, len, startpoint);
	free(data);
	data=NULL;
	printf("Ta daaa!\n");
	return 0;
}

int is_int(char a){
	if (a=='0' || a=='1'|| a=='2' || a=='3' || a=='4'|| a=='5' ||
		a=='6' || a=='7'|| a=='8' || a=='9'){
		return 1;
	}
	return 0;
}

int get_sides(side_t *data){
	//Read the side data from the array of characters
	char point1, point2;
	//Reading the input into the array
	int c, len=0, current_size=LEN;
	//Reading the characters one by one
    while((scanf("%c %c %d\n", &point1, &point2, &c)==3)){
    	if(len==current_size){
			current_size *= 2;
			data = realloc(data, 
				current_size*sizeof(*data));
			if (data==NULL)
				exit(EXIT_FAILURE);
    	}

		data[len].end1 = point1;
		data[len].end2 = point2;
		data[len].length = c;

    	len++;

	}

	return len;
}


void stage0(side_t *data, int len, char startpoint){
	printf("\nStage 0 Output \n--------------\n");
	int j, vertex, sum = 0, odd, even;
	//Find vertex and the sides
	point_t P[MAX];
	vertex=find_point_side(P, data, len);
	/*

	for (int k=0; k<vertex; k++){
		printf("%c %d\n",P[k].vertex, P[k].sides);
	}
	*/
	//Find mininum length
	int minlength, maxlength;
	minlength=minlen(data, len);
	maxlength=maxlen(data, len);
	//Find total length
	for (j=0; j<len; j++){
		int sidelength = data[j].length;
		sum+=sidelength;
	}
	//Find odd points
	odd=num_odd(P, vertex);

	//Find even points
	even=num_even(P, vertex);

	printf("S0: Map is composed of %d vertices and %d edges\n", vertex, len);
	printf("S0: Min. edge value: %d\n", minlength);
	printf("S0: Max. edge value: %d\n", maxlength);
	printf("S0: Total value of edges: %d\n", sum);
	printf("S0: Route starts at \"%c\"\n", startpoint);
	printf("S0: Number of vertices with odd degree: %d\n", odd);
	printf("S0: Number of vertices with even degree: %d\n", even);
	if (even==2){
		printf("S0: Multigraph is traversable\n");
		exit(EXIT_FAILURE);
	}else if (odd!=0){
		
		exit(EXIT_FAILURE);
	}else{
		printf("S0: Multigraph is Eulerian\n");
	}

}

int newpoint(char availablepoints[MAX], char new, int av){
	for (int i = 0; i < av; i++)
	{
		if (availablepoints[i]==new)
			return 0;
	}
	return 1;
}

void stage1(side_t *data, int len, char startpoint){
	printf("\nStage 1 Output \n--------------\n");
	int p, i=0, q=0, av=1;
	//Make array to assert which array has been processed
	int processed[len];
	for (p=0; p<len; p++){
		*(processed+p)=0;
	}
	//Find the circuits in total
	list_t *before;
	before=(list_t*)malloc(50*sizeof(list_t));
	//Make a list to test all available points to be used
	char availablepoints[MAX];
	availablepoints[0]=startpoint;
	char curpoint;
	while(!allprocessed(processed, len)&& q<len){
		//Find current position 
		char curr;
		curr=startpoint0(processed, len, data, startpoint, availablepoints, av);

		curpoint=curr;
		//Initialise the chosen side
		side_t a;
		int j;
		list_t *route;
		route=make_empty_list();
		//Find the best pathway and append in list
		for (j=0; j<len; j++){
			int pos, i, min, k;
			for (k=0; k<len; k++){
				if (!processed[k]){
					pos=k;
					min=data[k].length;
					break;
				}
			}

			char thispoint='z', otherend;
			for (i=0; i<len; i++){
				if (data[i].length<min && (!processed[i])){
					
					if (data[i].end1==curpoint){
						thispoint=data[i].end2;
						min=data[i].length;
						pos=i;
					}
					else if (data[i].end2==curpoint) {
						thispoint=data[i].end1;
						min=data[i].length;
						pos=i;
					}
				}
				
				else if (data[i].length==min && (!processed[i])){
					
					if (data[i].end1==curpoint){
						otherend=data[i].end2;
						if (otherend<thispoint){
							thispoint=otherend;
							pos=i;
						}
					}
					else if(data[i].end2==curpoint){
						otherend=data[i].end1;
						if (otherend<thispoint){
							thispoint=otherend;
							pos=i;
						}
					
					}
					
				}
				
			}
			//printf("%d pos%d processed\n", pos, processed[pos]);
			a=data[pos];
			//printf("%c %c %d\n", a.end1, a.end2, a.length);
			insert_at_foot(route, a);
			if (a.end1 == curpoint){
				//New point
				curpoint=a.end2;
			}
			else if (a.end2 == curpoint){
				//New point
				curpoint= a.end1;
			}
			processed[pos]=1;
			if (newpoint(availablepoints, curpoint, av)){
				availablepoints[av]=curpoint;
				av+=1;
			}
			printf("\n%c  %d\n", curpoint, av);*/
			if (curpoint==curr){
				break;
			}

		}
		read_list(route, curr);
		
		if (i==0)
			before=route;
		else{

			if (curr==startpoint){
				route->foot->next=before->head;
				before->head=route->head;

				before->length+=route->length;
			}
			
			else{
				int w;
				list_t *newlist;
				newlist=make_empty_list();
				char current;
				current=startpoint;
				node_t *join;
				side_t curside;
				join=(before->head);
				int process=0;
				for (w=0; w<=before->length; w++){
					
					if (curr==current && process==0){
						newlist->foot->next=route->head;
						newlist->foot=route->foot;
						route->foot->next=join;
						process=1;
						newlist->length+=(route->length);
						
					}
					else{
						if (w!=0)
						join=join->next;
						curside=join->data;
						insert_at_foot(newlist, curside);						
					}
					//Update current point
					if (join->data.end1==current){
						current=join->data.end2;
					}else{
						current=join->data.end1;
					}
					//read_list(newlist, startpoint);
					

				}
				before=newlist;
			}
		}
		i++;
		printf("S1:");
		read_list(before, startpoint);
		q+=1;
		
	}

	//Find and display scenic value
	char current=curpoint;
	int d=1, total=0, y;
	y=(before->length);
	while (!is_empty_list(before) && d<=y){
		side_t q;
		q=get_head(before);
		char next;
		if (q.end1==current){
			next=q.end2;
		}else{
			next=q.end1;
		}
		int a;
		a=q.length;
		a*=d;
		d+=1;
		total+=a;
		//Move the loccation to next element
		current=next;
		before=remove_head(before);
		
	}
	printf("S1: Scenic route value is %d\n", total);
	free_list(before);
	before=NULL;
}

/*
void join(list_t* list1, char start1, list_t* list2, char start2){
	//circuit 1 is the new one, circuit 2 is the route before

	if (start1==start2){
		list2->foot->next=list1->head;
		list2->foot=list1->foot;
		list2->length+=list1->length;
	}
	
	else{
		int i;
		list_t *newlist;
		newlist=make_empty_list();
		char current;
		current=start2;
		node_t *join;
		side_t curside;
		join=(list2->head);
		int process=0;
		for (i=0; i<=list2->length; i++){
			if (start1==current&&process==0){

				newlist->foot->next=list1->head;
				newlist->foot=list1->foot;
				list1->foot->next=join;
				process=1;
				newlist->length+=list1->length;
				
			}
			else{
				curside=join->data;

				insert_at_foot(newlist, curside);
				
			}

			
			//update current point
			if (join->data.end1==current){
				current=join->data.end2;
			}else{
				current=join->data.end1;
			}
			read_list(newlist, start2);
			join=join->next;

		}
		list2=newlist;
		
	}
	
}
*/

void read_list(list_t *route, char startpoint){
	node_t *cur;
	cur=(route->head);
	char current;
	current=startpoint;
	printf("%c", startpoint);
	int g;
	g=route->length;
	while (g>0){
		char next;
		if (cur->data.end1==current){
			next=cur->data.end2;
		}else{
			next=cur->data.end1;
		}

		//printf("q: %c %c\n", q.end1, q.end2);
		printf("-%d->%c", cur->data.length, next);
		//move the loccation to next element
		cur=cur->next;
		current=next;
		g-=1;

	}
	printf("\n");
	cur=NULL;
	
}

int allprocessed(int *processed, int len){
	for (int i = 0; i < len; i++)
	{
		if (processed[i]==0)
			return 0;
	}
	return 1;
}
/*
void stage2(side_t *data, int len, char startpoint){
	printf("\nStage 2 Output \n--------------\n");
	int p, i=0;
	//Make array to assert which array has been processed
	int processed[len];
	for (p=0; p<len; p++){
		*(processed+p)=0;
	}
	//Find the circuits in total
	list_t *before;
	before=(list_t*)malloc(50*sizeof(list_t));

	char curpoint;
	while(!allprocessed(processed, len)){

		//Find current position 
		char curr;
		curr=startpoint0(processed, len, data, startpoint, availablepoints, av);

		curpoint=curr;
		//Initialise the chosen side
		side_t a;
		int j;
		list_t *route;
		route=make_empty_list();
		//Find the best pathway and append in list
		for (j=0; j<len; j++){
			int pos=0, i, min;
			min=data[0].length;
			for (i=0; i<len; i++){
				if (data[i].length<min && (data[i].end1==curpoint || 
					data[i].end2==curpoint) &&(!processed[i])){
					min=data[i].length;
					pos=i;
				}
			}
			//printf("%d\n", pos);
			a=data[pos];
			//printf("%c %c %d\n", a.end1, a.end2, a.length);
			insert_at_foot(route, a);
			if (a.end1 == curpoint){
				//New point
				curpoint=a.end2;
			}
			else if (a.end2 == curpoint){
				//New point
				curpoint= a.end1;
			}
			//printf("%c\n", curpoint);

			processed[pos]=1;
			if (curpoint==curr){
				break;
			}

		}
		if (i==0)
			before=route;
		else{

			if (curr==startpoint){
				route->foot->next=before->head;
				before->head=route->head;

				before->length+=route->length;
			}
			
			else{
				int w;
				list_t *newlist;
				newlist=make_empty_list();
				char current;
				current=startpoint;
				node_t *join;
				side_t curside;
				join=(before->head);
				int process=0;
				for (w=0; w<=before->length; w++){
					
					if (curr==current && process==0){

						newlist->foot->next=route->head;
						newlist->foot=route->foot;
						route->foot->next=join;
						process=1;
						newlist->length+=(route->length);
						
					}
					else{
						if (w!=0)
						join=join->next;
						curside=join->data;
						insert_at_foot(newlist, curside);						
					}
					//update current point
					if (join->data.end1==current){
						current=join->data.end2;
					}else{
						current=join->data.end1;
					}
					//read_list(newlist, startpoint);
					

				}
				before=newlist;
			}
		}
		i++;

		printf("S2:");
		read_list(before, startpoint);
	}


	//Find the route and display
	
	char current=curpoint;
	int d=1, total=0;
	while (!is_empty_list(before)){
		side_t q;
		q=get_head(before);
		char next;
		if (q.end1==current){
			next=q.end2;
		}else{
			next=q.end1;
		}
		int a;
		a=q.length;
		a*=d;
		d+=1;
		total+=a;
		//printf("q: %c %c\n", q.end1, q.end2);
		//printf("-%d->%c", a, next);
		//move the loccation to next element
		current=next;
		before=remove_head(before);
		
	}
	printf("S1: Scenic route value is %d\n", total);
	free_list(before);
	before=NULL;
}
*/
char startpoint0(int *processed, int len, side_t *data, char startpoint, char availablepoints[MAX], int av){
	int i, start=0;
	char curpoint;

	for (i = 0; i < len; i++)
	{
		if (processed[i]==0 && (!newpoint(availablepoints, data[i].end1, av) || !newpoint(availablepoints, data[i].end2, av))){
			if (data[i].end1==startpoint || data[i].end2==startpoint){
				start=1;
			}
			curpoint=data[i].end1;
		}

	}
	if (start)
		return startpoint;
	else
		return curpoint;
}

int num_odd(point_t P[MAX], int vertex){

	int i, j=0;
	for (i=0; i<vertex; i++){
		if ((P[i].sides)%2!=0){
			j+=1;
		}
	}
	return j;
}
int num_even(point_t P[MAX], int vertex){
    int i, j=0;
	for (i=0; i<vertex; i++){
		if ((P[i].sides)%2==0){
			j+=1;
		}
	}
	return j;
}

int minlen(side_t *data, int len){
	int min, i;
	//Initialise min to be the length of the first side
	min=data[0].length;
	for (i=1; i<len; i++){
		if(min>data[i].length){
			min=data[i].length;
		}
	}
	return min;
}

int maxlen(side_t *data, int len){
	int max, i;
	//Initialise min to be the length of the first side
	max=data[0].length;
	for (i=1; i<len; i++){
		if(max<data[i].length){
			max=data[i].length;
		}
	}
	return max;
}

int find_point_side(point_t P[MAX], side_t *data, int len){
	//Find total number of sides each point contains
	int i,num=0;
	//Loop around each sides
	for (i=0; i<len; i++){
		side_t a;
		a=*(data+i);
		//Loop around each points 
		int j=0, k=0;
		while(j<=num){

			//Create a new point
			if (j==num){
				point_t A;
				A.vertex=a.end1;
				A.sides=1;
				P[num]=A;
				num+=1;
				break;
			}			
			//If the end already exist in the list
			else if (P[j].vertex == a.end1){
				P[j].sides+=1;
				break;
			}
			j++;
		}
		while (k<=num){
			//Create a new point
			if (k==num){
				point_t B;
				B.vertex=a.end2;
				B.sides=1;
				P[num]=B;
				num+=1;
				break;
			}
			//If the end already exist in the list
			else if (P[k].vertex == a.end2){
				P[k].sides+=1;
				break;
			}
			k++;
		}
	}

	return num;
}

/*
int scenic(list_t *list){
	int i=1, total=0;
	while (list->foot!=NULL){
		side_t a;
		a= get_head(list);
		int s;
		s=a.length;
		printf("%d\n", s);
		s*=i;
		i+=1;
		total+=s;
		list = get_tail(list);
	}
	return total;
}
*/