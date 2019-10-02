// Copyright 2019 HypeVR

#ifndef UNIT_TEST_LOG_INCLUDE_LOGTEST_H_
#define UNIT_TEST_LOG_INCLUDE_LOGTEST_H_

HVR_WINDOWS_DISABLE_ALL_WARNING
#include "gtest/gtest.h"
HVR_WINDOWS_ENABLE_ALL_WARNING

class LogTest : public ::testing::Test
{
 protected:
  LogTest();
  ~LogTest() override;

  void SetUp() override;
  void TearDown() override;
};

#endif  // UNIT_TEST_LOG_INCLUDE_LOGTEST_H_
