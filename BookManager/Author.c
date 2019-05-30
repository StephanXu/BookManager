#include "Author.h"
#include <string.h>

Author* author_construct(char* author_name)
{
	Author* author = (Author*)malloc(sizeof(Author));
	if (!author)
	{
		return 0;
	}
	strcpy_s(author->name, MAX_AUTHOR_LENGTH, author_name);
	return author;
}


void author_destory(Author* author)
{
	free(author);
}
