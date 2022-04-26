// https://github.com/notSam25/cpp-header Because I am lazy.

#pragma once
#pragma warning(disable : 4996) // CRT_SECURE_NO_WARNINGS

#define ll long long
#if defined(_WIN32)
#define PLATFORM_NAME "windows"
#elif defined(_WIN64)
#define PLATFORM_NAME "windows"
#elif defined(__linux__)
#define PLATFORM_NAME "linux"
#else
#define PLATFORM_NAME NULL
#endif

#include <functional>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <array>
#include <cmath>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <array>
#include <vector>
#include <chrono>
#include <ctime>

namespace Common
{
    inline const char* GetOperatingSystemName()     {
        return (PLATFORM_NAME == NULL) ? "" : PLATFORM_NAME;
    }

    inline std::string GetSystemOutput(const char *cmd)     {
        std::array<char, 128> buffer;
        std::string result;
        #if defined(_WIN32)
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
        #elif defined(_WIN64)
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
        #elif defined(__linux__)
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        #endif

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            result += buffer.data();

        return result;
    }

    inline void PrintSystemInformation()    {
        printf("[dbg] OS Name     -> %s\n", GetOperatingSystemName());

        if(strcmp(PLATFORM_NAME, "linux") == 0) {
            printf("[dbg] OS Version  -> %s", GetSystemOutput("cat /etc/os-release | grep VERSION=").c_str());
            printf("[dbg] Username    -> %s", GetSystemOutput("whoami").c_str());
        } else
            printf("[dbg] OS Version  -> %s\n", GetSystemOutput("Get-WmiObject -Class win32_OperatingSystem | Select Version, BuildNumber").c_str()); 
    }

    class Debug {
    public:
        Debug(bool _UseLogFile = true) : UseLogFile(_UseLogFile) {}
        enum class LogType {
            Error = 0,
            Warning,
            Info
        };
        void LogData(LogType type, const std::string &data)
        {
            switch (type)
            {
            case LogType::Error:
                std::cout << "\033[1;31m[!]\033[0m " << data << std::endl;
                break;
            case LogType::Warning:
                std::cout << "\033[1;33m[#]\033[0m " << data << std::endl;
                break;
            case LogType::Info:
                std::cout << "\033[1;34m[*]\033[0m " << data << std::endl;
                break;

            default:
                break;
            }
            if(UseLogFile)  {
                //Log data in file
            }
        }

    private:
        bool UseLogFile;
    };
}
