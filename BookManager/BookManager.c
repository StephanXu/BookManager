
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "app.h"
#include "list.h"
#include "BookDatabase.h"
#include "UIElement.h"
#include "UITitleBar.h"
#include "DialogAddBook.h"
#include "DialogHome.h"
#include "DialogBooks.h"
#include "DialogBookDetail.h"
#include "DialogAbout.h"
/*
TODO:
	ui_draw_text_limited 会有中文截断现象
*/


int init_console()
{
	// get handle
	app.h_input_console = GetStdHandle(STD_INPUT_HANDLE);
	app.h_output_console = GetStdHandle(STD_OUTPUT_HANDLE);
	app.h_foreground_buffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);

	if (INVALID_HANDLE_VALUE == app.h_input_console ||
		INVALID_HANDLE_VALUE == app.h_output_console)
	{
		printf("Fatal Error: Initialize console handle failed.\n");
		return 0;
	}

	// set cursor style
	CONSOLE_CURSOR_INFO cursor_info;
	if (!GetConsoleCursorInfo(app.h_output_console, &cursor_info))
	{
		printf("Fatal Error: Hide cursor 1/2 failed[%d].\n", GetLastError());
		return 0;
	}
	cursor_info.bVisible = 0;
	if (!SetConsoleCursorInfo(app.h_output_console, &cursor_info))
	{
		printf("Fatal Error: Hide cursor 2/2 failed[%d].\n", GetLastError());
	}

	// set size and color
	char command[0x30] = { 0 };
	sprintf_s(command, sizeof(command), "mode con cols=%d lines=%d",
		UI_WIDTH,
		UI_HEIGHT);
	system(command);						// set console size
	system("color 1A");						// set console color

	// set mode
	unsigned int mode;
	GetConsoleMode(app.h_input_console, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	mode |= ENABLE_MOUSE_INPUT;
	SetConsoleMode(app.h_input_console, mode);
	
	SetConsoleActiveScreenBuffer(app.h_foreground_buffer);
	return 1;
}

void render(UIElement* element)
{
	CONSOLE_CURSOR_INFO cursor_info;
	const COORD buffer_size = { UI_WIDTH,UI_HEIGHT },
		buffer_coord = { 0,0 };
	SMALL_RECT read_region = { 0,0,UI_WIDTH,UI_HEIGHT },
		write_region = { 0,0,UI_WIDTH,UI_HEIGHT };

	element->render(element);

	SetConsoleCursorPosition(app.h_foreground_buffer, app.cursor_pos);

	if (!GetConsoleCursorInfo(app.h_foreground_buffer, &cursor_info))
	{
		printf("Fatal Error: Hide cursor 1/2 failed[%d].\n", GetLastError());
		return 0;
	}
	cursor_info.bVisible = app.cursor_visible;
	SetConsoleCursorInfo(app.h_foreground_buffer, &cursor_info);

	ReadConsoleOutput(app.h_output_console,
		app.foreground_buffer, buffer_size, buffer_coord, &read_region);
	WriteConsoleOutput(app.h_foreground_buffer,
		app.foreground_buffer, buffer_size, buffer_coord, &write_region);

}

void title_event(UITitleBar* title)
{
	if (!title)
	{
		return;
	}
	ui_element_set_visible(dialog_home.container, 0);
	ui_element_set_visible(dialog_books.container, 0);
	ui_element_set_visible(dialog_about.container, 0);
	switch (title->current_page)
	{
	case 0:
		ui_element_set_visible(dialog_home.container, 1);
		break;
	case 1:
		ui_element_set_visible(dialog_books.container, 1);
		break;
	case 2:
		ui_element_set_visible(dialog_about.container, 1);
		break;
	default:
		break;
	}
}

int main()
{
	BookDatabase* bookdb = 0;
	UITitleBar* title = 0;
	INPUT_RECORD input_record;
	COORD mouse_pos;
	DWORD res = 0;
	int refresh = 1;
	// Initialize console basic settings
	if (!init_console())
	{
		return 0;
	}
	// Initialize database
	bookdb = bookdb_construct(0);
	sprintf_s(app.database_path, MAX_PATH, "store.db");
	bookdb_load(bookdb, app.database_path);
	// Initialize UI
	app.ui = ui_container_construct(0);
	dialog_home_init(app.ui);
	dialog_books_init(app.ui, bookdb);
	dialog_about_init(app.ui);
	dialog_add_book_init(app.ui,bookdb);
	dialog_book_detail_init(app.ui, bookdb);

	title = ui_titlebar_construct("吃太饱图书管理系统");
	ui_element_set_pos_relatively(title, 0, 2, 3, 98, 12);
	ui_element_set_event(title, title_event);
	ui_container_append_element(app.ui, title);

	if (!bookdb)
	{
		printf("Fatal Error: Construct book's database failed");
	}

	for (;;)
	{
		if (refresh)
		{
			ui_container_auto_remove(app.ui);
			render(app.ui);
			refresh = 0;
		}
		ReadConsoleInput(app.h_input_console, &input_record, 1, &res);
		switch (input_record.EventType)
		{
		case MOUSE_EVENT:
		{
			if (FROM_LEFT_1ST_BUTTON_PRESSED ==
				input_record.Event.MouseEvent.dwButtonState)
			{
				mouse_pos = input_record.Event.MouseEvent.dwMousePosition;
				if (0 == input_record.Event.MouseEvent.dwEventFlags)
				{
					app.ui->basic.event_proc(app.ui,
						MOUSE_LEFT_PRESS,
						mouse_pos.X,
						mouse_pos.Y);
					refresh = 1;
				}
			}
			break;
		}
		case KEY_EVENT:
		{
			if (input_record.Event.KeyEvent.bKeyDown)
			{
				app.ui->basic.event_proc(app.ui,
					KEY_INPUT,
					input_record.Event.KeyEvent.uChar.UnicodeChar,
					0);
				refresh = 1;
			}
			break;
		}
		default:
			break;
		}
	}

	ui_titlebar_destory(app.ui);
	return 0;
}
