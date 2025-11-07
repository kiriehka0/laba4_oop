#pragma once
#include "point.h"
#include <memory>
#include <string>

template<typename T, typename = std::enable_if_t<is_scalar<T>::value>>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point<T> geometric_center() const = 0;
    virtual double area() const = 0;
    virtual void print_vertices() const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
    virtual std::string name() const = 0;
    
    explicit operator double() const {
        return area();
    }
    
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }
};
