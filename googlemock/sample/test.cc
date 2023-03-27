



#include "mock_test.h"





using namespace testing;

TEST(comst, mocking) {
  mock_comst mock;
	copi pi(100, copi::access_t::mutex);

//	EXPECT_CALL(mock, readpdo()).WillOnce(testing::Return(1));

//	EXPECT_CALL(mock, readpdo(Ref(pi), static_cast<uint8_t*>(nullptr), static_cast<size_t>(0), static_cast<size_t>(8)));//.WillRepeatedly(Return(8));

	EXPECT_CALL(mock, pin()).Times(1).WillRepeatedly(ReturnRef(pi));//Times(1);
    EXPECT_CALL(mock, wait_for(1, static_cast<std::chrono::steady_clock::duration>(10))).WillRepeatedly(Return (true));
    EXPECT_CALL(mock, _sync() ).WillRepeatedly(Return ("sync"));

	EXPECT_EQ((mock._sync()), "sync");
	EXPECT_EQ((mock.wait_for(1, static_cast<std::chrono::steady_clock::duration>(10))), false);

	EXPECT_EQ((mock.pin().size()), 100);


//   EXPECT_CALL(calc, Multiply(2, 3)).WillOnce(testing::Return(6));
//   EXPECT_EQ(calc.Add(2, 3), 5);
//   EXPECT_EQ(calc.Multiply(2, 3), 6);
}
