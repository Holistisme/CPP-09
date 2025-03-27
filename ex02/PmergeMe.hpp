#pragma once

/* ############################################################################################## */

#include <algorithm>
#include <cerrno>
#include <deque>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

/* ############################################################################################## */

#include "ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

#define greater	 >
#define less	 <
#define equal_to ==

/* ############################################################################################## */

class PmergeMe {
	public:
		PmergeMe(char *argv[]);
		PmergeMe(const PmergeMe &source);
		PmergeMe &operator=(const PmergeMe &source);
		~PmergeMe(void);

		void process(void) const;
	private:
		std::vector<unsigned int> _vector;
		std::deque<unsigned	 int> _deque;

		std::vector<unsigned int> processVector(void) const;
		std::deque<unsigned int>  processDeque(void)  const;
};