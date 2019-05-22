#include "pch.h"
#include "../CppUtils/Source/Identifier.h"

DEFINE_IDENTIFIER_WITH_INVALID_VALUE(CarId, std::string, "Null");
DEFINE_IDENTIFIER_WITH_INVALID_VALUE(BikeId, std::uint64_t, 0u);


TEST(InvalidableIdentifier_TestConstructors, InvalidableIdentifier_ConstructorNoParam)
{
	const CarId car;
	EXPECT_FALSE(car.IsValid());

	const BikeId bike;
	EXPECT_FALSE(bike.IsValid());
}

TEST(InvalidableIdentifier_TestConstructors, InvalidableIdentifier_ConstructorWithValue)
{
	const CarId car("Car");
	EXPECT_TRUE(car.IsValid());

	const BikeId bike(1);
	EXPECT_TRUE(bike.IsValid());
}

TEST(InvalidableIdentifier_TestConstructors, InvalidableIdentifier_CopyConstructor)
{
	const CarId car1("MyCar");
	const CarId car2(car1);
	EXPECT_TRUE(car1.IsValid());
	EXPECT_TRUE(car1 == car2);
}

TEST(InvalidableIdentifier_TestConstructors, InvalidableIdentifier_CopyWithNonConstArg)
{
	CarId car1("MyCar");
	const CarId car2(car1);
	EXPECT_TRUE(car1.IsValid());
	EXPECT_TRUE(car2.IsValid());
	EXPECT_TRUE(car1 == car2);
}

TEST(InvalidableIdentifier_TestConstructors, MoveConstructor)
{
	CarId car1("MyCar");
	const CarId car2(std::move(car1));
	EXPECT_TRUE(car2.IsValid());
	EXPECT_EQ(car2, CarId("MyCar"));
	EXPECT_NE(car1, CarId("MyCar"));
}

TEST(InvalidableIdentifier_TestOperators, InvalidableIdentifier_Equality)
{
	const CarId car1("MyCar");
	const CarId car2("MyCar");
	EXPECT_TRUE(car1.IsValid());
	EXPECT_TRUE(car2.IsValid());
	EXPECT_TRUE(car1 == car2);
}

TEST(InvalidableIdentifier_TestOperators, InvalidableIdentifier_InEquality)
{
	const CarId car1("MyCar1");
	const CarId car2("MyCar2");
	EXPECT_TRUE(car1.IsValid());
	EXPECT_TRUE(car2.IsValid());
	EXPECT_TRUE(car1 != car2);
}

TEST(InvalidableIdentifier_TestOperators, InvalidableIdentifier_CopyAssignment)
{
	const CarId car1("MyCar");
	const CarId car2 = car1;
	EXPECT_TRUE(car1.IsValid());
	EXPECT_TRUE(car2.IsValid());
	EXPECT_TRUE(car1 == car2);
}

TEST(InvalidableIdentifier_TestOperators, InvalidableIdentifier_CopyAssignmentWithNonConstArg)
{
	CarId car1("MyCar");
	const CarId car2 = car1;
	EXPECT_TRUE(car1.IsValid());
	EXPECT_TRUE(car2.IsValid());
	EXPECT_TRUE(car1 == car2);
}

TEST(InvalidableIdentifier_TestOperators, InvalidableIdentifier_MoveAssignment)
{
	CarId car1("MyCar1");
	CarId car2("MyCar2");
	car2 = std::move(car1);
	EXPECT_TRUE(car2.IsValid());
	EXPECT_EQ(car2, CarId("MyCar1"));
	EXPECT_NE(car1, CarId("MyCar1"));
}

TEST(InvalidableIdentifier_TestAccessors, InvalidableIdentifier_GetValueLValueRef)
{
	const CarId car1("MyCar");
	EXPECT_EQ(car1.GetValue(), "MyCar");
}

TEST(InvalidableIdentifier_TestAccessors, InvalidableIdentifier_GetValueRValueRef)
{
	const std::string c1("MyCar");
	const std::string& c2 = CarId("MyCar").GetValue();
	EXPECT_EQ(c1, c2);
}
