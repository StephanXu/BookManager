#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include "List.h"
#include "BookDatabase.h"
#include "Author.h"

BookDatabase* bookdb_construct(BookDatabase* bookdb)
{
	BookDatabase* db = (BookDatabase*)malloc(sizeof(BookDatabase));
	if (!db)
	{
		return 0;
	}
	if (!bookdb)
	{
		db->books = list_construct(book_construct, book_destory);
		db->id_count = 0;
	}
	else
	{
		db->books = list_copy(bookdb->books);
		db->id_count = bookdb->id_count;
	}

	if (!db->books)
	{
		free(db);
		return 0;
	}
	return db;
}


void bookdb_destory(BookDatabase* bookdb)
{
	list_free(bookdb->books);
	free(bookdb);
}


int bookdb_add_book_extra(BookDatabase* bookdb, char* name, List* author)
{
	if (!bookdb || !name || !author)
	{
		return 0;
	}
	Book* book = book_construct_extra(++bookdb->id_count,
		name,
		author,
		AVAILABLE);
	if (list_push_back_manually(bookdb->books, book));
	{
		return book->id;
	}
	return 0;
}


int bookdb_add_book(
	BookDatabase* bookdb,
	char* name,
	unsigned int num_of_author, ...)
{
	int i = 0, res = 0;
	if (!bookdb || !name)
	{
		return 0;
	}
	List* author_list = list_construct(author_construct, author_destory);
	if (!author_list)
	{
		return 0;
	}
	va_list arg_list;
	va_start(arg_list, num_of_author);
	for (i = 0; i < num_of_author; ++i)
	{
		list_push_back(author_list, va_arg(arg_list, char*));
	}
	va_end(arg_list);
	res = bookdb_add_book_extra(bookdb, name, author_list);
	list_free(author_list);
	return res;
}


int _equal_book_id(Book* curt, unsigned int param)
{
	return curt->id == param;
}
Iterator _bookdb_get_book_by_id(BookDatabase* bookdb, unsigned int id)
{
	if (!bookdb || !bookdb->books)
	{
		return iterator_construct_empty();
	}
	return list_search(bookdb->books,
		(ListCompareProc)_equal_book_id,
		(void*)id);
}


void bookdb_remove_book(BookDatabase* bookdb, unsigned int id)
{
	list_erase(_bookdb_get_book_by_id(bookdb, id));
}


int bookdb_get_book_information(
	BookDatabase* bookdb,
	unsigned int id,
	Book** dest)
{
	if (!dest)
	{
		return 0;
	}
	Book* book = iterator_read(_bookdb_get_book_by_id(bookdb, id));
	if (!book)
	{
		return 0;
	}
	*dest = book_construct(book);
	return 1;
}


int bookdb_update_book(
	BookDatabase* bookdb,
	unsigned int id,
	Book* source)
{
	if (!bookdb)
	{
		return 0;
	}
	Iterator iter = _bookdb_get_book_by_id(bookdb, id);
	if (iterator_equal(iter, list_end(bookdb->books)) ||
		iterator_equal(iter, iterator_construct_empty()))
	{
		return 0;
	}
	Book* curt_book = ((Book*)iterator_read(iter));
	book_copy(curt_book, source);
	curt_book->id = id;	// Id is unique so it is a readonly variable here.
	return 1;
}


void bookdb_print_book_list(BookDatabase* bookdb)
{
	Iterator iter;
	if (!bookdb)
	{
		return;
	}
	for (iter = list_begin(bookdb->books);
		!iterator_equal(iter, list_end(bookdb->books));
		iterator_move(&iter))
	{
		printf("%d. %s\n", ((Book*)iterator_read(iter))->id, ((Book*)iterator_read(iter))->name);
	}
}

void bookdb_set_book_status(
	BookDatabase* bookdb,
	unsigned int id,
	BookStatus status)
{
	Iterator it;
	if (!bookdb)
	{
		return;
	}
	it = _bookdb_get_book_by_id(bookdb, id);
	if (iterator_equal(it, list_end(bookdb->books)))
	{
		return;
	}
	((Book*)iterator_read(it))->status = status;
}


void bookdb_save(
	BookDatabase* bookdb,
	char* path)
{
	Iterator it;
	Book* book = 0;
	BookFlat book_flat;
	FILE* file = 0;
	if (!bookdb || !path)
	{
		return;
	}
	if (fopen_s(&file, path, "wb"))
	{
		return;
	}
	if (!file)
	{
		return;
	}
	fwrite(&bookdb->id_count, sizeof(unsigned int), 1, file);
	for (it = list_begin(bookdb->books);
		!iterator_equal(it, list_end(bookdb->books));
		iterator_move(&it))
	{
		book = (Book*)iterator_read(it);
		if (!book)
		{
			continue;
		}
		book_flat_object(book, &book_flat);
		fwrite(&book_flat, sizeof(unsigned char), sizeof(BookFlat), file);
	}
	fclose(file);
}

void bookdb_load(BookDatabase* bookdb, char* path)
{
	BookFlat book_flat;
	FILE* file = 0;
	Book* book = 0;
	List* author_list = 0;
	if (!bookdb || !path)
	{
		return;
	}
	if (fopen_s(&file, path, "rb"))
	{
		return;
	}
	if (!file)
	{
		return;
	}
	fread(&bookdb->id_count, sizeof(unsigned int), 1, file);
	while (fread(&book_flat, sizeof(BookFlat), 1, file))
	{
		author_list = list_construct(author_construct, author_destory);
		if (!author_list)
		{
			fclose(file);
			break;
		}
		split_author(book_flat.author, ",",
			author_list);
		book = book_construct_extra(book_flat.id,
			book_flat.book_name,
			author_list,
			book_flat.status);
		list_push_back_manually(bookdb->books, book);

		list_free(author_list);
	}
	fclose(file);
}