#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 21
#define MAXRANGE 1000
#define MAXSUPER 20000

void stage1(char F[][MAX], int num);
void stage2(char F[][MAX], int num);
void stage3(char F[][MAX], int num);
void capital(char sup[MAXSUPER], char sub[MAX]);
int get_sub_in_superstring(char superstring[MAXSUPER], char substring[MAX]);
int get_sub_tail_superstring(char superstring[MAXSUPER], char substring[MAX]);
int mygetchar();
int max_alignment_in_superstring(char superstring[MAXSUPER], 
	char F[][MAX], int num, int *processed);
int max_alignment_in_superstring3(char superstring[MAXSUPER], 
	char F[][MAX], int num, int *processed);
int read_string_array(char F[][MAX]);




int mygetchar(){
	//The function provided on LMS
	//Scan the next input character
	int nextchar;
	while ((nextchar=getchar()) == '\r') {
	}
	return nextchar;
}


int read_string_array(char F[][MAX]){
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
	//Displaying the total number of fragments and characters read
	printf("\nStage 0 Output\n--------------\n");
	printf("%d fragments read, %d characters in total\n\n", i, k);
	return i;
}


void capital(char sup[MAXSUPER], char sub[MAX]){
	//Capitalise the heading character of substring in the superstring
	int i;
	//Get the position of the first character in substring in superstring
	i = get_sub_in_superstring(sup, sub);
	//Capitalise the 
	char a = toupper(*(sup+i));
	*(sup+i) = a;
}

int get_sub_in_superstring(char superstring[MAXSUPER], char substring[MAX]){
	//Testing if substring can be find inside the superstring
	//Return the position of substring's first letter in superstring
	//Return -1 for non matching

	int i, superlength = 0, sublength = 0;
	//Find the length of superstring
	while (superstring[superlength] != '\0' && superlength < MAXSUPER){
		superlength += 1;
	}

	//Find the length of substring
	while (substring[sublength] !='\0' && sublength < MAX){
		sublength += 1;
	}

	if (strlen(superstring) == 0){
		//For empty superstring, return -1 for non matching
		return -1;
	}
	else{
		//Loop around superstring to find if substring matches
		for (i=0; i <= (superlength-sublength); i++) {
		    if (strncasecmp(superstring+i, substring, sublength) == 0) {
		    	//Return the first position that the matching is found
				return i;
		    }
		}
	}
	//Return -1 if not found
	return -1;
}



int get_sub_tail_superstring(char superstring[MAXSUPER], char substring[MAX]){
	//Testing if head of substring can match the tail of superstring
	//return the number of matching letters in superstring and substring
	//return 0 for no matching characters
	int num = 0, i, j = 0;
	int superlength = 0, sublength = 0;
	//Find the length of superstring
	while (superstring[superlength] != '\0' && superlength < MAXSUPER){
		superlength += 1;
	}
	//Find the length of substring
	while (substring[sublength] != '\0' && sublength < MAX){
		sublength += 1;
	}
	if (strlen(superstring) == 0){
		//For empty superstring, return 0 for no overlapping letters
		return 0;
	}
	//Testing if first i characters of substring matches superstring
	for (i = 1; i <= sublength; i++){
		if (i>superlength)
			//Come to the end of superstring
			return num;
		//Loop from i th character
		//Test if tail of superstring matches the head of substring
		j = 0;
		//Find if first i characters matches last i characters
		while (j < i){
			//Compare each character regardless of capitalised or not
			if (toupper(superstring[superlength-i+j])!=toupper(substring[j])){
				//Finding the character that is not matching
				break;
			}
			//If all i letters in substring matches superstring
			if (j == (i-1)){
				//Updates the number of head-to-tail matching 
				num = i;   
			}
			j++;
		}
	}
	//Return the number of overlaping characters from head to tail
	return num;
}


