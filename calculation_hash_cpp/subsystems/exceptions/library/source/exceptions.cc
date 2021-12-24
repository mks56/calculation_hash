#include <exceptions.h>

#include <iomanip>
#include <iostream>
#include <utility>

#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast.hpp>

const std::string Exceptions::kDebugPath = "/tmp/exceptions.txt";
bool Exceptions::is_first_exception_ = true;

Exceptions::Exceptions(std::string origin_function,
                       int32_t function_line,
                       int32_t error_code)
    : origin_function_(std::move(origin_function)),
      error_code_(error_code),
      line_(function_line) {}

Exceptions::Exceptions(std::string origin_function,
                       int32_t function_line,
                       int32_t error_code,
                       std::string file,
                       std::string function,
                       std::string info)
    : file_(std::move(file)),
      function_(std::move(function)),
      info_(std::move(info)),
      origin_function_(std::move(origin_function)),
      error_code_(error_code),
      line_(function_line) {}

static std::string GetCurrentTime() {
  auto current_time = std::time(0);
  return boost::lexical_cast<std::string>(
      std::put_time(std::gmtime(&current_time), "%Y-%m-%d %X"));
}

template <typename T>
static std::string ToString(T number) {
  std::ostringstream stream;
  stream << number;
  return stream.str();
}

void Exceptions::ShowDebug(const DebugType& debug_flags) const {
  std::string error_string =
      GetCurrentTime() + " " + "[" + file_ + ":" + ToString<int32_t>(line_)

      + "]" + " exception occurred " + function_ + "()->" + origin_function_ +
      " with error code " +

      ToString<int32_t>(error_code_) + " with info: " + info_ + "\n";

  std::string error_utf8_string = error_string;
  std::string error_std_string = error_string;

  if (debug_flags == kPrint) {
    std::cout << error_std_string;
  }

  if (debug_flags == kSaveToFile) {
    if (is_first_exception_) {
      is_first_exception_ = false;
      InitNewSession();
    }
    WriteToFile(error_utf8_string);
  }
}

std::string Exceptions::NewSessionText() {
  static const std::string kSeparate =
      "\n=============================================================\n";
  static const std::string kNewSession =
      " ][                   New Debug Session                   ][\n";
  static const std::string kCurrentTime = " ][           Current time: ";
  static const std::string kCurrentTimeLastPart = "           ][\n";
  return kSeparate + kNewSession + kCurrentTime + GetCurrentTime() +
         kCurrentTimeLastPart + kSeparate;
}

void Exceptions::WriteToFile(const std::string& string_data) {
  boost::filesystem::ofstream file_stream;
  boost::filesystem::path path(kDebugPath);
  file_stream.open(path, std::ios_base::app);

  if (!file_stream.is_open()) {
    std::cout << "Can't write to " << Exceptions::kDebugPath << std::endl;
    return;
  }
  file_stream << string_data;
  file_stream.close();
}

void Exceptions::InitNewSession() { WriteToFile(NewSessionText()); }

const char* Exceptions::what() const noexcept {
  return "Exceptions occurred, call ShowDebug() for more details";
}

int32_t Exceptions::ErrorCode() const { return error_code_; }

std::string Exceptions::Info() const { return info_; }
