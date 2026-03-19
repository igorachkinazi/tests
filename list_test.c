#include <stdio.h>
#include <assert.h>
#include <string.h>


typedef struct dl_list_elem
{
    struct dl_list_elem *next;
    struct dl_list_elem *prev;
} TransitDLListElem;

typedef struct dl_list_head
{
    TransitDLListElem *first;
    TransitDLListElem *last;
} TransitDLListHead;

void init_list(TransitDLListHead *plist)
{
    plist->first = plist->last = NULL;
}

_Bool list_empty(TransitDLListHead *plist)
{
    return  (plist->first == NULL);
}

void add_to_list(TransitDLListHead *plist, TransitDLListElem *elem)
{
    assert(elem->prev == NULL);
    assert(elem->next == NULL);
    if(plist->last) {
        plist->last->next = elem;
        elem->prev = plist->last;
        elem->next = NULL;
        plist->last = elem;
    }
    else {
        plist->first = plist->last = elem;
        elem->next = elem->prev = NULL;
    }
}

TransitDLListElem *get_first_from_the_list(TransitDLListHead *plist)
{
    return plist->first;
}

void remove_from_list(TransitDLListHead *plist, TransitDLListElem *elem)
{
    if(elem == plist->first) {
        plist->first = elem->next;
        assert(elem->prev == NULL);
    }
    else
       assert(elem->prev);

    if(elem == plist->last) {
        plist->last = elem->prev;
        assert(elem->next == NULL);
    }
    else
       assert(elem->next);

    if(elem->next)
        elem->next->prev = elem->prev;
    if(elem->prev)
        elem->prev->next = elem->next;

    elem->next = elem->prev = NULL;
}

typedef struct test_elem
{
   TransitDLListElem elem;
   int value;
} DLTestElem;

void print_list(TransitDLListHead *plist)
{
   TransitDLListElem *pe;
   for(pe = plist->first; pe; pe = pe->next)
      printf("%d ", ((DLTestElem*)pe)->value);

   if(plist->first == NULL)
      printf("List is empty");
   printf("\n");
}

int main()
{
   TransitDLListHead dllist;
   DLTestElem array[5];

   memset(array, 0, sizeof(array));
   init_list(&dllist);

   for(int i = 0; i < 5; i++) {
      array[i].value = i+1;
      add_to_list(&dllist, &array[i].elem);
   }
   print_list(&dllist);
   remove_from_list(&dllist, get_first_from_the_list(&dllist));
   print_list(&dllist);
   remove_from_list(&dllist, &array[3].elem);
   print_list(&dllist);
   remove_from_list(&dllist, &array[4].elem);
   print_list(&dllist);
   remove_from_list(&dllist, &array[1].elem);
   remove_from_list(&dllist, &array[2].elem);
   print_list(&dllist);

   return 0;
}

