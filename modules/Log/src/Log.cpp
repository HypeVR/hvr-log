// Copyright 2017 Caoyang Jiang

#include "Hvr/Log/Log.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <iostream>
#include <memory>
#include <string>
#include <vector>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
std::shared_ptr<Log> Log::ptr_ = nullptr;

void Log::Create(const std::string& app_name, const char* argv0)
{
  if (ptr_ == nullptr) ptr_ = std::make_shared<Log>(app_name, argv0);
}

void Log::Reset()
{
  ptr_.reset();
  ptr_ = nullptr;
}

std::shared_ptr<Log> Log::Get()
{
  return ptr_;
}

Log::Log(const std::string& app_name, const char* argv0)
{
  Global_Initialize(app_name, argv0);
}

Log::~Log()
{
}

void Log::Global_Initialize(const std::string& app_name, const char* argv0)
{
  std::string info_log_name    = "INFO_" + app_name + "_";
  std::string warning_log_name = "WARNING_" + app_name + "_";
  std::string error_log_name   = "ERROR_" + app_name + "_";

  ::FLAGS_logbuflevel = -1;
  google::SetLogDestination(google::GLOG_INFO, info_log_name.c_str());
  google::SetLogDestination(google::GLOG_WARNING, warning_log_name.c_str());
  google::SetLogDestination(google::GLOG_ERROR, error_log_name.c_str());
  google::SetLogSymlink(google::GLOG_WARNING, "");
  google::SetLogSymlink(google::GLOG_INFO, "");
  google::SetLogSymlink(google::GLOG_ERROR, "");
  // google::SetStderrLogging(google::GLOG_FATAL);
  google::SetStderrLogging(google::GLOG_ERROR);
  google::InitGoogleLogging(argv0);

  ::FLAGS_log_prefix = false;
#ifndef NDEBUG
  google::SetStderrLogging(google::INFO);
  ::FLAGS_log_prefix = true;
#endif
}

void Log::Global_Shutdown()
{
  google::ShutdownGoogleLogging();
}

void Log::Log_Warning(const std::string& message)
{
  if (Log::Get() != nullptr) LOG(WARNING) << message.c_str();
}

void Log::Log_Info(const std::string& message)
{
  if (Log::Get() != nullptr) LOG(INFO) << message.c_str();
}

void Log::Log_Error(const std::string& message)
{
  if (Log::Get() != nullptr) LOG(ERROR) << message.c_str();
}

void Log::Send_Fatal(const std::string& message)
{
  google::SendEmail("caoyang@hypevr.com", "Fatal Error", message.c_str());
}

}  // namespace hvr
