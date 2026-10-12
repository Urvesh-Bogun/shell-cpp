#include "parser.hpp"

#include <string>
#include <vector>

#include "gtest/gtest.h"

using Tokens = std::vector<std::string>;

TEST(ParserTest, TokeniserNoInput)
{
  Tokens t = tokenise("");
  ASSERT_TRUE(t.empty());
}

TEST(ParserTest, TokeniserOneWord)
{
  Tokens t = tokenise("hello");
  ASSERT_EQ(t.size(), 1u);
  EXPECT_EQ(t[0], "hello");
}

TEST(ParserTest, TokeniserTwoWords)
{
  Tokens t = tokenise("hello hi");
  ASSERT_EQ(t.size(), 2u);
  EXPECT_EQ(t[0], "hello");
  EXPECT_EQ(t[1], "hi");
}

TEST(ParserTest, TokeniserThreeWords)
{
  Tokens t = tokenise("hello hi yo");
  ASSERT_EQ(t.size(), 3u);
  EXPECT_EQ(t[0], "hello");
  EXPECT_EQ(t[1], "hi");
  EXPECT_EQ(t[2], "yo");
}
