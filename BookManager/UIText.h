#pragma once
#include "UIElement.h"

#ifndef UI_TEXT_H
#define UI_TEXT_H

#define MAX_TEXT_CAPTION_LENGTH (1024)

typedef struct UIText
{
	UIElement basic;
	char caption[MAX_TEXT_CAPTION_LENGTH];
}UIText;


UIText* ui_text_construct(char* caption);

void ui_text_destory(UIText* text);

void ui_text_render(UIText* text);

void ui_text_on_event(
	UIText* text,
	UIEventType event_type,
	int param1,
	int param2);

void ui_text_set_caption(UIText* text, char* caption);

#endif