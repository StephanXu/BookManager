/*============================================
Date:	2019/5/24
Description:
	A title bar
============================================*/
#pragma once
#include <Windows.h>
#include "UIElement.h"
#include "UIContainer.h"

#ifndef UI_TITLE_BAR_H
#define UI_TITLE_BAR_H

#define MAX_TITLE_LENGTH (50)

typedef enum NavItem
{
	HOME = 0,
	BOOKS,
	ABOUT
}NavItem;

typedef struct UITitleBar
{
	UIElement basic;
	char caption[MAX_TITLE_LENGTH];
	unsigned int current_page;
}UITitleBar;

extern const char* kNavTitle[];

/* Contruct function of 'UITitleBar*/
UITitleBar* ui_titlebar_construct(char* name);
/* Destory function of 'UITitleBar' */
void ui_titlebar_destory(UITitleBar* title);
void ui_titlebar_on_event(UITitleBar* title, UIEventType event_type, int param1, int param2);
/* Render a title */
void ui_titlebar_render(UITitleBar* title);

#endif