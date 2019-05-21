#include "pch.h"
#include "../CppUtils/Source/Identifier.h"

DEFINE_IDENTIFIER(CarId, std::string);


TEST(TestConstructors, CopyConstructor)
{
	const CarId car1("MyCar");
	const CarId car2(car1);
	EXPECT_TRUE(car1 == car2);
}

TEST(TestConstructors, CopyWithNonConstArg)
{
	CarId car1("MyCar");
	const CarId car2(car1);
	EXPECT_TRUE(car1 == car2);
}

TEST(TestConstructors, MoveConstructor)
{
	CarId car1("MyCar");
	const CarId car2(std::move(car1));
	EXPECT_EQ(car2, CarId("MyCar"));
	EXPECT_NE(car1, CarId("MyCar"));
}

TEST(TestOperators, Equality)
{
	const CarId car1("MyCar");
	const CarId car2("MyCar");
	EXPECT_TRUE(car1 == car2);
}

TEST(TestOperators, InEquality)
{
	const CarId car1("MyCar1");
	const CarId car2("MyCar2");
	EXPECT_TRUE(car1 != car2);
}

TEST(TestOperators, CopyAssignment)
{
	const CarId car1("MyCar");
	const CarId car2 = car1;
	EXPECT_TRUE(car1 == car2);
}

TEST(TestOperators, CopyAssignmentWithNonConstArg)
{
	CarId car1("MyCar");
	const CarId car2 = car1;
	EXPECT_TRUE(car1 == car2);
}

TEST(TestOperators, MoveAssignment)
{
	CarId car1("MyCar1");
	CarId car2("MyCar2");
	car2 = std::move(car1);
	EXPECT_EQ(car2, CarId("MyCar1"));
	EXPECT_NE(car1, CarId("MyCar1"));
}

TEST(TestAccessors, GetValueLValueRef)
{
	const CarId car1("MyCar");
	EXPECT_EQ(car1.GetValue(), "MyCar");
}

TEST(TestAccessors, GetValueRValueRef)
{
	const std::string c1("MyCar");
	const std::string& c2 = CarId("MyCar").GetValue();
	EXPECT_EQ(c1, c2);
}




