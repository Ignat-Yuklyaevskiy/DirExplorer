#include "Directory.h"

Directory::Directory(std::string path)
{
	if (!fs::exists(path))
		throw new exception("Ошибка директории");
	this->path = path;
}

void Directory::UpdatePaths()
{
	for (auto& item : fs::directory_iterator(this->path))
		this->entries.push_back(item);
}

vector<string>& Directory::GetPathsString()
{
	vector<string>* list = new vector<string>();
	for (auto& item : this->entries)
		list->push_back(item.path().filename().string());
	return *list;
}

int Directory::GetFileCount()
{
	int count = 0;
	for (const auto& item : fs::directory_iterator(path))
		if (!item.is_directory())
			count++;
	return count;
}

int Directory::GetPathCount()
{
	int count = 0;
	for (const auto& item : fs::directory_iterator(path))
		if (item.is_directory())
			count++;
	return count;
}

double Directory::GetFilesSize()
{
	double size = 0;
	for (const auto& item : fs::directory_iterator(path))
		size += item.file_size();
	return size;
}

vector<string>& Directory::GetDrives()
{
	vector<string> list;

	for (char drive = 'A'; drive <= 'Z'; drive++)
	{
		char c[3]{ drive, ':', 0 };
		fs::path p(c);
		if (fs::exists(p))
			list.push_back(p.string());
	}

	return list;
}

bool Directory::Forward(int index)
{

	return false;
}

bool Directory::Backward(int index)
{
	return false;
}

string Directory::GetCurrentPath()
{
	return this->path;
}
