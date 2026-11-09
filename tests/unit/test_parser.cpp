#include <string>
#include <vector>

#include "parser.hpp"

#include "gtest/gtest.h"

using Tokens = std::vector<std::string>;

TEST(ParserTest, TokeniserNoInput)
{
  Tokens t = tokenise("");
  ASSERT_TRUE(t.empty());
}

TEST(ParserTest, TokeniserOneArg)
{
  Tokens t = tokenise("hello");
  ASSERT_EQ(t.size(), 1u);
  EXPECT_EQ(t[0], "hello");
}

TEST(ParserTest, TokeniserTwoWordsOneArg)
{
  Tokens t = tokenise("\"hello hi\"");
  ASSERT_EQ(t.size(), 1u);
  EXPECT_EQ(t[0], "hello hi");
}

TEST(ParserTest, TokeniserTwoWordsTwoArgs)
{
  Tokens t = tokenise("hello hi");
  ASSERT_EQ(t.size(), 2u);
  EXPECT_EQ(t[0], "hello");
  EXPECT_EQ(t[1], "hi");
}

TEST(ParserTest, TokeniserTwoArgsWithDoubleQuote)
{
  Tokens t = tokenise("echo \"hello world\"");
  ASSERT_EQ(t.size(), 2u);
  EXPECT_EQ(t[0], "echo");
  EXPECT_EQ(t[1], "hello world");
}

TEST(ParserTest, TokeniserFourArgsWithDoubleQuote)
{
  Tokens t = tokenise("echo \"hello world\">foo.txt");
  ASSERT_EQ(t.size(), 4);
  EXPECT_EQ(t[0], "echo");
  EXPECT_EQ(t[1], "hello world");
  EXPECT_EQ(t[2], ">");
  EXPECT_EQ(t[3], "foo.txt");
}

TEST(ParserTest, TokeniserDoubleQuotesAndAppend)
{
  Tokens t = tokenise(R"("Hi ! " >>foo.txt)");
  ASSERT_EQ(t.size(), 3u);
  EXPECT_EQ(t[0], "Hi ! ");
  EXPECT_EQ(t[1], ">>");
  EXPECT_EQ(t[2], "foo.txt");
}

TEST(ParserTest, TokeniserSingleQuotesAndAppend)
{
  Tokens t = tokenise(R"(echo "My name is  '$USER' ">> foo.txt)");
  ASSERT_EQ(t.size(), 4u);
  EXPECT_EQ(t[0], "echo");
  EXPECT_EQ(t[1], "My name is  '$USER' ");
  EXPECT_EQ(t[2], ">>");
  EXPECT_EQ(t[3], "foo.txt");
}
