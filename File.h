#include <filesystem>
#include <set>
using namespace std;
namespace fs = std::filesystem;
class File
{
private:
	fs::path path;
	unsigned long long size;
public:
	File(fs::path path);
	friend bool operator< (const File& file1, const File& file2);
};

