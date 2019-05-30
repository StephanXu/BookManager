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

UIButton* ui_button_construct(char* caption);

void ui_button_destory(UIButton* button);

void ui_button_set_caption(UIButton* cover, char* caption);

void ui_button_render(UIButton* button);

void ui_button_on_event(
	UIButton* button,
	UIEventType event_type,
	int param1,
	int param2);
#endif