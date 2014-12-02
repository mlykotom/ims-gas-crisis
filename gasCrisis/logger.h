/**
** IMS projekt
*/

#pragma once

#include <string>
#include <vector>

class cLogger
{
public:
	cLogger(void);
	~cLogger(void);

private:
	std::string mFile;

	std::vector<std::string> mStateNames;

	bool mFlowLogs;
	bool mStatLogs;

public:
	void createFlowLog(const std::string& type, const std::string& source, const std::string& destination, double amount);
	void createStatLog(const std::string& type, const std::string& source, const std::string& message);

	void addStateName(const std::string& stateName);

	void setLogFile(const std::string& file);
	void showFlowLogs(bool show);
	void showStatLogs(bool show);
};