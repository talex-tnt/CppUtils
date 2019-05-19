#include "pch.h"
#include "../CppUtils/Identifier.h"

class CarTrait{};
using CarId = utils::Identifier<CarTrait, std::string>;


TEST(TestEqualityOperator, TestName)
{
	CarId car1("MyCar");
	CarId car2("MyCar");
	EXPECT_TRUE(car1 == car2);
}

TEST(TestInEqualityOperator, TestName)
{
	CarId car1("MyCar1");
	CarId car2("MyCar2");
	EXPECT_TRUE(car1 != car2);
}