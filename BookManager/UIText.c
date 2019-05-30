#include "UIText.h"
#include "UIUtils.h"
#include <stdio.h>
UIText* ui_text_construct(char* caption)
{
	UIText* text = (UIText*)malloc(sizeof(UIText));
	if (!text)
	{
		return 0;
	}
	ui_element_initialize(&text->basic,
		ui_text_on_event,
		ui_text_render,
		ui_text_destory);
	memset(text->caption, 0, MAX_TEXT_CAPTION_LENGTH);
	if (caption)
	{
		sprintf_s(text->caption, MAX_TEXT_CAPTION_LENGTH, "%s", caption);
	}
	ui_element_set_attributes(text,
		0,
		BACKGROUND_INTENSITY);
	return text;
}

void ui_text_destory(UIText* text)
{
	if (text)
	{
		free(text);
	}
}

void ui_text_render(UIText* text)
{
	COORD coor = text->basic.p1;
	const short kAttributes = text->basic.attributes_foreground |
		text->basic.attributes_background;
	int i = 0;

	if (!text)
	{
		return;
	}

	// render caption
	coor.X = relative_persentage_X(text, 0);
	coor.Y = relative_persentage_Y(text, 0);
	//ui_draw_text(coor, text->caption, kAttributes);
	ui_draw_text_limited(coor.X, coor.Y,
		text->basic.p2.X, text->basic.p2.Y,
		text->caption, kAttributes);
}

void ui_text_on_event(
	UIText* text,
	UIEventType event_type,
	int param1,
	int param2)
{
	if (!text || !text->basic.visible)
	{
		return;
	}
	if (text->basic.customed_event)
	{
		text->basic.customed_event(text,
			event_type,
			param1,
			param2);
	}
}


void ui_text_set_caption(UIText* text, char* caption)
{
	if (!text || !caption)
	{
		return;
	}
	sprintf_s(text->caption, MAX_TEXT_CAPTION_LENGTH, "%s", caption);
}
