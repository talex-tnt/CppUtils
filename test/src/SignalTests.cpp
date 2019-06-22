#include "gtest/gtest.h"
#include "cpp-utils/Identifier.h"
#include "cpp-utils/Signal.h"

namespace
{

void square(int& value) { value *= value; }

TEST(SignalTest, myTest)
{
	int value = 0;
	utils::Signal<int> sig;
	auto c = sig.Connect([ &value ] (int v) { value += v; });

	const int delta = 100;
	sig.Emit(delta);

	EXPECT_EQ(value, delta);
}


TEST(SignalTest, myTest2)
{
	int value = 10;
	
	int expected = value;
	square(expected);
	
	utils::Signal<int&> sig;
	auto c = sig.Connect(square);

	sig.Emit (value);

	EXPECT_EQ(value, expected);

}

}

