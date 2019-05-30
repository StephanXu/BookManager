#include <stdio.h>
#include <Windows.h>
#include "UIInputBox.h"
#include "UIUtils.h"


/* Construct function of 'UIInputBox' */
UIInputBox* ui_inputbox_construct(char* caption)
{
	UIInputBox* inputbox = (UIInputBox*)malloc(sizeof(UIInputBox));
	if (!inputbox)
	{
		return 0;
	}
	ui_element_initialize(&inputbox->basic,
		ui_inputbox_on_event,
		ui_inputbox_render,
		ui_inputbox_destory);
	memset(inputbox->caption, 0, MAX_INPUTBOX_CAPTION_LENGTH);
	memset(inputbox->text, 0, MAX_INPUTBOX_INPUT_LENGTH);
	if (caption)
	{
		sprintf_s(inputbox->caption, MAX_INPUTBOX_CAPTION_LENGTH, "%s", caption);
	}
	inputbox->curt_pos = 0;
	inputbox->bind_buffer = 0;
	ui_element_set_attributes(inputbox,
		0,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	//ui_element_set_pos_relatively(inputbox, 0, 30, 45, 70, 55);
	return inputbox;
}

void ui_inputbox_destory(UIInputBox* inputbox)
{
	if (inputbox)
	{
		free(inputbox);
	}
}

void ui_inputbox_bind_buffer(
	UIInputBox* inputbox, 
	char* buf, 
	unsigned int buf_size)
{
	if (!inputbox || !buf)
	{
		return;
	}
	inputbox->bind_buffer = buf;
	inputbox->bind_buffer_size = buf_size;
}

void ui_inputbox_render(UIInputBox* inputbox)
{
	COORD coor = inputbox->basic.p1;
	const int kWidth = 0;
	const int kHeight = 2;
	const short kAttributes =
		inputbox->basic.attributes_foreground | 
		inputbox->basic.attributes_background;
	int i = 0;

	if (!inputbox || !inputbox->basic.visible)
	{
		return;
	}
	*(int*)(&kWidth) = abs(inputbox->basic.p2.X - inputbox->basic.p1.X);

	// Height is readonly
	inputbox->basic.p2.Y = inputbox->basic.p1.Y + 3;
	*(int*)(&kHeight) = 3;

	if (kWidth < 0)
	{
		return;
	}

	// Sync bind buffer
	if (inputbox->bind_buffer)
	{
		if (strcmp(inputbox->bind_buffer, inputbox->text))
		{
			strcpy_s(inputbox->text,
				MAX_INPUTBOX_INPUT_LENGTH,
				inputbox->bind_buffer);
		}
	}

	//// render shadow
	//ui_draw_rectangle_simply(inputbox->basic.p1.X + 1,
	//	inputbox->basic.p1.Y + 1,
	//	inputbox->basic.p2.X + 1,
	//	inputbox->basic.p2.Y + 1,
	//	' ',
	//	0);

	//// render background color
	//ui_draw_rectangle_simply(inputbox->basic.p1.X,
	//	inputbox->basic.p1.Y,
	//	inputbox->basic.p2.X,
	//	inputbox->basic.p2.Y,
	//	' ',
	//	kAttributes);

	// render caption
	coor.X = relative_persentage_X(inputbox, 5);
	coor.Y = relative_persentage_Y(inputbox, 0) + 1;
	ui_draw_text(coor, inputbox->caption, kAttributes);

	// render text
	coor.X += strlen(inputbox->caption) + 2;
	ui_draw_text(coor, inputbox->text, kAttributes);

	// render line
	ui_draw_rectangle_simply(
		relative_persentage_X(inputbox, 5) + strlen(inputbox->caption) + 1,
		relative_persentage_Y(inputbox, 100) - 1,
		relative_persentage_X(inputbox, 100),
		relative_persentage_Y(inputbox, 100) - 0,
		'_', kAttributes);
}

void ui_inputbox_on_event(
	UIInputBox* inputbox,
	UIEventType event_type,
	int param1,
	int param2)
{
	short mouse_x = 0, mouse_y = 0;
	int i = 0;
	COORD coor;
	CONSOLE_CURSOR_INFO cursor_info;
	unsigned short wide_char_tmp[MAX_INPUTBOX_INPUT_LENGTH];
	unsigned int wide_char_length = 0;
	if (!inputbox)
	{
		return;
	}

	switch (event_type)
	{
	case MOUSE_LEFT_PRESS:
	{
		coor.X = relative_persentage_X(inputbox, 5) + 
			strlen(inputbox->caption) + 2 + 
			strlen(inputbox->text);
		coor.Y = relative_persentage_Y(inputbox, 0) + 1;
		app.cursor_visible = 1;
		app.cursor_pos = coor;
		break;
	}
	case LOST_FOCUS:
	{
		app.cursor_visible = 0;
		coor.X = 0;
		coor.Y = 0;
		app.cursor_pos = coor;
		break;
	}
	case KEY_INPUT:
	{
		MultiByteToWideChar(CP_OEMCP,
			0,
			inputbox->text,
			-1,
			wide_char_tmp,
			MAX_INPUTBOX_INPUT_LENGTH);
		wide_char_length = wcslen(wide_char_tmp);
		if (13 == param1 || 9 == param1)
		{
			break;
		}
		else if (8 == param1)
		{
			if (wide_char_length > 0)
			{
				wide_char_tmp[wide_char_length - 1] = '\0';
			}
		}
		else if (/*49 < param1 && */wide_char_length < MAX_INPUTBOX_INPUT_LENGTH - 1)
		{
			wide_char_tmp[wide_char_length] = param1;
			wide_char_tmp[wide_char_length + 1] = '\0';
		}

		WideCharToMultiByte(CP_OEMCP,
			0,
			wide_char_tmp,
			-1,
			inputbox->text,
			MAX_INPUTBOX_INPUT_LENGTH,
			0,
			0);
		//refresh cursor position
		coor.X = relative_persentage_X(inputbox, 5) +
			strlen(inputbox->caption) + 2 +
			strlen(inputbox->text);
		coor.Y = relative_persentage_Y(inputbox, 0) + 1;
		app.cursor_visible = 1;
		app.cursor_pos = coor;
		//copy bind buffer
		if (inputbox->bind_buffer)
		{
			strcpy_s(inputbox->bind_buffer,
				inputbox->bind_buffer_size,
				inputbox->text);
		}
		break;
	}
	default:
		break;
	}

	if (inputbox->basic.customed_event)
	{
		inputbox->basic.customed_event(inputbox,
			event_type,
			param1,
			param2);
	}
}