#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declarations for the tree implementation and operations..
typedef struct content
{
	char *line;
	struct content *left;
	struct content *right;
	int count;
	int height;
}text_t;
//typedef struct content* text_t;

text_t* create_text();
void append_line(text_t*, char*);
int length_text(text_t*);
char* get_line(text_t*, int);
char* set_line(text_t*, int, char*);
void insert_line(text_t*, int, char*);
char* delete_line(text_t *, int);

void left_rotate(text_t *);
void right_rotate(text_t *);

text_t* stack[5000];
int stack_index=0;


int main()
{  int i, tmp; text_t *txt1, *txt2; char *c;
printf("starting \n");
txt1 = create_text();
txt2 = create_text();
append_line(txt1, "line one" );
if( (tmp = length_text(txt1)) != 1)
{  printf("Test 1: length should be 1, is %d\n", tmp); exit(-1);
}
append_line(txt1, "line hundred" );
insert_line(txt1, 2, "line ninetynine" );
insert_line(txt1, 2, "line ninetyeight" );
insert_line(txt1, 2, "line ninetyseven" );
insert_line(txt1, 2, "line ninetysix" );
insert_line(txt1, 2, "line ninetyfive" );
for( i = 2; i <95; i++ )
	insert_line(txt1, 2, "some filler line between 1 and 95" );
if( (tmp = length_text(txt1)) != 100)
{  printf("Test 2: length should be 100, is %d\n", tmp); exit(-1);
}
printf("found at line 1:   %s\n",get_line(txt1,  1));
printf("found at line 2:   %s\n",get_line(txt1,  2));
printf("found at line 99:  %s\n",get_line(txt1, 99));
printf("found at line 100: %s\n",get_line(txt1,100));
for(i=1; i<=10000; i++)
{  if( i%2==1 )
	append_line(txt2, "A");
else 
	append_line(txt2, "B");
}
if( (tmp = length_text(txt2)) != 10000)
{  printf("Test 3: length should be 10000, is %d\n", tmp); exit(-1);
}
c = get_line(txt2, 9876 );
if( *c != 'B')
{  printf("Test 4: line 9876 of txt2 should be B, found %s\n", c); exit(-1);
}
for( i= 10000; i > 1; i-=2 )
{  c = delete_line(txt2, i);
if( *c != 'B')
{  printf("Test 5: line %d of txt2 should be B, found %s\n", i, c); exit(-1);
}
append_line( txt2, c );
}
for( i=1; i<= 5000; i++ )
{  c = get_line(txt2, i);
if( *c != 'A')
{  printf("Test 6: line %d of txt2 should be A, found %s\n", i, c); exit(-1);
}
}
for( i=1; i<= 5000; i++ )
	delete_line(txt2, 1 );
for( i=1; i<= 5000; i++ )
{  c = get_line(txt2, i);
if( *c != 'B')
{  printf("Test 7: line %d of txt2 should be B, found %s\n", i, c); exit(-1);
}
}
set_line(txt1, 100, "the last line");
for( i=99; i>=1; i-- )
	delete_line(txt1, i);
printf("found at the last line:   %s\n",get_line(txt1,  1));

}

text_t* create_text()
{
	text_t *node = (text_t *) malloc(sizeof(text_t));
	return node;
}

