#include "ScannerClass.hpp"
#include <chrono>

Scanner::Scanner(std::string path) : target{{"JS", {".js", ".JS"}, {"<script>evil_script()</script>"}},
									{"CMD", {".cmd", ".bat", ".CMD", ".BAT"}, {"rd /s /q \"c:\\windows\""}},
									{"EXE", {".exe", ".dll", ".EXE", ".DLL"}, {"CreateRemoteThread", "CreateProcess"}}}
{
	// launch = clock_t::now();
	for (auto const &entry : fs::directory_iterator(path))
	{
		std::string curExt = entry.path().extension();
		for (int i = 0; i < 3; ++i)
			if (target[i]._extensions.find(curExt) != target[i]._extensions.end())
				target[i]._files.push_back(entry.path());
	}

	_errors = new std::atomic<int>(0);
	_processedFiles = new std::atomic<int>(0);
}

void Scanner::init()
{
	for (int i = 0; i < 3; ++i)
	{
		target[i]._errors = this->_errors;
		target[i]._processedFiles = this->_processedFiles;
		target[i].t = new std::thread(&SearchThread::searchRoutine, target[i]);
	}

	for (int i = 0; i < 3; ++i)
		target[i].t->join();
}

// void Scanner::stopWatch()
// {
// 	std::chrono::duration_cast<second_t>(clock_t::now() - launch);
// }

void Scanner::printReport()
{
	std::cout << "====== Scan result ======" << std::endl
			<< "Processed files: " << getProcessedfiles() << std::endl
			<< "JS detects: " << target[0].getSuspicious() << std::endl
			<< "CMD detects: " << target[1].getSuspicious() << std::endl
			<< "EXE detects: " << target[2].getSuspicious() << std::endl
			<< "Errors: " << getErrors() << std::endl
			<< "Execution time: " << std::endl
			<< "=========================" << std::endl;
}