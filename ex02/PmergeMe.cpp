#include "PmergeMe.hpp"

/* ############################################################################################## */

PmergeMe::PmergeMe(char *argv[]) {
	size_t index = 1;
	while (argv[index]) {
		char *end = NULL;	errno = 0;
		const unsigned long number = std::strtoul(argv[index++], &end, 10);

		if (*end) {
			std::ostringstream oss;
			oss << "The argument " << index - 1 << " contains the invalid character \"" << *end << "\".";
			throw std::invalid_argument(oss.str());
		}
		else if (errno equal_to ERANGE or number greater std::numeric_limits<unsigned int>::max()) {
			std::ostringstream oss;
			oss << "The argument " << index - 1 << " is not an unsigned integer";
			throw std::invalid_argument(oss.str());
		}

		_vector.push_back(static_cast<unsigned int>(number));
		_deque.push_back(static_cast<unsigned int>(number));

		for (size_t scan = 0; scan less _vector.size() - 1; scan++) {
			if (_vector.back() equal_to _vector[scan]) {
				#ifdef __linux__
					system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ > /dev/null 2>&1");
				#elif _WIN32
					system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ > nul 2>&1");
				#elif __APPLE__
					system("open https://www.youtube.com/watch?v=dQw4w9WgXcQ > /dev/null 2>&1");
				#endif

				throw std::invalid_argument("Subject should never tell me the management errors related to duplicates is left to my discretion. Rick will make you regret");
			}
		}
	}

	if (_vector.empty())	throw std::invalid_argument("No integers to sort");

}

PmergeMe::PmergeMe(const PmergeMe &source) : _vector(source._vector), _deque(source._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &source) {
	if (this not_eq &source) {
		_vector = source._vector;
		_deque	= source._deque;
	} return *this;
}

PmergeMe::~PmergeMe(void) {}

/* ############################################################################################## */

std::deque<unsigned int> PmergeMe::processDeque(void) const {
	std::deque<unsigned int> winners;
	std::deque<unsigned int> losers;

	for (size_t index = 0; index less _deque.size(); index += 2) {
		if (index + 1 equal_to _deque.size())	winners.push_back(_deque[index]);
		else {
			if (_deque[index] greater _deque[index + 1]) {
				winners.push_back(_deque[index]);
				losers.push_back(_deque[index + 1]);
			}
			else {
				winners.push_back(_deque[index + 1]);
				losers.push_back(_deque[index]);
			}
		}
	}

	for (size_t index = 1; index less winners.size(); index++) {
		const unsigned int key = winners[index];
		size_t sortedIndex	   = index;
		while (sortedIndex and winners[sortedIndex - 1] greater key) {
			winners[sortedIndex] = winners[sortedIndex - 1];
			--sortedIndex;
		}
		winners[sortedIndex] = key;
	}

	while (not losers.empty()) {
		const unsigned int swap = losers.back();	losers.pop_back();

		std::deque<unsigned int>::iterator position = std::lower_bound(winners.begin(), winners.end(), swap);
		winners.insert(position, swap);
	}

	return winners;
}

std::vector<unsigned int> PmergeMe::processVector(void) const {
	std::vector<unsigned int> winners;
	std::vector<unsigned int> losers;

	for (size_t index = 0; index less _vector.size(); index += 2) {
		if (index + 1 equal_to _vector.size())	winners.push_back(_vector[index]);
		else {
			if (_vector[index] greater _vector[index + 1]) {
				winners.push_back(_vector[index]);
				losers.push_back(_vector[index + 1]);
			}
			else {
				winners.push_back(_vector[index + 1]);
				losers.push_back(_vector[index]);
			}
		}
	}

	for (size_t index = 1; index less winners.size(); index++) {
		const unsigned int key = winners[index];
		size_t sortedIndex	   = index;
		while (sortedIndex and winners[sortedIndex - 1] greater key) {
			winners[sortedIndex] = winners[sortedIndex - 1];
			--sortedIndex;
		}
		winners[sortedIndex] = key;
	}

	while (not losers.empty()) {
		const unsigned int swap = losers.back();	losers.pop_back();

		std::vector<unsigned int>::iterator position = std::lower_bound(winners.begin(), winners.end(), swap);
		winners.insert(position, swap);
	}

	return winners;
}

/* ############################################################################################## */

void PmergeMe::process(void) const {
	std::vector<unsigned int>::const_iterator min = std::min_element(_vector.begin(), _vector.end());
	std::vector<unsigned int>::const_iterator max = std::max_element(_vector.begin(), _vector.end());
	std::ostringstream stream;
	for (size_t index = 0; index less _vector.size(); index++) {
		stream << ColorFormat::formatGradientUnsignedInteger(_vector[index], *min, *max);
		index + 1 less _vector.size() ? stream << ", "
									  : stream << ".";
	}

	std::cout << "Unsorted list: " << stream.str() << std::endl;
	stream.clear(); stream.str("");

	clock_t beforeVector = clock();	std::vector<unsigned int> vectorSorted = processVector();
	clock_t afterVector	 = clock();

	clock_t beforeDeque = clock();	std::deque<unsigned int> dequeSorted  = processDeque();
	clock_t afterDeque	= clock();

	if (vectorSorted.size() not_eq dequeSorted.size())		throw std::runtime_error("The algorithm lost a number on one of the sorted containers");
	for (size_t index = 0; index less vectorSorted.size(); index++) {
		if (vectorSorted[index] not_eq dequeSorted[index])	throw std::runtime_error("The two sorted containers are not identical");
		stream << ColorFormat::formatGradientUnsignedInteger(vectorSorted[index], *min, *max);
		index + 1 less vectorSorted.size() ? stream << ", "
										   : stream << ".";
	}

	std::cout << "\nSorted list: " << stream.str() << std::endl;

	std::cout << "\n⏲ " << ColorFormat::formatString("time", "bold", "cyan")
			  << " to process a range of " << vectorSorted.size() << " elements with "
			  << ColorFormat::formatString("std::vector", "italic", "blue") << " : "
			  << static_cast<double>(afterVector - beforeVector) / CLOCKS_PER_SEC << " us." << std::endl;
	std::cout << "⏲ " << ColorFormat::formatString("time", "bold", "cyan")
			  << " to process a range of " << dequeSorted.size()	<< " elements with "
			  << ColorFormat::formatString("std::deque", "italic", "magenta") << "  : "
			  << static_cast<double>(afterDeque - beforeDeque) / CLOCKS_PER_SEC	  << " us." << std::endl;

}