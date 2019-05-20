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

TEST(TestGetValueLValueRef, IdentifierTest)
{
	const CarId car1("MyCar");
	EXPECT_EQ(car1.GetValue(), "MyCar");
}


TEST(TestGetValueRValueRef, IdentifierTest)
{
	const std::string c1("MyCar");
	const std::string& c2 = CarId("MyCar").GetValue();
	EXPECT_EQ(c1, c2);
}
