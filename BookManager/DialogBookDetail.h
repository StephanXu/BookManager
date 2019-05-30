/*============================================
Date:	2019/5/28
Description:
	Dialog of book detail.
	More detail see 'DialogHome.h'
============================================*/
#pragma once
#include "UIContainer.h"
#include "UIBookCover.h"
#include "UIText.h"
#include "UIButton.h"
#include "BookDatabase.h"

#ifndef DIALOG_BOOK_DETAIL
#define DIALOG_BOOK_DETAIL

typedef struct DialogBookDetail
{
	UIContainer* container;
	BookDatabase* bookdb;

	UIBookCover* cover;
	UIText* caption;
	UIText* author;
	UIText* id;
	UIText* status;
	UIButton* change_status;
	unsigned int curt_id;
}DialogBookDetail;


int dialog_book_detail_init(
	UIContainer* parent_container, 
	BookDatabase* bookdb);

int dialog_book_detail_close();

void dialog_book_detail_show(Book* book);

void dialog_book_detail_delete_on_event(
	UIButton* button,
	UIEventType event_type,
	int param1,
	int param2);

void dialog_book_detail_cancel_on_event(
	UIButton* button,
	UIEventType event_type,
	int param1,
	int param2);

void dialog_book_detail_change_status_on_event(
	UIButton* button,
	UIEventType event_type, 
	int param1, 
	int param2);


#endif
