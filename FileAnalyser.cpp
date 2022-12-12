#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "Directory.h"

void PrintMenu(vector<string> menu, int currentSelect)
{
	for (size_t i = 0; i < menu.size(); i++)
		cout << (i == currentSelect ? "-" : "") << menu[i] << (i == currentSelect ? "-" : "") << endl;
}

enum CommandState { Select, Forward, Backward };

pair<int, CommandState> Menu(vector<string> menuItems)
{
	int currentSelect = 0;
	bool isRun = true;
	while (isRun)
	{
		system("cls");
		PrintMenu(menuItems, currentSelect);

		char x;
		x = _getch();
		if (x == '\r')
		{
			isRun = false;
			return make_pair(currentSelect, Select);
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
			case 27:
				//ESC 
				break;
			case 75:
				return make_pair(currentSelect, Backward);
			case 77:
				return make_pair(currentSelect, Forward);
			}
		}
	}
}



void PathHandle(string path)
{
	vector<string> menuItems{ "Кол-во файлов", "Кол-во директорий", "Размер", "Размер(rec)",
							  "Фильтрация по размеру",  "Фильтрация по дате", "Поиск дубликатов", "Выход" };
	bool isRun = true;

	Directory dir(path);
	while (isRun)
	{
		pair<int, CommandState> command = Menu(menuItems);
		cout << path << endl;
		switch (command.first)
		{
		case 0:
			cout << "Кол-во файлов: " << dir.GetFileCount() << endl;
			break;
		case 1:
			break;
		case 2:
			cout << "Размер: " << dir.GetFilesSize() << " байт." << endl;
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			isRun = false;
			break;
		}
		system("PAUSE");
	}
}

void DirectoryMenu()
{
	bool isRun = true;
	Directory dir("C:/");
	while (isRun)
	{
		pair<int, CommandState> command = Menu(dir.GetPathsString());
		switch (command.second)
		{
		case Select:
			PathHandle(dir.GetCurrentPath());
			break;
		case Forward:
			break;
		case Backward:
			break;
		}
	}
}

int main()
{
	setlocale(0, "RU");
	bool isRun = true;
	vector<string> menuItems{ "Ввод директории", "Выбор директории" };
	string input;
	while (isRun)
	{
		pair<int, CommandState> command = Menu(menuItems);
		switch (command.first)
		{
		case 0:
			cout << ">";
			getline(std::cin, input);
			PathHandle(input);
			system("PAUSE");
			break;
		case 1:
			DirectoryMenu();
			break;
		}
	}

	return 0;
}
