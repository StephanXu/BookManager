#pragma once
#include <stdio.h>
#include "UIElement.h"

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#define MAX_DIALOG_CAPTION_LENGTH (50)

typedef struct UIDialog
{
	UIElement basic;
	char caption[MAX_DIALOG_CAPTION_LENGTH];
}UIDialog;

/* Construct function of dialog */
UIDialog* ui_dialog_construct(char* caption);

/* Destory functon of 'UIDialog' */
void ui_dialog_destory(UIDialog* dialog);

/* Render of 'UIDialog' */
void ui_dialog_render(UIDialog* dialog);

#endif