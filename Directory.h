#include <string>
#include <filesystem>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <stack>

using namespace std;
namespace fs = std::filesystem;
class Directory
{
private:
	std::string path;
	vector<fs::directory_entry> entries;
	void UpdatePaths();
public:
	static vector<string>& GetDrives();
	Directory(std::string path);
	vector<string>& GetPathsString();
	int GetFileCount();
	int GetPathCount();
	double GetFilesSize();
	bool Forward(int index);
	bool Backward();
	string GetCurrentPath();
	unsigned long long GetDirectorySize();
	vector<fs::directory_iterator> GetBiggerFiles(unsigned long long size);
};

