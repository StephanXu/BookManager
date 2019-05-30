/*============================================
Date:	2019/5/25
Description:
	Book database.
	Including add, list, remove, search.
Usage example:
	int main()
	{
		BookDatabase* bookdb = bookdb_construct(0);
		bookdb_add_book(bookdb,
			"The Three-Body Problem",
			1,
			"Liu Cixin");
		bookdb_add_book(bookdb,
			"The Communist Manifesto",
			2,
			"Karl Marx",
			"Friedrich Engels");

		bookdb_print_book_list(bookdb);

		Book* book;
		bookdb_get_book_information(bookdb, 2, &book);
		book_print_information(book);
		book_destory(book);

		bookdb_remove_book(bookdb, 1);
		bookdb_add_book(bookdb,
			"Test book",
			2,
			"Test Author 1",
			"Test author 2");

		bookdb_print_book_list(bookdb);

		bookdb_destory(bookdb);
		return 0;
	}
============================================*/

#pragma once
#include "List.h"
#include "Author.h"
#include "Book.h"

#ifndef BOOK_DATABASE_H
#define BOOK_DATABASE_H

typedef struct BookDatabase
{
	List* books;	// Type of 'Book'
	unsigned int id_count;
}BookDatabase;


/* Construct function of 'BookDatabase' */
BookDatabase* bookdb_construct(BookDatabase* bookdb);

/* Destory function of 'BookDatabase' */
void bookdb_destory(BookDatabase* bookdb);

/*
Add a book to book database.
Return id(>0) for success, 0 for failed.
*/
int bookdb_add_book_extra(BookDatabase* bookdb, char* name, List* author);

/*
Add a book to book database.
Args:
	bookdb:			book database
	name:			book name
	num_of_author:	num of author
	...:			(string) author's names
Return id(>0) for success, 0 for failed.
*/
int bookdb_add_book(BookDatabase* bookdb, char* name, unsigned int num_of_author, ...);

/*
Get a book object by its id
Return 1 for success, 0 for failed.
*/
Iterator _bookdb_get_book_by_id(BookDatabase* bookdb, unsigned int id);

/* Remove a book from book database by its id */
void bookdb_remove_book(BookDatabase* bookdb, unsigned int id);

/* Get a book's object's copy by its id */
int bookdb_get_book_information(BookDatabase* bookdb, unsigned int id, Book** dest);

/*
Update a book's information
Args:
	bookdb:	book database
	id:		book's id
	source:	Object for updating.
			variable 'id' of this argument will be ignored.
Return 1 for success, 0 for failed.
*/
int bookdb_update_book(BookDatabase* bookdb, unsigned int id, Book* source);

/* Print book list in book database */
void bookdb_print_book_list(BookDatabase* bookdb);

void bookdb_set_book_status(
	BookDatabase* bookdb, 
	unsigned int id, 
	BookStatus status);

void bookdb_save(
	BookDatabase* bookdb,
	char* path);

void bookdb_load(BookDatabase* bookdb, char* path);

#endif