#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef TEST_LIST // defined if we are compiling the unit tests
# define ELEMENT_T int
#endif

#ifndef ELEMENT_T // the client program forgot to say what the element type is
# error "List: ELEMENT_T is not defined"
#endif

/* struct Link represents each link in a linked list.
 * aLink->data holds one element in the list.
 * aLink->next holds a pointer to the next link, or 0 if aLink is the last link in the list.
 */

struct Link {
    ELEMENT_T data;  // the element stored in this link
    struct Link *next;  // pointer to next link, or 0 at end of list
    struct Link *first; // pointer to first link in list
};

struct List{
    struct Link *first; // pointer to first link in list
    struct Link *last; // pointer to last link in list
};

struct List *newList(void) {
    struct List *list = malloc(sizeof(*list));
    list->first = 0;
    list->last = 0;
    return list;
}

/* Create a new link with the given element data and pointer to the next link in the list.
 */
struct Link *newLink(ELEMENT_T data, struct Link *next) {
    struct Link *link = malloc(sizeof(*link));
    link->data = data;
    link->next = next;
    return link;
}

/* Delete a link.
 */
void Link_delete(struct Link *link) {
    free(link);
}

int List_isEmpty(struct List *list) {
    return list->first == 0;
}

void List_addFirst(struct List *list, ELEMENT_T data) {
    struct Link *link = newLink(data, list->first);
    list->first = link;
    // if it's the only link in the list, it's also the last link
    if (list->last == 0) {
        list->last = link;
    }
}

ELEMENT_T List_removeFirst(struct List *list) {
    if (list->first == 0) {
        printf("List_removeFirst: list is empty\n");
        exit(1);
    }
    struct Link *link = list->first;
    list->first = link->next;
    if (list->first == 0) {
        list->last = 0;
    }
    ELEMENT_T data = link->data;
    Link_delete(link);
    return data;
}

void List_addLast(struct List *list, ELEMENT_T data) {
    struct Link *link = newLink(data, 0);
    if (list->first == 0) {
        list->first = list->last = link;
    } else {
        list->last->next = link;
        list->last = link;
    }
}

size_t List_size(struct List *list) {
    size_t size = 0;
    for (struct Link *link = list->first; link != 0; link = link->next) {
        size++;
    }
    return size;
}

/* struct List represents an entire linked list.
 * If aList is empty then aList->first should be 0.
 * If aList contains at least one link then aList->first points to the first link.
 * The last link in the list should always have its 'next' pointer set to 0.
 */

/*** From Q2: DEFINE struct List and functions HERE ***/

#ifdef TEST_LIST // this is defined if we should include the unit tests

int main(int argc, char**argv){
    struct List *list = newList();
    assert(list != 0);
    assert(list->first == 0);

    assert(List_isEmpty(list));

    List_addFirst(list, 1);
    assert(!List_isEmpty(list));

    assert(1 == List_removeFirst(list));
    assert(List_isEmpty(list));
    List_addFirst(list, 1);
    List_addFirst(list, 2);
    List_addFirst(list, 3);
    assert(!List_isEmpty(list));
    assert(3 == List_removeFirst(list));
    assert(2 == List_removeFirst(list));
    assert(1 == List_removeFirst(list));
    assert(List_isEmpty(list));

    assert(0 == list->last);
    List_addFirst(list, 42);
    assert(0 != list->last);
    assert(42 == List_removeFirst(list));
    assert(0 == list->last);

    List_addLast(list, 2);
    List_addFirst(list, 1);
    List_addLast(list, 3);
    List_addFirst(list, 0);
    assert(0 == List_removeFirst(list));
    assert(1 == List_removeFirst(list));
    assert(2 == List_removeFirst(list));
    assert(3 == List_removeFirst(list));
    assert(List_isEmpty(list));

    assert(0 == List_size(list));
    for (int i = 1; i <= 10; i++) {
        List_addLast(list, i);
        assert(i == List_size(list));
    }

    struct Link *link = newLink(1, 0); // last link in list: [1]
    assert(link != 0);
    assert(link->data == 1);

    link = newLink(2, link);           // add link at front: [2 1]
    assert(link != 0);
    assert(link->data == 2);
    assert(link->next != 0);
    assert(link->next->data == 1);

    link = newLink(3, link);           // add link at front: [3 2 1]
    assert(link != 0);
    assert(link->data == 3);
    assert(link->next != 0);
    assert(link->next->data == 2);

    printf("all tests passed\n");      // insert new unit tests above this line

    return 0;
}

#endif
