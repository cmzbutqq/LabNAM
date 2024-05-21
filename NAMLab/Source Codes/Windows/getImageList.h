/*************************************************
author: Bowen Yang
date:2019/05/08
describe: Get a list of picture names in a folder.
**************************************************/
#pragma once
#include <iostream>
#include <vector>
#include <io.h>

void getImageList(std::string path, std::vector<std::string>& files)
{
	long long   hFile = 0;
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getImageList(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}