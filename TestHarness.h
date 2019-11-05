#pragma once
//////////////////////////////////////////////
// Executor.h - Base implementation         //
// ver 1.0                                  //
// Application: Project for CSE687, 2019    //
// Author: Thomas McIntosh                  //
//////////////////////////////////////////////

/*
Module Operations:
==================
This module ....
Public Interface:
=================
Build Process:
==============
Required Files:
-
Build Commands:
-
Maintance History:
==================
*/
#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <ctime>
#include <vector>
#include "Functor.h"
#include <chrono>

class TestHarness
{
public:
	/*
	 * ENUM:
	 *  LOW: Sets Logging: Returns Pass or Fail
	 *  MEDIUM: Sets Logging: Returns application specific messages for pass and fail, along with the result
	 *	HIGH: Sets Logging: Returns values values of application specific variables and an optional time-date stamp.
	 */
	enum LogReportLevel { LOW, MEDIUM, HIGH };
	TestHarness();
	~TestHarness();
	void Executor();
	void SetReportLevel(LogReportLevel); //Sets the reporting level
	void Log(bool, std::string, int);
	template <typename Test>
	void AddtoTestCases(Test&);
	void AddtoTestCases(std::function<void()>);
	void ResetTestCases();
	std::string ToString();

private:
	std::string GetDate();
	LogReportLevel logReportLevel = LogReportLevel::LOW;
	std::vector<std::function<void()>> TestCases;
	std::stringstream fullReport;
};

#endif