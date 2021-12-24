#include <QCoreApplication>

#include <basic_functional.h>
#include <input_data.h>

int main(int argc, char* argv[]) {
  QCoreApplication application(argc, argv);

  InputData input_data;
  input_data.SetInputData();

  BasicFunctional basic_functional(
      input_data.GetPathToReadFile(), input_data.GetDirectoryToWriteFile(),
      input_data.GetFileNameToWriteFile(), input_data.GetBlockSizeForRead());
  basic_functional.GetSignatureFile();

  return application.exec();
}
