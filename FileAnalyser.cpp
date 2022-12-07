#include <iostream>
#include <filesystem>
#include <string>


namespace fs = std::filesystem;

int main()
{
    std::string path = "C:/";
	for (const auto& item : fs::directory_iterator(path))
	{
		std::cout << item.path() << std::endl;
	}
    return 0;
}
