#include "circle.h"

int main() {
    double radius;
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius;
    Circle circle(radius);

    double area = circle.calculateArea();
    std::cout << "The area of the circle is: " << area << std::endl;
    
    
}
