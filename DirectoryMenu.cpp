#include "DirectoryMenu.h"

DirectoryMenu::DirectoryMenu(Directory* dir) : TextMenu(dir->GetPathsString(), dir->GetCurrentPath())
{
	this->dir = dir;
}

void DirectoryMenu::PathHandle(string path)
{
	vector<string> menuItems{ "���-�� ������", "���-�� ����������", "������", "������(rec)",
						  "���������� �� �������",  "���������� �� ����", "����� ����������", "�����" };
	bool isRun = true;
	double volume;

	while (isRun)
	{
		pair<int, CommandState> command = TextMenu(menuItems, path).Start();
		if (command.second == Exit)
		{
			break;
		}
		cout << path << endl;
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
			for (auto item : dir->GetBiggerFiles(volume))
				cout << item.string() << "\t" << fs::file_size(item) << endl;
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
			PathHandle(dir->GetCurrentPath());
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
