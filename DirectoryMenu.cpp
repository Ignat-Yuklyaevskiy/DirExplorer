#include "DirectoryMenu.h"

DirectoryMenu::DirectoryMenu(Directory* dir) : TextMenu(dir->GetPathsString(), dir->GetCurrentPath())
{
	this->dir = dir;
}

bool DirectoryMenu::isLeap(int year)
{
	return (((year % 4 == 0) &&
		(year % 100 != 0)) ||
		(year % 400 == 0));
}

bool DirectoryMenu::isValidDate(int d, int m, int y)
{
	if (y > 3000 || y < 1900)
		return false;
	if (m < 1 || m > 12)
		return false;
	if (d < 1 || d > 31)
		return false;
	if (m == 2)
	{
		if (isLeap(y))
			return (d <= 29);
		else
			return (d <= 28);
	}
	if (m == 4 || m == 6 ||
		m == 9 || m == 11)
		return (d <= 30);

	return true;
}

void DirectoryMenu::PathHandle()
{
	vector<string> menuItems{ "Кол-во файлов", "Кол-во директорий", "Размер", "Размер(rec)",
							  "Фильтрация по размеру",  "Фильтрация по дате", "Поиск дубликатов", "Выход" };
	bool isRun = true;
	int volume = 0;
	int dd, mm, yyyy;
	string input;
	stringstream ss;
	stringstream ssDate;
	string strDate;
	time_t t;
	string tmp;
	struct tm tm = { 0 };
	while (isRun)
	{
		pair<int, CommandState> command = TextMenu(menuItems, dir->GetCurrentPath()).Start();
		if (command.second == Exit)
		{
			break;
		}
		try
		{
			switch (command.first)
			{
			case 0:
				volume = dir->GetFileCount();
				cout << "Кол-во файлов: " << volume << endl;
				Logger::WriteLog(dir->GetCurrentPath(), "Количество файлов", to_string(volume));
				break;
			case 1:
				volume = dir->GetPathCount();
				cout << "Кол-во директорий: " << volume << endl;
				Logger::WriteLog(dir->GetCurrentPath(), "Количество диркторий", to_string(volume));
				break;
			case 2:
				volume = dir->GetFilesSize();
				cout << "Размер: " << volume << " байт." << endl;
				Logger::WriteLog(dir->GetCurrentPath(), "Размер файлов в директории", to_string(volume));
				break;
			case 3:
				volume = dir->GetDirectorySize();
				cout << "Размер со вложенными папками: " << dir->GetDirectorySize() << " байт." << endl;
				Logger::WriteLog(dir->GetCurrentPath(), "Размер всех файлов", to_string(volume));
				break;
			case 4:
				cout << "Введите размер: ";
				cin >> volume;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					volume = 0;
					throw exception("Неправильный формат ввода числа");
					Logger::WriteLog(dir->GetCurrentPath(), "Фильтрация по размеру", "Error: Неправильный формат ввода числа.");
				}
				input = "";
				for (auto item : dir->FilterBySize(volume))
				{
					input += "\n";
					cout << item.string() << "\t" << fs::file_size(item) << endl;
					ss << item.string() << "\t" << fs::file_size(item) << endl;
					getline(ss, tmp);
					input += tmp;
				}
				Logger::WriteLog(dir->GetCurrentPath(), "Фильтрация по размеру: " + to_string(volume) + ".", input);
				break;
			case 5:
				cout << "Введите дату (dd.mm.yyyy): ";
				cin >> input;
				// TODO: Использовать strftime
				if (sscanf(input.c_str(), "%d.%d.%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year) < 3)
				{
					throw exception("Неправильный формат даты");
					Logger::WriteLog(dir->GetCurrentPath(), "Фильтрация по дате", "Error: Неправильный формат даты.");
				}
				if (!isValidDate(tm.tm_mday, tm.tm_mon, tm.tm_year))
				{
					throw exception("Неправильное значение даты");
					Logger::WriteLog(dir->GetCurrentPath(), "Фильтрация по дате", "Error: Неправильное значение даты.");
				}
				tm.tm_mon--;
				tm.tm_year -= 1900;
				tm.tm_isdst = -1;
				t = mktime(&tm);
				input = "";
				for (auto item : dir->FilterByDate(t))
				{
					// TODO: Вывод даты изменений?
					input += "\n";
					cout << item.string() << endl;
					getline(ss, tmp);
					input += tmp;
				}
				ssDate << std::chrono::system_clock::from_time_t(t);
				getline(ssDate, strDate);
				Logger::WriteLog(dir->GetCurrentPath(), "Фильтрация по дате: " + strDate + ".", input);
				break;
			case 6:
				input = "";
				for (auto item : dir->SearchDuplicates())
				{
					input += "\n";
					cout << item.string() << "\t" << fs::file_size(item) << endl;
					ss << item.string() << "\t" << fs::file_size(item) << endl;
					getline(ss, tmp);
					input += tmp;
				}
				Logger::WriteLog(dir->GetCurrentPath(), "Поиск дубликатов", input);
				break;
			case 7:
				isRun = false;
				break;
			}
		}
		catch (std::exception& ex)
		{
			cout << ex.what() << endl;
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
		case Exit:
			isRun = false;
			break;
		}
	}
}
