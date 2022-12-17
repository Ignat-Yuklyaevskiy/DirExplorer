#include "TextMenu.h"

TextMenu::TextMenu(vector<string> menuItems, string title)
{
	this->menuItems = menuItems;
	this->title = title;
}

void TextMenu::PrintMenu(int currentSelect)
{
	int count = currentSelect / 25;
	for (size_t i = 25 * count; i < (25 * count) + 25 && i < menuItems.size(); i++)
	{
		cout << (i == currentSelect ? "-" : "") << menuItems[i] << (i == currentSelect ? "-" : "") << endl;
	}
}

pair<int, CommandState> TextMenu::Start()
{
	int currentSelect = 0;
	bool isRun = true;
	while (isRun)
	{
		system("cls");
		cout << title << endl;
		PrintMenu(currentSelect);
		char x;
		x = _getch();
		if (x == '\r')
		{
			isRun = false;
			return make_pair(currentSelect, Select);
		}
		else
			if (x == 27)
			{
				return make_pair(currentSelect, Exit);
			}
			else
			{
				switch (_getch())
				{
				case 72:
					if (currentSelect > 0)
						currentSelect--;
					break;
				case 80:
					if (currentSelect < menuItems.size() - 1)
						currentSelect++;
					break;
				case 75:
					return make_pair(currentSelect, Backward);
				case 77:
					return make_pair(currentSelect, Forward);
				}
			}
	}
}
