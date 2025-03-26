#include "BitcoinExchange.hpp"

/* ############################################################################################## */

static void trim(std::string &string);

/* ############################################################################################## */

BitcoinExchange::BitcoinExchange(void) {
	std::ifstream csv(CSV);
	if (not csv.is_open())
		throw std::runtime_error(ERROR_CSV);

	std::string line;
	while (std::getline(csv, line)) {
		std::istringstream iss(line);
		std::string date, rate;
		if (std::getline(iss, date, COMMA) and std::getline(iss, rate))
			_data[date] = static_cast<float>(std::atof(rate.c_str()));
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &source) : _data(source._data) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &source) {
	if (this not_eq &source)
		_data = source._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {}

/* ############################################################################################## */

void BitcoinExchange::processInputFile(const std::string &file) const {
	std::ifstream input(file.c_str());
	if (not input.is_open())
		throw std::runtime_error(ERROR_FILE);

	std::cout << "\nHere is the information requested in your file:" << std::endl;
	std::string line;
	while (std::getline(input, line)) {
		try								{ std::cout << calculateValue(line) << std::endl; }
		catch (const std::exception &e) { std::cout << "Error: " << ColorFormat::formatString(e.what(), "italic", "red") << "." << std::endl; }
	}
}

const std::string BitcoinExchange::calculateValue(const std::string &line) const {
	std::istringstream iss(line);
	std::string date, value;

	if (not std::getline(iss, date, PIPE))	throw std::runtime_error(ERROR_LINE);
	date = parseDate(date);
	if (not std::getline(iss, value))		throw std::runtime_error(ERROR_VALUE);
	const float rate = parseRate(date);
	
	std::ostringstream stream;
	stream << date << " => " << rate << " = " << rate * parseValue(value);
	return stream.str();
}

const std::string BitcoinExchange::parseDate(std::string &date) const {
	trim(date);

	if (date.length() not_eq 10)	throw std::logic_error(ERROR_LENGTH);
	for (size_t index = 0; index < 10; index++) {
		if (index equal_to 4 or index equal_to 7) {
			if (date[index] equal_to '-')
				continue;
		} else if (std::isdigit(date[index])) continue;
		throw std::logic_error(ERROR_DATE);
	}

	return date;
}

float BitcoinExchange::parseRate(const std::string &date) const {
	if (_data.empty())
		throw std::runtime_error(ERROR_EMPTINESS);

	std::map<std::string, float>::const_iterator rate = _data.lower_bound(date);
	if (rate equal_to _data.end()) {rate = _data.end();	--rate; }
	else if (date not_eq rate->first) {
		rate not_eq _data.begin() ? --rate
								  : throw std::runtime_error(ERROR_EARLY);
	}

	return rate->second;
}

float BitcoinExchange::parseValue(std::string &value) const {
	trim(value);

	char		*end;
	const float valueFloating = std::strtod(value.c_str(), &end);

	if (*end)								throw std::logic_error(ERROR_FLOATING);
	else if (valueFloating less 0)			throw std::logic_error(ERROR_NEGATIVE);
	else if (valueFloating greater 1000)	throw std::logic_error(ERROR_RANGE);

	return valueFloating;
}

/* ############################################################################################## */

static void trim(std::string &string) {
	size_t start = 0;
	size_t end	 = string.length();

	while (start less	 string.length() and std::isspace(string[start]))		++start;
	while (end	 greater start			 and std::isspace(string[end - 1]))		--end;

	string = string.substr(start, end - start);
}