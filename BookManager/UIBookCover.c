#include "UIBookCover.h"
#include "app.h"
#include <stdio.h>
#include "UIUtils.h"

UIBookCover* ui_book_cover_construct(char* caption)
{
	UIBookCover* cover = (UIBookCover*)malloc(sizeof(UIBookCover));
	if (!cover)
	{
		return 0;
	}
	ui_element_initialize(&cover->basic,
		ui_book_cover_on_event,
		ui_book_cover_render,
		ui_book_cover_destory);
	memset(cover->caption, 0, MAX_BOOK_TITLE_LENGTH);
	if (caption)
	{
		sprintf_s(cover->caption, MAX_BOOK_TITLE_LENGTH, "%s", caption);
	}
	ui_element_set_attributes(cover,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		BACKGROUND_RED | BACKGROUND_BLUE);
	return cover;
}

void ui_book_cover_destory(UIBookCover* cover)
{
	if (cover)
	{
		free(cover);
	}
}

void ui_book_cover_set_caption(UIBookCover* cover, char* caption)
{
	if (!cover || !caption)
	{
		return;
	}
	sprintf_s(cover->caption, MAX_BOOK_TITLE_LENGTH, "%s", caption);
}

void ui_book_cover_render(UIBookCover* cover)
{
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	COORD coor = cover->basic.p1;
	const int kWidth = UI_BOOK_COVER_WIDTH;
	const int kHeight = UI_BOOK_COVER_HEIGHT;
	const short kAttributes = cover->basic.attributes_foreground |
		cover->basic.attributes_background;
	int i = 0;

	if (!cover)
	{
		return;
	}

	*(int*)(&kWidth) = abs(cover->basic.p2.X - cover->basic.p1.X);
	*(int*)(&kHeight) = abs(cover->basic.p2.Y - cover->basic.p1.Y);

	GetConsoleScreenBufferInfo(app.h_output_console, &buffer_info);
	SetConsoleTextAttribute(app.h_output_console, kAttributes);

	// render background color
	ui_draw_rectangle_simply(cover->basic.p1.X,
		cover->basic.p1.Y,
		cover->basic.p1.X + kWidth,
		cover->basic.p1.Y + kHeight,
		' ',
		kAttributes);

	// render caption
	coor.X = relative_persentage_X(cover, 0) + 1;
	coor.Y = relative_persentage_Y(cover, 0) + 1;
	ui_draw_text_limited(coor.X,
		coor.Y,
		relative_persentage_X(cover, 100) - 1,
		coor.Y + kHeight,
		cover->caption,
		kAttributes);

	SetConsoleTextAttribute(app.h_output_console, buffer_info.wAttributes);
}

void ui_book_cover_on_event(
	UIBookCover* cover,
	UIEventType event_type,
	int param1,
	int param2)
{
	if (!cover || !cover->basic.visible)
	{
		return;
	}
	if (cover->basic.customed_event)
	{
		cover->basic.customed_event(cover,
			event_type,
			param1,
			param2);
	}
}