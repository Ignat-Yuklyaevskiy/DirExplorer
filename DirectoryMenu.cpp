#include "DirectoryMenu.h"

DirectoryMenu::DirectoryMenu(Directory* dir) : TextMenu(dir->GetPathsString(), dir->GetCurrentPath())
{
	this->dir = dir;
}

void DirectoryMenu::PathHandle()
{
	vector<string> menuItems{ "Кол-во файлов", "Кол-во директорий", "Размер", "Размер(rec)",
						  "Фильтрация по размеру",  "Фильтрация по дате", "Поиск дубликатов", "Выход" };
	bool isRun = true;
	int volume;
	int dd, mm, yyyy;
	string input;
	time_t t;
	struct tm tm = { 0 };
	while (isRun)
	{
		pair<int, CommandState> command = TextMenu(menuItems, dir->GetCurrentPath()).Start();
		if (command.second == Exit)
		{
			break;
		}
		switch (command.first)
		{
		case 0:
			cout << "Кол-во файлов: " << dir->GetFileCount() << endl;
			break;
		case 1:
			cout << "Кол-во директорий: " << dir->GetPathCount() << endl;
			break;
		case 2:
			cout << "Размер: " << dir->GetFilesSize() << " байт." << endl;
			break;
		case 3:
			cout << "Размер со вложенными папками: " << dir->GetDirectorySize() << " байт." << endl;
			break;
		case 4:
			cout << "Введите размер: ";
			cin >> volume;
			for (auto item : dir->FilterBySize(volume))
				cout << item.string() << "\t" << fs::file_size(item) << endl;
			break;
		case 5:
			cout << "Введите дату (dd.mm.yyyy): ";
			cin >> input;
			// TODO Exceptions
			// TODO: Использовать strftime
			sscanf(input.c_str(), "%d.%d.%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
			tm.tm_mon--;
			tm.tm_year -= 1900;
			tm.tm_isdst = -1;
			t = mktime(&tm);
			for (auto item : dir->FilterByDate(t))
			{
				// TODO: Вывод даты изменений?
				cout << item.string() << endl;
			}
			break;
		case 6:
			for (auto item : dir->SearchDuplicates())
				cout << item.string() << "\t" << fs::file_size(item) << endl;
			break;
		case 7:
			isRun = false;
			break;
		}
		system("PAUSE");
	}
}

void DirectoryMenu::Start()
{
	bool isRun = true;
	while (isRun)
	{
		pair<int, CommandState> command = TextMenu(this->dir->GetPathsString(), this->dir->GetCurrentPath()).Start();
		switch (command.second)
		{
		case Select:
			dir->Forward(command.first);
			PathHandle();
			break;
		case Forward:
			dir->Forward(command.first);
			break;
		case Backward:
			dir->Backward();
			break;
		case Exit: isRun = false;
			break;
		}
	}
}
