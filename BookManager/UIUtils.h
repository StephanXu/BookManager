#pragma once
#include <Windows.h>
#include "UIElement.h"
#ifndef UI_Utils_H
#define UI_Utils_H

unsigned int _relative_persentage(void* ui_element, int y_axis, unsigned int persentage);

unsigned int relative_persentage_X(void* ui_element, unsigned int persentage);

unsigned int relative_persentage_Y(void* ui_element, unsigned int persentage);

void ui_draw_rectangle(COORD p1, COORD p2, const char texture, const short attributes);

void ui_draw_rectangle_simply(short x1, short y1, short x2, short y2, const char texture, const short attributes);

void ui_draw_text(COORD p, char* text, const short attributes);

void ui_draw_text_simply(short x, short y, char* text, const short attributes);

void ui_draw_text_limited(
	short x1,
	short y1, 
	short x2, 
	short y2,
	char* text, 
	const short attributes);

int split_author(
	char* source,
	char* splitter,
	List* author_list);

#endif