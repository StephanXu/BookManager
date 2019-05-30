/*============================================
Date:	2019/5/28
Description:
	A book cover element.
	It has a readonly size(15*9). So please do not set a too large position 
	to it. I might influence event's catching.
============================================*/

#pragma once
#include "UIElement.h"

#ifndef UI_BOOK_COVER_H
#define UI_BOOK_COVER_H

#define MAX_BOOK_TITLE_LENGTH (100)
#define UI_BOOK_COVER_WIDTH (15)
#define UI_BOOK_COVER_HEIGHT (9)

typedef struct UIBookCover
{
	UIElement basic;
	char caption[MAX_BOOK_TITLE_LENGTH];
}UIBookCover;

UIBookCover* ui_book_cover_construct(char* caption);

void ui_book_cover_destory(UIBookCover* bc);

void ui_book_cover_set_caption(UIBookCover* cover, char* caption);

void ui_book_cover_render(UIBookCover* bc);

void ui_book_cover_on_event(
	UIBookCover* button,
	UIEventType event_type,
	int param1,
	int param2);

#endif