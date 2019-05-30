#include "List.h"
#include <memory.h>
#include <malloc.h>

void _list_free_node(
	ListNode* node, 
	ListNodeContentDestory destory_func)
{
	if (!node)
	{
		return;
	}
	if (node->next)
	{
		_list_free_node(node->next, destory_func);
	}
	if (destory_func)
	{
		destory_func(node->content);
	}
	free(node);
}


void list_free(List* list)
{
	if (!list)
	{
		return;
	}
	if (list->header)
	{
		_list_free_node(list->header, list->destory_func);
	}
	free(list);
}


List* list_construct(
	ListNodeContentConstruct construct_func, 
	ListNodeContentDestory destory_func)
{
	List* list = (List*)malloc(sizeof(List));
	if (!list)
	{
		return 0;
	}
	memset(list, 0, sizeof(List));
	list->conscturct_func = construct_func;
	list->destory_func = destory_func;
	return list;
}


List* list_copy(List* source_list)
{
	if (!source_list)
	{
		return 0;
	}
	List* list = list_construct(source_list->conscturct_func, 
		source_list->destory_func);
	for (Iterator it = list_begin(source_list);
		!iterator_equal(it, list_end(source_list));
		iterator_move(&it))
	{
		list_push_back(list, iterator_read(it));
	}
	return list;
}


ListNode* list_push_back_manually(List* list, void* content)
{
	if (!list)
	{
		return 0;
	}
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (!node)
	{
		return 0;
	}
	memset(node, 0, sizeof(ListNode));

	node->content = content;

	if (!list->tail)
	{
		list->header = node;
	}
	else
	{
		list->tail->next = node;
	}
	list->tail = node;
	list->size++;
	return node;
}


ListNode* list_push_back(List* list, void* content)
{
	void* new_content = list->conscturct_func ?
		list->conscturct_func(content) :
		content;
	if (!new_content)	// memory alloc fail
	{
		return 0;
	}
	ListNode* node = list_push_back_manually(list, new_content);
	if (!node)
	{
		list->destory_func(new_content);
	}
	return node;
}


Iterator list_erase(Iterator iter)
{
	if (!iter.list || !iter.list->header || !iter.current)
	{
		return iterator_construct_empty();
	}
	ListNode* last = 0;
	ListNode* node = iter.list->header;
	while (node != iter.current)
	{
		last = node;
		node = node->next;
	}
	if (last)
	{
		last->next = node->next;
		if (node == iter.list->tail)
		{
			iter.list->tail = last;
		}
		iter.current = last;
	}
	else
	{
		iter.list->header = node->next;
		if (!iter.list->header)
		{
			iter.list->tail = 0;
		}
		iter.current = iter.list->header;
	}
	
	//delete node
	node->next = 0;
	_list_free_node(node, iter.list->destory_func);
	return iter;
}


Iterator list_begin(List* list)
{
	return iterator_construct(list, list->header);
}


Iterator list_end(List* list)
{
	if (!list->tail)
	{
		return iterator_construct(list, 0);
	}
	return iterator_construct(list, list->tail->next);
}


Iterator list_search(List* list,
	ListCompareProc compare_proc,
	void* param)
{
	Iterator it;
	for (it = list_begin(list);
		!iterator_equal(it, list_end(list));
		iterator_move(&it))
	{
		if (compare_proc(it.current->content, param))
		{
			return it;
		}
	}
	return it;
}


Iterator iterator_construct(List* list, ListNode* current)
{
	Iterator iter = { 0,0 };
	if (!list)
	{
		return iter;
	}
	iter.current = current;
	iter.list = list;
	return iter;
}


Iterator iterator_construct_empty()
{
	Iterator iter = { 0,0 };
	return iter;
}


void* iterator_read(Iterator iter)
{
	if (!iter.current)
	{
		return 0;
	}
	return iter.current->content;
}


void iterator_move(Iterator* iter)
{
	if (!iter || !iter->current)
	{
		return;
	}
	iter->current = iter->current->next;
}


int iterator_equal(Iterator lhs, Iterator rhs)
{
	return lhs.current == rhs.current;
}
