#include "../include/queue.h" 


static inline uint64_t verify_queue (queue *const p_queue);


static uint64_t verify_queue(queue *const p_queue)
{
    uint64_t error = 0;

    if (p_queue->data == nullptr) 
    {
        error = error | INVALID_DATA;
    }
    if (p_queue->size > p_queue->capacity) 
    {
        error = error | INVALID_CAPACITY;
    }
    if(p_queue->data == nullptr)
    {
        error = error | INVALID_QUEUE_UNITIALIZED;
    }
    
    return error;
}



#define CHECK_QUEUE(p_queue)                                                            \
    if (error != 0)                                                                     \
    {                                                                                   \
        if((error & INVALID_DATA) != 0)                                                 \
            printf("INVALID_DATA\n");                                                   \
        if((error & INVALID_CAPACITY) != 0)                                             \
            printf("INVALID_CAPACITY\n");                                               \
        if((error & INVALID_QUEUE_REINITIALIZIED) != 0)                                 \
            printf("INVALID_QUEUE_REINITIALIZIED\n");                                   \
        if((error & INVALID_QUEUE_UNITIALIZED) != 0)                                    \
            printf("INVALID_QUEUE_UNITIALIZED\n");                                      \
        if((error & INVALID_EMPTY_QUEUE) != 0)                                          \
            printf("INVALID_EMPTY_QUEUE\n");                                            \
        queue_dump(p_queue);                                                            \
    }


void queue_ctor(queue *const p_queue)
{
    assert(p_queue);
    
    uint64_t error = 0;

    if(p_queue->size     != 0  ||
       p_queue->capacity != 0  ||    
       p_queue->data     != nullptr) 
    {
        error = error | INVALID_QUEUE_REINITIALIZIED;
        CHECK_QUEUE(p_queue);
        return ;
    }

    item_t *data = (item_t *) calloc(CAPACITY, sizeof(item_t));
    assert(data);

    p_queue->size      = 0;
    p_queue->capacity  = CAPACITY;
    p_queue->data      = data;
    p_queue->head      = 0;
    p_queue->tail      = 0;

    error = verify_queue(p_queue);
    CHECK_QUEUE(p_queue);
} 


void queue_dtor(queue *const p_queue)
{
    assert(p_queue);

    uint64_t error = verify_queue(p_queue);
    if(error)
    {
        CHECK_QUEUE(p_queue)
        return ;  
    }  
 
    free(p_queue->data);
    p_queue->size        = 0;
    p_queue->capacity    = 0;
    p_queue->data        = nullptr; 
    p_queue->head        = 0;
    p_queue->tail        = 0; 
}


void push_head(queue *const p_queue, const item_t element)
{
    assert(p_queue);

    uint64_t error = verify_queue(p_queue);
    if(error)
    {
        CHECK_QUEUE(p_queue);
        return;
    }
    if(p_queue->size == p_queue->capacity)
    {
        error = error | INVALID_CAPACITY;
    }

    item_t *data = p_queue->data;

    data[p_queue->head] = element;
    p_queue->head = (p_queue->head + 1) % p_queue->capacity;
    p_queue->size++;

    error = verify_queue(p_queue);
    CHECK_QUEUE(p_queue);
}


void pop_tail(queue *const p_queue, item_t *const p_element)
{
    assert(p_queue);
    assert(p_element);

    uint64_t error = verify_queue(p_queue);
    if(error || (p_queue->size == 0) )
    {
        if(p_queue->size == 0)
            error = error | INVALID_EMPTY_QUEUE;
        CHECK_QUEUE(p_queue);
        return;
    }

    item_t *data = p_queue->data;

    *p_element = data[p_queue->tail];
    p_queue->tail = (p_queue->tail + 1) % p_queue->capacity;
    p_queue->size--;

    error = verify_queue(p_queue);
    CHECK_QUEUE(p_queue);
}


void queue_dump(queue *const p_queue)
{
    assert(p_queue);
    uint64_t error = verify_queue(p_queue);

    item_t *data = p_queue->data;

    printf("|===================================================|\n"
           "|                                                   |\n" 
           "|                           Queue DUMP              |\n"
           "|                                                   |\n"
           "|===================================================|\n"
           "| Queue information:                                |\n"
           "| Address:            %-30p|\n"
           "| Size:               %-30zu|\n"
           "| Capacity:           %-30zu|\n"
           "| Data:               %-30p|\n",
            p_queue,                 
            p_queue->size,        
            p_queue->capacity,       
            p_queue->data);
    printf("|                                                   |\n"
           "| Elements:                                         |\n");

    for(size_t i = 1; i <= p_queue->size; i++)
        printf("| *%7zu:           %-29" SPECIFICATOR " |\n", i, data[i - 1]);
      
    if( (error & INVALID_CAPACITY) == 0)
        for(size_t i = p_queue->size + 1; i <= p_queue->capacity; i++)
            printf("|  %7zu:           %-29" SPECIFICATOR " |\n", i, data[i - 1]);
    printf("|===================================================|\n");
}
