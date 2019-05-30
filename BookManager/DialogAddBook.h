/*============================================
Date:	2019/5/27
Description:
	Dialog of add book.
	More detail see 'DialogHome.h'
============================================*/
#pragma once
#include "UIElement.h"
#include "UIContainer.h"
#include "UIDialog.h"
#include "UIUtils.h"
#include "UIButton.h"
#include "BookDatabase.h"

#ifndef DIALOG_ADD_BOOK_H
#define DIALOG_ADD_BOOK_H

typedef struct DialogAddBook
{
	UIContainer* container;
	BookDatabase* bookdb;

	char book_name[MAX_BOOK_NAME_LENGTH];
	char book_author[MAX_AUTHOR_LENGTH];
}DialogAddBook;

int dialog_add_book_init(
	UIContainer* parent_container,
	BookDatabase* bookdb);

int dialog_add_book_close();

void dialog_add_book_show();

void dialog_add_book_confirm_on_event(
	UIButton* confirm, 
	UIEventType event_type, 
	int param1, 
	int param2);

void dialog_add_book_cancel_on_event(
	UIButton* button, 
	UIEventType event_type, 
	int param1, 
	int param2);

extern DialogAddBook dialog_add_book;

#endif