/*============================================
Date:	2019/5/27
Description:
	A button
============================================*/
#pragma once
#include "UIElement.h"

#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#define MAX_BUTTON_CAPTION_LENGTH (50)

typedef struct UIButton
{
	UIElement basic;
	char caption[MAX_BUTTON_CAPTION_LENGTH];
}UIButton;

/* Construct function of 'UIButton' */
UIButton* ui_button_construct(char* caption);

/* Destorying function of 'UIButton */
void ui_button_destory(UIButton* button);

/* Set button's caption */
void ui_button_set_caption(UIButton* cover, char* caption);

/* Button's render */
void ui_button_render(UIButton* button);

/* Event */
void ui_button_on_event(
	UIButton* button,
	UIEventType event_type,
	int param1,
	int param2);
#endif