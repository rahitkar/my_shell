#ifndef __LIST_H
#define __LIST_H

typedef char* Char_ptr;

typedef enum
{
  Failure,
  Success
} Status;

typedef struct node
{
  Char_ptr command;
  Char_ptr alias;
  struct node *next;
} Node;

typedef Node *Node_ptr;
typedef struct
{
  Node *head;
  Node *last;
  int count;
} List;

typedef List* List_ptr;

List_ptr create_list(void);
Status add_to_end(List_ptr list, Char_ptr command, Char_ptr alias);

void display(List_ptr);

Status remove_at(List_ptr, int position);

Status clear_list(List_ptr); // Removes all elements in the list
void destroy_list(List_ptr); // Frees the elements and the list structure from memory

int search(List_ptr list, char* alias);

#endif