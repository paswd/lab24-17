#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include "exptree.h"
#include "basfunc.h"

typedef struct _queue_node QueueNode;
typedef struct _queue Queue;

Queue* queue_create(void);
void queue_destroy(Queue **queue);
void queue_push(Queue *queue, Item value);
Item queue_pop(Queue *queue);
Item queue_first(Queue *queue);
bool queue_is_empty(Queue *queue);


#endif
