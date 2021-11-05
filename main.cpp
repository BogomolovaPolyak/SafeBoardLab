#include "ScannerClass.hpp"

int main(int argc, char **argv)
{
	std::string path;
	if (argc > 2)
		return 0;
	Scanner scanner(argv[1]);
	scanner.init();
	scanner.printReport();
}