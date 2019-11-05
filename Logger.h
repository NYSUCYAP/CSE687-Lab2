#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>


class Logger
{
public:
	/*
	 * ENUM:
	 *  LOW: Sets Logging: Returns Pass or Fail
	 *  MEDIUM: Sets Logging: Returns application specific messages for pass and fail, along with the result
	 *	HIGH: Sets Logging: Returns values values of application specific variables and an optional time-date stamp.
	 */
	enum LogReportLevel { LOW, MEDIUM, HIGH };

	Logger();
	~Logger();
	void SetReportLevel(LogReportLevel reportLevel);
	void Log(bool succeed, std::string report, int testNumber);
	std::string ToString();
	void Clear();
private:
	LogReportLevel logReportLevel;
	std::string GetDate();
	std::stringstream fullReport;
};
