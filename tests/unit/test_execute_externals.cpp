#include "execute_externals.hpp"

#include <gtest/gtest.h>
#include <string_view>

// Simulates bin file being found
std::string binFound(std::string_view) { return "usr/bin/binfile"; }

// Simulates bin file not being found (empty string)
std::string binNotFound(std::string_view) { return ""; }

TEST(isExternalTest, externalsTrue)
{
  EXPECT_TRUE(isExternal("ls", binFound));
  EXPECT_TRUE(isExternal("ls -l", binFound));
  EXPECT_TRUE(isExternal("cat", binFound));
}

TEST(isExternalTest, externalsFalse)
{
  EXPECT_FALSE(isExternal("", binNotFound));
  EXPECT_FALSE(isExternal("Hello hi", binNotFound));
}
