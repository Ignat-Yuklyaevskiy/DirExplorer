#include "Directory.h"

Directory::Directory(std::string path)
{
	if (!fs::exists(path))
		throw new exception("Ошибка директории");
	this->path = path;
	UpdatePaths();
}

void Directory::UpdatePaths()
{
	entries.clear();
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
	vector<string>* list = new vector<string>();

	for (char drive = 'A'; drive <= 'Z'; drive++)
	{
		char c[4]{ drive, ':', '\\', 0};
		fs::path p(c);
		if (fs::exists(p))
			list->push_back(p.string());
	}

	return *list;
}

bool Directory::Forward(int index)
{
	if (index >= 0 && index < entries.size())
	{
		if (entries[index].is_directory())
		{
			path = entries[index].path().string();
			UpdatePaths();
			return true;
		}

	}
	return false;
}

bool Directory::Backward()
{
	fs::path p = fs::path(this->path);
	if (p.has_parent_path())
	{
		this->path = p.parent_path().string();
		UpdatePaths();
		return true;
	}
	return false;
}

string Directory::GetCurrentPath()
{
	return this->path;
}

double Directory::GetDirectorySize()
{
	fs::recursive_directory_iterator it(path);
	fs::recursive_directory_iterator end;
	vector<fs::path> allFiles;

	std::copy_if(it, end, std::back_inserter(allFiles), [](const fs::path& path) {
		return !fs::is_directory(path);
	});

	return 0.0;
}
