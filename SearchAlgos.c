#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<limits.h>
int number_of_nodes,no_of_alphabets=0;
int dfs(int upper_triangular_matrix[number_of_nodes][number_of_nodes],char,char,int,char h[]);
int bfs(int upper_triangular_matrix[number_of_nodes][number_of_nodes],char,char,int,char h[]);
int ucs(int upper_triangular_matrix[number_of_nodes][number_of_nodes],char,char,int,char h[]);

int main()
{
	char node_alphabets[20],start_variable,end_variable;
	int i,number_of_nodes_copy,edge_number,j,row_number,column_number,file_numeric_value,two_digit_calc=0;
    char file_character[25];
    FILE *fp;

    fp = fopen("data.txt","r");//read file

    if(fp == NULL)
    {
        perror("Error while opening file");
        exit(EXIT_FAILURE);
    }

    fgets(file_character,25,fp);
    printf("The number of nodes is %c\n",file_character[0]);
    printf("The number of edges is %c%c\n",file_character[2],file_character[3]);
    
	number_of_nodes_copy = number_of_nodes = (int)(file_character[0]) - 48;
    edge_number = ((int)(file_character[2]) - 48)* 10 + ((int)(file_character[3])) - 48;
    
    int numeric_matrix[number_of_nodes][number_of_nodes],upper_triangular_matrix[number_of_nodes][number_of_nodes];
    
    for(i = 0; i < number_of_nodes ; i++)//initialize the numeric_matrix
	{
		for( j = 0 ; j < number_of_nodes ; j++)
		{
			numeric_matrix[i][j] = 0;
		}
	}
    
    fgets(file_character,25,fp);
    start_variable = file_character[0];
    end_variable = file_character[2];
    
    printf("The Start Nodes is %c\n",start_variable);
    printf("The Goal Node is %c\n",end_variable);
    
    while(number_of_nodes_copy != 0)
	{
		fgets(file_character,25,fp);
		node_alphabets[no_of_alphabets] = file_character[4];//to record all node alphabets present in file in node_alphabet array
		number_of_nodes_copy = number_of_nodes_copy - 1;
		no_of_alphabets++;
	}
	
	
	while(edge_number != 0)
	{
		fgets(file_character,25,fp);
		for( i = 0 ; i < no_of_alphabets ; i++)
		{
			if(file_character[0] == node_alphabets[i])
				row_number = i;
			if(file_character[2] == node_alphabets[i])
				column_number = i;	
		}
		file_numeric_value = (int)(file_character[4]) - 48;//to get the edge cost(single digit)
		if(isdigit(file_character[5]) != 0)//to get the egde cost if it is two digit number
		{
			two_digit_calc = (int)(file_character[5]) - 48;
			file_numeric_value = file_numeric_value * 10 + two_digit_calc;
		}
		two_digit_calc = 0;
		for( i = 0 ; i < number_of_nodes ; i++)
		{
			for( j = 0 ; j < number_of_nodes ; j++)
			{
				if(i == row_number && j == column_number || i == column_number && j == row_number)
				{
					numeric_matrix[i][j] = file_numeric_value;//filling the numeric_matrix with values read
					break;
				}
			}
		}
		edge_number--;
	}
	
	printf("The matrix formed is :\n\n");
	for( i = 0 ; i < number_of_nodes ; i++)
	{
		for( j = 0 ; j < number_of_nodes ; j++)
		{
			if(i>j)
				upper_triangular_matrix[i][j] = 0;
			else
				upper_triangular_matrix[i][j] = numeric_matrix[i][j];//to form the upper triangular matrix
		}
	}
	
	for( i = 0 ; i < number_of_nodes ; i++)
	{
		for( j = 0 ; j < number_of_nodes ; j++)
		{
			printf("%d ",upper_triangular_matrix[i][j]);//to print the upper triangular matrix
		}
		printf("\n");
	}
	
    fclose(fp);
    
    dfs(upper_triangular_matrix, start_variable, end_variable, number_of_nodes, node_alphabets);
    bfs(upper_triangular_matrix, start_variable, end_variable, number_of_nodes, node_alphabets);
    ucs(upper_triangular_matrix, start_variable, end_variable, number_of_nodes, node_alphabets);
    return 0;
}

