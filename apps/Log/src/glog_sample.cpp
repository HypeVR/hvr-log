// Copyright 2017 Ahmad Hasan

#include "Hvr/Log/Log.h"
void readme()
{
  hvr::Log::Log_Error(
      " Usage: ./exec <path/to/xml> <start_frame_number> <end_frame_number>");
}

int main(int argc, char **argv)
{
  hvr::Log::Create("glog_sample", argv[0]);

  if (argc < 4)
  {
    readme();
    return -1;
  }
}
