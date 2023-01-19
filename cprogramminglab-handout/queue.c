/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author junhe <junhe0618@gmail.com>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

static void queue_free_ele(list_ele_t **ele) {
    if (ele == NULL || *ele == NULL) {
        return;
    }

    free((*ele)->value);
    free(*ele);

    *ele = NULL;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    if (q == NULL) {
        return;
    }
    /* How about freeing the list elements and the strings? */
    list_ele_t *next = NULL;
    for (list_ele_t *cur = q->head; cur != NULL; cur = next) {
        next = cur->next;
        queue_free_ele(&cur);
    }
    /* Free queue structure */
    free(q);
}

static list_ele_t *queue_alloca_new_ele(const char *s) {
    if (s == NULL) {
        return NULL;
    }
    /* What should you do if the q is NULL? */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return NULL;
    }
    /* Don't forget to allocate space for the string and copy it */
    newh->value = malloc(strlen(s) + 1);
    /* What if either call to malloc returns NULL? */
    if (newh->value == NULL) {
        free(newh);
        return NULL;
    }
    strcpy(newh->value, s);
    newh->next = NULL;
    return newh;
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    if (q == NULL || s == NULL) {
        return false;
    }

    list_ele_t *newh = queue_alloca_new_ele(s);
    if (newh == NULL) {
        return false;
    }
    newh->next = q->head;
    q->head = newh;

    // record tail
    if (q->size == 0) {
        q->tail = newh;
    }

    // update size
    q->size++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    if (q == NULL || s == NULL) {
        return false;
    }

    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q->size == 0) {
        return queue_insert_head(q, s);
    }

    list_ele_t *newt = queue_alloca_new_ele(s);
    if (newt == NULL) {
        return false;
    }
    q->tail->next = newt;
    q->tail = newt;
    q->size++;

    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    if (q == NULL || buf == NULL || bufsize < 1) {
        return false;
    }
    /* You need to fix up this code. */
    list_ele_t *curHead = q->head;
    if (curHead == NULL) {
        return false;
    }

    q->head = q->head->next;

    q->size--;
    if (q->size == 0) {
        q->tail = NULL;
    }

    strncpy(buf, curHead->value, bufsize - 1);
    buf[bufsize - 1] = '\0';

    queue_free_ele(&curHead);
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    if (q == NULL) {
        return 0;
    }
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    if (q == NULL || q->size <= 1) {
        return;
    }
    /* You need to write the code for this function */
    list_ele_t *oldHead = q->head;
    list_ele_t *cur = oldHead->next;
    while (cur != NULL) {
        oldHead->next = cur->next;
        cur->next = q->head;
        q->head = cur;
        cur = oldHead->next;
    }
    // swap head and tail
    q->tail = oldHead;
}
