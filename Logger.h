#include <string>
#include <fstream>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std;

class Logger
{
public:
	static void WriteLog(std::string path, std::string operation, std::string result);
};

