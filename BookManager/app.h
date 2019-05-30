#pragma once
#include <Windows.h>
#include "UIContainer.h"
#ifndef APP_H
#define APP_H

#define UI_WIDTH (100)
#define UI_HEIGHT (40)

typedef struct App
{
	HANDLE h_input_console;
	HANDLE h_output_console;
	COORD cursor_pos;
	unsigned int cursor_visible;
	UIContainer* ui;

	HANDLE h_foreground_buffer;
	CHAR_INFO foreground_buffer[100 * 40];

	char database_path[MAX_PATH];
}App;

extern App app;

#endif