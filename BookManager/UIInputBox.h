/*============================================
Date:	2019/5/27
Description:
	A Inputbox.
	Inputbox can bind a buffer. And it can automatically sync the buffer at 
	the time it has been changed.
============================================*/
#pragma once
#include "app.h"
#include "UIElement.h"

#ifndef UI_INPUT_BOX
#define UI_INPUT_BOX

#define MAX_INPUTBOX_CAPTION_LENGTH (10)
#define MAX_INPUTBOX_INPUT_LENGTH (50)

typedef struct UIInputBox
{
	UIElement basic;
	char caption[MAX_INPUTBOX_CAPTION_LENGTH];
	char text[MAX_INPUTBOX_INPUT_LENGTH];
	int curt_pos;
	char* bind_buffer;
	unsigned int bind_buffer_size;
}UIInputBox;

/* Construct function of 'UIInputBox' */
UIInputBox* ui_inputbox_construct(char* caption);

void ui_inputbox_destory(UIInputBox* inputbox);

void ui_inputbox_bind_buffer(
	UIInputBox* inputbox, 
	char* buf, 
	unsigned int buf_size);

void ui_inputbox_render(UIInputBox* inputbox);

void ui_inputbox_on_event(
	UIInputBox* inputbox,
	UIEventType event_type,
	int param1,
	int param2);
#endif