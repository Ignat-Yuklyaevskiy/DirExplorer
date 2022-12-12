#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
class Directory
{
private:
	std::string path;
	vector<fs::directory_entry> entries;
	void UpdatePaths();
public:
	Directory(std::string path);
	vector<string>& GetPathsString();
	int GetFileCount();
	int GetPathCount();
	double GetFilesSize();
	static vector<string>& GetDrives();
	bool Forward(int index);
	bool Backward(int index);
	string GetCurrentPath();
};

