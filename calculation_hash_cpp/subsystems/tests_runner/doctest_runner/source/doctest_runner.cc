#include <doctest_runner.h>

#define DOCTEST_CONFIG_IMPLEMENT
#include <cross_platform_doctest.h>

int RunDoctest(int argc, char* argv[]) {
  doctest::Context context;

  context.setOption("order-by", "name");
  context.applyCommandLine(argc, argv);

  return context.run();
}
