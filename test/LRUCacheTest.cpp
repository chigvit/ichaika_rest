#include "gtest/gtest.h"

#include "LRUCache.hpp"

TEST(LRUCache, _)
{
  LRUCache cache(2);

  cache.put(1, 1);
  cache.put(2, 2);
  EXPECT_EQ(cache.get(1), 1);
  cache.put(3, 3);
  EXPECT_EQ(cache.get(2), -1);
  cache.put(4, 4);
  EXPECT_EQ(cache.get(1), -1);
  EXPECT_EQ(cache.get(3), 3);
  EXPECT_EQ(cache.get(4), 4);
}