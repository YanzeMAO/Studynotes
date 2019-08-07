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
#define LEN 50
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
char startpoint0(int *processed, int len, side_t *data, char startpoint, list_t *before);
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


int main(int argc, char* argv[]){
	//In stage 0, reading the input file
	//Get the number of fragment after reading the input file 
	int len;
	side_t *data;
	data=(side_t*)malloc(LEN*sizeof(side_t));
	char startpoint=argv[1][0];
	len = get_sides(data);
	//stage0(data, len, startpoint);
	//stage1(data, len, startpoint);
	stage2(data, len, startpoint);
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



void stage1(side_t *data, int len, char startpoint){
	printf("\nStage 1 Output \n--------------\n");
	int p, i=0, q=0;
	//Make array to assert which array has been processed
	int processed[len];
	for (p=0; p<len; p++){
		*(processed+p)=0;
	}
	//Find the circuits in total
	list_t *before;
	before=(list_t *)malloc(sizeof(list_t));
	char curpoint;
	while(!allprocessed(processed, len)&& q<len){
		//Find current position 
		char curr;
		curr=startpoint0(processed, len, data, startpoint, before);

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

			if (curpoint==curr){
				break;
			}

		}
		//read_list(route, curr);
		
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
						if (w!=0){
							join=join->next;
						}
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

void stage2(side_t *data, int len, char startpoint){
	printf("\nStage 2 Output \n--------------\n");
	int p, i=0, q=0;

	//Make array to assert which array has been processed
	//Find the circuits in total

	int processed[len];
	for (p=0; p<len; p++){
		*(processed+p)=0;
	}

	//Find the first circuit
    //Find current position 
	char curpoint1;
	curpoint1=startpoint;
	//Initialise the chosen side
	side_t b;
	int j;
	list_t *before;
	before=make_empty_list();
	//Find the best pathway and append in list
	for (j=0; j<len; j++){
		int pos, i, min, k;
		//Find the first unprocessed point
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
				
				if (data[i].end1==curpoint1){
					thispoint=data[i].end2;
					min=data[i].length;
					pos=i;
				}
				else if (data[i].end2==curpoint1) {
					thispoint=data[i].end1;
					min=data[i].length;
					pos=i;
				}
			}
			
			else if (data[i].length==min && (!processed[i])){
				
				if (data[i].end1==curpoint1){
					otherend=data[i].end2;
					if (otherend<thispoint){
						thispoint=otherend;
						pos=i;
					}
				}
				else if(data[i].end2==curpoint1){
					otherend=data[i].end1;
					if (otherend<thispoint){
						thispoint=otherend;
						pos=i;
					}
				
				}
				
			}
			
		}
		//printf("%d pos%d processed\n", pos, processed[pos]);
		b=data[pos];
		//printf("%c %c %d\n", a.end1, a.end2, a.length);
		insert_at_foot(before, b);
		if (b.end1 == curpoint1){
			//New point
			curpoint1=b.end2;
		}
		else if (b.end2 == curpoint1){
			//New point
			curpoint1= b.end1;
		}
		processed[pos]=1;
		if (curpoint1==startpoint){
			break;
		}
	}
	//read_list(before, startpoint);
	//Find all points can be the position for next appending
	int appendpos=0, y, maxscenic=0, finalpos=0;
	char finalpoint, appendpoint=startpoint;
	node_t *side;
	side=before->head;
	y=before->length;
	//Find the largest scenic route
	while (appendpos<=y){
		int canappend=0;
		
		for (int u = 0; u < len; u++){
			if (processed[u]==0){
				
				if (data[u].end1==appendpoint || data[u].end2==appendpoint){
					canappend=1;
					break;
				}
			}
		}

		if (canappend){
			printf("appendpoint%c\n", appendpoint);
			//printf("%p %p", before->head, before->foot);
			before->foot->next=NULL;
			list_t *thisroute;
			thisroute=(list_t*)malloc(sizeof(list_t));
			thisroute->head=before->head;
			thisroute->foot=before->foot;
			thisroute->length=before->length;

			char curpoint;
			int thisprocessed[len];
			for (int t = 0; t < len; t++)
			{
				thisprocessed[t]=processed[t];
			}
			
			int newlen=len-1;
			int secondappend=1;
			while(!allprocessed(thisprocessed, len)&& q<len){
				//Find current position 
				char curr;
				/*for (int o = 0; o < len; o++)
				{
					printf("%d ", thisprocessed[o]);
				}*/
				curr=startpoint0(thisprocessed, newlen, data, startpoint, thisroute);
				if (secondappend)
					curr=appendpoint;
				printf("\nstart%c\n", curr);
				curpoint=curr;
				//Initialise the chosen side
				side_t a;
				int j;
				list_t *route;
				route=make_empty_list();
				printf("oldlist");
				read_list(thisroute, startpoint);
				//Find the best pathway and append in list
				for (j=0; j<len; j++){
					int pos, i, min, k;
					for (k=0; k<len; k++){
						if (!thisprocessed[k]){
							pos=k;
							min=data[k].length;
							break;
						}
					}

					char thispoint='z', otherend;
					for (i=0; i<len; i++){
						if (data[i].length<min && (!thisprocessed[i])){
							
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
						
						else if (data[i].length==min && (!thisprocessed[i])){
							
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
					thisprocessed[pos]=1;

					if (curpoint==curr){
						break;
					}

				}
				//printf("new list");
				read_list(route, curr);
				//printf("appendpos %d\n", appendpos);
				if (secondappend){
					if (curr==startpoint &&appendpos==0){
						route->foot->next=thisroute->head;
						thisroute->head=route->head;
						thisroute->length+=route->length;
					}else{
						int w;
						list_t *newlist;
						newlist=make_empty_list();
						char current;
						current=startpoint;
						node_t *join;
						side_t curside;
						join=(thisroute->head);
						//int process=0;
						
						for (w=0; w<=thisroute->length; w++){
							//printf("%c %c", curr, current);
							if (w==appendpos){
								//read_list(newlist, appendpoint);
								//printf(	"%c %c\n", route->head->data.end1, route->head->data.end2);
								newlist->foot->next=route->head;
								//printf("%c\n", startpoint);
								newlist->foot=route->foot;
								route->foot->next=join;
								
								newlist->length+=(route->length);
							}
							else{
								if (w!=0){
									join=join->next;
								}
								curside=join->data;
								insert_at_foot(newlist, curside);	
								//read_list(newlist, startpoint);		
							}
							//Update current point
							if (join->data.end1==current){
								current=join->data.end2;
							}else{
								current=join->data.end1;
							}
							//read_list(newlist, startpoint);
						}
						thisroute=newlist;
					}
					secondappend=0;
				}else{
					if (curr==startpoint){
						route->foot->next=thisroute->head;
						thisroute->head=route->head;
						thisroute->length+=route->length;
					}else{
						int w;
						list_t *newlist;
						newlist=make_empty_list();
						char current;
						current=startpoint;
						node_t *join;
						side_t curside;
						join=(thisroute->head);
						int process=0;
						
						for (w=0; w<=thisroute->length; w++){
							//printf("%c %c", curr, current);
							if (curr==current && process==0){
								//read_list(newlist, appendpoint);
								//printf(	"%c %c\n", route->head->data.end1, route->head->data.end2);
								newlist->foot->next=route->head;
								//printf("%c\n", startpoint);
								newlist->foot=route->foot;
								route->foot->next=join;
								
								process=1;
								newlist->length+=(route->length);
								
							}
							else{
								if (w!=0){
									join=join->next;
								}
								curside=join->data;
								insert_at_foot(newlist, curside);	
								//read_list(newlist, startpoint);		
							}
							//Update current point
							if (join->data.end1==current){
								current=join->data.end2;
							}else{
								current=join->data.end1;
							}
							//read_list(newlist, startpoint);
						}
						thisroute=newlist;
					}
				}
				i++;
				printf("S2:");
				read_list(thisroute, startpoint);
				q+=1;
				

			}
			int s;
			printf("len:%d", thisroute->length);
			s=scenic(thisroute);
			if (maxscenic<s){
				finalpos=appendpos;
				finalpoint=appendpoint;
				maxscenic=s;
			}

		}
		if (side!=NULL){
			if(side->data.end1==appendpoint){
				appendpoint=side->data.end2;
			}else if (side->data.end2==appendpoint){
				appendpoint=side->data.end1;
			}

			side=side->next;
		}
		
		appendpos++;
	}
	printf("%d %d %c",maxscenic,finalpos, finalpoint);

	

	//Find and display scenic value
	int d=1, total=0, z;
	z=(before->length);
	while (!is_empty_list(before) && z<=y){
		side_t q;
		q=get_head(before);
		int a;
		a=q.length;
		a*=d;
		d+=1;
		total+=a;
		before=remove_head(before);
	}
	printf("S2: Scenic route value is %d\n", total);
	free_list(before);
	before=NULL;
}
int scenic(list_t *list){
	//Find and display scenic value
	int d=1, total=0, length, a;
	length=list->length;
	node_t *edge;
	edge=list->head; //Initialise node_t to be head
	while (d<=length){
		a=edge->data.length;
		a*=d;
		d+=1;
		total+=a;
		edge=edge->next;
	}
	printf("Scenic is %d\n", total);
	return total;
}
char startpoint0(int *processed, int len, side_t *data, char startpoint, list_t *before){
	//empty list before
	if (before->head==NULL)
		return startpoint;

	else{
		int i, j=0, m;
		m=before->length;
		char curpoint=startpoint;
		
		node_t *side;
		side=before->head;
		while (j<m){
			for (i = 0; i < len; i++){
				if (processed[i]==0){
					
					//printf("cur:%c start:%c\n", curpoint, startpoint);
					if (data[i].end1==startpoint || data[i].end2==startpoint){
						return startpoint;
					}
					
					if (data[i].end1==curpoint || data[i].end2==curpoint){
						
						return curpoint;
					}
				}
			}
			//printf("data:%c %c\n", side->data.end1, side->data.end2);
			//printf("curr%c\n", curpoint);
			if(side->data.end1==curpoint){
				curpoint=side->data.end2;
			}else if (side->data.end2==curpoint){
				curpoint=side->data.end1;
			}
			//printf("curr2%c\n", curpoint);
			side=side->next;
			j++;
		}
		
		return curpoint;
	}
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
