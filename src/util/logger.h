#include <string>

#pragma once

namespace Util
{

class Logger
{
 public:
   static void LogWarn(const std::string &message);
   static void LogError(const std::string &message);
   static void LogDebug(const std::string &message);
   static void Log(const std::string &message);
};

}
