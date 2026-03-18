#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//colurs
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"
#define BBLUE    "\033[1;34m"
#define SUCCESS		1
#define FAILURE		0

#define SAME		0
#define OPERAND1	1
#define OPERAND2	2

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
}node;

void addition(node *tail1, node *tail2, node **headR, node **tailR);
void subtraction(node *tail1, node *tail2, node **headR, node **tailR);
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);
void division(node *head_L1, node *head_opr2, node *tail_opr2,node **headR, node **tailR);

int cla_validation(int argc, char *argv[]);
void create_list(char *opr, node **head, node **tail);
void insert_first(node **head, node **tail, int data);
void insert_last(node **head, node **tail, int data);
void delete_list(node **head, node **tail);
void print_list(node *head);

int compare_list(node *head1, node *head2);
int list_len(node *head);
void remove_pre_zeros(node **head);

#endif