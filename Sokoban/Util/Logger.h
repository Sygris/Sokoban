#pragma once

#include <fstream>
#include <iostream>
#include <string>

class Logger
{
public:
    void Log(const std::string& sMessage);

    static Logger* GetLogger();
private:

    Logger();

    static Logger* m_instance;
    static std::ofstream m_Logfile;
};

