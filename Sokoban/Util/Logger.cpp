#include "Logger.h"
#include "Utilities.h"
#include <assert.h>

// Static Declaration
Logger* Logger::m_instance = nullptr;
std::ofstream Logger::m_Logfile;

Logger::Logger()
{
	m_Logfile.open("MemoryUsage.log", std::fstream::trunc);
}

Logger* Logger::GetLogger() {
	if (m_instance == nullptr) {

		m_instance = new Logger();
	}

	return m_instance;
}

void Logger::Log(const std::string& sMessage)
{
	m_Logfile << "[" << Util::CurrentDateTime() << "] ";
	m_Logfile << sMessage << "\n";
}