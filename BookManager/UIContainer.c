#include <stdio.h>
#include "app.h"
#include "List.h"
#include "UIContainer.h"

/* Construct function of 'UIContainer' */
UIContainer* ui_container_construct(void* _)
{
	UIContainer* container = (UIContainer*)malloc(sizeof(UIContainer));
	if (!container)
	{
		return 0;
	}
	ui_element_initialize(&container->basic,
		ui_container_on_event,
		ui_container_render,
		ui_container_destory);
	container->elements = list_construct(0, ui_element_destory);
	if (!container->elements)
	{
		free(container);
		return 0;
	}
	container->focus = 0;
	return container;
}

/* Destory function of 'UIContainer' */
void ui_container_destory(UIContainer* container)
{
	if (!container || !container->elements)
	{
		return 0;
	}
	list_free(container->elements);
	free(container);
}

/* Add an element to container */
int ui_container_append_element(UIContainer* container, UIElement* element)
{
	if (!container || !element)
	{
		return 0;
	}
	if (list_push_back(container->elements, element))
	{
		element->parent = container;
		if (element->event_proc)
		{
			element->event_proc(element,
				CREATED,
				0,
				0);
		}
		return 1;
	}
	return 0;
}

/* Remove an element from container */
int compare_element(UIElement* lhs, UIElement* rhs)
{
	return lhs == rhs;
}
int ui_container_remove_element(UIContainer* container, UIElement* element)
{
	Iterator it;
	if (!container || !element)
	{
		return 0;
	}
	it = list_search(container->elements, compare_element, element);
	if (iterator_equal(it, list_end(container->elements)))
	{
		return 0;
	}
	list_erase(it);
	return 1;
}
void ui_container_auto_remove(UIContainer* container)
{
	Iterator it;
	UIElement* element = 0;
	if (!container)
	{
		return;
	}
	for (it = list_begin(container->elements);
		!iterator_equal(it, list_end(container->elements));
		iterator_move(&it))
	{
		element = (UIElement*)iterator_read(it);
		if (!element)
		{
			continue;
		}
		if (element->deleted)
		{
			if (element == container->focus)
			{
				container->focus = 0;
			}
			it = list_erase(it);
			continue;
		}

		if (ui_container_on_event == element->event_proc)
		{
			ui_container_auto_remove(element);
		}
	}
}

/* Get element under mouse cursor */
UIElement* _ui_container_get_focus(UIContainer* container, int x, int y)
{
	Iterator it;
	UIElement* element = 0;
	UIElement* res = 0;
	if (!container)
	{
		return 0;
	}
	for (it = list_begin(container->elements);
		!iterator_equal(it, list_end(container->elements));
		iterator_move(&it))
	{
		element = (UIElement*)iterator_read(it);
		if (!element->event_proc || !element->visible)
		{
			continue;
		}
		if (element->p1.X <= x && element->p2.X >= x &&
			element->p1.Y <= y && element->p2.Y >= y)
		{
			res = element;
		}
	}
	return res;
}

/* Event process */
void ui_container_on_event(
	UIContainer* container, 
	UIEventType event_type, 
	int param1,
	int param2)
{
	UIElement* original_focus = 0;
	short mouse_x = 0, mouse_y = 0;
	if (!container)
	{
		return;
	}

	switch (event_type)
	{
	case MOUSE_LEFT_PRESS:
	{
		mouse_x = (short)param1;
		mouse_y = (short)param2;
		original_focus = container->focus;
		container->focus = _ui_container_get_focus(container, mouse_x, mouse_y);

		if (original_focus != container->focus &&
			original_focus &&
			original_focus->event_proc)
		{
			original_focus->event_proc(original_focus,
				LOST_FOCUS,
				0,
				0);
		}
		if (container->focus)
		{
			container->focus->event_proc(container->focus,
				MOUSE_LEFT_PRESS,
				param1,
				param2);
		}
		break;
	}
	case KEY_INPUT:
	{
		if (!container->focus || !container->focus->event_proc)
		{
			break;
		}
		container->focus->event_proc(container->focus,
			KEY_INPUT,
			param1,
			param2);
		break;
	}
	case LOST_FOCUS:
	{
		if (container->focus && container->focus->event_proc)
		{
			container->focus->event_proc(container->focus,
				LOST_FOCUS,
				param1,
				param2);
		}
		container->focus = 0;
		break;
	}
	default:
		break;
	}

	if (container->basic.customed_event)
	{
		container->basic.customed_event(container,
			event_type,
			param1,
			param2);
	}
}

/* Render process */
void ui_container_render(UIContainer* container)
{
	Iterator it;
	if (!container || !container->basic.visible)
	{
		return;
	}
	for (it = list_begin(container->elements);
		!iterator_equal(it, list_end(container->elements));
		iterator_move(&it))
	{
		((UIElement*)iterator_read(it))->render(iterator_read(it));
	}
}
