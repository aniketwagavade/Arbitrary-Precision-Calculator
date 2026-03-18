#include "apc.h"

// Function definitions
int cla_validation(int argc, char *argv[])		//validation of CLA
{
    int i;
	if(argc == 4)										// We expect exactly 4 arguments
	{
        i = 0;

		if(argv[1][i] == '+' || argv[1][i] == '-')		//check operand1 have sign or not
    		i++;
		while(argv[1][i])								//check remaining characters are digits or not
        {
            if(argv[1][i] >= '0' && argv[1][i] <='9')
                i++;
            else
                return -1;
        }

        i = 0;
		if (argv[3][i] == '+' || argv[3][i] == '-')		//check operand2 have sign or not
    		i++;

        while(argv[3][i])
        {
            if(argv[3][i] >= '0' && argv[3][i] <='9')	//check remaining characters are digits or not
                i++;
            else
                return -1;
        }
        return SUCCESS;
	}
	return FAILURE;
}

void create_list(char *opr, node **head, node **tail)
{
	int i = 0, num;

	// Skip sign if present
	if(opr[i] == '+' || opr[i] == '-')
		i++;

	// Convert each character into digit and insert
	while(opr[i])
	{
		num = opr[i] - '0'; //convert char to int
		insert_last(head, tail, num);
        i++;
	}
}

void insert_first(node **head, node **tail, int data)
{
    node *new_node = malloc(sizeof(node));		//Allocate memory for new node
    if(!new_node)								//check memory allocation or not
	{
		printf("Error : memory not allocate to new node");
        return;
	}
	//assign data and pointers to new node
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if(*head == NULL)		//if list is empty at update head and tail
        *head = *tail = new_node;
    else
    {   //list is not empty update head pointer add new node at begining
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
    }
}

void insert_last(node **head, node **tail, int data)
{
	//Allocating the memory for new node
	node *new = malloc(sizeof (node));

	// If the node is not created the returning failure
	if(!new)
	{
		printf("Error : memory not allocate to new node\n");
        return;
	}

	new -> data = data;
	new -> prev = NULL;
	new -> next = NULL;

	// If the list is empty then inserting the node as first node
	if (!*head && !*tail)
		*head = *tail = new;
	else
	{	// Add new node at the end
		new -> prev = *tail;
		(*tail) -> next = new;
		*tail = new;
	}
}

void print_list(node *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    while (head)		
	    {
		    // Printing the list 
		    printf("%d ", head -> data);

		    // Travering in forward direction 
		    head = head -> next;
	    }
        printf("\n");
    }

}

int list_len(node *head)
{
	int count = 0;
    while(head)  // until list reaches null
    {
        count++; //update the count 
        head = head->next;
    }
    return count;
}

int compare_list(node *head1, node *head2)
{
	int len1 = list_len(head1);
	int len2 = list_len(head2);

	//compare the length of the lists
	if(len1 > len2)
		return OPERAND1;
	else if(len1 < len2)
		return OPERAND2;
	else
	{
		//if length are same => compare the digits
		node *temp1 = head1;
		node *temp2 = head2;

        //traverse both lists
		while(temp1 || temp2) 	
		{
			if(temp1->data > temp2->data)
				return OPERAND1;
			else if(temp1->data < temp2->data)
				return OPERAND2;
			else
			{
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		return SAME;
	}
}

void remove_pre_zeros(node **head)
{
	// Remove zeros until first non-zero digit
	while((*head)->data == 0)
	{
		// If only one node left, stop
		if((*head)->next == NULL)
			return;

		*head = (*head)->next;
		
        free((*head)->prev);
		(*head)->prev = NULL;
		
	}
	return;
}

void delete_list(node **head, node **tail)
{
    node *temp = *head;

	// Traverse and delete nodes
    while(temp)
    {
        if(*head == *tail)
            *head = *tail = NULL;
        else
        {
            *head = temp->next;
            (*head)->prev = NULL;
        }
        temp = temp->next;
    }
    free(temp);
}