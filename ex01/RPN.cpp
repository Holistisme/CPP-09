#include "RPN.hpp"

/* ############################################################################################## */

RPN::RPN(const std::string &expression)	: _expression(expression)		  {								}
RPN::RPN(const RPN &source)				: _expression(source._expression) {								}
RPN &RPN::operator=(const RPN &source)									  { (void)source; return *this; }
RPN::~RPN(void)															  {								}

/* ############################################################################################## */

int RPN::process(void) const {
	std::istringstream iss(_expression);
	std::stack<int> operands;

	std::string token;
	while (iss >> token) {
		if (token equal_to "+" or token equal_to "-"
		 or token equal_to "*" or token equal_to "/") {
			if (operands.size() < 2)	throw std::logic_error("Impossible to operate on a stack of less than two elements");

			int operandsB = operands.top(); operands.pop();
			int operandsA = operands.top(); operands.pop();

			int operandsResult;
			if		(token equal_to "+")	operandsResult = operandsA + operandsB;
			else if (token equal_to "-")	operandsResult = operandsA - operandsB;
			else if (token equal_to "*")	operandsResult = operandsA * operandsB;
			else if (token equal_to "/")
						   { operandsB ?	operandsResult = operandsA / operandsB
				 					   :	throw std::logic_error("Division by 0 prohibited"); }

			operands.push(operandsResult);
		} else	std::isdigit(token[0]) ? operands.push(token[0] - '0')
									   : throw std::logic_error("Unknown token detected");
	}
	if		(operands.size() greater 1)	throw std::logic_error("Not all figures have been used, some operations are missing");
	else if (operands.size() not_eq 1)	throw std::logic_error("The RPN::process() function doesn't process any tokens");

	return operands.top();
}