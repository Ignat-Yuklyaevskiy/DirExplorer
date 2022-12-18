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
	if (y > 3000 ||	y < 1900)
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
	vector<string> menuItems{ "���-�� ������", "���-�� ����������", "������", "������(rec)",
						  "���������� �� �������",  "���������� �� ����", "����� ����������", "�����" };
	bool isRun = true;
	int volume = 0;
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
		try
		{
			switch (command.first)
			{
			case 0:
				cout << "���-�� ������: " << dir->GetFileCount() << endl;
				break;
			case 1:
				cout << "���-�� ����������: " << dir->GetPathCount() << endl;
				break;
			case 2:
				cout << "������: " << dir->GetFilesSize() << " ����." << endl;
				break;
			case 3:
				cout << "������ �� ���������� �������: " << dir->GetDirectorySize() << " ����." << endl;
				break;
			case 4:
				cout << "������� ������: ";
				cin >> volume;				
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
					volume = 0;
					throw exception("������������ ������ �����");
				}
				for (auto item : dir->FilterBySize(volume))
					cout << item.string() << "\t" << fs::file_size(item) << endl;

				break;
			case 5:
				cout << "������� ���� (dd.mm.yyyy): ";
				cin >> input;
				// TODO Exceptions
				// TODO: ������������ strftime
				if (sscanf(input.c_str(), "%d.%d.%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year) < 3)
					throw exception("������������ ������ �����");
				if (!isValidDate(tm.tm_mday,tm.tm_mon,tm.tm_year))
				{
					throw exception("������������ �������� ����");
				}
				tm.tm_mon--;
				tm.tm_year -= 1900;
				tm.tm_isdst = -1;
				t = mktime(&tm);
				for (auto item : dir->FilterByDate(t))
				{
					// TODO: ����� ���� ���������?
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
		case Exit: isRun = false;
			break;
		}
	}
}
