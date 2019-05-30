#include <Windows.h>
#include "app.h"
#include "UIUtils.h"
#include <stdio.h>

unsigned int _relative_persentage(
	UIElement* ui_element,
	int y_axis,
	unsigned int persentage)
{
	if (y_axis != 0 && y_axis != 1)
	{
		return 0;
	}

	short base = 0, top = 0;
	if (!ui_element)
	{
		base = 0;
		top = y_axis ? UI_HEIGHT : UI_WIDTH;
	}
	else
	{
		//base = *(short*)((unsigned short*)ui_element + y_axis);
		//top = *(short*)((unsigned short*)ui_element + y_axis + 2);
		base = y_axis ? ui_element->p1.Y : ui_element->p1.X;
		top = y_axis ? ui_element->p2.Y : ui_element->p2.X;
	}
	return base + (persentage * (top - base)) / 100;
}

unsigned int relative_persentage_X(
	UIElement* ui_element, 
	unsigned int persentage)
{
	return _relative_persentage(ui_element, 0, persentage);
}

unsigned int relative_persentage_Y(
	UIElement* ui_element, 
	unsigned int persentage)
{
	return _relative_persentage(ui_element, 1, persentage);
}

void ui_draw_rectangle(
	COORD p1, 
	COORD p2, 
	const char texture, 
	const short attributes)
{
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	const int kWidth = p2.X - p1.X;
	const int kHeight = p2.Y - p1.Y;
	int i = 0;
	COORD curt_pos = p1;
	char* single_line = (char*)malloc(kWidth + 1);
	if (!single_line)
	{
		return;
	}

	GetConsoleScreenBufferInfo(app.h_output_console, &buffer_info);
	SetConsoleTextAttribute(app.h_output_console, attributes);

	single_line[kWidth] = 0;
	memset(single_line, texture, kWidth);
	for (i = 0; i < kHeight; ++i, ++curt_pos.Y)
	{
		SetConsoleCursorPosition(app.h_output_console, curt_pos);
		printf("%s\n", single_line);
	}

	SetConsoleTextAttribute(app.h_output_console, buffer_info.wAttributes);
	free(single_line);
}

void ui_draw_rectangle_simply(
	short x1,
	short y1,
	short x2,
	short y2,
	const char texture,
	const short attributes)
{
	COORD p1 = { x1,y1 }, p2 = { x2,y2 };
	if (x2 - x1 < 0 || y2 - y1 < 0)
	{
		return;
	}
	ui_draw_rectangle(p1, p2, texture, attributes);
}

void ui_draw_text(COORD p, char* text, const short attributes)
{
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	int i = 0;
	if (!text)
	{
		return;
	}
	GetConsoleScreenBufferInfo(app.h_output_console, &buffer_info);
	SetConsoleTextAttribute(app.h_output_console, attributes);

	SetConsoleCursorPosition(app.h_output_console, p);
	printf(text);

	SetConsoleTextAttribute(app.h_output_console, buffer_info.wAttributes);
}

void ui_draw_text_simply(
	short x,
	short y,
	char* text,
	const short attributes)
{
	COORD coor = { x,y };
	ui_draw_text(coor, text, attributes);
}

void ui_draw_text_limited(
	short x1, 
	short y1, 
	short x2, 
	short y2, 
	char* text,
	const short attributes)
{
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	short int kWidth = x2 - x1;
	short int kHeight = y2 - y1;
	char command[10] = { 0 };
	unsigned int text_len = 0;
	unsigned int row_count = 0;
	int i = 0;
	COORD coor = { x1,y1 };

	if (!text)
	{
		return;
	}
	text_len = strlen(text);
	if (text_len < 1)
	{
		return;
	}
	if (kWidth % 2)
	{
		kWidth -= 1;
	}
	GetConsoleScreenBufferInfo(app.h_output_console, &buffer_info);
	SetConsoleTextAttribute(app.h_output_console, attributes);

	sprintf_s(command, 10, "%c.%ds", '%', kWidth);

	for (i = 0; i < text_len; row_count++)
	{
		SetConsoleCursorPosition(app.h_output_console, coor);
		if (row_count == kHeight && strlen(text + i) > kWidth)
		{
			sprintf_s(command, 10, "%c.%ds", '%', kWidth - 2);
			printf(command, text + i);
			printf("бн");
			break;
		}
		i += printf(command, text + i);
		printf("\n");
		coor.Y++;
	}

	SetConsoleTextAttribute(app.h_output_console, buffer_info.wAttributes);
}

int split_author(
	char* source,
	char* splitter,
	List* author_list)
{
	char* text_next = NULL;
	char* substr = NULL;
	if (!source || !splitter || !author_list)
	{
		return 0;
	}
	substr = strtok_s(source, splitter, &text_next);
	while (substr)
	{
		list_push_back(author_list, substr);
		substr = strtok_s(NULL, splitter, &text_next);
	}
	return 0;
}