// Copyright 2017 Caoyang Jiang

#ifndef MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_
#define MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <memory>
#include <string>
#include <vector>
HVR_WINDOWS_ENABLE_ALL_WARNING

#include "glog/logging.h"

namespace hvr
{
/**
 * @brief      Class for log.
 * @ingroup    Log
 * @author     Caoyang Jiang && Ahmad Hasan
 */
class Log
{
 public:
  static std::shared_ptr<Log> ptr_;

  /**
   * @brief      Create a log. Recreate a log will destory the previous log.
   *
   * @param[in]  app_name  The application name
   */
  static void Create(const std::string &app_name, const char *argv0);

  /**
   * @brief      Destroy log.
   */
  static void Reset();

  /**
   * @brief      Get singleton log
   *
   * @return     log
   */
  static std::shared_ptr<Log> Get();

  /**
   * @brief      Logs a warning.
   *
   * @param[in]  message  The message
   */
  static void Log_Warning(const std::string &message);

  /**
   * @brief      Logs an information.
   *
   * @param[in]  message  The message
   */
  static void Log_Info(const std::string &message);

  /**
   * @brief      Logs an error.
   *
   * @param[in]  message  The message
   */
  static void Log_Error(const std::string &message);

  explicit Log(const std::string &app_name, const char *argv0);
  ~Log();

  /**
   * @brief      Start logging system
   *
   * @param[in]  app_name  The application name
   */
  void Global_Initialize(const std::string &app_name, const char *argv0) const;

  /**
   * @brief      Shutdown logging system
   */
  void Global_Shutdown() const;
};
}  // namespace hvr

#endif  // MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_
