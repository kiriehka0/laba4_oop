#include <gtest/gtest.h>
#include "array.h"
#include "octagon.h"
#include "triangle.h"
#include "square.h"

TEST(ArrayTest, AddAndSize) {
    Array<Figure<int>> figures;
    EXPECT_EQ(figures.size(), 0);
    
    figures.add(std::make_shared<Octagon<int>>(0, 0, 1));
    figures.add(std::make_shared<Triangle<int>>(1, 1, 2));
    
    EXPECT_EQ(figures.size(), 2);
}

TEST(ArrayTest, Access) {
    Array<Figure<int>> figures;
    auto oct = std::make_shared<Octagon<int>>(0, 0, 5);
    figures.add(oct);
    
    EXPECT_EQ(figures[0]->geometric_center(), Point<int>(0, 0));
}

TEST(ArrayTest, Remove) {
    Array<Figure<int>> figures;
    figures.add(std::make_shared<Octagon<int>>(0, 0, 1));
    figures.add(std::make_shared<Triangle<int>>(1, 1, 2));
    figures.add(std::make_shared<Square<int>>(2, 2, 3));
    
    figures.remove(1);
    EXPECT_EQ(figures.size(), 2);
    EXPECT_EQ(figures[1]->geometric_center(), Point<int>(2, 2));
}

TEST(ArrayTest, Clear) {
    Array<Figure<int>> figures;
    figures.add(std::make_shared<Octagon<int>>(0, 0, 1));
    figures.add(std::make_shared<Triangle<int>>(1, 1, 2));
    
    figures.clear();
    EXPECT_EQ(figures.size(), 0);
}

TEST(ArrayTest, TotalArea) {
    Array<Figure<int>> figures;
    figures.add(std::make_shared<Square<int>>(0, 0, 1)); // area = 2
    figures.add(std::make_shared<Square<int>>(0, 0, 2)); // area = 8
    
    EXPECT_NEAR(total_area(figures), 10.0, 1e-9);
}

TEST(ArrayTest, MoveSemantics) {
    Array<Figure<int>> source;
    source.add(std::make_shared<Square<int>>(0, 0, 1));
    
    Array<Figure<int>> destination = std::move(source);
    EXPECT_EQ(source.size(), 0);
    EXPECT_EQ(destination.size(), 1);
}

TEST(ArrayTest, CopySemantics) {
    Array<Figure<int>> original;
    original.add(std::make_shared<Triangle<int>>(0, 0, 2));
    
    Array<Figure<int>> copy = original;
    EXPECT_EQ(original.size(), 1);
    EXPECT_EQ(copy.size(), 1);
    EXPECT_TRUE(*original[0] == *copy[0]);
}
