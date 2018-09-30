#pragma once
#include "autotest.h"
#include <cstddef>

class HuffmanTest : public Test {
public:
    void runAllTests();
    void test_count_freq();
    void test_build_tree();
    void test_build_codes();
    void test_coder_decoder();
};

