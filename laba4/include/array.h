#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <utility> 
#include "figure.h"

template<typename T>
class Array {
private:
    std::vector<std::shared_ptr<T>> data_;
    
public:
    Array() = default;
    
    // Конструктор копирования с перемещением
    Array(const Array& other) {
        data_.reserve(other.data_.size());
        for (const auto& item : other.data_) {
            data_.push_back(std::shared_ptr<T>(item->clone()));
        }
    }
    
    // Оператор присваивания с перемещением
    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            *this = std::move(temp);
        }
        return *this;
    }
    
    // Конструктор перемещения
    Array(Array&& other) noexcept = default;
    
    // Оператор перемещения
    Array& operator=(Array&& other) noexcept = default;
    
    void add(std::shared_ptr<T> item) {
        data_.push_back(std::move(item));
    }
    
    void remove(size_t index) {
        if (index < data_.size()) {
            data_.erase(data_.begin() + index);
        }
    }
    
    std::shared_ptr<T> operator[](size_t index) const {
        return data_.at(index);
    }
    
    size_t size() const {
        return data_.size();
    }
    
    size_t capacity() const {
        return data_.capacity();
    }
    
    void reserve(size_t new_capacity) {
        data_.reserve(new_capacity);
    }
    
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
    
    void clear() {
        data_.clear();
    }
};

template<typename T>
void print_figures_info(const Array<Figure<T>>& figures) {
    std::cout << "=== Figures Information ===" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        auto fig = figures[i];
        std::cout << "Figure " << i + 1 << " (" << fig->name() << "):" << std::endl;
        std::cout << "Geometric center: " << fig->geometric_center() << std::endl;
        fig->print_vertices();
        std::cout << "Area: " << fig->area() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

template<typename T>
double total_area(const Array<Figure<T>>& figures) {
    double total = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += figures[i]->area();
    }
    return total;
}
