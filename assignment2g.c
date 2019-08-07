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
#define DISPLAY 5
#define FIRST 10
/* type definitions --------------------------------------------------------*/
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
/* end type definitions ----------------------------------------------------*/

/* function prototypes -----------------------------------------------------*/
list_t *make_empty_list(void);
int    is_empty_list(list_t* list);
void   free_list(list_t* list);
list_t *insert_at_foot(list_t *list, side_t value);
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
void add_circuit(list_t *circuits, int *processed, 
	int len, side_t *data, char startpoint);
int find_route(side_t *data, point_t *P, int len, int vertex);
void join(list_t *list1, char start1, list_t *list2, char start2);
char startpoint0(int *processed, int len, side_t *data, 
	char startpoint, list_t *before);
int scenic(list_t *list);
void read_list(list_t *route,  char startpoint);
/* end function prototypes -------------------------------------------------*/


/*----------------------------------------------------------------------------
   Code that follows is written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
----------------------------------------------------------------------------*/

int main(int argc, char* argv[]){
	//In stage 0, reading the input file
	//Get the number of fragment after reading the input file 
	int len;
	side_t *data;
	data=(side_t*)malloc(LEN*sizeof(side_t));
	char startpoint=argv[1][0];
	len = get_sides(data);
	stage0(data, len, startpoint);  //display stage 0
	stage1(data, len, startpoint);  //display stage 1
	stage2(data, len, startpoint);  //display stage 2
	free(data);  //Free memory for data
	data=NULL;  //get rid of the data pointer
	printf("Ta daaa!\n");
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
    		//If the input exceeds capacity, double memory space
			current_size *= 2;
			data = realloc(data, 
				current_size*sizeof(*data));
			if (data==NULL)
				exit(EXIT_FAILURE);
    	}
		data[len].end1 = point1;  //scan the first point
		data[len].end2 = point2;  //scan the second point
		data[len].length = c;   //scan the length
    	len++;  //increment length
	}
	return len;
}

void stage0(side_t *data, int len, char startpoint){
	printf("\nStage 0 Output \n--------------\n");
	int j, vertex, sum = 0, odd, even;
	//Find vertex and the sides
	point_t P[MAX];  //used to store points
	vertex=find_point_side(P, data, len);
	//Find mininum length and max length
	int minlength, maxlength;
	minlength = minlen(data, len);
	maxlength = maxlen(data, len);
	//Find total length
	for (j=0; j<len; j++){
		int sidelength = data[j].length;   //find the length of side
		sum+=sidelength;    //increment total number of edge by 1
	}
	odd=num_odd(P, vertex);  //Find odd points
	even=num_even(P, vertex);  //Find even points
	printf("S0: Map is composed of %d vertices and %d edges\n", vertex, len);
	printf("S0: Min. edge value: %d\n", minlength);
	printf("S0: Max. edge value: %d\n", maxlength);
	printf("S0: Total value of edges: %d\n", sum);
	printf("S0: Route starts at \"%c\"\n", startpoint);
	printf("S0: Number of vertices with odd degree: %d\n", odd);
	printf("S0: Number of vertices with even degree: %d\n", even);
	if (even==2){
		printf("S0: Multigraph is traversable\n");
		exit(EXIT_FAILURE);  //exit if not Eulerian
	}else if (odd!=0){		
		exit(EXIT_FAILURE);  //exit if not Eulerian
	}else{
		printf("S0: Multigraph is Eulerian\n");
	}
}

int num_odd(point_t P[MAX], int vertex){
	//Find the number of vertex with odd connecting edges
	int i, j=0;
	for (i=0; i<vertex; i++){
		if ((P[i].sides)%2!=0){
			j+=1;  //increment j by 1 for odd point
		}
	}
	return j;
}

int num_even(point_t P[MAX], int vertex){
	//Find the number of vertex with even connecting edges
    int i, j=0;
	for (i=0; i<vertex; i++){
		if ((P[i].sides)%2==0){
			j+=1;  //increment j by 1 for even point
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
			min=data[i].length;  //updat min length
		}
	}
	return min;  //return the final minimum value
}

