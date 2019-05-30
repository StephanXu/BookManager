/*============================================
Date:	2019/5/25
Description:
	Author class. Be used in book.
============================================*/

#pragma once

#ifndef AUTHOR_H
#define AUTHOR_H

#define MAX_AUTHOR_LENGTH (128)

typedef struct Author
{
	char name[MAX_AUTHOR_LENGTH];
	/* TODO: More information... */
}Author;


/* Construct function of 'Author' */
Author* author_construct(char* author_name);

/* Destory function of 'Author' */
void author_destory(Author* author);

#endif