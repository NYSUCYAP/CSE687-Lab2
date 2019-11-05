#include "Logger.h"



Logger::Logger()
{
	logReportLevel = LogReportLevel::LOW;
}


Logger::~Logger()
{
}

/*
 * SetReportLevel
 * Allows you to change LogReportLevel.
 * Takes in an enum.
 */
void Logger::SetReportLevel(LogReportLevel reportLevel) {
	logReportLevel = reportLevel;
}

/*
 * Log
 * This Function creates the log report taking in three variables.
 * succeed: bool: test result
 * report: String: the log of all the tests
 * testNumber: int: The testNumber ran
 * return void
 */
void Logger::Log(bool succeed, std::string report, int testNumber) {
	std::string logString = "";
	if (succeed) {
		logString = "Test: " + std::to_string(testNumber) + " passed. ";

	} // End if succeed
	else {
		logString = "Test: " + std::to_string(testNumber) + " failed. ";
	} // End else: !succeed
	if (logReportLevel != LogReportLevel::LOW && !succeed) {
		logString += "Error Message: " + report + ". ";
	} // End if Report not Low
	if (logReportLevel == LogReportLevel::HIGH) {
		logString += "Test Ran: " + GetDate();
	} // End if Report High
	fullReport << logString << std::endl;
}

/*
 * GetDate
 * Gets the current timestamp for logging purposes
 * returns string: Current timestamp.
 */
std::string Logger::GetDate() {
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &result);
	return str;
}

/*
 * ToString
 * Returns a String and adds Test Results to the the top of the file.
 * return string:
 */
std::string Logger::ToString() {
	std::string returnString = this->fullReport.str();
	return returnString;
}

void Logger::Clear() {
	fullReport.str(std::string());
}