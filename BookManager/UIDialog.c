#include "app.h"
#include "UIDialog.h"
#include "UIElement.h"
#include "UIUtils.h"

/* Construct function of dialog */
UIDialog* ui_dialog_construct(char* caption)
{
	UIDialog* dialog = (UIDialog*)malloc(sizeof(UIDialog));
	if (!dialog)
	{
		return 0;
	}
	ui_element_initialize(&dialog->basic,
		0,
		ui_dialog_render,
		ui_dialog_destory);
	memset(dialog->caption, 0, MAX_DIALOG_CAPTION_LENGTH);
	if (caption)
	{
		sprintf_s(dialog->caption, MAX_DIALOG_CAPTION_LENGTH, "%s", caption);
	}
	ui_element_set_attributes(dialog,
		0,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	return dialog;
}

void ui_dialog_destory(UIDialog* dialog)
{
	if (dialog)
	{
		free(dialog);
	}
}

/* Render of 'UIDialog' */
void ui_dialog_render(UIDialog* dialog)
{
	COORD coor = dialog->basic.p1;
	const int kWidth = 0;
	const int kHeight = 0;
	const short kAttributes = dialog->basic.attributes_foreground |
		dialog->basic.attributes_background;
	int i = 0;

	if (!dialog || !dialog->basic.visible)
	{
		return;
	}
	*(int*)(&kWidth) = abs(dialog->basic.p2.X - dialog->basic.p1.X);
	*(int*)(&kHeight) = abs(dialog->basic.p2.Y - dialog->basic.p1.X);
	if (kWidth < 0)
	{
		return;
	}

	// render shadow
	ui_draw_rectangle_simply(dialog->basic.p1.X + 1,
		dialog->basic.p1.Y + 1,
		dialog->basic.p2.X + 1,
		dialog->basic.p2.Y + 1,
		' ',
		0);

	// render background color
	ui_draw_rectangle_simply(dialog->basic.p1.X,
		dialog->basic.p1.Y,
		dialog->basic.p2.X,
		dialog->basic.p2.Y,
		' ',
		kAttributes);

	// render caption
	coor.X = relative_persentage_X(dialog, 5);
	coor.Y = relative_persentage_Y(dialog, 0) + 1;
	ui_draw_text(coor, dialog->caption, kAttributes);
}

