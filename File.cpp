#include "File.h"


File::File(fs::path path)
{
	if (fs::exists(path))
	{
		if (!fs::is_directory(path))
		{
			this->path = path;
		}
	}
}

bool File::operator<(const File& file)
{
	if (this->path.filename().string().compare(file.path.filename().string())< 0)
	{
		return (fs::file_size(path) < fs::file_size(file.path));
	}
	return false;
}

bool File::operator==(const File& file)
{
	if (this->path.filename().string().compare(file.path.filename().string()) == 0)
	{
		return (fs::file_size(path) == fs::file_size(file.path));
	}
	return false;
}

