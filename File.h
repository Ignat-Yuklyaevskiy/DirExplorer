#include <filesystem>
#include <set>
using namespace std;
namespace fs = std::filesystem;
class File
{
private:
	fs::path path;
	
public:
	File(fs::path path);
	bool operator< (const File& file);
	bool operator== (const File& name);
};