int maxlen(side_t *data, int len){
	int max, i;
	//Initialise min to be the length of the first side
	max=data[0].length;
	for (i=1; i<len; i++){
		if(max<data[i].length){
			max=data[i].length;  //updaate max length
		}
	}
	return max;   //return the final max value
}

int find_point_side(point_t P[MAX], side_t *data, int len){
	//Find total number of sides each point contains
	int i, num=0;
	//Loop around each sides
	for (i=0; i<len; i++){
		side_t a;
		a=*(data+i);
		//Loop around each points 
		int j = 0, k = 0; //initialise variables
		while(j <= num){
			if (j == num){
				point_t A;  //Create a new point
				A.vertex=a.end1;  //find name of point
				A.sides=1;  //initialise side length to be 1
				P[num]=A;   //append the point to array
				num+=1;  //increment the number of point by one
				break;
			}			
			else if (P[j].vertex == a.end1){
				P[j].sides+=1;   //increment 1 if the end already exist
				break;    //finish the searching once found the point
			}
			j++;   //inrement the number of point searched
		}
		while (k<=num){
			//Create a new point
			if (k==num){
				point_t B;  //Create a new point
				B.vertex=a.end2;  //find name of point
				B.sides=1;   //initialise side length to be 1
				P[num]=B;   //append the point to array
				num+=1;     //increment the number of point by one
				break;    //finish searching after create the point
			}
			//If the end already exist in the list
			else if (P[k].vertex == a.end2){
				P[k].sides+=1;  //increment 1 if the end already exist
				break;   //finish the searching once found the point
			}
			k++;   //inrement the number of point searched
		}
	}
	return num;   //return the total number of points
}


