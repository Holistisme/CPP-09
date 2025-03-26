#pragma once

/* ############################################################################################## */

#include "../ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

/* ############################################################################################## */

#define COMMA ','
#define PIPE  '|'
#define SPACE ' '

#define less	 <
#define greater	 >
#define equal_to ==

#define CSV "data.csv"

#define ERROR_CSV  "CSV could not be opened"
#define ERROR_FILE "User file could not be opened"

#define ERROR_LINE		"The program was unable to retrieve the line"
#define ERROR_VALUE		"The program was unable to retrieve the requested value"
#define ERROR_LENGTH	"No effort at all. The date doesn't even have the required ten characters"
#define ERROR_DATE		"Parsing an invalid date"
#define ERROR_EMPTINESS "How the Hell the CSV file ended up empty"
#define ERROR_FLOATING	"https://en.cppreference.com/w/cpp/language/types#Standard_floating-point_types"
#define ERROR_NEGATIVE	"Some dream of making money, the proofreader of losing it. What indignity"
#define ERROR_RANGE		"No. You're too poor to ever have more than 1000 coins"
#define ERROR_EARLY		"Does Humanity already existed at that time"

/* ############################################################################################## */

class BitcoinExchange {
	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &source);
		BitcoinExchange &operator=(const BitcoinExchange &source);
		~BitcoinExchange(void);

		void			  processInputFile(const std::string &file) const;
		const std::string calculateValue(const std::string &line)	const;
		const std::string parseDate(std::string &date)				const;
		float		  	  parseRate(const std::string &date)		const;
		float		  	  parseValue(std::string &value)			const;
	private:
		std::map<std::string, float> _data;
};