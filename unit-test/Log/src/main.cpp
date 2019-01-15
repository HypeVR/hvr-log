// Copyright 2017 Ahmad Hasan

#include <string>

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "gtest/gtest.h"
HVR_WINDOWS_ENABLE_ALL_WARNING

std::string exe_path;  // NOLINT

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  exe_path = argv[0];

  // windows
  if (exe_path.find('\\') == std::string::npos &&
      exe_path.find('/') == std::string::npos)
  {
    exe_path = ".";
  }

  exe_path = exe_path.substr(0, exe_path.find_last_of("/\\"));

  return RUN_ALL_TESTS();
}
