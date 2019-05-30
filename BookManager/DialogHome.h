/*============================================
Date:	2019/5/30
Description:
	Dialog of home.
	A dialog is a group of UI elements. Just like a window. You should define
	all element and their event(when you need). UI framework will render them
	correctly. So you just focus on your layout, event. For each dialog,
	I strongly recommands you to implement 'init' function for initialize and
	'close' function for hiding or destorying. In 'DialogBookDetail.h', I bind 
	some event on UI element.
============================================*/
#pragma once
#include "UIElement.h"
#include "UIContainer.h"
#include "UIDialog.h"
#include "UIUtils.h"
#include "UIButton.h"
#include "BookDatabase.h"

#ifndef DIALOG_HOME_H
#define DIALOG_HOME_H

typedef struct DialogHome
{
	UIContainer* container;
}DialogHome;

/* Initialize function of 'DialogHome' */
int dialog_home_init(UIContainer* parent_container);

/* Hiding function of 'DialogHome' */
int dialog_home_close();

extern DialogHome dialog_home;

#endif