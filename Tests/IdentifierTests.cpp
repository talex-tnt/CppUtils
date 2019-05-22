#include "pch.h"
#include "../CppUtils/Source/Identifier.h"

DEFINE_IDENTIFIER(CarId, std::string);


TEST(Identifier_TestConstructors, Identifier_CopyConstructor)
{

	const CarId car1("MyCar");
	const CarId car2(car1);
	EXPECT_TRUE(car1 == car2);
}

TEST(Identifier_TestConstructors, Identifier_CopyWithNonConstArg)
{
	CarId car1("MyCar");
	const CarId car2(car1);
	EXPECT_TRUE(car1 == car2);
}

TEST(Identifier_TestConstructors, Identifier_MoveConstructor)
{
	CarId car1("MyCar");
	const CarId car2(std::move(car1));
	EXPECT_EQ(car2, CarId("MyCar"));
	EXPECT_NE(car1, CarId("MyCar"));
}

TEST(Identifier_TestOperators, Identifier_Equality)
{
	const CarId car1("MyCar");
	const CarId car2("MyCar");
	EXPECT_TRUE(car1 == car2);
}

TEST(Identifier_TestOperators, Identifier_InEquality)
{
	const CarId car1("MyCar1");
	const CarId car2("MyCar2");
	EXPECT_TRUE(car1 != car2);
}

TEST(Identifier_TestOperators, Identifier_CopyAssignment)
{
	const CarId car1("MyCar");
	const CarId car2 = car1;
	EXPECT_TRUE(car1 == car2);
}

TEST(Identifier_TestOperators, Identifier_CopyAssignmentWithNonConstArg)
{
	CarId car1("MyCar");
	const CarId car2 = car1;
	EXPECT_TRUE(car1 == car2);
}

TEST(Identifier_TestOperators, Identifier_MoveAssignment)
{
	CarId car1("MyCar1");
	CarId car2("MyCar2");
	car2 = std::move(car1);
	EXPECT_EQ(car2, CarId("MyCar1"));
	EXPECT_NE(car1, CarId("MyCar1"));
}

TEST(Identifier_TestAccessors, Identifier_GetValueLValueRef)
{
	const CarId car1("MyCar");
	EXPECT_EQ(car1.GetValue(), "MyCar");
}

TEST(Identifier_TestAccessors, Identifier_GetValueRValueRef)
{
	const std::string c1("MyCar");
	const std::string& c2 = CarId("MyCar").GetValue();
	EXPECT_EQ(c1, c2);
}
