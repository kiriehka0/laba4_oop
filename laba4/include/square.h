#pragma once
#include "figure.h"
#include <cmath>

template<typename T, typename = std::enable_if_t<is_scalar<T>::value>>
class Square : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T radius_;
    
public:
    Square(T x = 0, T y = 0, T radius = 1) 
        : center_(std::make_unique<Point<T>>(x, y)), radius_(radius) {}
    
    Square(const Point<T>& center, T radius) 
        : center_(std::make_unique<Point<T>>(center)), radius_(radius) {}
    
    Square(const Square& other)
        : center_(std::make_unique<Point<T>>(*other.center_)), radius_(other.radius_) {}
    
    Square& operator=(const Square& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            radius_ = other.radius_;
        }
        return *this;
    }
    
    Point<T> geometric_center() const override {
        return *center_;
    }
    
    double area() const override {
        return 2 * radius_ * radius_;
    }
    
    void print_vertices() const override {
        std::cout << "Square vertices: ";
        for (int i = 0; i < 4; ++i) {
            double angle = 2 * M_PI * i / 4 - M_PI / 4;
            T x = center_->x() + radius_ * std::cos(angle);
            T y = center_->y() + radius_ * std::sin(angle);
            std::cout << "(" << x << ", " << y << ") ";
        }
        std::cout << std::endl;
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Square<T>>(*this);
    }
    
    std::string name() const override { return "Square"; }
    
    bool operator==(const Figure<T>& other) const override {
        const Square* other_sq = dynamic_cast<const Square*>(&other);
        if (!other_sq) return false;
        return *center_ == *other_sq->center_ && radius_ == other_sq->radius_;
    }
    
    T radius() const { return radius_; }
    Point<T> center() const { return *center_; }
};
