#include <gtest/gtest.h>

#include "random.h"
#include "log.h"

int glob_argc;
char** glob_argv;

#include <fstream>

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  glob_argc = argc;
  glob_argv = argv;
  testing::InitGoogleTest(&argc, argv);

  srand(time(0));

  hlog = new Log::Log(Log::MEM);
  hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);
  hlog->setFeature(Log::FEATURE_PROFILE, true);

  std::ofstream outFile;
  outFile.open("trace.json", std::ios::out);
  hlog->setProfileStream(&outFile);

  int res = 0;

  {
    FUN();

    LOGU("Starting tests...");

    try {
      res = RUN_ALL_TESTS();
    } catch (...) {
      LOGUE("Other error");
    }
  }
  

  delete hlog;

  outFile.flush();
  outFile.close();

  return res;
}
