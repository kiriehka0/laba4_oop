#pragma once
#include "figure.h"
#include <cmath>

template<typename T, typename = std::enable_if_t<is_scalar<T>::value>>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T radius_;
    
public:
    Triangle(T x = 0, T y = 0, T radius = 1) 
        : center_(std::make_unique<Point<T>>(x, y)), radius_(radius) {}
    
    Triangle(const Point<T>& center, T radius) 
        : center_(std::make_unique<Point<T>>(center)), radius_(radius) {}
    
    Triangle(const Triangle& other)
        : center_(std::make_unique<Point<T>>(*other.center_)), radius_(other.radius_) {}
    
    Triangle& operator=(const Triangle& other) {
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
        return (3 * std::sqrt(3) / 4) * radius_ * radius_;
    }
    
    void print_vertices() const override {
        std::cout << "Triangle vertices: ";
        for (int i = 0; i < 3; ++i) {
            double angle = 2 * M_PI * i / 3 - M_PI / 2;
            T x = center_->x() + radius_ * std::cos(angle);
            T y = center_->y() + radius_ * std::sin(angle);
            std::cout << "(" << x << ", " << y << ") ";
        }
        std::cout << std::endl;
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Triangle<T>>(*this);
    }
    
    std::string name() const override { return "Triangle"; }
    
    bool operator==(const Figure<T>& other) const override {
        const Triangle* other_tri = dynamic_cast<const Triangle*>(&other);
        if (!other_tri) return false;
        return *center_ == *other_tri->center_ && radius_ == other_tri->radius_;
    }
    
    T radius() const { return radius_; }
    Point<T> center() const { return *center_; }
};
