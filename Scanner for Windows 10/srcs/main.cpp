#include "ScannerClass.hpp"

int main(int argc, char **argv)
{
	std::string path;
	switch (argc)
	{
	case 1:
		path = ".";
		break;
	case 2:
		path = argv[1];
		break;
	}

	if (path.empty() || !fs::is_directory(path))
	{
		std::cout << "Please enter the existing path" << std::endl;
		return 1;
	}
	
	try
	{
		Scanner scanner(path);
		scanner.init();
		scanner.printReport();
	}
	catch(fs::filesystem_error &fse)
	{
		std::cout << "Insufficient permissions to scan the contents of the directory" << std::endl;
		return 1;
	}
}