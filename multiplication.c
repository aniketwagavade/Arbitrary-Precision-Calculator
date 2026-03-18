#include "apc.h"

/*
* Function to multiply two numbers stored in linked lists
* tail1 -> last node of first number (multiplier)
* tail2 -> last node of second number (multiplicand)
* headR1, tailR1 -> final result list
*/

void multiplication(node *tail1, node *tail2, node **headR1, node **tailR1)
{
	// temp1, temp2 -> pointers to traverse operands from LSB to MSB
    // headR2, tailR2 -> store intermediate multiplication result
    // headAR, tailAR -> store addition result (final accumulated result)
    node *temp1 = tail1, *temp2 = tail2, *headR2 = NULL, *tailR2 = NULL, *headAR = NULL, *tailAR = NULL;

    int count = 0; // Keeps track of decimal shift (like adding zeros in manual multiplication)
	int carry, num1, num2, mul, res;
    
	// Loop through each digit of second number
    while(temp2)
    {
        carry = 0; // Reset carry for each new multiplication row
		
		// Add zeros at the end based on position (same as shifting in manual multiplication)
        for (int i = 0; i < count; i++)                         
            insert_first(&headR2, &tailR2, 0);
        
        while(temp1)
        {
            num1 = temp1->data;		// digit from first number                             
            num2 = temp2->data;     // digit from second number  
			
			// Perform multiplication with carry
            mul = num1*num2+carry;      
			
			// Extract result digit
            res = mul % 10; 

			// Update carry
            carry = mul / 10; 
			
			// For first iteration store directly in result list
            if(count == 0)                                      
                insert_first(headR1,tailR1,res);
            else
                insert_first(&headR2,&tailR2,res);

			// Move to next digit of first number
            temp1 = temp1->prev;                                   
        }

		// If carry remains after finishing multiplication
        if(carry)                                                
        {
            if(count == 0)
                insert_first(headR1,tailR1,carry);
            else
                insert_first(&headR2,&tailR2,carry);
        }
        
		// If not the first multiplication row
        if(count)
        {
			// Add intermediate result with accumulated result
            addition(*tailR1,tailR2,&headAR,&tailAR);      
			       
			// Delete old result list
            delete_list(headR1,tailR1);  
			
			// Delete temporary multiplication list
            delete_list(&headR2,&tailR2); 
			
			// Update result list with new addition result
            *headR1 = headAR;                                       
            *tailR1 = tailAR;

			// Reset addition result pointers
            headAR = tailAR=NULL;                                    
        }

		// Move to next digit of second number
        temp2 = temp2->prev;   
		
		// Reset first number pointer to its last digit
        temp1 = tail1;     
		
		// Increase position count (next row of multiplication)
        count++;                                                   
    }
}