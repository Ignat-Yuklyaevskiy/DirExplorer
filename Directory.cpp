#include "Directory.h"
#include "File.h"

Directory::Directory(std::string path)
{
	this->path = path;
	if (path.size() != 0 && !fs::exists(path))
		throw exception("Ошибка директории");
	UpdatePaths();
}

void Directory::UpdatePaths()
{
	entries.clear();
	if (path == "")
		this->entries = GetDrives();
	else
		for (auto& item : fs::directory_iterator(this->path, fs::directory_options::skip_permission_denied))
			this->entries.push_back(item);
}

vector<string>& Directory::GetPathsString()
{
	vector<string>* list = new vector<string>();
	for (auto& item : this->entries)
		list->push_back(path.size() == 0 ? item.path().string() : item.path().filename().string());
	return *list;
}

int Directory::GetFileCount()
{
	int count = 0;
	for (const auto& item : fs::directory_iterator(path, fs::directory_options::skip_permission_denied))
		if (!item.is_directory())
			count++;
	return count;
}

int Directory::GetPathCount()
{
	int count = 0;
	for (const auto& item : fs::directory_iterator(path, fs::directory_options::skip_permission_denied))
		if (item.is_directory())
			count++;
	return count;
}

double Directory::GetFilesSize()
{
	double size = 0;
	for (const auto& item : fs::directory_iterator(path, fs::directory_options::skip_permission_denied))
		size += item.file_size();
	return size;
}

vector<fs::directory_entry>& Directory::GetDrives()
{
	vector<fs::directory_entry>* list = new vector<fs::directory_entry>();

	for (char drive = 'A'; drive <= 'Z'; drive++)
	{
		char c[4]{ drive, ':', '\\', 0 };
		fs::path p(c);
		if (fs::exists(p))
			list->push_back(fs::directory_entry(p));
	}

	return *list;
}

void Directory::Forward(int index)
{
	if (index >= 0 && index < entries.size())
	{
		if (entries[index].is_directory())
		{
			path = entries[index].path().string();
			UpdatePaths();
		}
	}
	// TODO: Исключение индекс вне диапазона
}

void Directory::Backward()
{
	fs::path p = fs::path(this->path);
	if (p.has_parent_path() && p.parent_path().string() != this->path)
		this->path = p.parent_path().string();
	else
		this->path = "";
	UpdatePaths();
}

string Directory::GetCurrentPath()
{
	return this->path;
}

unsigned long long Directory::GetDirectorySize()
{
	unsigned long long length = 0;
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
			if (!(*begin).is_directory())
				length += (*begin).file_size();
			else
				s.push((*begin));
		}
	}

	return length;
}

vector<fs::path>& Directory::FilterBySize(unsigned long long size = 0)
{
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
			if (!(*begin).is_directory())
			{
				if ((*begin).file_size() > size)
					files->push_back(*begin);
			}
			else
				s.push((*begin));
		}
	}

	return *files;
}
vector<fs::path>& Directory::SearchDuplicates()
{
	vector<fs::path>* duplicates = new vector<fs::path>();
	set<File> files;
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
			if (!(*begin).is_directory())
			{
				if (!files.insert(File((*begin).path())).second)
					duplicates->push_back((*begin).path());
			}
			else
				s.push((*begin));
		}
	}

	return *duplicates;
}

vector<fs::path>& Directory::FilterByDate(time_t date)
{
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
			if (!(*begin).is_directory())
			{
				// TODO
				std::time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now() - (filesystem::file_time_type::clock::now() - (*begin).last_write_time()));
				if (t >= date)
					files->push_back((*begin).path());
			}
			else
				s.push((*begin));
		}
	}

	return *files;
}

