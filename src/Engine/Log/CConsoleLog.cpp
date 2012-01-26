#include "CConsoleLog.h"

#include <iostream>
using namespace std;

void CConsoleLog::doDebug(const std::string& log)
{
	cout << log << endl;
}

void CConsoleLog::doWarning(const std::string& log)
{
	cout << log << endl;
}

void CConsoleLog::doError(const std::string& log)
{
	cout << log << endl;
}

void CConsoleLog::doCritical(const std::string& log)
{
	cout << log << endl;
}