#include <stdio.h>
#include <Windows.h>
#include "app.h"
#include "UIElement.h"
#include "UIContainer.h"
#include "UITitleBar.h"
#include "UIUtils.h"

const char* kNavTitle[] = { "主页","书库","关于" };

UITitleBar* ui_titlebar_construct(char* name)
{
	UITitleBar* title = (UITitleBar*)malloc(sizeof(UITitleBar));
	if (!title)
	{
		return 0;
	}
	ui_element_initialize(&title->basic, 
		ui_titlebar_on_event, 
		ui_titlebar_render,
		ui_titlebar_destory);
	memset(title->caption, 0, MAX_TITLE_LENGTH);
	if (name)
	{
		sprintf_s(title->caption, MAX_TITLE_LENGTH, "%s", name);
	}
	title->current_page = 0;
	return title;
}

void ui_titlebar_destory(UITitleBar* title)
{
	if (title)
	{
		free(title);
	}
}

void ui_titlebar_on_event(
	UITitleBar* title,
	UIEventType event_type, 
	int param1, 
	int param2)
{
	short mouse_x = 0, mouse_y = 0;
	int i = 0;
	COORD coor;
	if (!title)
	{
		return;
	}

	if (MOUSE_LEFT_PRESS == event_type)
	{
		mouse_x = (short)param1;
		mouse_y = (short)param2;
		for (i = 0; i < sizeof(kNavTitle) / sizeof(char*); ++i)
		{
			coor.X = relative_persentage_X(title,
				90 - (sizeof(kNavTitle) / sizeof(char*) - i - 1) * 10);
			coor.Y = relative_persentage_Y(title, 40);

			if (mouse_x >= coor.X - 1 &&
				mouse_x <= coor.X + (short)strlen(kNavTitle[i]) + 1 &&
				mouse_y >= title->basic.p1.Y &&
				mouse_y <= title->basic.p2.Y)
			{
				title->current_page = i;
			}
		}
	}

	if (title->basic.customed_event)
	{
		title->basic.customed_event(title,
			event_type,
			param1,
			param2);
	}
}

void ui_titlebar_render(
	UITitleBar* title)
{
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	COORD coor = title->basic.p1;
	const int kWidth = 0;
	const int kHeight = 0;
	const short kAttributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	const short kHighLightAttributes =
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
		BACKGROUND_INTENSITY;
	int i = 0;

	if (!title || !title->basic.visible)
	{
		return;
	}
	*(int*)(&kWidth) = abs(title->basic.p2.X - title->basic.p1.X);
	*(int*)(&kHeight) = abs(title->basic.p2.Y - title->basic.p1.X);
	if (kWidth < 0)
	{
		return;
	}

	GetConsoleScreenBufferInfo(app.h_output_console, &buffer_info);
	SetConsoleTextAttribute(app.h_output_console, kAttributes);

	// render shadow
	ui_draw_rectangle_simply(title->basic.p1.X + 1,
		title->basic.p1.Y + 1,
		title->basic.p2.X + 1,
		title->basic.p2.Y + 1,
		' ',
		0);

	// render background color
	ui_draw_rectangle(title->basic.p1, title->basic.p2, ' ', kAttributes);

	// render caption
	coor.X = relative_persentage_X(title, 5);
	coor.Y = relative_persentage_Y(title, 40);
	SetConsoleCursorPosition(app.h_output_console, coor);
	printf(title->caption);

	// render navigate bar
	for (i = 0; i < sizeof(kNavTitle) / sizeof(char*); ++i)
	{
		coor.X = relative_persentage_X(title,
			90 - (sizeof(kNavTitle) / sizeof(char*) - i - 1) * 10);
		coor.Y = relative_persentage_Y(title, 40);
		if (title->current_page == i)
		{
			ui_draw_rectangle_simply(
				coor.X - 1,
				title->basic.p1.Y,
				coor.X + (short)strlen(kNavTitle[i]) + 1,
				title->basic.p2.Y,
				' ',
				kHighLightAttributes);
			SetConsoleTextAttribute(app.h_output_console, kHighLightAttributes);
			SetConsoleCursorPosition(app.h_output_console, coor);
			printf(kNavTitle[i]);
			SetConsoleTextAttribute(app.h_output_console, kAttributes);
		}
		else
		{
			SetConsoleCursorPosition(app.h_output_console, coor);
			printf(kNavTitle[i]);
		}
	}

	SetConsoleTextAttribute(app.h_output_console, buffer_info.wAttributes);
}
