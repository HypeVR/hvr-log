// Copyright 2017 Ahmad Hasan

#include <fstream>
#include <iostream>
#include <string>
#include "Hvr/Log/Log.h"

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "boost/filesystem.hpp"
#include "boost/regex.hpp"
#include "boost/regex_fwd.hpp"
#include "boost/token_iterator.hpp"
#include "boost/xpressive/regex_token_iterator.hpp"
HVR_WINDOWS_ENABLE_ALL_WARNING

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "gtest/gtest.h"
HVR_WINDOWS_ENABLE_ALL_WARNING

std::string exe_path = "";

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  exe_path = argv[0];
  exe_path = exe_path.substr(0, exe_path.find_last_of("/\\"));

  std::string directory;
  std::string extension      = ".log";
  std::string prefix_error   = "LOG__error";
  std::string prefix_info    = "LOG__info";
  std::string prefix_warning = "LOG__warning";
  directory                  = "/home/hypevr/hvr-log/build/unit-test/";
  boost::filesystem::recursive_directory_iterator rdi_err(directory);
  boost::filesystem::recursive_directory_iterator end_rdi_err;
  for (; rdi_err != end_rdi_err; rdi_err++)
  {
    if (extension.compare((*rdi_err).path().extension().string()) == 0)
    {
      std::size_t found = (*rdi_err).path().string().find(prefix_error);
      if (found != std::string::npos)
      {
        if (boost::filesystem::exists((*rdi_err).path().string()))
          std::remove((*rdi_err).path().string().c_str());
        break;
      }
    }
  }

  boost::filesystem::recursive_directory_iterator rdi_info(directory);
  boost::filesystem::recursive_directory_iterator end_rdi_info;
  for (; rdi_info != end_rdi_info; rdi_info++)
  {
    if (extension.compare((*rdi_info).path().extension().string()) == 0)
    {
      std::size_t found = (*rdi_info).path().string().find(prefix_info);
      if (found != std::string::npos)
      {
        if (boost::filesystem::exists((*rdi_info).path().string()))
          std::remove((*rdi_info).path().string().c_str());
        break;
      }
    }
  }

  boost::filesystem::recursive_directory_iterator rdi_war(directory);
  boost::filesystem::recursive_directory_iterator end_rdi_war;
  for (; rdi_war != end_rdi_war; rdi_war++)
  {
    if (extension.compare((*rdi_war).path().extension().string()) == 0)
    {
      std::size_t found = (*rdi_war).path().string().find(prefix_warning);
      if (found != std::string::npos)
      {
        if (boost::filesystem::exists((*rdi_war).path().string()))
          std::remove((*rdi_war).path().string().c_str());
        break;
      }
    }
  }
  return RUN_ALL_TESTS();
}
