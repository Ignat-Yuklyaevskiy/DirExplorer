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
		char c[4]{ drive, ':', '\\', 0 };
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

unsigned long long Directory::GetDirectorySize()
{
	stack<fs::path> s;
	/*std::copy_if(it, end, std::back_inserter(allFiles), [](const fs::path& path) {
		return !fs::is_directory(path);
	});*/
	/*unsigned long long s = 0;
	unsigned long long size = std::accumulate(it, end, s, [](unsigned long long size, const fs::path& path) {
		return size + (!fs::is_directory(path) ? fs::file_size(path) : 0);
		});
	*/
	unsigned long long length = 0;
	s.push(fs::path(this->path));
	while (!s.empty())
	{
		fs::path p = s.top();
		s.pop();
		fs::directory_iterator end;
		fs::directory_iterator begin(p, fs::directory_options::skip_permission_denied);
		for (; begin != end; ++begin)
		{
			if (!fs::is_directory((*begin)))
				length += (*begin).file_size();
			else
				s.push((*begin));
		}

	}

	return length;
}