int dfs(int upper_triangular_matrix[number_of_nodes][number_of_nodes], char start_variable, char end_variable, int number_of_nodes, char node_alphabets[])
{
	int y,i,q, next_node_to_check=0, node_index_value=0, node_alphabets_copy_counter=0, node_alphabets_copy_checker=0, f=0;
	char node_alphabets_copy[no_of_alphabets];
	
	printf("\nDFS:\n");
	printf("\nThe First Node visited is : %c\n",start_variable);
	
	for( y = 0 ; y < number_of_nodes ; y++)
	{
		for( i = 0 ; i < number_of_nodes ; i++)
		{
			if(upper_triangular_matrix[next_node_to_check][i] != 0)
			{
				for(q = 0 ; q < node_alphabets_copy_counter ; q++)
				{
					if(node_alphabets_copy[node_alphabets_copy_counter] == node_alphabets[i])//check whether the copy the node aphabet is present in the copy array
					{
						node_alphabets_copy_checker = 1;
						break;
					}
				}
				if(node_alphabets_copy_checker != 1)//put copy of the node alphabet in the copy array
				{
					node_index_value = i;
					node_alphabets_copy[node_alphabets_copy_counter] = node_alphabets[node_index_value];
					node_alphabets_copy_counter++; 
				}
				node_alphabets_copy_checker = 0;//reset counter
				f = i;
			}
			else if((++f) == number_of_nodes)//print the node at end of traversing the array
			{
				if(node_alphabets[node_index_value] != end_variable)//print as next node if not the goal node
				{
					printf("The Next Node visited is  : %c\n",node_alphabets[node_index_value]);
					next_node_to_check = node_index_value;
				}
				else
				{
					printf("The Next Node visited is  : %c\n",end_variable);//print as goal node when reached
					printf("The Goal Node is reached\n");
					f = 0;
				}
					
			}
			if(f == 0)
				break;
		}
		if(f == 0)
			break;
		
	}
	return 0;
}

int bfs(int upper_triangular_matrix[number_of_nodes][number_of_nodes], char start_variable, char end_variable, int number_of_nodes, char node_alphabets[])
{
	int y,i,u,q, next_node_to_check=0, node_index_value=0, node_alphabets_copy_counter=0, node_alphabets_copy_checker=0, f=0;
	char node_alphabets_copy[no_of_alphabets];
	
	printf("\n\nBFS:\n");
	printf("\nThe First Node visited is : %c\n",start_variable);
	
	for( y = 0 ; y < number_of_nodes ; y++)
	{
		for( i = 0 ; i < number_of_nodes ; i++)
		{
			if(upper_triangular_matrix[next_node_to_check][i] != 0)
			{
				for(q = 0 ; q < node_alphabets_copy_counter ; q++)//check whether the copy the node aphabet is present in the copy array
				{
					if(node_alphabets_copy[q] == node_alphabets[i])
					{
						node_alphabets_copy_checker = 1;
						break;
					}
				}
				if(node_alphabets_copy_checker != 1)//put copy of the node alphabet in the copy array
				{
					node_index_value = i;
					node_alphabets_copy[node_alphabets_copy_counter] = node_alphabets[node_index_value];
					node_alphabets_copy_counter++; 	
				}
				node_alphabets_copy_checker = 0;//reset counter
				f = i;
			}
			else if((++f) == number_of_nodes)//print the node at end of traversing the array
			{
				if(node_alphabets_copy[0] != end_variable)//print as next node if not the goal node
				{
					printf("The Next Node visited is  : %c\n",node_alphabets_copy[0]);
					for( q = 0 ; q < no_of_alphabets ; q++)//to find index of the node visited
					{
						if(node_alphabets_copy[0] == node_alphabets[q])
						{
							next_node_to_check = q;
							break; 
						}
					}
					for( u = 0 ; u < node_alphabets_copy_counter - 1 ; u++)//to remove the first element from the array
					{
						node_alphabets_copy[u] = node_alphabets_copy[u+1];
					}	
					node_alphabets_copy_counter--;
				}
				else
				{
					printf("The Next Node visited is  : %c\n",end_variable);//print as goal node when reached
					printf("The Goal Node is reached\n");
					f = 0;
				}
					
			}
			if(f == 0)
				break;
		}
		if(f == 0)
			break;
		
	}
	return 0;
}


