#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(List));
  list->head = NULL;
  list->last = NULL;
  list->count = 0;
  return list;
}

Node_ptr create_node(char* command, char* alias)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->command = command;
  new_node->alias = alias;
  new_node->next = NULL;
  return new_node;
}

Status add_to_end(List_ptr list, char* command, char* alias)
{
  Node_ptr new_node = create_node(command, alias);
  if (list->head == NULL)
  {
    list->head = new_node;
  }
  else
  {
    list->last->next = new_node;
  }
  list->last = new_node;
  list->count++;
  return Success;
}

void display(List_ptr list)
{
  Node_ptr p_walk = list->head;
  while(p_walk != NULL)
  {
    printf("%s=%s\n",p_walk->alias, p_walk->command);
    p_walk = p_walk->next;
  }
} 

Status remove_from_start(List_ptr list)
{
  Node_ptr first_element = list->head;
  if(list->head == NULL)
  {
    return Failure;
  }
  list->head = first_element->next;
  list->count--;
  free(first_element);
  return Success;
}

Status remove_from_end(List_ptr list)
{
  Node_ptr last_element = list->last;
  Node_ptr previous_element;
  Node_ptr p_walk = list->head;
  int position = 0;
  if(list->head == NULL)
  {
    return Failure;
  }
  if(list->count == 1)
  {
    free(list->head);
    list->head = NULL;
    list->count--;
    return Success;
  }
  while(position < list->count){
    if(position == (list->count - 2))
    {
     previous_element = p_walk;
    }
    p_walk = p_walk->next;
    position++;
  }
  list->last = previous_element;
  previous_element->next = NULL;
  list->count--;
  free(last_element);
  return Success;
}

 Status remove_at(List_ptr list,int position)
{
  Node_ptr p_walk = list->head;
  Node_ptr previous_element;
  Node_ptr remove_element;
  if(position < 0 || position >= list->count)
  {
    return Failure;
  }
  if(position == 0)
  {
    return remove_from_start(list); 
  }
  if(position == (list->count - 1))
  {
    return remove_from_end(list);
  }
  int count = 0;
  while(count <= position){
    if(count == position - 1)
    {
     previous_element = p_walk;
     remove_element = p_walk->next;
    }
    p_walk = p_walk->next;
    count++;
  }
  previous_element->next = p_walk;
  free(remove_element);
  list->count--;
  return Success;
}

Status clear_list(List_ptr list)
{
  Node_ptr p_walk = list->head;
  Node_ptr clear_element = NULL;
  while(p_walk != NULL)
  {
    clear_element = p_walk;
    p_walk = p_walk->next;
    free(clear_element);
  }
  list->head = NULL;
  list->last = NULL;
  list->count = 0;
  return Success;
}

void destroy_list(List_ptr list)
{
Node_ptr p_walk = list->head;
  Node_ptr clear_element = NULL;
  while(p_walk != NULL)
  {
    clear_element = p_walk;
    p_walk = p_walk->next;
    free(clear_element);
  }
  list->head = NULL;
  list->last = NULL;
  list->count = 0;
  free(list);
}

int search(List_ptr list, char* alias)
{
  
  int position = 0;
  Node_ptr iterator = list->head;
  while (iterator != NULL)
  {
    if (!strcmp(alias, iterator->alias))
    {
      return position;
    }
    position++;
    iterator = iterator->next;
  }
  return -1;
}