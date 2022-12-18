#include "File.h"


File::File(fs::path path)
{
	if (fs::exists(path))
	{
		if (!fs::is_directory(path))
		{
			this->path = path;
			this->size = fs::file_size(path);
		}
	}
}

bool operator<(const File& file1, const File& file2)
{
	string s1 = file1.path.filename().string();
	string s2 = file2.path.filename().string();
	unsigned long long size1 = file1.size;
	unsigned long long size2 = file2.size;
	if (size1 == size2)
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	else
		return size1 < size2;
}