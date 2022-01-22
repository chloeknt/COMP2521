// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List mergeOrdered(List list1, List list2) {
    // Edge cases
    if (list1 == NULL && list2 == NULL) {
        return NULL;
    } else if (list1 == NULL) {
        return list2;
    } else if (list2 == NULL) {
        return list1;
    }
    
    Node curr1 = list1->first;   
    Node curr2 = list2->first;
    
    List merged = ListNew();
    // First node 
    if (curr1->value <= curr2->value) {
        Node new = newNode(curr1->value);
        merged->first = new;
        merged->last = new;
        curr1 = curr1->next;
    } else {
        Node new = newNode(curr2->value);
        merged->first = new;
        merged->last = new;
        curr2 = curr2->next;
    }
    
    // Loop and compare
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->value <= curr2->value) {
            Node new = newNode(curr1->value);
            merged->last->next = new;
            merged->last = new;
            curr1 = curr1->next;
        } else {
            Node new = newNode(curr2->value);
            merged->last->next = new;
            merged->last = new;
            curr2 = curr2->next;
        }    
    }
    
    // When end of one is reached, add the rest of other
    while (curr1 != NULL) {
        Node new = newNode(curr1->value);
        merged->last->next = new;
        merged->last = new;
        curr1 = curr1->next;
    }
    
    while (curr2 != NULL) {
        Node new = newNode(curr2->value);
        merged->last->next = new;
        merged->last = new;
        curr2 = curr2->next;
    }

    return merged;
}

