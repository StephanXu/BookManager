#include "DialogAbout.h"
#include "UIElement.h"
#include "UIContainer.h"
#include "UIDialog.h"
#include "UIText.h"
#include "UIUtils.h"
DialogAbout dialog_about;

int dialog_about_init(UIContainer* parent_container)
{
	int i = 0;
	if (!parent_container)
	{
		return 0;
	}

	UIContainer* about = ui_container_construct(0);
	ui_element_set_pos_relatively(about, 0, 2, 15, 98, 94);
	ui_container_append_element(parent_container, about);

	UIDialog* dialog = ui_dialog_construct("¹ØÓÚ");
	ui_element_set_pos_relatively(dialog, 0, 2, 15, 98, 94);
	ui_container_append_element(about, dialog);

	const char* str_logo1[5] = {
		" ______     ______     ______     __  __",
		"/\\  == \\   /\\  __ \\   /\\  __ \\   /\\ \\/ /",
		"\\ \\  __<   \\ \\ \\/\\ \\  \\ \\ \\/\\ \\  \\ \\  _\"-.",
		" \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\",
		"  \\/_____/   \\/_____/   \\/_____/   \\/_/\\/_/"
	};
	const char* str_logo2[5] = {
		" __    __     ______     __   __     ______     ______     ______     ______",
		"/\\ \"-./  \\   /\\  __ \\   /\\ \"-.\\ \\   /\\  __ \\   /\\  ___\\   /\\  ___\\   /\\  == \\",
		"\\ \\ \\-./\\ \\  \\ \\  __ \\  \\ \\ \\-.  \\  \\ \\  __ \\  \\ \\ \\__ \\  \\ \\  __\\   \\ \\  __<",
		" \\ \\_\\ \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\\\\"\\_\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\",
		"  \\/_/  \\/_/   \\/_/\\/_/   \\/_/ \\/_/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_/ /_/"
	};
	
	for (i = 0; i < 5; ++i)
	{
		//logo1
		UIText* logo = ui_text_construct(str_logo1[i]);
		ui_element_set_pos(logo,
			relative_persentage_X(about, 25),
			relative_persentage_Y(about, 15) + i,
			relative_persentage_X(about, 80),
			relative_persentage_Y(about, 15) + i + 1);
		ui_element_set_attributes(logo,
			FOREGROUND_BLUE,
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		ui_container_append_element(about, logo);
		//logo2
		logo = ui_text_construct(str_logo2[i]);
		ui_element_set_pos(logo,
			relative_persentage_X(about, 8),
			relative_persentage_Y(about, 32) + i,
			relative_persentage_X(about, 92),
			relative_persentage_Y(about, 32) + i + 1);
		ui_element_set_attributes(logo,
			FOREGROUND_BLUE,
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		ui_container_append_element(about, logo);
	}

	UIText* author = ui_text_construct("Ðìè÷º­ | www.mrxzh.com");
	ui_element_set_pos(author,
		relative_persentage_X(about, 37),
		relative_persentage_Y(about, 70),
		relative_persentage_X(about, 63),
		relative_persentage_Y(about, 70)+ 1);
	ui_element_set_attributes(author,
		0,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	ui_container_append_element(about, author);

	UIText* github = ui_text_construct("Github: https://github.com/StephanXu/BookManager");
	ui_element_set_pos(github,
		relative_persentage_X(about, 25),
		relative_persentage_Y(about, 75),
		relative_persentage_X(about, 75),
		relative_persentage_Y(about, 75) + 1);
	ui_element_set_attributes(github,
		0,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	ui_container_append_element(about, github);

	UIText* ip = ui_text_construct("Copyright 2019. Stephan all rights reserved");
	ui_element_set_pos(ip,
		relative_persentage_X(about, 28),
		relative_persentage_Y(about, 85),
		relative_persentage_X(about, 75),
		relative_persentage_Y(about, 85) + 1);
	ui_element_set_attributes(ip,
		FOREGROUND_INTENSITY,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	ui_container_append_element(about, ip);

	dialog_about.container = about;

	return 1;
}

int dialog_about_close()
{
	ui_element_set_visible(dialog_about.container, 0);
	return 1;
}
