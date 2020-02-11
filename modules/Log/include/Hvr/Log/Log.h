// Copyright 2019 HypeVR

#ifndef MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_
#define MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

#include "glog/logging.h"
HVR_WINDOWS_ENABLE_ALL_WARNING

namespace hvr
{
enum class Severity
{
  NA,
  INFO,
  WARNING,
  ERROR
};

/**
 * @brief      Class for log.
 * @ingroup    Log
 * @author     Caoyang Jiang && Ahmad Hasan
 */
class Log
{
 public:
  /**
   * @brief      Create a log. Recreate a log will destory the previous log.
   *
   * @param[in]  app_name  The application name
   */
  HVR_LOG_DLL
  static void Create(const std::string &app_name,
                     const char *argv0,
                     bool make_thread_safe = false);

  /**
   * @brief      Create a log. Recreate a log will destory the previous log.
   */
  HVR_LOG_DLL
  static void Create(const char *argv0, bool make_thread_safe = false);

  /**
   * @brief      Destroy log.
   */
  HVR_LOG_DLL
  static void Reset();

  /**
   * @brief      Get singleton log
   *
   * @return     log
   */
  HVR_LOG_DLL
  static std::shared_ptr<Log> Get();

  HVR_LOG_DLL
  Log(const std::string &app_name, const char *argv0, bool make_thread_safe);

  HVR_LOG_DLL
  ~Log();

  /**
   * @brief      Start logging system
   *
   * @param[in]  app_name  The application name
   */
  HVR_LOG_DLL
  void Global_Initialize(const std::string &app_name, const char *argv0) const;

  /**
   * @brief      Shutdown logging system
   */
  HVR_LOG_DLL
  void Global_Shutdown() const;

  /**
   * @brief      Logs an error.
   *
   * @param[in]  var1   any type of variable that has << overload
   * @param[in]  var2   parameter pack that has << overload
   *
   * @tparam     T      type of var1
   * @tparam     Types  types of individual parameters in var2
   */
  template <typename T, typename... Types>
  static void Log_Error(T var1, Types... var2)
  {
    if (!initialized_)
    {
      return;
    }
    if (thread_safe_) mtx_.lock();
    Log_Error_Internal(var1, var2...);
    if (thread_safe_) mtx_.unlock();
  }

  /**
   * @brief      Logs a warning.
   *
   * @param[in]  var1   any type of variable that has << overload
   * @param[in]  var2   parameter pack that has << overload
   *
   * @tparam     T      type of var1
   * @tparam     Types  types of individual parameteers in var2
   */
  template <typename T, typename... Types>
  static void Log_Warning(T var1, Types... var2)
  {
    if (!initialized_)
    {
      return;
    }
    if (thread_safe_) mtx_.lock();
    Log_Warning_Internal(var1, var2...);
    if (thread_safe_) mtx_.unlock();
  }

  /**
   * @brief      Logs an information.
   *
   * @param[in]  var1   any type of variable that has << overload
   * @param[in]  var2   parameter pack that has << overload
   *
   * @tparam     T      type of var1
   * @tparam     Types  types of individual parameteers in var2
   */
  template <typename T, typename... Types>
  static void Log_Info(T var1, Types... var2)
  {
    if (!initialized_)
    {
      return;
    }
    if (thread_safe_) mtx_.lock();
    Log_Info_Internal(var1, var2...);
    if (thread_safe_) mtx_.unlock();
  }

  /**
   * @brief      Logs an information.
   *
   * @return     reference to log singleton
   */
  HVR_LOG_DLL
  static Log &LogInfo();

  /**
   * @brief      Logs a warning.
   *
   * @return     reference to log singleton
   */
  HVR_LOG_DLL
  static Log &LogWarning();

  /**
   * @brief      Logs an error.
   *
   * @return     reference to log singleton
   */
  HVR_LOG_DLL
  static Log &LogError();

  /**
   * @brief      Overloaded output operator.
   *
   * @param[in]  msg   The message
   *
   * @tparam     T     Data type
   *
   * @return     reference to log singleton
   */
  template <typename T>
  Log &operator<<(const T &msg)
  {
    switch (severity_)
    {
      case Severity::INFO: os_inf_ << msg; break;
      case Severity::WARNING: os_war_ << msg; break;
      case Severity::ERROR: os_err_ << msg; break;
      default: Log_Info_Internal(msg); break;
    }
    return *Get();
  }

  /**
   * @brief      Puts a newline whenever this function pointer is used for
   *             logging, if in output operator mode, print the last line and
   *             creates newline.
   *
   * @param      os    std::ostringstream
   *
   * @return     a new line
   */
  HVR_LOG_DLL static std::ostream &endl(std::ostream &os);

 private:
  template <typename T, typename... Types>
  static void Log_Error_Internal(T var1, Types... var2)
  {
    os_err_ << var1;
    Log_Error_Internal(var2...);
  }

  template <typename T, typename... Types>
  static void Log_Warning_Internal(T var1, Types... var2)
  {
    os_war_ << var1;
    Log_Warning_Internal(var2...);
  }

  template <typename T, typename... Types>
  static void Log_Info_Internal(T var1, Types... var2)
  {
    os_inf_ << var1;
    Log_Info_Internal(var2...);
  }

 private:
  HVR_LOG_DLL
  static std::shared_ptr<Log> ptr_;

  HVR_LOG_DLL
  static std::atomic_bool thread_safe_;

  HVR_LOG_DLL
  static std::atomic_bool initialized_;

  HVR_LOG_DLL
  static std::mutex mtx_;

  HVR_LOG_DLL
  static Severity severity_;

  HVR_LOG_DLL
  static bool info_begin_;
  HVR_LOG_DLL
  static bool warning_begin_;
  HVR_LOG_DLL
  static bool error_begin_;

  HVR_LOG_DLL
  static void Log_Error_Internal();
  HVR_LOG_DLL
  static void Log_Warning_Internal();
  HVR_LOG_DLL
  static void Log_Info_Internal();

  HVR_LOG_DLL
  static void Log_Error_Internal_SL();
  HVR_LOG_DLL
  static void Log_Warning_Internal_SL();
  HVR_LOG_DLL
  static void Log_Info_Internal_SL();

  HVR_LOG_DLL
  static std::ostringstream os_err_;
  HVR_LOG_DLL
  static std::ostringstream os_war_;
  HVR_LOG_DLL
  static std::ostringstream os_inf_;
};

}  // namespace hvr

#endif  // MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_