int ucs(int a[number_of_nodes][number_of_nodes], char start_variable, char end_variable, int number_of_nodes, char node_alphabets[])
{
	int cost_matrix[number_of_nodes];
	int i,j,y,k=0,min,cost=0,f=1,visited_counter=0,u,q,visit_counter=0,b=1;
	char visited[number_of_nodes],visit[number_of_nodes];

	for (i = 0; i < number_of_nodes; ++i)
	{
			cost_matrix[i] = a[k][i];
	}
	
	printf("\n\nUCS:\n");
	printf("\nThe First Node visited is : %c\n",start_variable);
	visited[visited_counter] = start_variable;
	visited_counter++;
	
	for( y = 0 ; y < number_of_nodes ; y++)
	{

		min = INT_MAX;
		if (y != 0)
		{
			for(i = 0 ; i < number_of_nodes ; i++)
			{
				if(a[k][i] != 0)
				{
					if(cost_matrix[i] + a[k][i] >= a[k][i])
					{
						cost_matrix[i] = a[k][i];
					}
				}
			}
		}
		
		for (i = 0; i < number_of_nodes; i++)
		{
			if(min > cost_matrix[i] && cost_matrix[i] != 0)
			{
				min = cost_matrix[i];
				k = i;
			}
		}
		
		cost_matrix[k] = INT_MAX;

		if(node_alphabets[k] != end_variable)
		{	
			printf("The next node visited is  : %c\n", node_alphabets[k]);
			visited[visited_counter] = node_alphabets[k];
			visited_counter++;
		}
		else
		{
			printf("The Next Node visited is  : %c\n",end_variable);//print as goal node when reached
			printf("The Goal Node is reached\n");
			visited[visited_counter] = end_variable;
			f = 0;
		}
		if(f == 0)
			break;
	}
	u = visited_counter + 1;
	f = 1;
	for(y = 0 ; y < number_of_nodes ; y++)
	{
		for(i = 0 ; i < number_of_nodes ; i++)
		{
			if(visited[visited_counter] == node_alphabets[i])//to get node value from node_alphabet array
			{
				visit[visit_counter] = visited[visited_counter];//put the node in visit array
				k = i;
			}
		}
		for(j = 0 ; j < number_of_nodes ; j++)
		{
			if(a[j][k] != 0)
			{
				
				for(q = 0 ; q < u; q++)//to get the index value of node from node_alphabet array
				{
					if(visited[q] == node_alphabets[j])
					{
						visited_counter = q;//to get node using backtracking
						b = 0;//counter to stop backtracking
						break;
					}
				}
			}
			if(b == 0)
			{
				cost = cost + a[j][k];//caculate cost
				break;
			}
			if(visited[visited_counter] == start_variable)//to break loop when start variable reached
				f = 0;				
		}
		visit_counter++;
		if(f == 0)
			break;
		b = 1;
	}
	printf("The Path taken : \n");
	for(i = visit_counter - 1; i >= 0 ; i--)//to print the path to be taken
		printf("%c  ",visit[i]);
	printf("\nCost = %d",cost);
	
	return 0;
}
