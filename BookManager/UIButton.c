#include "UIButton.h"
#include "app.h"
#include <stdio.h>
#include "UIUtils.h"

UIButton* ui_button_construct(char* caption)
{
	UIButton* button = (UIButton*)malloc(sizeof(UIButton));
	if (!button)
	{
		return 0;
	}
	ui_element_initialize(&button->basic,
		ui_button_on_event,
		ui_button_render,
		ui_button_destory);
	memset(button->caption, 0, MAX_BUTTON_CAPTION_LENGTH);
	if (caption)
	{
		sprintf_s(button->caption, MAX_BUTTON_CAPTION_LENGTH, "%s", caption);
	}
	ui_element_set_attributes(button,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		BACKGROUND_INTENSITY);
	return button;
}

void ui_button_destory(UIButton* button)
{
	if (button)
	{
		free(button);
	}
}

void ui_button_set_caption(UIButton* cover, char* caption)
{
	if (!cover || !caption)
	{
		return;
	}
	sprintf_s(cover->caption, MAX_BUTTON_CAPTION_LENGTH, "%s", caption);
}

void ui_button_render(UIButton* button)
{
	COORD coor = button->basic.p1;
	const int kWidth = 0;
	const int kHeight = 0;
	const short kAttributes = button->basic.attributes_foreground |
		button->basic.attributes_background;
	int i = 0;

	if (!button)
	{
		return;
	}
	*(int*)(&kWidth) = abs(button->basic.p2.X - button->basic.p1.X);
	*(int*)(&kHeight) = abs(button->basic.p2.Y - button->basic.p1.Y);
	if (kWidth < 0)
	{
		return;
	}


	// render background color
	ui_draw_rectangle_simply(button->basic.p1.X,
		button->basic.p1.Y,
		button->basic.p2.X,
		button->basic.p2.Y,
		' ',
		kAttributes);

	// render caption
	coor.X = relative_persentage_X(button, 50) - strlen(button->caption) / 2;
	coor.Y = relative_persentage_Y(button, 30);
	ui_draw_text(coor, button->caption, kAttributes);
}

void ui_button_on_event(
	UIButton* button,
	UIEventType event_type,
	int param1,
	int param2)
{
	if (!button || !button->basic.visible)
	{
		return;
	}
	if (button->basic.customed_event)
	{
		button->basic.customed_event(button,
			event_type,
			param1,
			param2);
	}
}