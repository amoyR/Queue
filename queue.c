#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
  int id;
  int price;
} purchase_data;


typedef struct linked_list_tag
{
  struct linked_list_tag *next;
  purchase_data *log; 
} linked_list;


int init (linked_list **head)
{
  *head = (linked_list*)malloc(sizeof(linked_list));
  (*head)->next = NULL;
  (*head)->log = NULL;

  return 0;
}

int finalize (linked_list **head)
{
  free((*head)->log);
  free(*head);

  *head = NULL;

  return 0;
}

linked_list *fetch_tail (linked_list *head)
{
  linked_list *tail;
  tail = head;
  while(tail->next != NULL) {
    tail = tail->next;
  }

  return tail;
}


purchase_data *create_purchase_data (int id, int price)
{
  purchase_data *new_purchase_data;
  new_purchase_data = (purchase_data*)malloc(sizeof(purchase_data));
  new_purchase_data->id = id;
  new_purchase_data->price = price;

  return new_purchase_data;
}

int enqueue (linked_list *head, purchase_data *new_purchase_data)
{
  linked_list *new_tail;
  new_tail = (linked_list*)malloc(sizeof(linked_list));
  new_tail->next = NULL;
  new_tail->log = new_purchase_data;

  linked_list *pre_tail;
  pre_tail = fetch_tail(head);
  pre_tail->next = new_tail;  

  return 0;
}

purchase_data *dequeue (linked_list *head, purchase_data *dequeued_data) 
{
  linked_list *queue_head;
  queue_head = head->next;

  if (queue_head != NULL) {
    dequeued_data = queue_head->log;
    head->next = queue_head->next;
    free(queue_head->log);
    free(queue_head);

  } else {
    dequeued_data = NULL;
  }

  return dequeued_data;
}

int print_queue (linked_list *head)
{
  linked_list *current_node;
  current_node = head->next;
  if (current_node != NULL) {
    while(current_node->next != NULL) {
      printf("id -> %d price -> %d\n", current_node->log->id, current_node->log->price);
      current_node = current_node->next;
    }
    printf("id -> %d price -> %d\n", current_node->log->id, current_node->log->price);
  } else {
    printf("queue is empty\n");
  }

  return 0;
}


int main (void) 
{
  linked_list *head;
  purchase_data *dequeued_data; 

  init(&head);

  purchase_data *add_data;
  add_data = create_purchase_data(200, 200);
  enqueue(head, add_data);
  print_queue(head);

  dequeue(head, dequeued_data);
  print_queue(head);
  dequeue(head, dequeued_data);
  dequeue(head, dequeued_data);
  dequeue(head, dequeued_data);
  print_queue(head);
  
  finalize(&head);
  return 0;
}


