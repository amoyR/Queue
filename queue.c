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
  purchase_data *item; 
} linked_list;


int init (linked_list **head, purchase_data *head_purchase_data)
{
  *head = (linked_list*)malloc(sizeof(linked_list));
  (*head)->next = NULL;
  (*head)->item = head_purchase_data;

  return 0;
}


linked_list *fetch_tail (linked_list *head)
{
  linked_list *tail;
  for (tail = head; ; tail = tail->next) {
    if (tail->next == NULL) {
      break;
    }
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
  new_tail->item = new_purchase_data;

  linked_list *pre_tail;
  pre_tail = fetch_tail(head);
  pre_tail->next = new_tail;  

  return 0;
}

int dequeue (linked_list **head, purchase_data *dequeued_data) 
{
  if (*head == NULL) {
    return 0;

  } else if ((*head)->next == NULL) {
    dequeued_data = (*head)->item;
    free((*head)->item);
    free(*head);

    *head = NULL;

    return 0;
  } else {
    linked_list *pre_head;
    pre_head = *head;
    dequeued_data = pre_head->item;
    *head = pre_head->next;

    free(pre_head->item);
    free(pre_head);

    return 0;
  }

}

int print_queue (linked_list *head)
{
  if (head == NULL) {
    printf("queue is empty\n");
  } else {
    for (linked_list *current_node = head; ; current_node = current_node->next) {
      printf("id -> %d price -> %d\n", current_node->item->id, current_node->item->price);
      if (current_node->next == NULL) {
        break;
      }
    }
  }

  return 0;
}


int main (void) 
{
  linked_list *head = NULL;
  purchase_data *init_purchase_data; 
  purchase_data dequeued_data; 

  init_purchase_data = create_purchase_data(100, 100);
  init(&head, init_purchase_data);

  purchase_data *add_data;
  add_data = create_purchase_data(200, 200);
  enqueue(head, add_data);

  dequeue(&head, &dequeued_data);
  dequeue(&head, &dequeued_data);
  dequeue(&head, &dequeued_data);
  dequeue(&head, &dequeued_data);
  print_queue(head);


  return 0;
}


