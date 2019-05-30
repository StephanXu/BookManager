#include "DialogAddBook.h"
#include "UIElement.h"
#include "UIContainer.h"
#include "UIInputBox.h"
#include "UIButton.h"
#include "UIDialog.h"
#include "UIText.h"
#include "BookDatabase.h"
#include "DialogBooks.h"

DialogAddBook dialog_add_book;

int dialog_add_book_init(
	UIContainer* parent_container,
	BookDatabase* bookdb)
{
	const short kForegroundAttributes = 0;
	const short kBackgroundAttributes = BACKGROUND_RED | BACKGROUND_GREEN;
	if (!parent_container || !bookdb)
	{
		return 0;
	}

	UIContainer* add_book = ui_container_construct(0);
	ui_element_set_pos_relatively(add_book, 0, 20, 30, 80, 70);
	ui_container_append_element(parent_container, add_book);

	UIDialog* dialog = ui_dialog_construct("添加图书");
	ui_element_set_pos_relatively(dialog, 0, 20, 30, 80, 70);
	ui_element_set_attributes(dialog, 
		kForegroundAttributes, 
		kBackgroundAttributes);
	ui_container_append_element(add_book, dialog);

	UIInputBox* book_name = ui_inputbox_construct("书名");
	ui_element_set_pos_relatively(book_name, add_book, 5, 20, 90, 20);
	ui_element_set_attributes(book_name,
		kForegroundAttributes,
		kBackgroundAttributes);
	ui_inputbox_bind_buffer(book_name, 
		dialog_add_book.book_name,
		MAX_BOOK_NAME_LENGTH);
	ui_container_append_element(add_book, book_name);

	UIInputBox* author = ui_inputbox_construct("作者");
	ui_element_set_pos_relatively(author, add_book, 5, 40, 90, 40);
	ui_element_set_attributes(author,
		kForegroundAttributes,
		kBackgroundAttributes);
	ui_inputbox_bind_buffer(author,
		dialog_add_book.book_author,
		MAX_AUTHOR_LENGTH);
	ui_container_append_element(add_book, author);

	UIText* tips = ui_text_construct("提示：多个作者请使用逗号隔开");
	ui_element_set_pos_relatively(tips, add_book, 17, 65, 50, 75);
	ui_element_set_attributes(tips,
		kForegroundAttributes,
		kBackgroundAttributes);
	ui_container_append_element(add_book, tips);

	UIButton* confirm = ui_button_construct("添加");
	ui_element_set_pos_relatively(confirm, add_book, 70, 90, 90, 95);
	ui_element_set_event(confirm, dialog_add_book_confirm_on_event);
	ui_container_append_element(add_book, confirm);
	
	UIButton* cancel = ui_button_construct("取消");
	ui_element_set_pos_relatively(cancel, add_book, 45, 90, 65, 95);
	ui_element_set_event(cancel, dialog_add_book_cancel_on_event);
	ui_container_append_element(add_book, cancel);

	dialog_add_book.bookdb = bookdb;
	dialog_add_book.container = add_book;
	ui_element_set_visible(dialog_add_book.container, 0);

	memset(dialog_add_book.book_name, 0, MAX_BOOK_NAME_LENGTH);
	memset(dialog_add_book.book_author, 0, MAX_AUTHOR_LENGTH);
	return 1;
}

int dialog_add_book_close()
{
	ui_element_set_visible(dialog_add_book.container, 0);
	return 1;
}

void dialog_add_book_show()
{
	memset(dialog_add_book.book_name, 0, MAX_BOOK_NAME_LENGTH);
	memset(dialog_add_book.book_author, 0, MAX_AUTHOR_LENGTH);
	ui_element_set_visible(dialog_add_book.container, 1);
}

void dialog_add_book_confirm_on_event(
	UIButton* confirm,
	UIEventType event_type,
	int param1,
	int param2)
{
	List* author_list = 0;
	if (!confirm || !dialog_add_book.bookdb)
	{
		return;
	}

	switch (event_type)
	{
	case MOUSE_LEFT_PRESS:
	{
		author_list = list_construct(author_construct, author_destory);
		if (!author_list)
		{
			break;
		}
		split_author(dialog_add_book.book_author, ",",
			author_list);
		bookdb_add_book_extra(dialog_add_book.bookdb,
			dialog_add_book.book_name,
			author_list);
		list_free(author_list);
		author_list = 0;
		bookdb_save(dialog_add_book.bookdb, app.database_path);
		dialog_books_refresh_books();
		dialog_add_book_close();
		break;
	}
	default:
		break;
	}
}

void dialog_add_book_cancel_on_event(
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
		dialog_add_book_close();
		break;
	}
	default:
		break;
	}
}