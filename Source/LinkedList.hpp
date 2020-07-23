#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

template<typename item_type>
class LinkedList
{   
public :
    LinkedList(item_type val) : value(val)
    {
    }
    item_type value;
    LinkedList<item_type>* next = NULL;
};

#endif