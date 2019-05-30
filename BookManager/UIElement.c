#pragma once
#include "UIElement.h"
#include "List.h"
#include "UIUtils.h"

void ui_element_initialize(
	UIElement* ui_element,
	UIEvent event_proc,
	UIRender render_proc,
	ListNodeContentDestory destory_proc)
{
	ui_element->event_proc = event_proc;
	ui_element->render = render_proc;
	ui_element->element_destory = destory_proc;
	ui_element->customed_event = 0;
	ui_element->parent = 0;
	ui_element->deleted = 0;
	ui_element->visible = 1;
	ui_element->attributes_background = 
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	ui_element->attributes_foreground = 0;
}

void ui_element_destory(UIElement* element)
{
	if (element->element_destory)
	{
		element->element_destory(element);
	}
}

void ui_element_set_pos(
	UIElement* element, 
	short x1, 
	short y1, 
	short x2, 
	short y2)
{
	COORD p1 = { x1,y1 }, p2 = { x2,y2 };
	if (!element || x2 - x1 < 0 || y2 - y1 < 0)
	{
		return;
	}
	element->p1 = p1;
	element->p2 = p2;
}

/* Set relative position */
void ui_element_set_pos_relatively(
	UIElement* element, 
	UIElement* base, 
	short x1, 
	short y1, 
	short x2, 
	short y2)
{
	ui_element_set_pos(element,
		relative_persentage_X(base, x1), relative_persentage_Y(base, y1),
		relative_persentage_X(base, x2), relative_persentage_Y(base, y2));
}

void ui_element_set_event(UIElement* element, UIEvent customed_proc)
{
	if (!element)
	{
		return;
	}
	element->customed_event = customed_proc;
}

void ui_element_mark_as_deleted(UIElement* element)
{
	if (!element)
	{
		return;
	}
	element->deleted = 1;
}

void ui_element_set_visible(
	UIElement* element,
	unsigned int visible)
{
	if (!element)
	{
		return;
	}
	element->visible = visible;
}

void ui_element_set_attributes(
	UIElement* element,
	unsigned short foreground,
	unsigned short background)
{
	if (!element)
	{
		return;
	}
	element->attributes_foreground = foreground;
	element->attributes_background = background;
}