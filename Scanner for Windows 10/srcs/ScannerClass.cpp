#include "ScannerClass.hpp"
#include <chrono>

Scanner::Scanner(std::string path) : target{{"JS", {".js", ".JS"}, {"<script>evil_script()</script>"}},
									{"CMD", {".cmd", ".bat", ".CMD", ".BAT"}, {"rd /s /q \"c:\\windows\""}},
									{"EXE", {".exe", ".dll", ".EXE", ".DLL"}, {"CreateRemoteThread", "CreateProcess"}}}
{
	_path = path;
	_execTime.startTime = clock_t::now();
	parseDir();
	_errors = new std::atomic<int>(0);
	_processedFiles = new std::atomic<int>(0);
}

void Scanner::parseDir()
{
	for (auto const &entry : fs::directory_iterator(_path))
	{
		std::string curExt = entry.path().extension().generic_string();
		for (int i = 0; i < 3; ++i)
			if (target[i]._extensions.find(curExt) != target[i]._extensions.end())
				target[i]._files.push_back(entry.path());
	}
}

void Scanner::init()
{
	for (int i = 0; i < 3; ++i)
	{
		target[i]._errors = this->_errors;
		target[i]._processedFiles = this->_processedFiles;
		target[i].t = new std::thread(&SearchThread::searchRoutine, std::ref(target[i]));
	}

	for (int i = 0; i < 3; ++i)
		target[i].t->join();
}

void Scanner::printReport()
{
	stopWatch();
	std::cout << "====== Scan result ======" << std::endl
			<< "Processed files: " << getProcessedfiles() << std::endl
			<< "JS detects: " << target[0].getSuspicious() << std::endl
			<< "CMD detects: " << target[1].getSuspicious() << std::endl
			<< "EXE detects: " << target[2].getSuspicious() << std::endl
			<< "Errors: " << getErrors() << std::endl
			<< "Execution time: " << _execTime.timeFormat.str() << std::endl
			<< "=========================" << std::endl;
}

void Scanner::stopWatch()
{
	auto elapsed = clock_t::now() - _execTime.startTime;
	_execTime.elapsed_hh = std::chrono::duration_cast<std::chrono::hours>(elapsed);
	_execTime.elapsed_mm = std::chrono::duration_cast<std::chrono::minutes>(elapsed - _execTime.elapsed_hh);
	_execTime.elapsed_ss = std::chrono::duration_cast<std::chrono::seconds>(elapsed - _execTime.elapsed_hh - _execTime.elapsed_mm);

	_execTime.timeFormat << std::setw(2) << std::setfill('0') << _execTime.elapsed_hh.count() << ":"
						<< std::setw(2) << std::setfill('0') << _execTime.elapsed_mm.count() << ":"
						<< std::setw(2) << std::setfill('0') << _execTime.elapsed_ss.count();
}