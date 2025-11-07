#include

#include "point.h"

TEST(PointTest, DefaultConstructor) {

Point p;

EXPECT_EQ(p.x(), 0);

EXPECT_EQ(p.y(), 0);

}

TEST(PointTest, ParameterizedConstructor) {

Point p(1.5, 2.5);

EXPECT_DOUBLE_EQ(p.x(), 1.5);

EXPECT_DOUBLE_EQ(p.y(), 2.5);

}

TEST(PointTest, Setters) {

Point p;

p.set_x(10);

p.set_y(20);

EXPECT_EQ(p.x(), 10);

EXPECT_EQ(p.y(), 20);

}

TEST(PointTest, Equality) {

Point p1(1, 2);

Point p2(1, 2);

Point p3(3, 4);

EXPECT_TRUE(p1 == p2);

EXPECT_FALSE(p1 == p3);

EXPECT_TRUE(p1!= p3);

}

TEST(PointTest, OutputStream) {

Point p(3, 4);

std::stringstream ss;

ss << p;

EXPECT_EQ(ss. str(), "(3, 4)");

}
