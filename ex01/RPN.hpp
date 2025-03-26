#pragma once

/* ############################################################################################## */

#include <stack>
#include <sstream>

/* ############################################################################################## */

#define greater	 >
#define equal_to ==

/* ############################################################################################## */

class RPN {
	public:
		RPN(const std::string &expression);
		RPN(const RPN &source);
		RPN &operator=(const RPN &source);
		~RPN(void);

		int process(void) const;
	private:
		const std::string _expression;
};