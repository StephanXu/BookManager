#include "DialogHome.h"
#include "UIElement.h"
#include "UIContainer.h"
#include "UIInputBox.h"
#include "UIButton.h"
#include "BookDatabase.h"

DialogHome dialog_home;

int dialog_home_init(UIContainer* parent_container)
{
	if (!parent_container)
	{
		return 0;
	}

	UIContainer* home = ui_container_construct(0);
	ui_element_set_pos_relatively(home, 0, 2, 15, 98, 94);
	ui_container_append_element(parent_container, home);

	UIDialog* dialog = ui_dialog_construct("ึ๗าณ");
	ui_element_set_pos_relatively(dialog, 0, 2, 15, 98, 94);
	ui_container_append_element(home, dialog);

	dialog_home.container = home;

	return 1;
}

int dialog_home_close()
{
	ui_element_set_visible(dialog_home.container, 0);
	return 1;
}
