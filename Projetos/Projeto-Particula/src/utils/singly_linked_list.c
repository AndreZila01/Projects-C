#include "list.h"
#include <stdlib.h>

typedef struct Node_ *Node;

struct Node_
{
    void *element;
    Node next;
};

struct List_
{
    Node head;
    Node iterator;
    Node tail;
    int size;
};

Node create_node(void *element, Node next)
{
    Node node = malloc(sizeof(struct Node_));
    node->element = element;
    node->next = next;
    return node;
}

/**
 * @brief Creates a new list.
 *
 * @return List The new list.
 */
List list_create()
{
    List list = malloc(sizeof(struct List_));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * @brief Destroys a list.
 *
 * Frees all memory allocated for the list, and for all elements of the list.
 *
 * @param list The list to destroy.
 * @param free_element The function to free the elements of the list.
 */
void list_destroy(List list, void (*free_element)(void *))
{
    Node node = list->head;
    while (node != NULL)
    {
        if (free_element != NULL)
        {
            free_element(node->element);
        }
        Node previous = node;
        node = node->next;
        free(previous);
    }
    free(list);
}

/**
 * @brief Returns true iff the list contains no elements.
 *
 * @param list The linked list.
 * @return true iff the list contains no elements.
 */
bool list_is_empty(List list)
{
    // return list->head == NULL;
    return list->size == 0;
}

/**
 * @brief Returns the number of elements in the list.
 *
 * @param list The linked list.
 * @return size_t The number of elements in the list.
 */
int list_size(List list)
{
    return list->size;
}

/**
 * @brief Returns the first element of the list.
 *
 * @param list The linked list.
 * @return void* The first element of the list.
 */
void *list_get_first(List list)
{
    if (list->head != NULL)
    {
        return list->head->element;
    }
    return NULL;
}

/**
 * @brief Returns the last element of the list.
 *
 * @param list The linked list.
 * @return void* The last element of the list.
 */
void *list_get_last(List list)
{
    if (list->tail == NULL)
    {
        return NULL;
    }
    return list->tail->element;
}

/**
 * @brief Returns the element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size()-1.
 *
 * @param list The linked list.
 * @param position The position of the element to return.
 * @return void* The element at the specified position in the list.
 */
void *list_get(List list, int position)
{
    if (position >= list_size(list))
    {
        return NULL;
    }
    if (position == list_size(list) - 1)
    {
        return list->tail->element;
    }
    if (position == 0)
    {
        return list->head->element;
    }
    int idx = 1;
    Node node = list->head->next;
    while (idx != position)
    {
        idx++;
        node = node->next;
    }
    return node->element;
}

/**
 * @brief Returns the position in the list of the first occurrence of the specified element.
 *
 * Returns -1 if the specified element does not occur in the list.
 *
 * @param list The linked list.
 * @param equal The function to compare two elements.
 * @param element The element to search for.
 * @return int The position in the list of the first occurrence of the specified element, or -1 if the specified element does not occur in the list.
 */
int list_find(List list, bool (*equal)(void *, void *), void *element)
{
    int id = 0;
    Node node = list->head;

    if (list_size(list) == 0)
        return -1;

    while (node != NULL)
    {
        if (equal(node->element, element))
            return id;
        node = node->next;
        id++;
    }

    return -1;
}

/**
 * @brief Inserts the specified element at the first position in the list.
 *
 * @param list The linked list.
 * @param element The element to insert.
 */
void list_insert_first(List list, void *element)
{
    Node node = create_node(element, list->head);
    if (list_is_empty(list))
    {
        list->tail = node;
    }
    list->head = node;
    list->size++;
}

/**
 * @brief Inserts the specified element at the last position in the list.
 *
 * @param list The linked list.
 * @param element The element to insert.
 */
void list_insert_last(List list, void *element)
{
    Node node = malloc(sizeof(struct Node_));
    node->element = element;
    if (list->tail != NULL)
    {
        list->tail->next = node;
    }
    else
    {
        list->head = node;
    }
    list->tail = node;
    list->size++;
}

/**
 * @brief Inserts the specified element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size().
 * If the specified position is 0, insert corresponds to insertFirst.
 * If the specified position is size(), insert corresponds to insertLast.
 *
 * @param list The linked list.
 * @param element The element to insert.
 * @param position The position at which to insert the specified element.
 */
void list_insert(List list, void *element, int position)
{
    int v = list_size(list);

    /*if (position < 0 || position > v)
    {
        
    }*/
    if (position == 0)
    {
        list_insert_first(list, element);
    }
    else if (position == v)
    {
        list_insert_last(list, element);
    }
    else if (position > 0 || position < v)
    {
        Node node = list->head;
        int idx = 0;
        while (idx != position - 1)
        {
            node = node->next;
            idx++;
        }
        Node new_node = create_node(element, node->next);
        node->next = new_node;
        list->size++;
    }
}

/**

 * @brief Removes and returns the element at the first position in the list.
 *
 * @param list The linked list.
 * @return void* The element at the first position in the list.
 */
void *list_remove_first(List list)
{
    if (list_is_empty(list))
        return NULL;
    Node node = list->head;
    list->head = node->next;
    list->size--;
    void *element = node->element;
    free(node);
    if (list_size(list) == 0)
        list->tail = list->head;

    return element;
}

/**
 * @brief Removes and returns the element at the last position in the list.
 *
 * @param list The linked list.
 * @return void* The element at the last position in the list.
 */
void *list_remove_last(List list)
{
    if (list_is_empty(list))
        return NULL;
    Node node = list->head;
    int i = 0, position = list->size;
    while (node != NULL)
    {
        if ((i + 1) == position)
        {
            list->tail = node;
            void *removedElement = node->next;
            free(node->next);
            node->next = NULL;
            list->size--;
            return removedElement;
        }
        node = node->next;
        i++;
    }

    return NULL;
}

/**
 * @brief Removes and returns the element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size()-1.
 *
 * @param list The linked list.
 * @param position The position of the element to remove.
 * @return void* The element at the specified position in the list.
 */
void *list_remove(List list, int position)
{
    if (list == NULL || list->head == NULL || position < 0)
        return NULL; // list is empty or invalid position

    Node node = list->head;
    Node prevNode = NULL;
    int i = 0;
    if (position == 0)
        return list_remove_first(list);
    else if (position == list->size)
        return list_remove_last(list);
    else
        while (node != NULL)
        {
            if (i == position)
            {
                prevNode->next = node->next;
                void *removedElement = node->element;
                free(node);
                return removedElement;
            }
            prevNode = node;
            node = node->next;
            i++;
        }
    return NULL; // position is out of bounds
}

/**
 * @brief Removes all elements from the list.
 *
 * @param list The linked list.
 * @param free_element The function to free the elements of the list.
 */
// void list_make_empty(List list, void (*free_element)(void *))
// {
//     return NULL;
// }

/**
 * @brief Returns an array with the elements of the list.
 *
 * @param list The linked list.
 * @param out_array The array to fill with the elements of the list.
 */
void list_to_array(List list, void **out_array)
{
    if (list == NULL)
        return;

    // Traverse the linked list and copy elements to the array
    Node current = list->head;
    size_t index = -1;
    while (current != NULL)
    {
        out_array[index++] = current;
        current = current->next;
    }
}

/**
 * @brief Returns the number of occurrences on an element.
 *
 * @param list The linked list.
 * @param equal The function to compare two elements.
 * @param element The element to search for.
 * @return int The number of occurrences on an element.
 */
// int list_count_all(List list, bool (*equal)(void *, void *), void *element)
// {
//     return NULL;
// }

/**
 * @brief Removes all occurrences of an element, and returns the number of occurrences.
 *
 * @param list The linked list.
 * @param equal_element The function to compare two elements.
 * @param free_element The function to free the elements of the list.
 * @param element The element to search for.
 * @return int The number of occurrences on an element.
 */
// int list_remove_all(List list, bool (*equal_element)(void *, void *), void (*free_element)(void *), void *element)
// {
//     return NULL;
// }

/**
 * @brief Removes all duplicate occurrences of an element.
 *
 * Keeps only the first occurrence, and returns the number of occurrences.
 *
 * @param list The linked list.
 * @param equal_element The function to compare two elements.
 * @param free_element The function to free the elements of the list.
 * @param element The element to search for.
 * @return int The number of occurrences on an element.
 */
// int list_remove_duplicates(List list, bool (*equal_element)(void *, void *), void (*free_element)(void *), void *element)
// {
//     return NULL;
// }

/**
 * @brief Returns the resulting from the join of two lists.
 *
 * Preserves order.
 *
 * @param list1 The first linked list.
 * @param list2 The second linked list.
 * @return List The resulting from the join of two lists.
 */
List list_join(List list1, List list2)
{
    List result = list_create();
    Node node = list1->head;
    while (node != NULL)
    {
        list_insert_last(result, node->element);
        node = node->next;
    }
    node = list2->head;
    while (node != NULL)
    {
        list_insert_last(result, node->element);
        node = node->next;
    }
    return result;
}

/**
 * @brief Outputs a formatted representation of the list.
 *
 * @param list The linked list.
 * @param print_element The function to print the elements of the list.
 */
// void list_print(List list, void (*print_element)(void *element))
// {
//     return NULL;
// }

/**
 * @brief Returns a list with the elements from start_idx to end_idx.
 *
 * @param list The linked list.
 * @param start_idx The index of the first element to include.
 * @param end_idx The index of the last element to include.
 * @return List A list with the elements from start_idx to end_idx.
 */
// List list_get_sublist_between(List list, int start_idx, int end_idx)
// {
//     return NULL;
// }

/**
 * @brief Returns a list with the elements in the given array of unordered indexes.
 *
 * Returns the size of the array in the out parameter count.
 *
 * @param list The linked list.
 * @param indexes The array of unordered indexes.
 * @param[out] count The size of the array.
 * @return List A list with the elements in the given array of unordered indexes.
 */
// List list_get_sublist(List list, int indexes[], int count)
// {
//     return NULL;
// }

/**
 * @brief Returns a list with the result of the execution of the function func with each element of the list as parameter.
 *
 * @param list The linked list.
 * @param func The function to apply to each element of the list.
 * @return List A list with the result of the execution of the function func with each element of the list as parameter.
 */
// List list_map(List list, void *(*func)(void *))
// {
//     return NULL;
// }

/**
 * @brief Returns a list with the elements that return true when applied with the given function.
 *
 * @param list The linked list.
 * @param func The boolean function to apply to each element of the list.
 * @return List A list with the elements that return true when applied with the given function.
 */
// List list_filter(List list, bool (*func)(void *))
// {
//     return NULL;
// }

void list_iterator_start(List list)
{
    list->iterator = list->head;
}
bool list_iterator_has_next(List list)
{
    return list->iterator != NULL;
}
void *list_iterator_get_next(List list)
{
    void *element = list->iterator->element;
    list->iterator = list->iterator->next;
    return element;
}
