#include "parser.hpp"

#include <vector>

#include "gtest/gtest.h"

using Tokens = std::vector<std::string>;

TEST(ParserTest, Tokeniser)
{
  std::string no_words{""};
  Tokens no_words_tok{tokenise(no_words)};
  ASSERT_TRUE(no_words_tok.empty());

  std::string one_word{"hello"};
  Tokens one_word_tok{tokenise(one_word)};
  ASSERT_EQ(one_word_tok.size(), 1);
  ASSERT_EQ(one_word_tok[0], "hello");

  std::string two_words{"hello hi"};
  Tokens two_words_tok{tokenise(two_words)};
  ASSERT_EQ(two_words_tok.size(), 2);
  ASSERT_EQ(two_words_tok[0], "hello");
  ASSERT_EQ(two_words_tok[1], "hi");

  std::string three_words{"hello hi yo"};
  Tokens three_words_tok{tokenise(three_words)};
  ASSERT_EQ(three_words_tok.size(), 3);
  ASSERT_EQ(three_words_tok[0], "hello");
  ASSERT_EQ(three_words_tok[1], "hi");
  ASSERT_EQ(three_words_tok[2], "yo");
}

TEST(ParserTest, Command)
{
  std::string three_words{"hello hi yo"};
  Tokens three_words_tok{tokenise(three_words)};
  Command cmd = populateCommand(three_words_tok);
  ASSERT_EQ(cmd.executable, "hello");
  ASSERT_EQ(cmd.args.size(), 2);
}