void stage1(side_t *data, int len, char startpoint){
	printf("\nStage 1 Output \n--------------\n");
	int p, index=0, q=0, j, displaylast=0;  //initialise variables
	//Make array to assert which array has been processed
	int processed[len];
	for (p=0; p<len; p++){
		*(processed+p)=0;  //initally all sides unprocessed
	}
	list_t *before;   //used to store previous pathway
	before=make_empty_list();
	char curpoint;  //find the current point 
	while(!allprocessed(processed, len)&& q<len){
		char curr;  //Find current position
		curr=startpoint0(processed, len, data, startpoint, before);
		curpoint=curr;
		side_t a; //Initialise the chosen side
		list_t *route;
		route=make_empty_list();
		//Find the best pathway and append in list
		for (j=0; j<len; j++){
			int pos, i, min, k;
			for (k=0; k<len; k++){
				if (!processed[k]){
					pos=k;  //Find the first possible side to be used
					min=data[k].length;  //initialise min length
					break;
				}
			}
			char thispoint='z', otherend;
			for (i=0; i<len; i++){
				if (data[i].length<min && (!processed[i])){					
					if (data[i].end1==curpoint){
						thispoint=data[i].end2;
						min=data[i].length;  //Update min value
						pos=i;  //Find new position
					}
					else if (data[i].end2==curpoint) {
						thispoint=data[i].end1;
						min=data[i].length;  //Update min value
						pos=i;  //Find new position
					}
				}				
				else if (data[i].length==min && (!processed[i])){					
					if (data[i].end1==curpoint){
						otherend=data[i].end2; //Compare ASCII code
						if (otherend<thispoint){
							thispoint=otherend;
							pos=i;
						}
					}
					else if(data[i].end2==curpoint){
						otherend=data[i].end1; //Compare ASCII code 
						if (otherend<thispoint){
							thispoint=otherend;
							pos=i;
						}					
					}				
				}				
			}
			a=data[pos];
			insert_at_foot(route, a);
			if (a.end1 == curpoint){
				curpoint=a.end2;  //New point is the other end
			}
			else if (a.end2 == curpoint){
				curpoint= a.end1;  //New point is the other end
			}
			processed[pos]=1;
			if (curpoint==curr){
				break;
			}
		}		
		if (index==0)
			before=route;  //first ciruit is the starting one
		else{
			if (curr==startpoint){
				//Join two circuits head to tail
				route->foot->next=before->head;
				before->head=route->head;
				before->length+=route->length;
			}
			else{
				list_t *newlist;
				newlist=make_empty_list();
				char current;
				current=startpoint;
				node_t *join;
				side_t curside;
				join=(before->head);
				int process=0, w;
				for (w=0; w<=before->length; w++){
					if (curr==current && process==0){
						//Insert new circuit in appending position
						newlist->foot->next=route->head;
						newlist->foot=route->foot;
						route->foot->next=join;
						process=1;
						newlist->length+=(route->length);
					}
					else{
						//Append sides from old list to new 
						if (w!=0){
							join=join->next;  //change into next side
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
				}
				free_list(before);
				before=newlist;
			}
		}
		index++;
		if (index < FIRST ||((index%5)==0)){
			printf("S1:");
			read_list(before, startpoint);
		}
		if ((index%5)==0){
			displaylast=0;
		}else{
			displaylast=1;
		}
		q+=1;
	}
	if (displaylast){
		printf("S1:");
		read_list(before, startpoint);
	}
	int d;
	d=scenic(before);   //Find the scenic value and display
	printf("S1: Scenic route value is %d\n", d);
	free_list(before);  //free memory used by before
	before=NULL;  //Point before to NULL
}

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
*insert_at_foot(list_t *list, side_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = NULL;
	if (list->foot==NULL) {
		//This is the first insertion into the list 
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	list->length+=1;
	return list;
}

void read_list(list_t *route, char startpoint){
	node_t *cur;        //find the location of edge being tested now
	cur=(route->head);  //initially find the first edge
	char current;       //find the point being processed now
	current=startpoint;  //start from the first point of circuit
	printf("%c", startpoint); //display start point of circuit
	int g, print=0;
	g = route->length;
	while (g>0){
		char next;
		if (cur->data.end1 == current){
			next=cur->data.end2;
		}else{
			next=cur->data.end1;
		}
		//Display the data head and tail
		if (print <= DISPLAY || g <= (DISPLAY+1)){
			printf("-%d->%c", cur->data.length, next);
		}else if (print==(DISPLAY+1)){
			printf("...");
		}
		if (g==(DISPLAY+2) && (g < print)){
			printf("%c", next);
		}
		cur=cur->next;  //Move the location to next element
		current = next;

		g-=1;
		print+=1;
	}
	printf("\n");
	cur = NULL;
}

int allprocessed(int *processed, int len){
	//Test if all elements has been processed
	int i;
	for (i = 0; i < len; i++)
	{
		if (processed[i] == 0)
			return 0;
	}
	return 1;
}

int scenic(list_t *list){
	//Find and display scenic value of the pathway
	int d=1, total=0, length, a;  
	length = list->length;   //find the length of the list
	node_t *edge;    //find the side to be counted
	edge=list->head; //Initialise node_t to be head
	while (d<=length){
		a=edge->data.length;
		a*=d;      //multiply scenic value with weight
		d+=1;      //increment index by 1
		total+=a;   //aggregate value to total
		edge=edge->next;  //find the next edge
	}
	return total;
}

char startpoint0(int *processed, int len, side_t *data, 
	char startpoint, list_t *before){
	if (before->head == NULL)
		return startpoint;  //empty list, start at starting point
	else{
		int i, j = 0, m;    //initialise all the varibales
		m=before->length;  //find the length of the prevous list
		char curpoint=startpoint;   //start from starting point
		node_t *side;    //make a pointer to find data in list
		side=before->head;  //initially start from head of list
		while (j < m){
			//Loop around the previous cicuit to find available point 
			for (i = 0; i < len; i++){
				if (processed[i] == 0){		
					if (data[i].end1 == curpoint ||
						data[i].end2 == curpoint){
						return curpoint; //points in unprocessed edge
					}
				}
			}
			if(side->data.end1 == curpoint){
				curpoint=side->data.end2;  //Find next point in cirsuit
			}else if (side->data.end2 == curpoint){
				curpoint=side->data.end1;  //Find the other end of edge
			}
			side=side->next;  //If not found find next point in circuit
			j++;
		}
		return curpoint;  //return the final chosen point
	}
}

void stage2(side_t *data, int len, char startpoint){
	printf("\nStage 2 Output \n--------------\n");
	int p, i=0, q=0, displaylast=0; //initialise variables
	//Make array to assert which array has been processed
	int processed[len];
	for (p=0; p<len; p++){
		*(processed+p)=0;	//Assign each edges to initially unprocessed
	}    
	char curpoint1;  //Find current position 
	curpoint1=startpoint;
	//Initialise the chosen side
	side_t b;
	int j;
	list_t *before;
	before=make_empty_list();
	//Find the first circuit
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
					min=data[i].length;   //update the min
					pos=i;   //update the position
				}
				else if (data[i].end2==curpoint1) {
					thispoint=data[i].end1;
					min=data[i].length;   //update the min
					pos=i;   //update the position
				}
			}
			else if (data[i].length==min && (!processed[i])){
				if (data[i].end1==curpoint1){
					otherend=data[i].end2;
					if (otherend<thispoint){
						thispoint=otherend;
						pos=i;   //update the position
					}
				}
				else if(data[i].end2==curpoint1){
					otherend=data[i].end1;
					if (otherend<thispoint){
						thispoint=otherend;
						pos=i;  //update the position
					}
				}
			}
		}
		b=data[pos];  //find the side
		insert_at_foot(before, b);  //insert the side into the route
		if (b.end1 == curpoint1){
			curpoint1=b.end2; //New point
		}
		else if (b.end2 == curpoint1){
			curpoint1= b.end1; //New point
		}
		processed[pos]=1;
		if (curpoint1==startpoint){
			break;
		}
	}
	printf("S2:");
	read_list(before, startpoint);
	//Find all points can be the position for next appending
	int appendpos=0, y, maxscenic=0, finalpos=0;
	char finalpoint, appendpoint=startpoint;
	node_t *side;  //initialise a side
	side=before->head;   //initialise the side to be starting one
	y=before->length;
	//Find the largest scenic route based on possible ways to to extend 
	//the first circuit from different vertices
	while (appendpos<=y){
		int canappend=0, u;
		for (u = 0; u < len; u++){
			if (processed[u]==0){
				if (data[u].end1==appendpoint ||
					data[u].end2==appendpoint){
					canappend=1;  //this point can append circuit
					break;  //finiish searching once found
				}
			}
		}
		if (canappend){
			before->foot->next=NULL;   //initialise the foot point NULL
			list_t *thisroute;   //make a new route of the append point
			thisroute=(list_t*)malloc(sizeof(list_t));
			thisroute->head=before->head;
			thisroute->foot=before->foot;
			thisroute->length=before->length;
			char curpoint;     //find the processed point 
			int thisprocessed[len], t, j;   //make a copy of the processed
			for (t = 0; t < len; t++)
			{
				thisprocessed[t]=processed[t];  //copy processed 
			}
			int newlen=len-1;    //new length is one less from initial
			int secondappend=1;  //append start postion 
			while(!allprocessed(thisprocessed, len)&& q<len){
				char curr;     //Find start position 
				curr=startpoint0(thisprocessed, newlen, 
					data, startpoint, thisroute);  
				if (secondappend)
					curr=appendpoint; //firstly position on appended point
				curpoint=curr;    //start from first point
				side_t a;   //Initialise the chosen side
				list_t *route;   //find the new circuit
				route=make_empty_list();
				//Find the best pathway and append in list
				for (j = 0; j < len; j++){
					int pos, i, min, k;
					for (k = 0; k< len; k++){
						if (!thisprocessed[k]){
							pos=k;  //find the first available position
							min=data[k].length;  //initialise min
							break;   //finish searching once found
						}
					}
					char thispoint='z', otherend;  //initialise variables
					for (i = 0; i < len; i++){
						if (data[i].length < min && (!thisprocessed[i])){
							if (data[i].end1 == curpoint){
								thispoint = data[i].end2;
								min = data[i].length;
								pos = i;   //find new position
							}
							else if (data[i].end2 == curpoint) {
								thispoint = data[i].end1;
								min = data[i].length;
								pos = i;  //find new position
							}
						}
						else if (data[i].length == min && 
							(!thisprocessed[i])){
							if (data[i].end1 == curpoint){
								otherend = data[i].end2;  //compare ASCII
								if (otherend < thispoint){
									thispoint = otherend;
									pos = i; //find new position
								}
							}
							else if(data[i].end2 == curpoint){
								otherend = data[i].end1;  //compare ASCII
								if (otherend < thispoint){
									thispoint = otherend;
									pos = i;  
								}
							}
						}	
					}
					a = data[pos];  //find the side being inserted 
					insert_at_foot(route, a); //append the side in list
					if (a.end1 == curpoint){
						curpoint = a.end2; //new point is the other end
					}
					else if (a.end2 == curpoint){
						curpoint = a.end1; //new point is the other end
					}
					thisprocessed[pos] = 1;
					if (curpoint==curr){
						break;   //finish the circuit once come back 
					}
				}
				if (secondappend){
					//firstly join the circuit on the appending position
					if (curr==startpoint && appendpos==0){
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
						for (w=0; w<=thisroute->length; w++){
							if (w==appendpos){
								//Join the circuits head to tail
								newlist->foot->next=route->head;
								newlist->foot=route->foot;
								route->foot->next=join;
								newlist->length+=(route->length);
							}
							else{
								//Append sides from old list to new 
								if (w!=0){
									join=join->next;  //go to next side
								}
								curside=join->data;   
								insert_at_foot(newlist, curside); 		
							}
							//Update current point after a loop
							if (join->data.end1==current){
								current=join->data.end2;  //other end
							}else{
								current=join->data.end1;  //other end
							}
						}
						thisroute=newlist;  //assign the old route to new
					}
					secondappend = 0;  //not append to certainly again
				}else{
					if (curr == startpoint){
						route->foot->next=thisroute->head;
						thisroute->head=route->head;
						thisroute->length+=route->length;
					}else{
						list_t *newlist;
						newlist=make_empty_list();
						char current;  //find the current position
						current=startpoint; //start from beginning
						node_t *join;  //used to get the data
						side_t curside;  //used to store side
						join=(thisroute->head);  //start from head
						int process=0, w;
						for (w=0; w<=thisroute->length; w++){
							if (curr==current && process==0){
								newlist->foot->next=route->head;
								newlist->foot=route->foot;
								route->foot->next=join;
								process=1;  //new route is processed
								newlist->length+=(route->length);
							}
							else{
								if (w != 0){
									join=join->next; //get next data
								}
								curside=join->data;  //find the data
								insert_at_foot(newlist, curside);		
							}
							//Update current point
							if (join->data.end1 == current){
								current=join->data.end2;
							}else{
								current = join->data.end1;
							}
						}
						thisroute=newlist;  //assign old to new route
					}
				}
				i++;
				q += 1;
			}
			int s;  //find scenic value of this route
			s=scenic(thisroute);
			if (maxscenic<s){
				finalpos=appendpos;  // compare the value with previous max
				finalpoint=appendpoint;
				maxscenic=s;  //get max route compare old and new scenic 
			}
		}
		if (side!=NULL){
			if(side->data.end1==appendpoint){
				appendpoint=side->data.end2;  //next point in 1st circuit
			}else if (side->data.end2==appendpoint){
				appendpoint=side->data.end1;  //find other end of side
			}
			side=side->next;  //get next data
		}
		appendpos++;  //increment append postion by 1
	}
	q=0; //initialise the number of data being processed
	int e, secondappend=1, index=1;  //append to the chosen point second time
	char curpoint;  //find the current position
	while(!allprocessed(processed, len)&& q<len){
		char curr;   //Find start position 
		curr=startpoint0(processed, len, data, startpoint, before);
		if (secondappend)
			curr=finalpoint;
		curpoint=curr;  //start from curr
		side_t a;  //Initialise the chosen side
		list_t *route;
		route=make_empty_list();
		//Find the ideal circuit pathway and append in list
		for (e=0; e<len; e++){
			int pos, i, min, k;
			for (k=0; k<len; k++){
				if (!processed[k]){
					pos=k;  //find the position of first available side
					min=data[k].length;  //initialise min value
					break;  //finish once a side is found
				}
			}
			char thispoint='z', otherend; //find the available points 
			for (i=0; i<len; i++){
				if (data[i].length<min && (!processed[i])){
					if (data[i].end1==curpoint){
						thispoint=data[i].end2; //find the point with min
						min=data[i].length;  //find the new min value
						pos=i;   //find the new position
					}
					else if (data[i].end2==curpoint) {
						thispoint=data[i].end1;   //find the point with min
						min=data[i].length;  //find the new min value
						pos=i;   //find the new position 
					}
				}
				else if (data[i].length==min && (!processed[i])){
					if (data[i].end1==curpoint){
						otherend=data[i].end2;  //compare ASCII of points
						if (otherend<thispoint){
							thispoint=otherend;   //find the new point
							pos=i;  //find the new position
						}
					}
					else if(data[i].end2==curpoint){
						otherend=data[i].end1;  //compare ASCII of points
						if (otherend<thispoint){
							thispoint=otherend;  //find the new point
							pos=i;   //find the new position
						}
					}
				}
			}
			a=data[pos];  //find the side used
			insert_at_foot(route, a);  //insert data in the list
			if (a.end1 == curpoint){
				curpoint=a.end2;  //New point
			}
			else if (a.end2 == curpoint){
				curpoint= a.end1;   //New point
			}
			processed[pos]=1;
			if (curpoint==curr){
				break;  //finish the loop once back to commencing point
			}
		}
		if (secondappend){
			if (curr==startpoint &&finalpos==0){
				//Join two circuits head to tail
				route->foot->next=before->head;  
				before->head=route->head;       
				before->length+=route->length;
			}else{
				int w;
				list_t *newlist;     //create a new list
				newlist=make_empty_list();
				char current;       //find the current position
				current=startpoint;  //start from startpoint
				node_t *join;        //find the data
				side_t curside;      //find the side
				join=(before->head);  //start with head
				for (w=0; w<=before->length; w++){
					if (w==finalpos){
						//Join the new route to the new list
						newlist->foot->next=route->head;
						newlist->foot=route->foot;
						route->foot->next=join;
						newlist->length+=(route->length);
					}
					else{
						//get data from old circuit one by one
						if (w!=0){
							join=join->next;
						}
						curside=join->data;  //find the side
						insert_at_foot(newlist, curside);	
					}
					if (join->data.end1==current){
						current=join->data.end2;  //Update current
					}else{
						current=join->data.end1;  //Update current
					}
				}
				before=newlist;  //assign old route to new route
			}
			secondappend = 0;  //second append is done
		}else{
			if (curr==startpoint){
				route->foot->next=before->head;
				before->head=route->head;
				before->length+=route->length;
			}else{
				list_t *newlist;  //create a new list
				newlist=make_empty_list();  
				char current;   //find the current point
				current=startpoint;  //start from beginning point
				node_t *join;   //create a pointer to get data
				side_t curside;  //find the side
				join=(before->head);  //start from fisrt side
				int process=0, w;
				for (w=0; w<=before->length; w++){
					if (curr==current && process==0){	
						newlist->foot->next=route->head;
						newlist->foot=route->foot;
						route->foot->next=join;
						process=1;  //mark as processed
						newlist->length+=(route->length);
					}
					else{
						if (w!=0){
							join=join->next;  //get next data
						}
						curside=join->data;  //find the side
						insert_at_foot(newlist, curside);  //append side
					}
					//Update current point
					if (join->data.end1==current){
						current=join->data.end2;  //new point
					}else{
						current=join->data.end1;  //new point
					}
				}
				before=newlist;  //assign the old route to be new route
			}
		}
		index++;
		if (index < FIRST ||((index % DISPLAY)==0)){
			printf("S2:");    //display the circuit found
			read_list(before, startpoint);
		}
		if ((index%DISPLAY)==0){
			displaylast=0;
		}else{
			displaylast=1;
		}
		q+=1;
	}
	if (displaylast){
		printf("S2:");    //display the last circuit found
		read_list(before, startpoint);
	}
	printf("S2: Scenic route value is %d\n", maxscenic);
	free_list(before);  //free the memory
	before=NULL;     //assign pointer to be NULL
}