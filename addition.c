#include "apc.h"
/*
 * Function: addition
 * 
 * Adds two large numbers stored as doubly linked lists.
 * Each node contains a single digit.
 *
 * tail1 : pointer to the last node of first number
 * tail2 : pointer to the last node of second number
 * headR : pointer to head of result list
 * tailR : pointer to tail of result list
 */

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    // Temporary pointers to traverse both numbers from the last digit
    node *temp1 = tail1, *temp2 = tail2;
    int num1, num2, sum, result, carry = 0;

    // traverse lists until both lists are reaching NULL
    while(temp1 || temp2)
    {
        // Get digit from first number
        if(temp1 != NULL)
        {
            num1 = temp1->data;   //read digit(last digit)
            temp1 = temp1->prev;  //move to previous node
        }
        else
            num1 = 0;             //no digit in dll , take as 0
        // Get digit from second number
        if(temp2 != NULL)
        {
            num2 = temp2->data;     //read digit(last digit)
            temp2 = temp2->prev;    //move to previous node
        }
        else
            num2 = 0;               //no digit in dll , take as 0

        sum = num1 + num2 + carry;      // add both digits
        result = sum % 10;            // % gives  single digit to store in result
        carry = sum / 10;             // update carry for next iteration
        insert_first(headR, tailR, result);       // store result digit at begining of headR list(insert_first)
    }

    // If carry is still left after addition, add it to result
    if(carry)
    {
        insert_first(headR, tailR, carry);
    }
}