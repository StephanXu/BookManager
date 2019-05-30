#pragma once
#include "UIContainer.h"
#ifndef DIALOG_ABOUT_H
#define DIALOG_ABOUT_H

typedef struct DialogAbout
{
	UIContainer* container;
}DialogAbout;

int dialog_about_init(UIContainer* parent_container);

int dialog_about_close();

extern DialogAbout dialog_about;

#endif