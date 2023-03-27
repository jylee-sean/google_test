


#include "testHeader.h"

class mock_comst : public comst
{
	public:

	MOCK_METHOD(copi&, pin, (), (override));
	MOCK_METHOD(copi&, pout, (), (override));
	MOCK_METHOD(bool, wait_for, (size_t ncycles, std::chrono::steady_clock::duration timeout), (override));
	MOCK_METHOD(ssize_t, readpdo, (copi& pi, uint8_t* dst, size_t bit_offset, size_t bit_size), (override));
	MOCK_METHOD(ssize_t, writepdo, (copi& pi, uint8_t* const src, size_t bit_offset, size_t bit_size), (override));
	MOCK_METHOD(ssize_t, readsdo, (uint16_t slave_id, uint16_t index, uint8_t sub_index, uint8_t *dst, size_t bit_size), (override));
	MOCK_METHOD(ssize_t, writesdo, (uint16_t slave_id, uint16_t index, uint8_t sub_index, uint8_t *src, size_t bit_size), (override));
	MOCK_METHOD(const char*, _sync, (), (override));
	MOCK_METHOD(const char*, _evnt, (), (override));
};