#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "Directory.h"
#include "File.h"

/**
 *  TODO
 *  1. Наследование
 *  2. Исключения
 *  3. Класс Command ?
 *  4. Класс Menu (Обычное меню, Меню директорий)
 *  5. Работа с датой
 */

void PrintMenu(vector<string> menu, int currentSelect)
{
	int count = currentSelect / 25;
	for (size_t i = 25 * count; i < (25 * count) + 25 && i < menu.size(); i++)
	{
		cout << (i == currentSelect ? "-" : "") << menu[i] << (i == currentSelect ? "-" : "") << endl;
	}
}

enum CommandState { Select, Forward, Backward, Exit };

pair<int, CommandState> Menu(vector<string> menuItems, string title)
{
	int currentSelect = 0;
	bool isRun = true;
	while (isRun)
	{
		system("cls");
		cout << title << endl;
		PrintMenu(menuItems, currentSelect);

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



void PathHandle(string path)
{
	vector<string> menuItems{ "Кол-во файлов", "Кол-во директорий", "Размер", "Размер(rec)",
							  "Фильтрация по размеру",  "Фильтрация по дате", "Поиск дубликатов", "Выход" };
	bool isRun = true;
	double volume;
	
	Directory dir(path);
	while (isRun)
	{
		pair<int, CommandState> command = Menu(menuItems, path);
		if (command.second == Exit)
		{
			break;
		}
		cout << path << endl;
		switch (command.first)
		{
		case 0:
			cout << "Кол-во файлов: " << dir.GetFileCount() << endl;
			break;
		case 1: cout << "Кол-во директорий: " << dir.GetPathCount() << endl;
			break;
		case 2:
			cout << "Размер: " << dir.GetFilesSize() << " байт." << endl;
			break;
		case 3:
			cout << "Размер со вложенными папками - " << dir.GetDirectorySize() << endl;
			break;
		case 4: cout << "Введите размер" << endl;
			cin >> volume;
			dir.GetBiggerFiles(volume);
			// TODO: Вывод файлов на экран 
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
	Directory dir("");
	while (isRun)
	{
		pair<int, CommandState> command = Menu(dir.GetPathsString(), dir.GetCurrentPath());
		switch (command.second)
		{
		case Select:
			dir.Forward(command.first);
			PathHandle(dir.GetCurrentPath());
			break;
		case Forward:
			dir.Forward(command.first);
			break;
		case Backward:dir.Backward();
			break;
		case Exit: isRun = false;
			break;
		}
	}
}
vector<fs::path> SearchDuplicate(string name, unsigned long long size)
{
	vector<vector<fs::path>> duplicates;
	set<File> setfile;
	vector<fs::path>* files = new vector<fs::path>();
	stack<fs::path> s;
	s.push(fs::path(this->path));
	while (!s.empty())
	{
		fs::path p = s.top();
		s.pop();
		fs::directory_iterator end;
		fs::directory_iterator begin(p, fs::directory_options::skip_permission_denied);
		for (; begin != end; ++begin)
		{
			if (!(*begin).is_directory() && (*begin).file_size() > size)
				files->push_back(*begin);
			else
				s.push((*begin));
		}
	}
	
		return ;
}

int main()
{
	setlocale(0, "RU");
	bool isRun = true;
	vector<string> menuItems{ "Ввод директории", "Выбор директории", "Справка" };
	string input;
	while (isRun)
	{
		pair<int, CommandState> command = Menu(menuItems, "Главное меню");
		if (command.second == Exit)
			break;
		switch (command.first)
		{
		case 0:
			cout << ">";
			getline(std::cin, input);
			PathHandle(input);
			break;
		case 1:
			DirectoryMenu();
			break;
		case 2:
			cout << "Right    - переход в директорию" << endl;
			cout << "Left     - выход из директории" << endl;
			cout << "Up, Down - перемещение по меню" << endl;
			cout << "Enter    - выбор директории для анализа" << endl;
			cout << "Esc      - возврат в предыдущее меню" << endl;
			break;
		}
		system("PAUSE");
	}

	return 0;
}
