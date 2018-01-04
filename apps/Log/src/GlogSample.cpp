// Copyright 2017 Ahmad Hasan

#include <iostream>
#include "Hvr/Log/Log.h"

void readme()
{
  hvr::Log::Log_Error(1, "msjhfg", 34, hvr::Log::hvr_endl, "sdkufgti");
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
