// Copyright 2017 Caoyang Jiang

#ifndef MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_
#define MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <iostream>
#include <memory>
#include <sstream>
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

  Log(const std::string &app_name, const char *argv0);
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
    os_err << var1;
    Log_Error(var2...);
  }

  /**
   * @brief      Logs an error with a template specialization.
   *
   * @param      var1   The variable 1 is a function pointer
   * @param[in]  var2   parameter pack that has << overload
   *
   * @tparam     Types  types of individual parameters in var2
   */
  template <typename... Types>
  static void Log_Error(std::ostream &(*var1)(std::ostream &), Types... var2)
  {
    os_err << var1;
    Log_Error(var2...);
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
    os_war << var1;
    Log_Warning(var2...);
  }

  /**
     * @brief      Logs an warning with a template specialization.
     *
     * @param      var1   The variable 1 is a function pointer
     * @param[in]  var2   parameter pack that has << overload
     *
     * @tparam     Types  types of individual parameters in var2
     */
  template <typename... Types>
  static void Log_Warning(std::ostream &(*var1)(std::ostream &), Types... var2)
  {
    os_err << var1;
    Log_Warning(var2...);
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
    os_inf << var1;
    Log_Info(var2...);
  }

  /**
     * @brief      Logs an info with a template specialization.
     *
     * @param      var1   The variable 1 is a function pointer
     * @param[in]  var2   parameter pack that has << overload
     *
     * @tparam     Types  types of individual parameters in var2
     */
  template <typename... Types>
  static void Log_Info(std::ostream &(*var1)(std::ostream &), Types... var2)
  {
    os_err << var1;
    Log_Info(var2...);
  }

 private:
  static void Log_Error();
  static void Log_Warning();
  static void Log_Info();

  static std::ostringstream os_err;
  static std::ostringstream os_war;
  static std::ostringstream os_inf;
};

}  // namespace hvr

#endif  // MODULES_LOG_INCLUDE_HVR_LOG_LOG_H_
