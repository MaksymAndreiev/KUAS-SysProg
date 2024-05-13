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
    ELEMENT_T    data;  // the element stored in this link
    struct Link *next;  // pointer to next link, or 0 at end of list
};

/* Create a new link with the given element data and pointer to the next link in the list.
 */
struct Link *newLink(ELEMENT_T data, struct Link *next)
{
    struct Link *link = malloc(sizeof(*link));
    link->data = data;
    link->next = next;
    return link;
}

/* Delete a link.
 */
void Link_delete(struct Link *link)
{
    free(link);
}

/* struct List represents an entire linked list.
 * If aList is empty then aList->first should be 0.
 * If aList contains at least one link then aList->first points to the first link.
 * The last link in the list should always have its 'next' pointer set to 0.
 */

/*** From Q2: DEFINE struct List and functions HERE ***/

#ifdef TEST_LIST // this is defined if we should include the unit tests

int main(int argc, char**argv)
{
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
