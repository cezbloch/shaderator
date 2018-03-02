// Copyright (c) 2017 KeesWare Cezary Bloch (PL)

#include "CpuTimeMeasurement.h"

CpuTimeMeasurement::CpuTimeMeasurement(const std::string& text)
  : m_text(text),
  m_start(std::chrono::system_clock::now()),
  m_end(std::chrono::system_clock::now())
{
}

CpuTimeMeasurement::~CpuTimeMeasurement()
{
  m_end = std::chrono::system_clock::now();
  const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start);
}
