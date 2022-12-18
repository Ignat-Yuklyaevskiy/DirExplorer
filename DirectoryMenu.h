#define _CRT_SECURE_NO_WARNINGS
#include "TextMenu.h"
#include "Directory.h"
#include <stdio.h>
#include <locale.h>
#include <time.h>



class DirectoryMenu :
	public TextMenu
{
private:
	Directory* dir;
	bool isLeap(int year);
	bool isValidDate(int d, int m, int y);
public:
	void PathHandle();
	DirectoryMenu(Directory* dir);
	void Start();
};

