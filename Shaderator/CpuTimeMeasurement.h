// Copyright (c) 2017 KeesWare (PL)
#pragma once

#include <chrono>
#include <string>

class CpuTimeMeasurement {
public:
  explicit CpuTimeMeasurement(const std::string& text);
  virtual ~CpuTimeMeasurement();
private:
  std::string m_text;
  std::chrono::time_point<std::chrono::system_clock> m_start;
  std::chrono::time_point<std::chrono::system_clock> m_end;
};
