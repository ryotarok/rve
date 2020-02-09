#include "gtest/gtest.h"

extern "C" {
#include "core/codetranslator.h"
}

// helper

// test

TEST(codetranslator, new_and_delete) {
  codetranslator_t *translator = codetranslator_new();
  ASSERT_TRUE(NULL != translator);
  codetranslator_delete(translator);
}

TEST(codetranslator, translate_empty) {}
