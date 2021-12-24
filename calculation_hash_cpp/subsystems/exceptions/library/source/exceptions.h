#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <chrono>
#include <exception>
#include <string>

#define CHECK_RESULT(FunctionName, expected)                               \
  do {                                                                     \
    auto function_result = FunctionName;                                   \
    if (function_result != expected) {                                     \
      throw Exceptions(#FunctionName, __LINE__, function_result, __FILE__, \
                       __FUNCTION__);                                      \
    }                                                                      \
  } while (0)

#define CHECK_RESULT_WITH_INFO(FunctionName, expected, INFO)               \
  do {                                                                     \
    auto function_result = FunctionName;                                   \
    if (function_result != expected) {                                     \
      throw Exceptions(#FunctionName, __LINE__, function_result, __FILE__, \
                       __FUNCTION__, INFO);                                \
    }                                                                      \
  } while (0)

#define REPORT_ISSUE(INFO)                                               \
  do {                                                                   \
    throw Exceptions("true", __LINE__, 1, __FILE__, __FUNCTION__, INFO); \
  } while (0)

#define CHECK_RESULT_EXPECT_TRUE(FunctionName, INFO)                        \
  do {                                                                      \
    auto function_result = FunctionName;                                    \
    if (!function_result) {                                                 \
      throw Exceptions(#FunctionName, __LINE__, -1, __FILE__, __FUNCTION__, \
                       INFO);                                               \
    }                                                                       \
  } while (0)

class Exceptions final : public std::exception {
 public:
  enum DebugType {
    kDebug = 2,
    kPrint = 4,
    kSaveToFile = 8,
    kDebugAndSave = kDebug | kSaveToFile
  };

  Exceptions() = default;

  Exceptions(std::string origin_function,
             int32_t function_line,
             int32_t error_code);

  Exceptions(std::string origin_function,
             int32_t function_line,
             int32_t error_code,
             std::string file,
             std::string function,
             std::string info = {});

  static void InitNewSession();
  static void WriteToFile(const std::string& string_data);
  [[nodiscard]] const char* what() const noexcept override;

  void ShowDebug(const DebugType& debug_flags = kDebugAndSave) const;
  [[nodiscard]] int32_t ErrorCode() const;
  [[nodiscard]] std::string Info() const;

 private:
  static std::string NewSessionText();

  static const std::string kDebugPath;

  static bool is_first_exception_;

  std::string file_;
  std::string function_;
  std::string info_;
  std::string origin_function_;

  int32_t error_code_ = 0;
  int32_t line_ = 0;
};

#endif  // EXCEPTIONS_H
