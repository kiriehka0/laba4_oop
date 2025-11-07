#pragma once
#include "figure.h"
#include <cmath>

template<typename T, typename = std::enable_if_t<is_scalar<T>::value>>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T radius_;
    
public:
    Octagon(T x = 0, T y = 0, T radius = 1) 
        : center_(std::make_unique<Point<T>>(x, y)), radius_(radius) {}
    
    Octagon(const Point<T>& center, T radius) 
        : center_(std::make_unique<Point<T>>(center)), radius_(radius) {}
    
    Octagon(const Octagon& other)
        : center_(std::make_unique<Point<T>>(*other.center_)), radius_(other.radius_) {}
    
    Octagon& operator=(const Octagon& other) {
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
        return 2 * radius_ * radius_ * (1 + std::sqrt(2));
    }
    
    void print_vertices() const override {
        std::cout << "Octagon vertices: ";
        for (int i = 0; i < 8; ++i) {
            double angle = 2 * M_PI * i / 8;
            T x = center_->x() + radius_ * std::cos(angle);
            T y = center_->y() + radius_ * std::sin(angle);
            std::cout << "(" << x << ", " << y << ") ";
        }
        std::cout << std::endl;
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Octagon<T>>(*this);
    }
    
    std::string name() const override { return "Octagon"; }
    
    bool operator==(const Figure<T>& other) const override {
        const Octagon* other_oct = dynamic_cast<const Octagon*>(&other);
        if (!other_oct) return false;
        return *center_ == *other_oct->center_ && radius_ == other_oct->radius_;
    }
    
    T radius() const { return radius_; }
    Point<T> center() const { return *center_; }
};
