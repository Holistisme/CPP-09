#include "RPN.hpp"

/* ############################################################################################## */

#include "ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

#include <iostream>

/* ############################################################################################## */

#define less <

/* ############################################################################################## */

static std::string argvToString(const int argc, char *argv[]);

/* ############################################################################################## */

int main(int argc, char *argv[]) {
	int status = EXIT_SUCCESS;

	try {
		std::cout << "\nWelcome to the program ”" << ColorFormat::formatString("RPN™", "blue", "blink", "bold") << "“!" << std::endl;

		const std::string operation = argvToString(argc, argv);
		if (not operation.empty())	{
			RPN rpn(operation);	const int result = rpn.process();

			std::cout << "\nI've " << ColorFormat::formatString("managed", "green")
					  << " to do the damn math: " << result << std::endl;
		}
		else {
			std::cout << ColorFormat::formatString("\nBro, I'm dealing with numbers, not your ", "italic")
					  << ColorFormat::formatString("IQ", "italic", "red")
					  << ColorFormat::formatString("...", "italic") << std::endl;
			status = EXIT_FAILURE;
		}
	} catch (const std::exception &e) {
		std::cout << "\nThe following "		   << ColorFormat::formatString("exception", "red", "bold")
				  << " has been encountered: " << ColorFormat::formatString(e.what(), "red", "bold") << "." << std::endl;
		status = EXIT_FAILURE;
	}
	std::cout << "\nThanks for using ”" << ColorFormat::formatString("RPN™", "blue", "blink", "bold") << "“!\n" << std::endl;
	return status;
}

static std::string argvToString(const int argc, char *argv[]) {
	std::cout << ColorFormat::formatString("\nLoading and checking program ", "italic")
			  << ColorFormat::formatString("arguments", "italic", "yellow")
			  << ColorFormat::formatString("...", "italic") << std::endl;

	if (argc less 2)
		std::cout << ColorFormat::formatString("Analyzing the ", "italic")
				  << ColorFormat::formatString("void", "italic", "magenta")
				  << ColorFormat::formatString(" is not my job, I'm not unemployed.", "italic") << std::endl;
	else if (argc greater 2) {
		std::ostringstream stream;
		for (int index = 1; index < argc; index++) {
			stream << "\"" << ColorFormat::formatString(argv[index], "italic", "red");
			if (index + 1 less argc)		stream << "\", ";
			if (index equal_to argc / 2)	stream << "\"" << ColorFormat::formatString("user Is + Stupid *", "italic", "red") << "\", ";
		}
		std::cout << "You think the program is a flea market? I won't deal with all that expressions: " << stream.str() << "\"." << std::endl;
	}
	else {
		std::cout << ColorFormat::formatString("The expression \"", "italic")
				  << ColorFormat::formatString(argv[1], "italic", "green")
				  << ColorFormat::formatString("\" is properly proposed, I don't have to insult the proofreader...", "italic") << std::endl;
		return argv[1];
	}

	std::cout << "\nThanks for using ”" << ColorFormat::formatString("RPN™", "blue", "blink", "bold") << "“!\n" << std::endl;
	exit(EXIT_FAILURE);
}