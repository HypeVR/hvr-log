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

  return RUN_ALL_TESTS();
}
