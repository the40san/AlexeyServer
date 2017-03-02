#include "logger.h"

#include <iostream>

using namespace Util;

void Util::Logger::LogWarn(const std::string &message)
{
  std::cerr << "[WARN]" << message << std::endl;
}

void Util::Logger::LogError(const std::string &message)
{
  std::cerr << "[ERROR]" << message << std::endl;
}

void Util::Logger::Log(const std::string &message)
{
  std::cerr << "[DEBUG]" << message << std::endl;
}
