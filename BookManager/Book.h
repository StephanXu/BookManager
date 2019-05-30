/*============================================
Date:	2019/5/25
Description:
	Book class. Be used in BookDatabase.
============================================*/

#pragma once
#include "Author.h"

#ifndef BOOK_H
#define BOOK_H

#define MAX_BOOK_NAME_LENGTH (256)

typedef enum BookStatus
{
	AVAILABLE = 0,
	LENT
}BookStatus;

typedef struct Book
{
	unsigned int id;
	char name[MAX_BOOK_NAME_LENGTH];
	List* author;	// Type of 'Author'
	BookStatus status;
	/* TODO: More information... */
}Book;

typedef struct BookFlat
{
	unsigned int id;
	unsigned int status;
	char book_name[MAX_BOOK_NAME_LENGTH];
	char author[MAX_AUTHOR_LENGTH];
}BookFlat;

/* Copy a book to an exists object */
void book_copy(Book* dest, Book* source);

/* Construct function of 'Book' */
Book* book_construct_extra(unsigned int id, char* name, List* author, BookStatus status);
Book* book_construct(Book* book);

/* Destory function of 'book' */
void book_destory(Book* book);

/* Print a book's information */
void book_print_information(Book* book);

void book_flat_object(Book* book, BookFlat* dest);

#endif
