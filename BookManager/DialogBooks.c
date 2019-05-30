#include "DialogBooks.h"
#include "UIElement.h"
#include "UIContainer.h"
#include "UIInputBox.h"
#include "UIButton.h"
#include "BookDatabase.h"
#include "UIBookCover.h"
#include "DialogBookDetail.h"
#include "DialogAddBook.h"
DialogBooks dialog_books;

int dialog_books_init(
	UIContainer* parent_container,
	BookDatabase* bookdb)
{
	int i = 0;
	if (!parent_container || !bookdb)
	{
		return 0;
	}

	UIContainer* books = ui_container_construct(0);
	ui_element_set_pos_relatively(books, 0, 2, 15, 98, 94);
	ui_container_append_element(parent_container, books);
	dialog_books.container = books;
	dialog_books.bookdb = bookdb;

	UIDialog* dialog = ui_dialog_construct("书库");
	ui_element_set_pos_relatively(dialog, books, 0, 0, 100, 100);
	ui_container_append_element(books, dialog);

	UIButton* add_book = ui_button_construct("添加");
	ui_element_set_pos_relatively(add_book, books, 58, 5, 68, 7);
	ui_element_set_event(add_book, dialog_books_add_book_on_event);
	ui_container_append_element(books, add_book);

	UIButton* last_page = ui_button_construct("上一页");
	ui_element_set_pos_relatively(last_page, books, 72, 5, 83, 7);
	ui_element_set_event(last_page, dialog_books_last_page_on_event);
	ui_container_append_element(books, last_page);

	UIButton* next_page = ui_button_construct("下一页");
	ui_element_set_pos_relatively(next_page, books, 86, 5, 96, 7);
	ui_element_set_event(next_page, dialog_books_next_page_on_event);
	ui_container_append_element(books, next_page);

	dialog_books.covers_srow = 0;
	for (i = 0; i < BOOKS_COVER_LIST_PAGE_CONTENT; ++i)
	{
		dialog_books.covers[i] = 0;
		dialog_books.books[i] = 0;
	}
	dialog_books_refresh_books();

	return 1;
}

int dialog_books_close()
{
	ui_element_set_visible(dialog_books.container, 0);
	return 1;
}

void dialog_books_refresh_books()
{
	Iterator it;
	int count = 0;
	int idx = 0;
	int i = 0;
	Book* book = 0;
	if (!dialog_books.container)
	{
		return;
	}
	if (dialog_books.covers_srow * BOOKS_COVER_LIST_PAGE_CONTENT >
		dialog_books.bookdb->books->size)
	{
		dialog_books.covers_srow--;
	}
	for (it = list_begin(dialog_books.bookdb->books);
		!iterator_equal(it, list_end(dialog_books.bookdb->books));
		iterator_move(&it), count++)
	{
		if (BOOKS_COVER_LIST_COL * dialog_books.covers_srow > count)
		{
			continue;
		}
		book = iterator_read(it);
		if (!book)
		{
			return;
		}
		idx = count - BOOKS_COVER_LIST_COL * dialog_books.covers_srow;
		if (idx >= BOOKS_COVER_LIST_PAGE_CONTENT)
		{
			break;
		}
		if (!dialog_books.covers[idx])
		{
			dialog_books.covers[idx] = ui_book_cover_construct(book->name);
			ui_element_set_event(dialog_books.covers[idx],
				dialog_books_cover_on_event);
			ui_container_append_element(dialog_books.container,
				dialog_books.covers[idx]);
		}
		else
		{
			ui_book_cover_set_caption(dialog_books.covers[idx],
				book->name);
		}
		if (AVAILABLE == book->status)
		{
			ui_element_set_attributes(dialog_books.covers[idx],
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
				BACKGROUND_RED | BACKGROUND_BLUE);
		}
		else
		{
			ui_element_set_attributes(dialog_books.covers[idx],
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
				BACKGROUND_INTENSITY);
		}
		ui_element_set_pos(dialog_books.covers[idx],
			relative_persentage_X(dialog_books.container, 5 + 19 * (idx % BOOKS_COVER_LIST_COL)),
			relative_persentage_Y(dialog_books.container, 20 + 40 * (idx / BOOKS_COVER_LIST_COL)),
			relative_persentage_X(dialog_books.container, 5 + 19 * (idx % BOOKS_COVER_LIST_COL)) + UI_BOOK_COVER_WIDTH,
			relative_persentage_Y(dialog_books.container, 20 + 40 * (idx / BOOKS_COVER_LIST_COL)) + UI_BOOK_COVER_HEIGHT);
		dialog_books.books[idx] = book;
	}
	idx = count - BOOKS_COVER_LIST_COL * dialog_books.covers_srow;
	for (i = idx; i < BOOKS_COVER_LIST_PAGE_CONTENT; ++i)
	{
		if (dialog_books.covers[i])
		{
			ui_element_mark_as_deleted(dialog_books.covers[i]);
		}
		dialog_books.covers[i] = 0;
		dialog_books.books[i] = 0;
	}
}

void dialog_books_cover_on_event(
	UIBookCover* cover,
	UIEventType event_type,
	int param1,
	int param2)
{
	int idx = 0;
	if (!cover)
	{
		return;
	}
	
	switch (event_type)
	{
	case MOUSE_LEFT_PRESS:
	{
		idx = cover - dialog_books.covers;
		for (idx = 0; idx < BOOKS_COVER_LIST_PAGE_CONTENT; ++idx)
		{
			if (dialog_books.covers[idx] == cover)
			{
				break;
			}
		}
		if (BOOKS_COVER_LIST_PAGE_CONTENT == idx)
		{
			break;
		}
		if (idx >= 0 &&
			idx < BOOKS_COVER_LIST_PAGE_CONTENT &&
			dialog_books.books[idx])
		{
			dialog_book_detail_show(dialog_books.books[idx]);
		}
		break;
	}
	default:
		break;
	}
}

void dialog_books_add_book_on_event(
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
		dialog_add_book_show();
		break;
	}
	default:
		break;
	}
}

void dialog_books_last_page_on_event(
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
		if (dialog_books.covers_srow > 0)
		{
			dialog_books.covers_srow--;
			dialog_books_refresh_books();
		}
		break;
	}
	default:
		break;
	}
}

void dialog_books_next_page_on_event(
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
		dialog_books.covers_srow++;
		dialog_books_refresh_books();
		break;
	}
	default:
		break;
	}
}