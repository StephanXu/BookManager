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

int dialog_home_init(UIContainer* parent_container);

int dialog_home_close();

extern DialogHome dialog_home;

#endif