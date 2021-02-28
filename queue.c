#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    } /* if malloc returned NULL */
    q->head = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) {
        return;
    } /* if q is NULL */
    /* Free the list elements and the strings */
    list_ele_t *current = q->head;
    while (current) {
        list_ele_t *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(q); /* Free queue structure */
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
        return false;
    } /* if q is NULL */
    list_ele_t *newhead;
    newhead = malloc(sizeof(list_ele_t));
    /* If malloc returned NULL */
    if (!newhead) {
        return false;
    }
    newhead->next = NULL;
    /* Allocate space for the string */
    unsigned int str_length = strlen(s) + 1;
    newhead->value = malloc(str_length);
    /* If malloc returned NULL */
    if (!newhead->value) {
        free(newhead);
        return false;
    }
    /* Copy the string */
    strncpy(newhead->value, s, str_length);
    /* Concatenate with other nodes */
    if (!q->rear) {
        q->rear = newhead;
    }
    newhead->next = q->head;
    q->head = newhead;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newrear = malloc(sizeof(list_ele_t));
    if (!newrear) {
        return false;
    } /* If malloc returned NULL */
    newrear->next = NULL;
    /* Remember: It should operate in O(1) time */
    unsigned int str_length = strlen(s) + 1;
    newrear->value = malloc(str_length);
    /* If malloc returned NULL */
    if (!newrear->value) {
        free(newrear);
        return false;
    }
    /* Copy the string */
    strncpy(newrear->value, s, str_length);
    /* Concatenate with other nodes */
    if (!q->head) {
        q->head = newrear;
    } else {
        q->rear->next = newrear;
    }
    q->rear = newrear;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head) {
        return false;
    } /* If queue is NULL or empty */
    list_ele_t *del = q->head;
    q->head = q->head->next;
    /* If sp is non-NULL, copy the removed string to *sp */
    if (sp) {
        strncpy(sp, del->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    /* The space used by the list element and the string should be freed. */
    free(del->value);
    free(del);
    /* If all the elements are removed */
    if (!q->head) {
        q->rear = NULL;
    }
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if (!q) {
        return 0;
    } else {
        return q->size;
    }
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head) {
        return;
    }
    // list_ele_t *init_head = q->head;
    list_ele_t *init_rear = q->rear;
    list_ele_t *current = q->head;
    /* Start the reverse process */
    while (current != init_rear) {
        list_ele_t *next = current->next;
        current->next = q->rear->next;
        q->rear->next = current;
        current = next;
    }
    q->head = init_rear; /* Declare the initial rear(init_rear) as head */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || (q->size < 2)) {
        return;
    }
    do {
        do {
            if (q->head->value > q->head->next->value) {
                swap(q->head, q->head->next);
            }
            q->head->next = q->head->next->next;
        } while (q->head->next);
        q->head = q->head->next;
    } while (q->head);
}
