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

TEST(PopulateCommandTest, PopulateCommandNoInput)
{
  Tokens t = tokenise("");
  Command cmd = populateCommand(t);
  ASSERT_TRUE(cmd.executable.empty());
  ASSERT_TRUE(cmd.args.empty());
}

TEST(PopulateCommandTest, PopulateCommandOneExNoArgs)
{
  Tokens t = tokenise("hello");
  Command cmd = populateCommand(t);
  ASSERT_FALSE(cmd.executable.empty());
  EXPECT_EQ(cmd.executable, "hello");
  ASSERT_TRUE(cmd.args.empty());
}

TEST(PopulateCommandTest, PopulateCommandOneArg)
{
  Tokens t = tokenise("hello hi");
  Command cmd = populateCommand(t);
  ASSERT_FALSE(cmd.executable.empty());
  EXPECT_EQ(cmd.executable, "hello");
  ASSERT_EQ(cmd.args.size(), 1);
  EXPECT_EQ(cmd.args[0], "hi");
}

TEST(PopulateCommandTest, PopulateCommandTwoArgs)
{
  Tokens t = tokenise("hello hi yo");
  Command cmd = populateCommand(t);
  ASSERT_FALSE(cmd.executable.empty());
  EXPECT_EQ(cmd.executable, "hello");
  ASSERT_EQ(cmd.args.size(), 2);
  EXPECT_EQ(cmd.args[0], "hi");
  EXPECT_EQ(cmd.args[1], "yo");
}

TEST(PopulateCommandTest, PopulateCommandThreeArgs)
{
  Tokens t = tokenise("hello hi yo yoohoo");
  Command cmd = populateCommand(t);
  ASSERT_FALSE(cmd.executable.empty());
  EXPECT_EQ(cmd.executable, "hello");
  ASSERT_EQ(cmd.args.size(), 3);
  EXPECT_EQ(cmd.args[0], "hi");
  EXPECT_EQ(cmd.args[1], "yo");
  EXPECT_EQ(cmd.args[2], "yoohoo");
}
