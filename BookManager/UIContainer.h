#pragma once
#include "List.h"
#include "UIElement.h"

#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

typedef struct UIContainer
{
	UIElement basic;
	List* elements;
	UIElement* focus;
}UIContainer;

/* Construct function of 'UIContainer' */
UIContainer* ui_container_construct(void* _);

/* Destory function of 'UIContainer' */
void ui_container_destory(UIContainer* container);

/* Add an element to container */
int ui_container_append_element(
	UIContainer* container,
	UIElement* element);

/* Remove an element from container */
int ui_container_remove_element(
	UIContainer* container, 
	UIElement* element);

/* Remove element that have 'deleted' mark */
void ui_container_auto_remove(UIContainer* container);

/* Get element under mouse cursor */
UIElement* _ui_container_get_focus(
	UIContainer* container,
	int x,
	int y);

/* Event process */
void ui_container_on_event(
	UIContainer* container, 
	UIEventType event_type, 
	int param1, 
	int param2);

/* Render process */
void ui_container_render(UIContainer* container);

#endif