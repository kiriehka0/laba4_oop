#include <iostream>
#include <limits>
#include "point.h"
#include "figure.h"
#include "octagon.h"
#include "triangle.h"
#include "square.h"
#include "array.h"

// Объявления функций
void demonstrate_move_semantics();
void demonstrate_array_types();
void demonstrate_figure_operations();

template<typename T>
std::shared_ptr<Figure<T>> create_octagon() {
    T x, y, radius;
    std::cout << "Enter Octagon center (x y): ";
    std::cin >> x >> y;
    std::cout << "Enter radius: ";
    std::cin >> radius;
    return std::make_shared<Octagon<T>>(x, y, radius);
}

template<typename T>
std::shared_ptr<Figure<T>> create_triangle() {
    T x, y, radius;
    std::cout << "Enter Triangle center (x y): ";
    std::cin >> x >> y;
    std::cout << "Enter radius: ";
    std::cin >> radius;
    return std::make_shared<Triangle<T>>(x, y, radius);
}

template<typename T>
std::shared_ptr<Figure<T>> create_square() {
    T x, y, radius;
    std::cout << "Enter Square center (x y): ";
    std::cin >> x >> y;
    std::cout << "Enter radius: ";
    std::cin >> radius;
    return std::make_shared<Square<T>>(x, y, radius);
}

template<typename T>
void interactive_menu() {
    Array<Figure<T>> figures;
    int choice;
    
    do {
        std::cout << "\n=== Interactive Menu ===" << std::endl;
        std::cout << "1. Add Octagon" << std::endl;
        std::cout << "2. Add Triangle" << std::endl;
        std::cout << "3. Add Square" << std::endl;
        std::cout << "4. Print all figures" << std::endl;
        std::cout << "5. Calculate total area" << std::endl;
        std::cout << "6. Remove figure by index" << std::endl;
        std::cout << "7. Clear all figures" << std::endl;
        std::cout << "8. Demonstrate move semantics" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                figures.add(create_octagon<T>());
                std::cout << "Octagon added." << std::endl;
                break;
            case 2:
                figures.add(create_triangle<T>());
                std::cout << "Triangle added." << std::endl;
                break;
            case 3:
                figures.add(create_square<T>());
                std::cout << "Square added." << std::endl;
                break;
            case 4:
                print_figures_info(figures);
                break;
            case 5:
                std::cout << "Total area: " << total_area(figures) << std::endl;
                break;
            case 6: {
                size_t index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                if (index < figures.size()) {
                    figures.remove(index);
                    std::cout << "Figure removed." << std::endl;
                } else {
                    std::cout << "Invalid index!" << std::endl;
                }
                break;
            }
            case 7:
                figures.clear();
                std::cout << "All figures cleared." << std::endl;
                break;
            case 8:
                demonstrate_move_semantics();
                break;
            case 0:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);
}

void demonstrate_move_semantics() {
    std::cout << "\n=== Move Semantics Demonstration ===" << std::endl;
    
    // Создаем маленький массив
    Array<Figure<int>> small_array;
    small_array.add(std::make_shared<Square<int>>(0, 0, 2));
    small_array.add(std::make_shared<Triangle<int>>(1, 1, 3));
    
    std::cout << "Small array size: " << small_array.size() << std::endl;
    std::cout << "Small array capacity: " << small_array.capacity() << std::endl;
    
    // Демонстрация перемещения
    Array<Figure<int>> large_array = std::move(small_array);
    
    std::cout << "After move:" << std::endl;
    std::cout << "Small array size: " << small_array.size() << std::endl;
    std::cout << "Large array size: " << large_array.size() << std::endl;
    std::cout << "Large array capacity: " << large_array.capacity() << std::endl;
    
    // Демонстрация работы с перемещенным массивом
    std::cout << "Figures in large array:" << std::endl;
    print_figures_info(large_array);
}

void demonstrate_array_types() {
    std::cout << "\n=== Array Types Demonstration ===" << std::endl;
    
    // Array<Figure<int>> - базовый тип
    Array<Figure<int>> figure_array;
    figure_array.add(std::make_shared<Octagon<int>>(0, 0, 5));
    figure_array.add(std::make_shared<Triangle<int>>(1, 1, 3));
    figure_array.add(std::make_shared<Square<int>>(2, 2, 4));
    
    std::cout << "Array<Figure<int>> demonstration:" << std::endl;
    print_figures_info(figure_array);
    std::cout << "Total area: " << total_area(figure_array) << std::endl;
    
    // Array<Square<double>> - тип наследник
    Array<Square<double>> square_array;
    square_array.add(std::make_shared<Square<double>>(0.5, 0.5, 2.5));
    square_array.add(std::make_shared<Square<double>>(1.5, 1.5, 3.5));
    
    std::cout << "\nArray<Square<double>> demonstration:" << std::endl;
    std::cout << "Number of squares: " << square_array.size() << std::endl;
    for (size_t i = 0; i < square_array.size(); ++i) {
        std::cout << "Square " << i + 1 << " area: " << square_array[i]->area() << std::endl;
    }
}

void demonstrate_figure_operations() {
    std::cout << "\n=== Figure Operations Demonstration ===" << std::endl;
    
    Square<int> square1(0, 0, 5);
    Square<int> square2 = square1; // Copy
    Square<int> square3(1, 1, 3);
    
    std::cout << "square1 == square2: " << (square1 == square2) << std::endl;
    std::cout << "square1 == square3: " << (square1 == square3) << std::endl;
    
    // Приведение к double (площадь)
    double area = static_cast<double>(square1);
    std::cout << "Square area as double: " << area << std::endl;
    
    // Клонирование
    auto cloned = square1.clone();
    std::cout << "Cloned square area: " << cloned->area() << std::endl;
}

int main() {
    std::cout << "=== Geometric Figures Program ===" << std::endl;
    
    // Демонстрации
    demonstrate_array_types();
    demonstrate_figure_operations();
    demonstrate_move_semantics();
    
    // Интерактивное меню
    interactive_menu<double>();
    
    return 0;
}
