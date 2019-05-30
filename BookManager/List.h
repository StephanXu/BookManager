/*============================================
Date:	2019/5/25
Description:
	List operation.
	Just like STL list class.
Usage example:
	typedef struct Num
	{
		int a, b;
	}Num;

	Num* num_construct(Num* num)
	{
		if (!num)
		{
			return 0;
		}
		Num* new_num = (Num*)malloc(sizeof(Num));
		if (!new_num)
		{
			return 0;
		}
		*new_num = *num;
		printf("num_construct: %p\n", new_num);
		return new_num;
	}

	void num_destory(Num* num)
	{
		if (!num)
		{
			return;
		}
		printf("num_destory: %p\n", num);
		free(num);
	}

	int num_compare(Num* lhs, int rhs)
	{
		return lhs->a == rhs;
	}

	int main()
	{
		List* list = list_construct(num_construct, num_destory);
		Num num = { 1,2 };
		//Push data
		list_push_back(list, &num);
		num.a = 3;
		num.b = 4;
		list_push_back(list, &num);
		//Show data
		for(Iterator it=list_begin(list);
			!iterator_equal(it,list_end(list));
			iterator_move(&it))
		{
			printf("%d,%d\n", ((Num*)iterator_read(it))->a, ((Num*)iterator_read(it))->b);
		}
		//Search Data
		Iterator res = list_search(list, num_compare, 1);
		if (!iterator_equal(res, list_end(list)))
		{
			num = *(Num*)iterator_read(res);
			printf("Search result:%d,%d\n", num.a, num.b);
		}
		else
		{
			printf("Search result: Not found.\n");
		}
		//Free memory
		list_free(list);

		printf("OK");
		return 0;
	}
============================================*/

#pragma once
#ifndef LIST_H
#define LIST_H


typedef int(*ListCompareProc)(void* current, void* param);


/*
Type of constructing and destroying process function point
*/
// only param for initial value
typedef void* (*ListNodeContentConstruct)(void* self);
// only param for current object
typedef void(*ListNodeContentDestory)(void* self);
typedef void(*ListNodeContentCopy)(void* self);


typedef struct ListNode ListNode;
struct ListNode
{
	ListNode* next;
	/*ATTENTION:	content won't be freed though the node 
					has already been freed.*/
	void* content;
};

typedef struct List
{
	ListNode* header;
	ListNode* tail;
	unsigned int size;

	ListNodeContentConstruct conscturct_func;
	ListNodeContentDestory destory_func;
}List;

typedef struct Iterator
{
	ListNode* current;
	List* list;
}Iterator;


/* Free a node and nodes after the node */
void _list_free_node(ListNode* node, ListNodeContentDestory destory_func);

/* Free a list */
void list_free(List* list);

/*
Initialize a list structure
Args:
	construct_func: Function point of contstruction function. It will be given 
					a point from 'list_push_back''s second argument. It is 
					supposed to return a point to the new object. If 
					construct_func is NULL, 'list_push_back' will simply 
					assign content point to node.
	destory_func:	Function point of destory function.
					It will be given a point direct to the object should be 
					deleted. Please free memory manually in destory function.
					If destory_func is NULL, 'list_free' will ignore freeing 
					content.
Return a point of 'List'
*/
List* list_construct(
	ListNodeContentConstruct construct_func,
	ListNodeContentDestory destory_func);

/* Copy a list */
List* list_copy(List* source_list);

/*
Append a node into list without constructing process.
Please do not call this function unless exactly necessary.
*/
ListNode* list_push_back_manually(List* list, void* content);

/*
Append a node into list
Args:
	list:		list to append
	content:	content of appending node
Return a point of 'node', return 0 when failed.
*/
ListNode* list_push_back(List* list, void* content);

/* Remove a node from list. Return a iterator directed to the node that after 
the deleted node. */
Iterator list_erase(Iterator iter);

/* Return iterator of header */
Iterator list_begin(List* list);

/* Return iterator of tail */
Iterator list_end(List* list);

/* 
Search in list
Args:
	List:			List for searching.
	compare_proc:	function point of compare process.
					Type of comparing process function point
					Example:
						In this example. 'curt' is the value given by search 
						function.
						'param' can be customized. (From argument 'param')
						int equal(int* curt, int* param)
						{
							return *curt == *param;
						}
	param:			See 'compare_func'.
Return:
	A iterator that direct to the first match.
	'list_end(list)' when no result.
*/
Iterator list_search(List* list, ListCompareProc compare_proc, void* param);

/* Construct function of iterator */
Iterator iterator_construct(List* list, ListNode* current);

/* Construct a empty iterator. It often used by constructing a failed return 
value. */
Iterator iterator_construct_empty();

/* Return content */
void* iterator_read(Iterator iter);

/* Move to the next node */
void iterator_move(Iterator* iter);

/*
Compare two interators.
Return True when they are equal.
*/
int iterator_equal(Iterator lhs, Iterator rhs);

#endif