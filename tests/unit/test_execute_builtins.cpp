#include "execute_builtins.hpp"

#include "gtest/gtest.h"

TEST(isBuiltinTest, builtinsTrue)
{
  EXPECT_TRUE(isBuiltin("exit"));
  EXPECT_TRUE(isBuiltin("echo"));
  EXPECT_TRUE(isBuiltin("pwd"));
  EXPECT_TRUE(isBuiltin("cd"));
  EXPECT_TRUE(isBuiltin("type"));
}

TEST(isBuiltinTest, builtinsFalse)
{
  EXPECT_FALSE(isBuiltin("ls"));
  EXPECT_FALSE(isBuiltin("hello hi"));
  EXPECT_FALSE(isBuiltin("nvim"));
  EXPECT_FALSE(isBuiltin(""));
}