void stage1(char F[][MAX],int num){
	//Display the superstrings processed in method in stage 1

	char superstring[MAXSUPER];	
	int len, i = 0, index, overlap;
	//Initialise the superstring by copying the first subtring in it
	strcpy(superstring, F[0]);

	//Reading the input strings one by one, modifying the superstring
	while (i < num){
		//Find the head-to-tail overlaping length
		overlap=get_sub_tail_superstring(superstring, F[i]);
		//Define if the substring can be found in superstring 
		index=get_sub_in_superstring(superstring, F[i]);
		//If subtring cannot be found in superstring
		if (index == -1){
			//Join the superstring and substring together
			//Find the suffix of superstring
			char source[MAX];
			strcpy(source, F[i]+overlap);
			//Appending the suffix behind the superstring
			strcat(superstring, source);
		}
		//Capitalise the first character of substring
		capital(superstring, F[i]);
		//Find the length of the new superstring
		len=strlen(superstring);
		//Display the result of the modified data
		printf("%2d : frg= %2d, slen= %3d %s\n", i, i, len, superstring);
		i+=1;
	}
}	

void stage2(char F[][MAX], int num){
	//Display the superstrings processed in method in stage 2

	char superstring[MAXRANGE];	
	int len = 0, i = 0, frag, processed[num], k, index, overlap;
	//Initialise the superstring by copying the first subtring in it
	strcpy(superstring, F[0]);

	//Initialise the processed pointer all zero to indicate none is processed
	for (k = 0; k<num; k++){
		processed[k] = 0;
	}

	//Adding fragments into the superstring one by one
	while (i < num){
		//Find which fragment has max alignment with superstring
		frag=max_alignment_in_superstring(superstring, F, num, processed);
		//Find the head-to-tail overlaping length of fragment
		overlap=get_sub_tail_superstring(superstring, F[frag]);
		//Define if the substring can be found inside the superstring
		index=get_sub_in_superstring(superstring, F[frag]);

		//If the fragment can not be found in superstring
		if (index == -1){
			//Join the superstring head to tail with the substring
			char source[MAX];  
			//Find the tail of substring
			strcpy(source, F[frag]+overlap);  
			//Join the suffix and the superstring together
			strcat(superstring, source);
		}
		//Capitalise the first letter of fragment
		capital(superstring, F[frag]);
		//Find length of new superstring
		len = strlen(superstring);  
		//Display the result of the modified data and new superstring
		printf("%2d : frg= %2d, slen= %3d ", i, frag, len);
		printf("%s\n", superstring); 
		i+=1;
	}
}



int max_alignment_in_superstring(char superstring[MAXSUPER], 
	char F[][MAX], int num, int *processed){
	//Find the position of max matching between substring and super string

	//Initialise the substring to compare with superstring
	char substring[MAX];
	int maxfrag = 0, i, pos, j;

	//Find the first available position
	for (j = 0; j < num; j++){
		if (*(processed+j) == 0){
			pos=j;
			break;
		}
	}

	//Find the fragment that matches the most of the superstring
	for (i=0; i<num; i++){
		//Find the max matching letters for each fragment
		int maxalign;
		//Make a copy of fragment to find out the matching part
		strcpy(substring, F[i]);	
		if (get_sub_in_superstring(superstring, substring) != -1){
			//The substring can be find within the superstring
			maxalign = strlen(substring);
		}else{
			//Can not find the substring in superstring
			//The substring can only be appended back to the superstring
			maxalign = get_sub_tail_superstring(superstring, substring);
		}
		//Compare length of matching part of the string with the previous max
		if ((maxalign>maxfrag) && (*(processed+i) == 0)){
			//Test if the substring has been used already previously
			pos = i;
			//Update the maximum alignment
			maxfrag = maxalign;  
		}
	}

	//Mark the used fragment processed in the processed array
	*(processed+pos) = 1;
	//Return the index of fragment chosen this time
	return pos;
}