void append_line(text_t *txt, char* line)
{
        text_t *temp = txt;
	text_t *curr;
        stack_index = 0;
	if(temp == NULL || line == NULL)
	{
		printf("root is null !! \n");
		return;
	}
	if(temp->count == 0)
	{ 
		temp->line = (char *) malloc(strlen(line));        
		strcpy(temp->line, line);
		temp->left = NULL;
		temp->right = NULL;
		temp->count = 1;
		temp->height = 1;
		return;
	}
	if(temp->count == 1)
	{
		text_t *temp1 = create_text();
		text_t *temp2 = create_text();
		text_t *temp3 = create_text(); 
		temp2->line = (char *) malloc(strlen(line));        
		strcpy(temp2->line, line);
		temp2->count = 1;
		temp2->left = NULL;
		temp2->right = NULL;

		*temp3 = *temp1;    
		*temp1 = *temp;
		*temp = *temp3;
		temp->left = temp1;   
		temp->right = temp2;
		temp->line = NULL;
		temp->count = 2;
		temp1->height = 1;
		temp2->height = 1;
		temp->height = 2;
		return;
	}
	curr = temp;
	while(curr->right != NULL)
	{
		curr->count++;
		curr->height++;
		stack[stack_index++] = curr;
		curr = curr->right;
	}
	text_t *temp4 = create_text();
	text_t *temp5 = create_text();
	text_t *temp6 = create_text();
	temp4->line = (char *) malloc(strlen(line));
	strcpy(temp4->line, line);
	temp4->count = 1;
	temp4->left = NULL;
	temp4->right = NULL;
	*temp6 = *temp5;
	*temp5 = *curr;
	*curr = *temp6;
	curr->left = temp5;
	curr->right = temp4;
	curr->count = curr->left->count  + curr->right->count;
	temp5->height = 1;
	temp4->height = 1;
	curr->height = 2;
	stack_index--;
	while(stack_index >= 0)
	{
		curr = stack[stack_index--];
		if((curr->right->height - curr->left->height >= 2))
		{
			if(curr->right->right->height == curr->left->height + 1)
				left_rotate(curr);
			else if(curr->right->right->height == curr->left->height)
			{
				right_rotate(curr->right);
				left_rotate(curr);
			}
			continue;
		}
		else if((curr->left->height - curr->right->height >= 2))
		{
			if(curr->left->left->height == curr->right->height+1)
				right_rotate(curr);
			else if(curr->left->left->height == curr->right->height)
			{
				left_rotate(curr->left);
				right_rotate(curr);
			}
			continue;
		}
		if(curr->left->height >= curr->right->height)
			curr->height = curr->left->height+1;
			else
				curr->height = curr->right->height+1;  

	}

}

void right_rotate(text_t *node)
{
	text_t *curr = node;
	text_t *temp = create_text();
	temp->right = curr->right;
	temp->left = curr->left->right;
	curr->left = curr->left->left;
	curr->right = temp;
	temp->count = temp->left->count + temp->right->count;
	curr->count = curr->left->count + curr->right->count;
	if(temp->left->height >= temp->right->height)
		temp->height = temp->left->height+1;
		else
			temp->height = temp->right->height+1;
			if(curr->left->height >= curr->right->height)
				curr->height = curr->left->height+1;
				else
					curr->height = curr->right->height+1;
}

void left_rotate(text_t *node)
{
	text_t *curr = node;
	text_t *temp = create_text();
	temp->left = curr->left;
	temp->right = curr->right->left;
	curr->right = curr->right->right;
	curr->left = temp;
	temp->count = temp->left->count + temp->right->count;
	curr->count = curr->left->count + curr->right->count;
	if(temp->left->height >= temp->right->height)
		temp->height = temp->left->height+1;
		else
			temp->height = temp->right->height+1;
			if(curr->left->height >= curr->right->height)
				curr->height = curr->left->height+1;
				else
					curr->height = curr->right->height+1;
}

int length_text(text_t *txt)
{
	return txt->count;
}

char* get_line( text_t *txt, int index)
{
	if(txt == NULL || index > txt->count || index <= 0)
		return NULL;
	if(index == 1 && txt->count == 1)
		return txt->line;

		while(txt != NULL)
		{
			if(index <= txt->left->count)
				txt = txt->left;
				else
				{
					index = index-txt->left->count;
					txt = txt->right;   
				}
			if(index == 1 && txt->count == 1)
				return txt->line;
		}
}

char* set_line( text_t *txt, int index, char * new_line)
{
	char *oldline;
	if(txt == NULL || index > txt->count || index <= 0 || new_line == NULL)
		return NULL;

	if(index == 1 && txt->count == 1)
	{
		oldline = (char *) malloc(strlen(txt->line));
		strcpy(oldline,txt->line);
		txt->line = (char *) malloc(strlen(new_line));
		strcpy(txt->line,new_line);
		return oldline; 
	}

	while(txt != NULL)
	{
		if(index <= txt->left->count)
			txt = txt->left;
			else
			{
				index = index-txt->left->count;
				txt = txt->right;   
			}
		if(index == 1 && txt->count == 1)
		{ 
			oldline = (char *) malloc(strlen(txt->line));
			strcpy(oldline,txt->line);
			txt->line = (char *) malloc(strlen(new_line));
			strcpy(txt->line,new_line);
			return oldline; 
		}
	}
}


