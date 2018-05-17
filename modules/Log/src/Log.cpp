// Copyright 2017 Caoyang Jiang

#include "Hvr/Log/Log.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
std::ostringstream Log::os_err = std::ostringstream();
std::ostringstream Log::os_war = std::ostringstream();
std::ostringstream Log::os_inf = std::ostringstream();
std::atomic<bool> Log::thread_safe;
std::mutex Log::mtx;

std::shared_ptr<Log> Log::ptr_ = nullptr;

void Log::Create(const std::string& app_name,
                 const char* argv0,
                 bool make_thread_safe)
{
  if (ptr_ == nullptr)
    ptr_ = std::make_shared<Log>(app_name, argv0, make_thread_safe);
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

Log::Log(const std::string& app_name, const char* argv0, bool make_thread_safe)
{
  thread_safe = make_thread_safe;
  Global_Initialize(app_name, argv0);
}

Log::~Log()
{
  Global_Shutdown();
}

void Log::Global_Initialize(const std::string& app_name,
                            const char* argv0) const
{
  ::FLAGS_logbuflevel = -1;
  if (!app_name.empty())
  {
    std::string info_log_name    = app_name + "_" + "INFO_";
    std::string warning_log_name = app_name + "_" + "WARNING_";
    std::string error_log_name   = app_name + "_" + "ERROR_";
    google::SetLogDestination(google::GLOG_INFO, info_log_name.c_str());
    google::SetLogDestination(google::GLOG_WARNING, warning_log_name.c_str());
    google::SetLogDestination(google::GLOG_ERROR, error_log_name.c_str());
  }
  google::SetLogSymlink(google::GLOG_WARNING, "");
  google::SetLogSymlink(google::GLOG_INFO, "");
  google::SetLogSymlink(google::GLOG_ERROR, "");
  // google::SetStderrLogging(google::GLOG_FATAL);
  google::SetStderrLogging(google::GLOG_ERROR);
  google::InitGoogleLogging(argv0);

  ::FLAGS_log_prefix = false;
#ifndef NDEBUG
  google::SetStderrLogging(google::GLOG_INFO);
  ::FLAGS_log_prefix = true;
#endif
}

void Log::Global_Shutdown() const
{
  google::ShutdownGoogleLogging();
}

void Log::Log_Error_Internal()
{
  if (Log::Get() != nullptr) LOG(ERROR) << os_err.str();
  os_err.str("");
}

void Log::Log_Warning_Internal()
{
  if (Log::Get() != nullptr) LOG(WARNING) << os_war.str();
  os_war.str("");
}

void Log::Log_Info_Internal()
{
  if (Log::Get() != nullptr) LOG(INFO) << os_inf.str();
  os_inf.str("");
}

std::ostream& Log::endl(std::ostream& os)
{
  return std::endl(os);
}
}  // namespace hvr
