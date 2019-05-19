#include "pch.h"
#include "../CppUtils/Identifier.h"

DEFINE_IDENTIFIER(CarId, std::string);

TEST(TestEqualityOperator, TestName)
{
	const CarId car1("MyCar");
	const CarId car2("MyCar");
	EXPECT_TRUE(car1 == car2);
}

TEST(TestInEqualityOperator, TestName)
{
	const CarId car1("MyCar1");
	const CarId car2("MyCar2");
	EXPECT_TRUE(car1 != car2);
}