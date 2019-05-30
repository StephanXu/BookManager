#pragma once
#include "UIElement.h"
#include "UIContainer.h"
#include "UIDialog.h"
#include "UIUtils.h"
#include "UIButton.h"
#include "UIBookCover.h"
#include "BookDatabase.h"

#ifndef DIALOG_BOOKS_H
#define DIALOG_BOOKS_H

#define BOOKS_COVER_LIST_COL (5)
#define BOOKS_COVER_LIST_ROW (2)
#define BOOKS_COVER_LIST_PAGE_CONTENT (BOOKS_COVER_LIST_COL * \
	BOOKS_COVER_LIST_ROW)

typedef struct DialogBooks
{
	UIContainer* container;
	BookDatabase* bookdb;
	UIBookCover* covers[BOOKS_COVER_LIST_PAGE_CONTENT];
	Book* books[BOOKS_COVER_LIST_PAGE_CONTENT];
	unsigned int covers_srow;
}DialogBooks;

int dialog_books_init(
	UIContainer* parent_container,
	BookDatabase* bookdb);

int dialog_books_close();

void dialog_books_refresh_books();

void dialog_books_cover_on_event(
	UIBookCover* cover, 
	UIEventType event_type, 
	int param1, 
	int param2);

void dialog_books_add_book_on_event(
	UIButton* button, 
	UIEventType event_type, 
	int param1, 
	int param2);

void dialog_books_last_page_on_event(
	UIButton* button,
	UIEventType event_type, 
	int param1,
	int param2);

void dialog_books_next_page_on_event(
	UIButton* button, 
	UIEventType event_type, 
	int param1, 
	int param2);

extern DialogBooks dialog_books;

#endif