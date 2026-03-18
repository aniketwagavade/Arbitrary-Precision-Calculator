#include "apc.h"

/*
* Function to perform division of tow number stored in linked lists
* head_L1 -> head of dividend
* head_OPR2 -> head of divisor 
* tail-OPR2 -> tail of divisor
* headR, tailR -> result list 
*/
void division(node *head_L1, node *head_OPR2, node *tail_OPR2, node **headR, node **tailR)
{
    int sub_count;	// Counts how many times divisor is subtracted (quotient digit)

	// OPR1 stores the current partial dividend during division
    node *head_OPR1 = NULL, *tail_OPR1 = NULL, *L1_temp = head_L1;

	// SR (Subtraction Result) stores result of OPR1 - OPR2
    node *head_SR = NULL;
    node *tail_SR = NULL;

	// Insert first digit of dividend into partial dividend list
    insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);  

	// Build initial partial dividend until it becomes >= divisor
    while(compare_list(head_OPR1,head_OPR2) == OPERAND2)    
    {
		// Move to next digit of dividend
        L1_temp = L1_temp -> next;    
		
		// If dividend digits finished and still smaller than divisor
        if(L1_temp == NULL)
        {
			// Quotient becomes 0
            insert_last(headR,tailR,0);
            break;
        }

		// Append next digit to partial dividend
        insert_last(&head_OPR1,&tail_OPR1,L1_temp->data);    
    }

	// Continue division until all digits of dividend are processed
    while(L1_temp != NULL)      
    {
		// Remove leading zeros from the partial dividend
        remove_pre_zeros(&head_OPR1);

		// Reset subtraction count for the current digit
        sub_count = 0;    

        while((compare_list(head_OPR1, head_OPR2) == OPERAND1) || (compare_list(head_OPR1, head_OPR2)) == SAME)   
        {
			// Perform subtraction: OPR1 = OPR1 - OPR2
            subtraction(tail_OPR1, tail_OPR2, &head_SR,&tail_SR);  
			
			// Delete the old partial dividend list
            delete_list(&head_OPR1, &tail_OPR1);   
			
			// Update OPR1 with the subtraction result
            head_OPR1 = head_SR;    
            tail_OPR1 = tail_SR;

			// Reset subtraction result pointers for next iteration
            head_SR = tail_SR = NULL;  

			// Remove leading zeros again after subtraction
            remove_pre_zeros(&head_OPR1); 

			// Increment count (how many times subtraction occurred)   
            sub_count++;    
        }

		// Store quotient digit in result list
        insert_last(headR, tailR, sub_count);  
		
		// Move to next digit of dividend
        L1_temp = L1_temp->next;    

        if(L1_temp == NULL)    
            break;

		// Bring down next digit to the partial dividend (long division step)
        insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);   
    }
}