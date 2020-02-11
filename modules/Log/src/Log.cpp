// Copyright 2019 HypeVR

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
std::ostringstream Log::os_err_ = std::ostringstream();
std::ostringstream Log::os_war_ = std::ostringstream();
std::ostringstream Log::os_inf_ = std::ostringstream();
std::atomic_bool Log::thread_safe_;
std::atomic_bool Log::initialized_;
std::mutex Log::mtx_;
Severity Log::severity_  = Severity::NA;
bool Log::info_begin_    = true;
bool Log::warning_begin_ = true;
bool Log::error_begin_   = true;

std::shared_ptr<Log> Log::ptr_ = nullptr;

void Log::Create(const std::string& app_name,
                 const char* argv0,
                 bool make_thread_safe)
{
  thread_safe_ = false;
  initialized_ = false;

  if (ptr_ == nullptr)
  {
    ptr_ = std::make_shared<Log>(app_name, argv0, make_thread_safe);
  }
}

void Log::Create(const char* argv0, bool make_thread_safe)
{
  std::string local_path =
      std::string(argv0).substr(std::string(argv0).find_last_of("/\\") + 1);
  std::string app_name = local_path.substr(0, local_path.find_last_of('.'));

  thread_safe_ = false;
  initialized_ = false;

  if (ptr_ == nullptr)
  {
    ptr_ = std::make_shared<Log>(app_name, argv0, make_thread_safe);
  }
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
  thread_safe_ = make_thread_safe;
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
    if (!FLAGS_logtostderr)
    {
      google::SetLogDestination(google::GLOG_INFO, info_log_name.c_str());
      google::SetLogDestination(google::GLOG_WARNING, warning_log_name.c_str());
      google::SetLogDestination(google::GLOG_ERROR, error_log_name.c_str());
    }
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

  initialized_ = true;
}

void Log::Global_Shutdown() const
{
  google::ShutdownGoogleLogging();
}

void Log::Log_Error_Internal()
{
  // 31 for red, 33 for yellow
  if (Log::Get() != nullptr)
  {
    LOG(ERROR) << "\033[1;33m" + os_err_.str() + "\033[0m\n";
  }
  os_err_.str("");
}

void Log::Log_Warning_Internal()
{
  if (Log::Get() != nullptr)
  {
    LOG(WARNING) << os_war_.str();
  }
  os_war_.str("");
}

void Log::Log_Info_Internal()
{
  if (Log::Get() != nullptr)
  {
    LOG(INFO) << os_inf_.str();
  }
  os_inf_.str("");
}

Log& Log::LogInfo()
{
  severity_ = Severity::INFO;
  // if (!info_begin_)
  //{
  //  Log_Info_Internal("\n");
  //}
  // else
  //{
  //  info_begin_ = false;
  //}
  return *Get();
}

Log& Log::LogWarning()
{
  severity_ = Severity::WARNING;
  // if (!warning_begin_)
  //{
  //  Log_Info_Internal("\n");
  //}
  // else
  //{
  //  warning_begin_ = false;
  //}
  return *Get();
}

Log& Log::LogError()
{
  severity_ = Severity::ERROR;
  // if (!error_begin_)
  //{
  //  Log_Info_Internal("\n");
  //}
  // else
  //{
  //  error_begin_ = false;
  //}
  return *Get();
}

std::ostream& Log::endl(std::ostream& os)
{
  switch (severity_)
  {
    case hvr::Severity::INFO:
      os_inf_ << std ::endl;
      Log_Info_Internal();
      return os;
    case hvr::Severity::WARNING:
      os_war_ << std ::endl;
      Log_Warning_Internal();
      return os;
    case hvr::Severity::ERROR:
      os_err_ << std ::endl;
      Log_Error_Internal();
      return os;
    default: return std::endl(os);
  }
}
}  // namespace hvr
