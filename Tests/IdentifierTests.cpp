#include "pch.h"
#include "../CppUtils/Source/Identifier.h"

DEFINE_IDENTIFIER(CarId, std::string);


TEST(TestEqualityOperator, IdentifierTest)
{
	const CarId car1("MyCar");
	const CarId car2("MyCar");
	EXPECT_TRUE(car1 == car2);
}

TEST(TestInEqualityOperator, IdentifierTest)
{
	const CarId car1("MyCar1");
	const CarId car2("MyCar2");
	EXPECT_TRUE(car1 != car2);
}

TEST(TestCopyConstructor, IdentifierTest)
{
	const CarId car1("MyCar");
	const CarId car2(car1);
	EXPECT_TRUE(car1 == car2);
}

TEST(TestCopyConstructorWithNonConstArg, IdentifierTest)
{
	CarId car1("MyCar");
	const CarId car2(car1);
	EXPECT_TRUE(car1 == car2);
}

TEST(TestCopyAssignementOperator, IdentifierTest)
{
	const CarId car1("MyCar");
	const CarId car2 = car1;
	EXPECT_TRUE(car1 == car2);
}

TEST(TestCopyAssignementOperatorWithNonConstArg, IdentifierTest)
{
	CarId car1("MyCar");
	const CarId car2 = car1;
	EXPECT_TRUE(car1 == car2);
}