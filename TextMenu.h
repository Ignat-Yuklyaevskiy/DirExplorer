#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <conio.h>
using namespace std;
namespace fs = std::filesystem;

enum CommandState { Select, Forward, Backward, Exit };

class TextMenu
{
private:
	vector<string> menuItems;
	string title;
public:
	TextMenu(vector<string> menuItems, string title);
	void PrintMenu(int currentSelect);
	pair<int, CommandState> Start();
};

