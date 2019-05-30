/*============================================
Date:	2019/5/26
Description:
	UI_Element is the basic class of all the elements. Every sub class should 
	contains a UI_Element object at the beginning.
============================================*/
#pragma once
#include <Windows.h>
#include "List.h"

#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

typedef enum UIEventType
{
	KEY_INPUT = 0,
	MOUSE_LEFT_PRESS,
	MOUSE_RIGHT_PRESS,
	GET_FOCUS,
	LOST_FOCUS,
	CREATED
}UIEventType;


typedef void(*UIEvent)(
	void* self,
	UIEventType event_type,
	int param1,
	int param2);
typedef void(*UIRender)(void* self);


typedef struct UIElement
{
	COORD p1, p2;
	UIEvent event_proc;
	UIRender render;
	ListNodeContentDestory element_destory;
	UIEvent customed_event;
	unsigned int deleted;
	unsigned int visible;
	unsigned short attributes_foreground;
	unsigned short attributes_background;
	struct UIElement* parent;
}UIElement;

/* Initialize a element object. It won't allocate memory */
void ui_element_initialize(
	UIElement* ui_element,
	UIEvent event_proc,
	UIRender render_proc,
	ListNodeContentDestory destory_proc);

/* 
Destory function of 'UIElement'. It will call 'element_destory' to 
free memory.
*/
void ui_element_destory(UIElement* element);

/* Set element's position */
void ui_element_set_pos(
	UIElement* element,
	short x1,
	short y1,
	short x2,
	short y2);

/* Set relative position */
void ui_element_set_pos_relatively(
	UIElement* element,
	UIElement* base,
	short x1,
	short y1,
	short x2,
	short y2
);

/* 
Set a customed event processing function.
The 'customed_proc' will be called from default 
event process function
*/
void ui_element_set_event(UIElement* element, UIEvent customed_proc);

/* Mark a element to be delete at the next rendering time. */
void ui_element_mark_as_deleted(UIElement* element);

/* Set visible */
void ui_element_set_visible(
	UIElement* element, 
	unsigned int visible);

/* Set attributes */
void ui_element_set_attributes(
	UIElement* element, 
	unsigned short foreground, 
	unsigned short background);

#endif