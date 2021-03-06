// Copyright 2019 HypeVR

HVR_WINDOWS_DISABLE_ALL_WARNING
#include <iostream>
#include "Hvr/Log/Log.h"
HVR_WINDOWS_ENABLE_ALL_WARNING

void readme()
{
  hvr::Log::Log_Error(1, "msjhfg", 34, hvr::Log::endl, "sdkufgti");
  hvr::Log::Log_Error("NewLine");
  hvr::Log::Log_Error("NewLine1");
  hvr::Log::Log_Error("NewLine2");

  hvr::Log::Log_Warning(1, "msjhfg", 34, "sdkufgti");
  hvr::Log::Log_Warning("NewLine");
  hvr::Log::Log_Warning("NewLine1");
  hvr::Log::Log_Warning("NewLine2");

  hvr::Log::Log_Info(1, "msjhfg", 34, hvr::Log::endl, "sdkufgti");
  hvr::Log::Log_Info("NewLine");
  hvr::Log::Log_Info("NewLine1");
  hvr::Log::Log_Info("NewLine2");
}

int main(int argc, char **argv)
{
  hvr::Log::Create(argv[0], false);

  if (argc < 4)
  {
    readme();
    return -1;
  }

  return 0;
}
