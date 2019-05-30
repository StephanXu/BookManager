#include "app.h"
#include "DialogBooks.h"
#include "DialogBookDetail.h"
#include "UIDialog.h"
#include "UIBookCover.h"
#include "UIButton.h"
#include "BookDatabase.h"

DialogBookDetail dialog_book_detail;

int dialog_book_detail_init(
	UIContainer* parent_container,
	BookDatabase* bookdb)
{
	int i = 0;
	const short kForegroundAttributes = 0;
	const short kBackgroundAttributes = BACKGROUND_RED | BACKGROUND_GREEN;
	if (!parent_container || !bookdb)
	{
		return 0;
	}

	UIContainer* book_detail = ui_container_construct(0);
	ui_element_set_pos_relatively(book_detail, 0, 20, 33, 80, 67);
	ui_container_append_element(parent_container, book_detail);
	dialog_book_detail.container = book_detail;
	dialog_book_detail.bookdb = bookdb;

	UIDialog* dialog = ui_dialog_construct("书籍详情");
	ui_element_set_pos_relatively(dialog, book_detail, 0, 0, 100, 100);
	ui_element_set_attributes(dialog,
		kForegroundAttributes,
		kBackgroundAttributes);
	ui_container_append_element(book_detail, dialog);

	dialog_book_detail.id = ui_text_construct(0);
	ui_element_set_pos_relatively(dialog_book_detail.id, book_detail,
		80, 10, 95, 15);
	ui_element_set_attributes(dialog_book_detail.id,
		kForegroundAttributes,
		kBackgroundAttributes);
	ui_container_append_element(book_detail, dialog_book_detail.id);

	dialog_book_detail.cover = ui_book_cover_construct(0);
	ui_element_set_pos(dialog_book_detail.cover,
		relative_persentage_X(book_detail, 5),
		relative_persentage_Y(book_detail, 25),
		relative_persentage_X(book_detail, 5) + UI_BOOK_COVER_WIDTH,
		relative_persentage_Y(book_detail, 25) + UI_BOOK_COVER_HEIGHT);
	ui_container_append_element(book_detail, dialog_book_detail.cover);

	dialog_book_detail.caption = ui_text_construct(0);
	ui_element_set_pos_relatively(dialog_book_detail.caption, book_detail, 
		35, 25, 95, 30);
	ui_element_set_attributes(dialog_book_detail.caption,
		kForegroundAttributes,
		kBackgroundAttributes);
	ui_container_append_element(book_detail, dialog_book_detail.caption);

	dialog_book_detail.author = ui_text_construct(0);
	ui_element_set_pos_relatively(dialog_book_detail.author, book_detail,
		35, 45, 95, 50);
	ui_element_set_attributes(dialog_book_detail.author,
		kForegroundAttributes,
		kBackgroundAttributes);
	ui_container_append_element(book_detail, dialog_book_detail.author);

	dialog_book_detail.status = ui_text_construct(0);
	ui_element_set_pos_relatively(dialog_book_detail.status, book_detail,
		35, 65, 95, 70);
	ui_element_set_attributes(dialog_book_detail.status,
		kForegroundAttributes,
		kBackgroundAttributes);
	ui_container_append_element(book_detail, dialog_book_detail.status);

	UIButton* delete_book = ui_button_construct("删除");
	ui_element_set_pos_relatively(delete_book, book_detail, 40, 85, 55, 95);
	ui_element_set_event(delete_book, dialog_book_detail_delete_on_event);
	ui_element_set_attributes(delete_book,
		0,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	ui_container_append_element(book_detail, delete_book);

	dialog_book_detail.change_status = ui_button_construct(0);
	ui_element_set_pos_relatively(dialog_book_detail.change_status, 
		book_detail, 60, 85, 75, 95);
	ui_element_set_event(dialog_book_detail.change_status, 
		dialog_book_detail_change_status_on_event);
	ui_element_set_attributes(dialog_book_detail.change_status,
		0,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	ui_container_append_element(book_detail, dialog_book_detail.change_status);

	UIButton* cancel = ui_button_construct("关闭");
	ui_element_set_pos_relatively(cancel, book_detail, 80, 85, 95, 95);
	ui_element_set_event(cancel, dialog_book_detail_cancel_on_event);
	ui_element_set_attributes(cancel,
		0,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	ui_container_append_element(book_detail, cancel);

	ui_element_set_visible(book_detail, 0);
	dialog_book_detail.curt_id = 0;
	return 1;
}

int dialog_book_detail_close()
{
	ui_element_set_visible(dialog_book_detail.container, 0);
	dialog_book_detail.curt_id = 0;
	return 1;
}

void dialog_book_detail_show(Book* book)
{
	Iterator it;
	char tmp_string[MAX_AUTHOR_LENGTH] = { 0 };
	if (!book)
	{
		return;
	}
	ui_book_cover_set_caption(dialog_book_detail.cover, book->name);
	ui_text_set_caption(dialog_book_detail.caption, book->name);
	for (it = list_begin(book->author);
		!iterator_equal(it, list_end(book->author));
		iterator_move(&it))
	{
		sprintf_s(tmp_string,
			MAX_AUTHOR_LENGTH,
			"%s, %s",
			tmp_string,
			((Author*)iterator_read(it))->name);
	}
	if (strlen(tmp_string) >= 2)
	{
		sprintf_s(tmp_string, MAX_AUTHOR_LENGTH, "%s", tmp_string + 2);
	}
	ui_text_set_caption(dialog_book_detail.author, tmp_string);
	// MAX_AUTHOR_LENGTH is far larger than id string's length. 
	// So we use tmp_string to store id string simply.
	dialog_book_detail.curt_id = book->id;	// Store id for deleting.
	sprintf_s(tmp_string, MAX_AUTHOR_LENGTH, "id: %d", book->id);
	ui_text_set_caption(dialog_book_detail.id, tmp_string);
	if (AVAILABLE == book->status)
	{
		ui_button_set_caption(dialog_book_detail.change_status, "借出");
		ui_text_set_caption(dialog_book_detail.status, "状态：可用");
		ui_element_set_attributes(dialog_book_detail.cover,
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			BACKGROUND_RED | BACKGROUND_BLUE);
	}
	else
	{
		ui_button_set_caption(dialog_book_detail.change_status, "收回");
		ui_text_set_caption(dialog_book_detail.status, "状态：借出");
		ui_element_set_attributes(dialog_book_detail.cover,
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			BACKGROUND_INTENSITY);
	}
	ui_element_set_visible(dialog_book_detail.container, 1);
}

void dialog_book_detail_delete_on_event(
	UIButton* button,
	UIEventType event_type,
	int param1,
	int param2)
{
	if (!button || !dialog_book_detail.bookdb)
	{
		return;
	}

	switch (event_type)
	{
	case MOUSE_LEFT_PRESS:
	{
		if (dialog_book_detail.curt_id > 0)
		{
			bookdb_remove_book(dialog_book_detail.bookdb,
				dialog_book_detail.curt_id);
			bookdb_save(dialog_book_detail.bookdb, app.database_path);
			dialog_books_refresh_books();
		}
		dialog_book_detail_close();
		break;
	}
	default:
		break;
	}
}

void dialog_book_detail_cancel_on_event(
	UIButton* button,
	UIEventType event_type,
	int param1,
	int param2)
{
	if (!button)
	{
		return;
	}

	switch (event_type)
	{
	case MOUSE_LEFT_PRESS:
	{
		dialog_book_detail_close();
		break;
	}
	default:
		break;
	}
}

void dialog_book_detail_change_status_on_event(
	UIButton* button,
	UIEventType event_type,
	int param1,
	int param2)
{
	if (!button)
	{
		return;
	}

	switch (event_type)
	{
	case MOUSE_LEFT_PRESS:
	{
		bookdb_set_book_status(dialog_book_detail.bookdb,
			dialog_book_detail.curt_id,
			!strcmp(button->caption, "借出") ? LENT : AVAILABLE);
		bookdb_save(dialog_book_detail.bookdb, app.database_path);
		dialog_books_refresh_books();
		dialog_book_detail_close();
		break;
	}
	default:
		break;
	}
}
