#include "TestHarness.h"
#include "..\..\Lab2TestDLL\Lab2TestDLL\TestHarnessDLL.h"

// Empty Constructor
TestHarness::TestHarness() {}
// Empty Deconstructor
TestHarness::~TestHarness() {}

/*
 * SetReportLevel
 * Allows you to change LogReportLevel.
 * Takes in an enum.
 */
void TestHarness::SetReportLevel(LogReportLevel reportLevel) {
	logReportLevel = reportLevel;
}

/*
 * Executor
 * Executes all items in the TestCases vector and logs the results.
 * return voids
 */
void TestHarness::Executor() {
	int testNumber = 1;
	for (auto& i : this->TestCases) {
		try {
			i();
			Log(1, "Pass", testNumber);
		}
		catch (std::exception & e) {
			Log(0, e.what(), testNumber);
		} // End of catch.
		testNumber++;
	} // End of for.
	std::cout << "\n";
}

/*
 * Log
 * This Function creates the log report taking in three variables.
 * succeed: bool: test result
 * report: String: the log of all the tests
 * testNumber: int: The testNumber ran
 * return void
 */
void TestHarness::Log(bool succeed, std::string report, int testNumber) {
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
std::string TestHarness::GetDate() {
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &result);
	return str;
}

/*
 * AddtoTestCases
 * callable: function point passed in to be added to the TestCases vector.
 * return void
 */
void TestHarness::AddtoTestCases(std::function<void()> callable) {
	TestCases.push_back(callable);
}

/*
 * Template typename Test
 * callable: function: Adds functor to the TestCases vector.
 * return void
 */
template <typename Test>
void TestHarness::AddtoTestCases(Test &test) {
	TestCases.push_back(test);
}

/*
 * ResetTestCases
 * Empties the vector of testcases
 * return void
 */
void TestHarness::ResetTestCases() {
	TestCases.clear();
	fullReport.str(std::string());
}

/*
 * ToString
 * Returns a String and adds Test Results to the the top of the file.
 * return string:
 */
std::string TestHarness::ToString() {
	std::cout << "Test Results: " << std::endl;
	std::string returnString = this->fullReport.str();
	return returnString;
}

/*
 * Test Case: Bad Allocation
 * Attempt to allocate an unsinged long to an int
 * return bool true: Should fail though because of error.
 */
bool TestBadAlloc() {
	std::bad_alloc x;
	while (true) {
		new int[99999ul];
	} // End while
	throw x;
	return true;
}

/*Creating classes for TestBadCastTest*/
//class Base { virtual void member() {} };
//class Derived : Base {};

/*
 * Test case: Bad Cast
 * Attempt to cast derived class to base class
 * return bool true: Should fail though because of error.
 */
bool TestBadCast() {
	std::bad_cast error;
	Base baseClass;
	Derived& derivedClass = dynamic_cast<Derived&>(baseClass);
	throw error;
	return true;
}

bool MathTestDLL()
{
	double num1[] = { 1.23456, 9.90010, 2.345, 18.9001, 5.0 };
	double num2[] = { 0.98765, 1.54321, 6.789, 2.0, 4.0 };
	double result[5] = {};
	long rand_num {};
	MATH* math_op = new MATH();

	std::srand(std::time(NULL));
	rand_num = std::rand() % 10 + 1;

	try
	{
		result[0] = math_op->Add(num1[0], num2[0]);
		result[1] = math_op->Subtract(num1[1], num2[1]);
		result[2] = math_op->Multiply(num1[2], num2[2]);
		result[3] = math_op->Divide(num1[3], num2[3]);
		result[4] = math_op->Remainder(num1[4], num2[4]);

		if (1)
		{
			std::cout << "Test 4 Validation:\n*****************" << std::endl;
			std::cout << "1. " << num1[0] << " + " << num2[0] << " = " << result[0] << std::endl;
			std::cout << "2. " << num1[1] << " - " << num2[1] << " = " << result[1] << std::endl;
			std::cout << "3. " << num1[2] << " * " << num2[2] << " = " << result[2] << std::endl;
			std::cout << "4. " << num1[3] << " / " << num2[3] << " = " << result[3] << std::endl;
			std::cout << "5. " << num1[4] << " % " << num2[4] << " = " << result[4] << std::endl;
			std::cout << "6. " << rand_num << "! = " << math_op->Factorial(rand_num) << std::endl;
		}
	}
	catch (std::runtime_error &rt)
	{
		std::cerr << "ERROR: Out of range: " << rt.what() << std::endl << std::endl;
		delete math_op;
		return false;
	}
		
	delete math_op;
	return true;
}


int main() {;
	FUNCTOR Funct;
	TestHarness testHarness;
	CIS687_TEST test;

	std::cout << "Running Test at a low level of reporting\n";
	testHarness.AddtoTestCases(TestBadAlloc);
	testHarness.AddtoTestCases(TestBadCast);
	testHarness.AddtoTestCases(Funct);
	testHarness.AddtoTestCases(MathTestDLL);	//MATH class from DLL
	testHarness.Executor();
	std::cout << testHarness.ToString();
	testHarness.ResetTestCases();
	testHarness.SetReportLevel(TestHarness::LogReportLevel::MEDIUM);
	std::cout << "\nRunning Test at a medium level of reporting\n";
	testHarness.AddtoTestCases(TestBadAlloc);
	testHarness.AddtoTestCases(TestBadCast);
	testHarness.AddtoTestCases(Funct);
	testHarness.AddtoTestCases(MathTestDLL);	//MATH class from DLL
	testHarness.Executor();
	std::cout << testHarness.ToString();
	testHarness.ResetTestCases();
	testHarness.SetReportLevel(TestHarness::LogReportLevel::HIGH);
	std::cout << "\nRunning Test at a high level of reporting\n";
	testHarness.AddtoTestCases(TestBadAlloc);
	testHarness.AddtoTestCases(TestBadCast);
	testHarness.AddtoTestCases(Funct);
	testHarness.AddtoTestCases(MathTestDLL);	//MATH class from DLL
	testHarness.Executor();
	std::cout << testHarness.ToString();
	testHarness.ResetTestCases();

	std::cin.get();	 
	return 0;
}