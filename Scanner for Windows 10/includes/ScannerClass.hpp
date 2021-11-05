#ifndef SCANNER_CLASS_HPP
#define SCANNER_CLASS_HPP

#include "SearchThreadClass.hpp"
#include <sstream>

class SearchThread;

class Scanner
{

using clock_t = std::chrono::steady_clock;

private:

	std::string _path;

	std::atomic<int> *_errors;
	std::atomic<int> *_processedFiles;
	struct ExecTime
	{
		std::chrono::time_point<clock_t> startTime;
		std::chrono::hours elapsed_hh;
		std::chrono::minutes elapsed_mm;
		std::chrono::seconds elapsed_ss;
		std::stringstream timeFormat;
	} _execTime;

	SearchThread target[3];

public:

	Scanner(std::string path);
	~Scanner() {delete _errors; delete _processedFiles;}
	int getProcessedfiles() {return *_processedFiles;}
	int getErrors() {return *_errors;}
	void parseDir();
	void init();
	void stopWatch();
	void printReport();
};

#endif