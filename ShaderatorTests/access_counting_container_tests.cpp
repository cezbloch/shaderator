#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING 

#include "gtest/gtest.h"

#define TRACE_ACCESS
#include "shaderator.h"

TEST(AccessCountingContainer, can_detect_element_read)
{
  AccessCountingContainer<int> buffer(4);
  auto el = buffer[0];

  EXPECT_EQ(buffer.get_read_count(0), 1);
  EXPECT_EQ(buffer.get_write_count(0), 0);
}

TEST(AccessCountingContainer, can_detect_element_write)
{
  AccessCountingContainer<int> buffer(4);
  buffer[0] = 1;

  EXPECT_EQ(buffer.get_read_count(0), 0);
  EXPECT_EQ(buffer.get_write_count(0), 1);
}