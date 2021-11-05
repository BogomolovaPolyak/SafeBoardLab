#ifndef SEARCH_THREAD_CLASS_HPP
#define SEARCH_THREAD_CLASS_HPP

#include "ScannerClass.hpp"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <filesystem>
#include <atomic>
#include "mingw.thread.h"

namespace fs = std::filesystem;

class Scanner;

class SearchThread
{

private:
	std::string _type;
	std::set<std::string> _extensions;
	std::vector<std::string> _toFind;
	int _suspicious = 0;
	std::thread *t;
	std::vector<fs::path> _files;
	std::atomic<int> *_errors;
	std::atomic<int> *_processedFiles;

	void searchRoutine()
	{
		for (auto current : _files)
			scanFile(current);
	}

	void scanFile(fs::path toCheck)
	{
		int uglyTmp = _suspicious;
		std::string line;
		std::ifstream file;
		if (_type == "EXE")
			file.open(toCheck, std::ios::binary);
		else
			file.open(toCheck);

		if (!file.is_open())
			(*_errors)++;
		else
		{
			(*_processedFiles)++;
			while (getline(file, line) && _suspicious == uglyTmp)
				for (auto &elem : _toFind)
					if (line.find(elem) != std::string::npos)
						++_suspicious;
		}
	}

public:

	SearchThread(std::string type, std::set<std::string> extensions, std::vector<std::string> toFind) :
				_type(type), _extensions(extensions), _toFind(toFind) {};
	int getSuspicious() {return _suspicious;}

	friend Scanner;
	// friend Scanner::Scanner(std::string path);
	// friend void Scanner::init();
};

#endif