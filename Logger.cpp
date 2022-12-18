#include "Logger.h"

void Logger::WriteLog(std::string path, std::string operation, std::string result)
{
	ofstream out("log.txt", std::ios_base::app);

	auto time = std::chrono::system_clock::now();
	out << time << "," << path << "," << operation << "," << result << endl;

	out.close();
}
