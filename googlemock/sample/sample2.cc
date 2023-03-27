#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Logger {
public:
  virtual ~Logger() {}
  virtual void Log(const std::string& message) const = 0;
};

class Calculator {
public:
  Calculator(Logger* logger) : logger_(logger) {}
  int Add(int a, int b) const {
    int result = a + b;
    logger_->Log("Addition: " + std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(result));
    return result;
  }
private:
  Logger* logger_;
};

class MockLogger : public Logger {
public:
  MOCK_CONST_METHOD1(Log, void(const std::string& message));
};

TEST(CalculatorTest, Add) {
  MockLogger logger;
  Calculator calc(&logger);

  EXPECT_CALL(logger, Log("Addition: 2 + 3 = 5")).Times(1);

  EXPECT_EQ(calc.Add(2, 3), 5);
}