


//#include "Target.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>

class Calculator {
public:
  virtual ~Calculator() {}
  virtual int Add(int a, int b) const { return a + b; }
  virtual int Multiply(int a, int b) const { return a * b; }
};

class MockCalculator : public Calculator {
public:
  MOCK_CONST_METHOD2(Add, int(int a, int b));
  MOCK_CONST_METHOD2(Multiply, int(int a, int b));
};

TEST(CalculatorTest, AddAndMultiply) {
  MockCalculator calc;
  EXPECT_CALL(calc, Add(2, 3)).WillOnce(testing::Return(5));
  EXPECT_CALL(calc, Multiply(2, 3)).WillOnce(testing::Return(6));
  EXPECT_EQ(calc.Add(2, 3), 5);
  EXPECT_EQ(calc.Multiply(2, 3), 6);
}