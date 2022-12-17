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
	vector<fs::directory_entry>& GetDrives();
public:
	Directory(std::string path);
	vector<string>& GetPathsString();
	int GetFileCount();
	int GetPathCount();
	double GetFilesSize();
	void Forward(int index);
	void Backward();
	string GetCurrentPath();
	unsigned long long GetDirectorySize();
	vector<fs::path>& GetBiggerFiles(unsigned long long size);
	vector<vector<fs::path>> SearchDuplicate(string name, unsigned long long size);
};

