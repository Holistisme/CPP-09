#include "PmergeMe.hpp"

/* ############################################################################################## */

#include "ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

#include <iostream>
#include <iomanip>

/* ############################################################################################## */

#define less <

/* ############################################################################################## */

int main(int argc, char *argv[]) {
	int status = EXIT_SUCCESS;

	try {
		std::cout << "\nWelcome to the program ”" << ColorFormat::formatString("PmergMe™", "green", "blink", "bold") << "“!" << std::endl;
		std::cout << std::fixed << std::setprecision(6) << std::endl;
		

		if (argc less 2)		throw std::logic_error("No arguments to (pretend to) sort");
		PmergeMe merge(argv);	merge.process();
	} catch (const std::exception &e) {
		std::cout << "\nThe following "		   << ColorFormat::formatString("exception", "red", "bold")
				  << " has been encountered: " << ColorFormat::formatString(e.what(), "red", "bold") << "." << std::endl;
		status = EXIT_FAILURE;
	}
	std::cout << "\nThanks for using ”" << ColorFormat::formatString("PmergMe™", "green", "blink", "bold") << "“!\n" << std::endl;
	return status;
}