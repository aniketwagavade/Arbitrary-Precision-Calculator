/*
NAME		  : ANIKET AJIT WAGAVADE
DATE		  : 1 JAN 2026
DESCRIPTION   : The Arbitrary Precision Calculator (APC) is a C-based console application that performs arithmetic operations on very large integers beyond standard data type limits.
				It uses doubly linked lists to store each digit and carry out operations digit-by-digit.
			   	The calculator supports addition, subtraction, multiplication, and division, handles negative numbers.
*/


#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;
	int p_flag1 = 0, p_flag2 = 0, n_flag1 = 0, n_flag2 = 0, result_sign = 0;

    // Validation
	if(!cla_validation(argc,argv))
	{
		printf("=======================================================\n");
		printf(CYAN"Error : Insufficient Command Line Arguments\n"RESET);
		printf(MAGENTA"For Addition 	   : pass like this Operand1 + Operand2\n");
		printf("For Subtraction	   : pass like this Operand1 - Operand2\n");
		printf("For Multiplication : pass like this Operand1 x Operand2\n");
		printf("For Division 	   : pass like this Operand1 / Operand2\n"RESET);
		printf("=======================================================\n");
		return FAILURE;
	}
	else if(cla_validation(argc,argv) == -1)
	{
		printf("\n=====================================================\n");
		printf(RED "Input Error: Operand contains invalid characters.\n");
		printf(RED "Kindly provide a valid numeric operand.\n" RESET);
		printf("=======================================================\n\n");
		return FAILURE;
	}

    // Create 2 lists of operands
	create_list(argv[1],&head1,&tail1);		// for operand 1
	create_list(argv[3],&head2,&tail2);		// for operand 2 

    //Remove pre zeros
	remove_pre_zeros(&head1);	// removing the pre zeros for operand 1 and 2(numbers entered by the user)
	remove_pre_zeros(&head2);

	if(argv[1][0] == '+')		// if the operand 1 is a +ve value then making the positive flag of operand1 1.
		p_flag1 = 1;
	else if(argv[1][0] == '-')	// else making -ve value 1.
		n_flag1 = 1;
	if(argv[3][0] == '+')		// if the operand 2 is a +ve value then making the 
		p_flag2 = 1;
	else if(argv[3][0] == '-')	// else making -ve value 1.
		n_flag2 = 1;

    char oper = argv[2][0];		// operator   CLA => ./a.out 2 + 3, the + will come.
	if(oper == '+')				// if the 3rd argument(index 2) in CLA (./a.out 2 + 3) is + then the following cases happen.
	{
		printf("========================================\n");
		printf(MAGENTA"%*s\n"RESET, 24, "ADDITION");
		printf("========================================\n");
		// -a + -b
		if(n_flag1 == 1 && n_flag2 == 1)		// if both the values are +ve then addition should take place. -10 + -20 = -30
		{
			oper = '+';
		}
		// +a + -b
		else if(n_flag1 == 0 && n_flag2 == 1)		// +10 + -20 = -10, sub takes place
		{
			oper = '-';
		}
		// -a + +b
		else if(n_flag1 == 1 && n_flag2 == 0)		// -10 + +20 = 10, sub takes place
		{
			oper = '-';
		}
	}
	else if(oper == '-')
	{
		printf("========================================\n");
		printf(MAGENTA"%*s\n"RESET,26,"SUBTRACTION");
		printf("========================================\n");
		// -a - -b
		if(n_flag1 == 1 && n_flag2==1)		// -10 + -20 = -30, sub takes place
		{
			oper = '-';
		}
		// +a - -b
		else if(n_flag1 == 0 && n_flag2 == 1)		// 10 - -20 = 30, add takes place
		{
			oper = '+';
		}
		// -a - +b
		else if(n_flag1 == 1 && n_flag2 == 0)		 // -10 - +20 = -30, add takes place
		{
			oper = '+';
		}
	}
	else if(oper == '/')
	{
		printf("========================================\n");
		printf(MAGENTA"%*s\n"RESET,24,"DIVISION");
		printf("========================================\n");
	}
	else
	{
		printf("========================================\n");
		printf(MAGENTA"%*s\n"RESET,27,"MULTIPLICATION");
		printf("========================================\n");
	}

	int len1 = list_len(head1);
	int len2 = list_len(head2);
	int max = len1 > len2 ? len1 : len2;

	/* Operand 1 */
	printf(CYAN "Operand 1 :" RESET);
	printf("   ");
	printf("%c", n_flag1 ? '-' : ' ');
	for(int i = 0; i < (max - len1) * 2; i++) printf(" ");
	print_list(head1);

	/* Operand 2 */
	printf(CYAN "Operand 2 :" RESET);
	printf(GREEN "(%c)" RESET,oper);
	printf("%c", n_flag2 ? '-' : ' ');
	for(int i = 0; i < (max - len2) * 2; i++) printf(" ");
	print_list(head2);
	printf("----------------------------------------\n");

	switch(oper)
	{
		case '+':
			// tail1 and tail2 are passed by value, and headR and tailR are passed by reference.
			addition(tail1, tail2, &headR, &tailR);
			if(n_flag1 == 1 && n_flag2 == 0)
				result_sign = 1;
			else
				result_sign = (n_flag1 && n_flag2);
			break;

		case '-':
		{
			// compare_list fn. would have compared the num1 and num2.
			int ret = compare_list(head1, head2);
			// this becomes true if OPERAND1 is returned from compare_list function.Then the num1 is bigger so it passes first to the subtraction fn.
			if (ret == OPERAND1)
			{
				subtraction(tail1, tail2, &headR, &tailR);	// num1's tail first (tail1), then num2's tail (tail2) is passed
				result_sign = n_flag1;
			}
			// this becomes true if OPERAND2 is returned from compare_list function.Then the num2 is bigger so it passes first to the subtraction fn.
			else if (ret == OPERAND2)
			{
				subtraction(tail2, tail1, &headR, &tailR);		// num2's tail first (tail1), then num1's tail (tail2) is passed
				result_sign = !n_flag1;
			}
			else
			{
				insert_first(&headR, &tailR, 0);
				result_sign = 0;
			}
			break;
		}

		case 'x':
		case 'X':
			multiplication(tail1, tail2, &headR, &tailR);		// calling the multiplication fn.
			result_sign = (n_flag1 != n_flag2);
			break;

		case '/':
			if(head1->data == 0 && head2->data == 0)
			{
				printf(YELLOW"RESULT	  :    0\n"RESET);
				printf(RESET"----------------------------------------\n");
				return FAILURE;
			}
			else if(head2->data == 0)
			{
				printf(RED"RESULT : Runtime Error : Divisible by Zero\n"RESET);
				printf(RESET"----------------------------------------\n");
				return FAILURE;
			}
			division(head1, head2, tail2, &headR, &tailR);	// calling the division fn.
			/* Decide sign AFTER division */
			if (headR->data == 0)
				result_sign = 0;                 // avoid -0
			else
				result_sign = (n_flag1 != n_flag2);
			break;

		default:
			printf("Invalid operator\n");
			return FAILURE;
	}

	// removing the pre zeros for the result. It must be done before printing.
	remove_pre_zeros(&headR);

	/* Result */
	int lenR = list_len(headR);
	if (lenR > max) max = lenR;
	printf(YELLOW "Result    :" RESET);
	for(int i = 0; i < (max - lenR) * 2 +3; i++) printf(" ");
	printf(BBLUE"%c", (result_sign && headR->data != 0) ? '-' : ' ');
	print_list(headR);
	printf(RESET"----------------------------------------\n");
	return SUCCESS;
}