#include "List.h"
#include "Book.h"
#include "Author.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

void book_copy(Book* dest, Book* source)
{
	if (!dest || !source)
	{
		return;
	}
	dest->id = source->id;
	dest->author = list_copy(source->author);
	dest->status = source->status;
	strcpy_s(dest->name, MAX_BOOK_NAME_LENGTH, source->name);
}


Book* book_construct_extra(
	unsigned int id,
	char* name,
	List* author,
	BookStatus status)
{
	Book* new_book = (Book*)malloc(sizeof(Book));
	if (!new_book)
	{
		return 0;
	}
	Book book;
	book.id = id;
	strcpy_s(book.name, MAX_BOOK_NAME_LENGTH, name);
	book.author = author;	// book copy will copy the list
	book.status = status;
	book_copy(new_book, &book);
	return new_book;
}
Book* book_construct(Book* book)
{
	return book_construct_extra(book->id,
		book->name,
		book->author,
		book->status);
}


void book_destory(Book* book)
{
	list_free(book->author);
	free(book);
}


void book_print_information(Book* book)
{
	if (!book)
	{
		return;
	}
	printf("Book name:\n\t%s\n", book->name);
	printf("Authors:\n");
	for (Iterator it = list_begin(book->author);
		!iterator_equal(it, list_end(book->author));
		iterator_move(&it))
	{
		printf("\t%s\n", ((Author*)iterator_read(it))->name);
	}
	switch (book->status)
	{
	case AVAILABLE:
		printf("Status:\n\tAvailable\n");
		break;
	case LENT:
		printf("Status:\n\tLent\n");
		break;
	default:
		printf("Status:\n\tBeaking\n");
		break;
	}
}

void book_flat_object(Book* book, BookFlat* dest)
{
	Iterator it;
	if (!book || !dest)
	{
		return;
	}
	dest->id = book->id;
	dest->status = book->status;
	strcpy_s(dest->book_name, MAX_BOOK_NAME_LENGTH, book->name);
	memset(dest->author, 0, MAX_AUTHOR_LENGTH);
	for (it = list_begin(book->author);
		!iterator_equal(it, list_end(book->author));
		iterator_move(&it))
	{
		sprintf_s(dest->author, MAX_AUTHOR_LENGTH, ",%s",
			((Author*)iterator_read(it))->name);
	}
	if (strlen(dest->author) > 0)
	{
		sprintf_s(dest->author, MAX_AUTHOR_LENGTH, "%s", dest->author + 1);
	}
	return;
}