// Copyright 2017 Ahmad Hasan

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <iostream>
#include "Hvr/Log/Log.h"
HVR_WINDOWS_ENABLE_ALL_WARNING

void readme()
{
  hvr::Log::Log_Error(1, "msjhfg", 34, hvr::Log::hvr_endl, "sdkufgti");
  hvr::Log::Log_Error("NewLine");
  hvr::Log::Log_Error("NewLine1");
  hvr::Log::Log_Error("NewLine2");
}

int main(int argc, char **argv)
{
  hvr::Log::Create("/home/hypevr/hvr-log/GlogSample", argv[0]);

  if (argc < 4)
  {
    readme();
    return -1;
  }

  return 0;
}