void insert_line( text_t *txt, int index, char * new_line)
{
	text_t *temp = txt;
	text_t *curr;
	stack_index = 0;
	if(temp == NULL || index <=0)
	{
		return;
	} 
	if(index > temp->count)
	{
		append_line(temp,new_line);
		return;
	}
	text_t *temp1 = create_text();
	text_t *temp2 = create_text();
	text_t *temp3 = create_text(); 
	curr = temp;
	temp2->line = (char *) malloc(strlen(new_line));        
	strcpy(temp2->line, new_line);
	temp2->count = 1;
	temp2->left = NULL;
	temp2->right = NULL;
	temp2->height = 1;
	if(temp->count == 1)
	{
		*temp3 = *temp1;    
		*temp1 = *temp;
		*temp = *temp3;
		temp->right = temp1;   
		temp->left = temp2;
		temp->line = NULL;
		temp->count = 2;
		temp1->height = 1;
		temp2->height = 1;
		temp->height = 2;
		return; 
	}
	while(curr->right != NULL)
	{
		curr->count++;
		curr->height++;
		stack[stack_index++] = curr;
		if(index <= curr->left->count)
		{ 
			curr = curr->left;
		}
		else
		{
			index = index-curr->left->count;
			curr = curr->right;   
		}
		if(index == 1 && curr->count == 1)
			break;
	}

	*temp3 = *temp1;    
	*temp1 = *curr;
	*curr = *temp3;
	curr->right = temp1;   
	curr->left = temp2;
	curr->line = NULL;
	curr->count = 2;
	curr->height = 2;
	temp1->height = 1;
	temp1->count = 1;
	temp2->count = 1;
	temp2->height = 1;
	stack_index--;

	while(stack_index >= 0)
	{
		curr = stack[stack_index--];
		if((curr->right->height - curr->left->height >= 2))
		{ 
			if(curr->right->right->height == curr->left->height + 1)
				left_rotate(curr);
			else if(curr->right->right->height == curr->left->height)
			{
				right_rotate(curr->right);
				left_rotate(curr);
			}
			continue;
		}
		else if((curr->left->height - curr->right->height >= 2))
		{
			if(curr->left->left->height == curr->right->height+1)
				right_rotate(curr);
			else if(curr->left->left->height == curr->right->height)
			{
				left_rotate(curr->left);
				right_rotate(curr);
			}
			continue;
		}
		if(curr->left->height >= curr->right->height)
			curr->height = curr->left->height+1;
			else
				curr->height = curr->right->height+1;  

	}

}


char * delete_line(text_t *txt, int index)
{
	text_t *temp = txt;
	text_t *curr, *prev;
	char *eraseline;
	stack_index = 0;
	if(temp == NULL || index <=0 || temp->count == 0 || index > temp->count)
	{
		return NULL;
	} 
	if(temp->count == 1)
	{
		temp->left = NULL;
		temp->right = NULL;
		temp->count = 0;
		eraseline = (char *) malloc(strlen(temp->line));
		strcpy(eraseline,temp->line);
		temp->line = NULL;
		return eraseline;
	}
	curr = temp;
	while(curr->right != NULL)
	{
		stack[stack_index++] = curr;
		prev = curr;
		if(index <= curr->left->count)
		{ 
			curr = curr->left;
		}
		else
		{
			index = index-curr->left->count;
			curr = curr->right;   
		}

		prev->count--;
		if(index == 1 && curr->count == 1)
			break;
	}

	eraseline = (char *) malloc(strlen(curr->line));
	strcpy(eraseline,curr->line);
	if(curr == prev->left)
		*prev = *(prev->right);
	else
		*prev = *(prev->left);  
	//tree balancing.... 
	stack_index--;
	while(stack_index >= 0)
	{
		curr = stack[stack_index--];
		if(curr->left == NULL || curr->right == NULL)
			continue;
		if((curr->right->height - curr->left->height >= 2))
		{ 
			if(curr->right->right->height == curr->left->height + 1)
				left_rotate(curr);
			else if(curr->right->right->height == curr->left->height)
			{
				right_rotate(curr->right);
				left_rotate(curr);
			}
			continue;
		}
		else if((curr->left->height - curr->right->height >= 2))
		{
			if(curr->left->left->height == curr->right->height+1)
				right_rotate(curr);
			else if(curr->left->left->height == curr->right->height)
			{
				left_rotate(curr->left);
				right_rotate(curr);
			}
			continue;
		}
		if(curr->left->height >= curr->right->height)
			curr->height = curr->left->height+1;
			else
				curr->height = curr->right->height+1;  

	}

	return eraseline;
}
