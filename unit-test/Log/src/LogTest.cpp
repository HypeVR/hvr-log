// Copyright 2019 HypeVR

#include "LogTest.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "boost/filesystem.hpp"
HVR_WINDOWS_ENABLE_ALL_WARNING

#include "Hvr/Log/Log.h"

extern std::string exe_path;

LogTest::LogTest() = default;

LogTest::~LogTest() = default;

void LogTest::SetUp()
{
}

void LogTest::TearDown()
{
  hvr::Log::Reset();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  std::string directory;
  std::string prefix_error   = "Log_ERROR";
  std::string prefix_info    = "Log_INFO";
  std::string prefix_warning = "Log_WARNING";
  directory                  = exe_path;
  boost::filesystem::recursive_directory_iterator rdi_err(directory);
  boost::filesystem::recursive_directory_iterator end_rdi_err;

  for (; rdi_err != end_rdi_err; rdi_err++)
  {
    std::size_t found = (*rdi_err).path().string().find(prefix_error);

    if (found != std::string::npos)
    {
      if (boost::filesystem::exists((*rdi_err).path().string()))
      {
        std::remove((*rdi_err).path().string().c_str());
      }
      break;
    }
  }

  boost::filesystem::recursive_directory_iterator rdi_info(directory);
  boost::filesystem::recursive_directory_iterator end_rdi_info;

  for (; rdi_info != end_rdi_info; rdi_info++)
  {
    std::size_t found = (*rdi_info).path().string().find(prefix_info);
    if (found != std::string::npos)
    {
      if (boost::filesystem::exists((*rdi_info).path().string()))
      {
        std::remove((*rdi_info).path().string().c_str());
      }
      break;
    }
  }

  boost::filesystem::recursive_directory_iterator rdi_war(directory);
  boost::filesystem::recursive_directory_iterator end_rdi_war;

  for (; rdi_war != end_rdi_war; rdi_war++)
  {
    std::size_t found = (*rdi_war).path().string().find(prefix_warning);
    if (found != std::string::npos)
    {
      if (boost::filesystem::exists((*rdi_war).path().string()))
      {
        std::remove((*rdi_war).path().string().c_str());
      }
      break;
    }
  }
}

TEST_F(LogTest, Log_Error)
{
  hvr::Log::Create(exe_path + "/Log", "LogTest");
  hvr::Log::Log_Error("Test_error");

  bool is_found = false;

  boost::filesystem::path p;
  std::string directory;
  std::string prefix = "Log_ERROR";
  directory          = exe_path;

  boost::filesystem::recursive_directory_iterator rdi(directory);
  boost::filesystem::recursive_directory_iterator end_rdi;

  for (; rdi != end_rdi; rdi++)
  {
    std::size_t found = (*rdi).path().string().find(prefix);

    if (found != std::string::npos)
    {
      std::ifstream fin;
      fin.open((*rdi).path().string());

      if (fin.fail())
      {
        std::cout << "Input file opening failed.\n";
      }

      else
      {
        std::string key = "[1;33mTest_error[0m";

        while (!fin.eof())
        {
          std::string temp;
          getline(fin, temp);

          for (std::size_t i = 0; i < key.size(); i++)
          {
            if (temp[i] == key[i])
            {
              is_found = true;
              break;
            }
          }
        }
        fin.close();
      }
    }
  }
  ASSERT_EQ(is_found, true);
}

TEST_F(LogTest, Log_Info)
{
  hvr::Log::Create(exe_path + "/Log", "LogTest");
  hvr::Log::Log_Error("Test_Info");

  bool is_found = false;

  boost::filesystem::path p;
  std::string directory;
  std::string prefix = "Log_INFO";
  directory          = exe_path;

  boost::filesystem::recursive_directory_iterator rdi(directory);
  boost::filesystem::recursive_directory_iterator end_rdi;

  for (; rdi != end_rdi; rdi++)
  {
    std::size_t found = (*rdi).path().string().find(prefix);

    if (found != std::string::npos)
    {
      std::ifstream fin;
      fin.open((*rdi).path().string());

      if (fin.fail())
      {
        std::cout << "Input file opening failed.\n";
      }

      else
      {
        std::string key = "[1;33mTest_Info[0m";

        while (!fin.eof())
        {
          std::string temp;
          getline(fin, temp);

          for (std::size_t i = 0; i < key.size(); i++)
          {
            if (temp == key)
            {
              is_found = true;
              break;
            }
          }
        }
        fin.close();
      }
    }
  }
  ASSERT_EQ(is_found, true);
}

TEST_F(LogTest, Log_Warning)
{
  hvr::Log::Create(exe_path + "/Log", "LogTest");
  hvr::Log::Log_Error("Test_Warning");

  bool is_found = false;

  boost::filesystem::path p;
  std::string directory;
  std::string prefix = "Log_WARNING";
  directory          = exe_path;

  boost::filesystem::recursive_directory_iterator rdi(directory);
  boost::filesystem::recursive_directory_iterator end_rdi;

  for (; rdi != end_rdi; rdi++)
  {
    std::size_t found = (*rdi).path().string().find(prefix);

    if (found != std::string::npos)
    {
      std::ifstream fin;
      fin.open((*rdi).path().string());

      if (fin.fail())
      {
        std::cout << "Input file opening failed.\n";
      }

      else
      {
        std::string key = "[1;33mTest_Warning[0m";

        while (!fin.eof())
        {
          std::string temp;
          getline(fin, temp);
          for (std::size_t i = 0; i < key.size(); i++)
          {
            if (temp == key)
            {
              is_found = true;
              break;
            }
          }
        }
        fin.close();
      }
    }
  }
  ASSERT_EQ(is_found, true);
}
