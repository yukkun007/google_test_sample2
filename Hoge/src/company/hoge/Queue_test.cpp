/* Copyright 2017 yukkun007 */
#include "company/hoge/Queue.h"
#include "gtest/gtest.h"

#ifdef _DEBUG
#pragma comment(lib, "gtestd.lib")
#else
#pragma comment(lib, "gtest.lib")
#endif

namespace company {
namespace hoge {

class QueueTest : public ::testing::Test {
 public:
    virtual void SetUp() {
        q1_.Enqueue(1);
        q2_.Enqueue(2);
        q2_.Enqueue(2);
        q3_.Enqueue(3);
        q3_.Enqueue(3);
        q3_.Enqueue(3);
    }

    virtual void TearDown() {
    }

    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
    Queue<int> q3_;
};

struct CalcCase {
  int value1;
  int value2;
  int expected_result;
};

class MyCalcTest : ::testing::TestWithParam<CalcCase> {
 public:
  MyCalc CreateObject(int value1, int value2) {
    MyCalc calc(value1, value2);
    return calc;
  }
 private:
};

TEST_P(MyCalcTest, Sample) {
  int version = 0;
  EProfile profile = EBadProfile;
  MyCalc calc = CreateObject(GetParam().value1, GetParam().value2);
  calc.CalculateAdd();
  const bool result = ParseVersionProfile(GetParam().input, &version, &profile);
  EXPECT_THAT(result, GetParam().success);
  if (result) {
    EXPECT_THAT(version, GetParam().expected_version);
    EXPECT_THAT(profile, GetParam().expected_profile);
  }
}

INSTANTIATE_TEST_CASE_P(OpenGLESCases, MyCalcTest,
                        ValuesIn(std::vector<CalcCase>{
                            {"100es", true, 100},
                            {"300es", true, 300},
                            {"310es", true, 310},
                            {"320es", true, 320},
                            {"99es", false, 0},
                            {"500es", false, 0},
                        }), );

TEST_F(QueueTest, IsEmptyInitially) {
    EXPECT_EQ(0, q0_.size());
    EXPECT_EQ(1, q1_.size());
    EXPECT_EQ(2, q2_.size());
    EXPECT_EQ(3, q3_.size());
}

}  // namespace hoge
}  // namespace company
