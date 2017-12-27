// Copyright 2017 Ahmad Hasan

#include "LogTest.h"

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

extern std::string exe_path;

LogTest::LogTest()
{
}

LogTest::~LogTest()
{
}

void LogTest::SetUp()
{
}

void LogTest::TearDown()
{
}

TEST_F(LogTest, Log_Error)
{
  hvr::Log::Create("LogTest", "LogTest");

  hvr::Log::Log_Error("Test_error");

  bool is_found = false;

  boost::filesystem::path p;
  std::string directory;
  std::string extension = ".log";
  std::string prefix    = "LOG__error";

  directory = "/home/hypevr/hvr-log/build/unit-test/";

  boost::filesystem::recursive_directory_iterator rdi(directory);
  boost::filesystem::recursive_directory_iterator end_rdi;

  for (; rdi != end_rdi; rdi++)
  {
    if (extension.compare((*rdi).path().extension().string()) == 0)
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
          std::string key = "Test_error";

          while (!fin.eof())
          {
            std::string temp = "";
            getline(fin, temp);

            for (size_t i = 0; i < key.size(); i++)
            {
              if (temp[i] == key[i]) is_found = true;
              break;
            }
          }
          fin.close();
        }
      }
    }
  }
  ASSERT_EQ(is_found, true);
}

TEST_F(LogTest, Log_Info)
{
  hvr::Log::Create("LogTest", "LogTest");

  hvr::Log::Log_Error("Test_Info");

  bool is_found = false;

  boost::filesystem::path p;
  std::string directory;
  std::string extension = ".log";
  std::string prefix    = "LOG__info";

  directory = "/home/hypevr/hvr-log/build/unit-test/";

  boost::filesystem::recursive_directory_iterator rdi(directory);
  boost::filesystem::recursive_directory_iterator end_rdi;

  for (; rdi != end_rdi; rdi++)
  {
    if (extension.compare((*rdi).path().extension().string()) == 0)
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
          std::string key = "Test_Info";

          while (!fin.eof())
          {
            std::string temp = "";
            getline(fin, temp);

            for (size_t i = 0; i < key.size(); i++)
            {
              if (temp[i] == key[i]) is_found = true;
              break;
            }
          }
          fin.close();
        }
      }
    }
  }
  ASSERT_EQ(is_found, true);
}

TEST_F(LogTest, Log_Warning)
{
  hvr::Log::Create("LogTest", "LogTest");

  hvr::Log::Log_Error("Test_Warning");

  bool is_found = false;

  boost::filesystem::path p;
  std::string directory;
  std::string extension = ".log";
  std::string prefix    = "LOG__warning";

  directory = "/home/hypevr/hvr-log/build/unit-test/";

  boost::filesystem::recursive_directory_iterator rdi(directory);
  boost::filesystem::recursive_directory_iterator end_rdi;

  for (; rdi != end_rdi; rdi++)
  {
    if (extension.compare((*rdi).path().extension().string()) == 0)
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
          std::string key = "Test_Warning";

          while (!fin.eof())
          {
            std::string temp = "";
            getline(fin, temp);

            for (size_t i = 0; i < key.size(); i++)
            {
              if (temp[i] == key[i]) is_found = true;
              break;
            }
          }
          fin.close();
        }
      }
    }
  }
  ASSERT_EQ(is_found, true);
}