int max_alignment_in_superstring3(char superstring[MAXSUPER], 
	char F[][MAX], int num, int *processed){
	//Find the position of max matching between substring and super string
	int i, pos, j, head, maxfrag = 0;

	//Find the first available position
	for (j = 0; j < num; j++){
		//If the fragment have not been processed, it is available
		if (*(processed+j) == 0){
			pos = j;
			break;
		}
	}

	//Loop around all fragments to find the max number of matching fragment
	for (i = 0; i < num;i++){
		//Find the max matching letters for each fragment
		int maxalign;
		char substring[MAX];
		//Make a copy of the subtring being processed
		strcpy(substring, F[i]);
		if (get_sub_in_superstring(superstring, substring) != -1){
			//The substring can be find within the superstring
			maxalign = strlen(substring);
		}else{
			//Find overlap of fragment appended back to the superstring
			maxalign = get_sub_tail_superstring(superstring, substring);
			//Find overlap of fragment appended in front of the superstring
			head = get_sub_tail_superstring(substring, superstring);
			//Find if the fragment is better to be joined in head or tail
			if (head >= maxalign)
				maxalign = head;
		}

		//Compare the matching part of the current string with the max before
		if ((maxalign > maxfrag) && (*(processed+i) == 0)){
			//If bigger alligned fragment has not been processed, choose it
			pos = i; 
			//Update the max alignment fragment
			maxfrag = maxalign;   
		}
	}

	//Mark the used fragment processed in the processed array
	*(processed+pos) = 1;
	//Return the postion of fragment with max alignment
	return pos;
}


void stage3(char F[][MAX], int num){
	//Find the position of max matching between substring and super string
	char superstring[MAXRANGE];	
	int len = 0, i = 0, frag, processed[num], k, head, tail, index;
	//Initialise the superstring by copying the first subtring in it
	strcpy(superstring, F[0]);
	//Initialise the processed array to indicate no fragments is processed
	for (k = 0; k < num; k++){
		processed[k] = 0;
	}
	//Loop around the array of fragments to process the superstring
	while (i < num){
		//Find the fragment that matches the superstring most
		frag = max_alignment_in_superstring3(superstring, F, num, processed);
		//Find the different alignments in joining in head or tail to super
		tail = get_sub_tail_superstring(superstring, F[frag]);
		head = get_sub_tail_superstring(F[frag], superstring);
		//Check if the fragment can be found inside the superstring 
		index = get_sub_in_superstring(superstring, F[frag]);
		if (index == -1){
			char source[MAXSUPER];
			if (tail >= head){
				//Find the suffix string and append behind the superstring
				strcpy(source, F[frag] + tail);
				strcat(superstring, source);
			}else{
				//Find the prefix string from the fragment
				strncpy(source, F[frag], (strlen(F[frag]) - head));
				source[(strlen(F[frag]) - head)] = '\0';
				//Make a temporary copy of superstring to process
				char tempsuper[MAXSUPER];
				char *p = tempsuper;
				//Join the prefix and superstring together
				p = strcat(source, superstring);
				//Points superstring to the new superstring
				strcpy(superstring, p);
				//Reset the pointers, free their memory
				memset(tempsuper, 0, strlen(tempsuper));
				memset(source, 0, strlen(source));
			}
		}
		//Capitalise the first character of the fragment
		capital(superstring, F[frag]);
		//Find length of the new superstring
		len = strlen(superstring);
		//Display the result of the modified data
		printf("%2d : frg= %2d, slen= %3d %s\n", i, frag, len, superstring);
		i += 1;
	}
}





int main(void){
	//Initialise the two dimensional char array to capture input words
	char File[MAXRANGE][MAX];
	//In stage 0, reading the input file
	//Get the number of fragment after reading the input file 
	int i = read_string_array(File);
	//Find the superstring joined together by method in stage 1 
	printf("\nStage 1 Output\n--------------\n");
	stage1(File, i);
	//Find the superstring joined together by method in stage 2 
	printf("\nStage 2 Output\n--------------\n");	
	stage2(File, i);
	//Find the superstring joined together by method in stage 3
	printf("\nStage 3 Output\n--------------\n");
	stage3(File, i);
	return 0;
}