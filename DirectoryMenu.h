#pragma once
#include "TextMenu.h"
#include "Directory.h"
class DirectoryMenu :
	public TextMenu
{
private:
	Directory* dir;
	void PathHandle(string path);
public:
	DirectoryMenu(Directory* dir);
	void Start();
};

