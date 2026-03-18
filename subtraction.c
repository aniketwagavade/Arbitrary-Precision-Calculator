#include "apc.h"
/*
* Function to subtract two numbers stored in doubly linked lists
* tail -> last node of first number
* tail2 -> last node od second number
* headR, tailR -> result list (output number)
*/
void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
	// temp pointers used to travese the lists from right to left (LSB to MSB)
    node *temp1 = tail1;
    node *temp2 = tail2;

	// borrow is used when is num1 is smaller than num2
    int borrow = 0, result, num1, num2;

	// Continue untill all digits of first number are processed
    while(temp1) 
    {
		// Take current digit from first number
        num1 = temp1->data; 

		// Move to previous digit (towards MSB)
        temp1 = temp1->prev; 
       
		// If seconf number still has digits
        if(temp2 != NULL)
        {
            num2 = temp2->data;	// Take digit from second number 
            temp2 = temp2->prev; // Move to previous digit 
		}  
        else    
        {       
			// If second number digits finished, treat as 0
            num2 = 0;  
        }
		// If previous subtraction generated a borrow
        if(borrow == 1)      
        {
            num1 = num1 - 1; // Reduce current digit  
            borrow = 0; // Reset borrow 
        }
		//If current digit of num1 is smaller thean num2
        if(num1 < num2)     
        {
            num1 = num1 + 10; // Borrow 10 from next higher figit 
            borrow = 1; // Set borrow for next iteration
        }

		// Perform subtraction of digits
        result = num1 - num2;   
		
		// Insert result digit at the beginning os result list
		// Because we are processing from LSB to MSB
        insert_first(headR, tailR, result); 
	}  
}