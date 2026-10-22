#ifndef math_stuff_hpp
#define math_stuff_hpp

#include <cmath>
#include <stdexcept>
#include <vector>

namespace constants
{
    constexpr double pi = 3.14159;
    constexpr const double& π = pi;

    constexpr double eulers_number = 2.71828;
    constexpr const double& e = eulers_number;

    const double golden_ratio = (1 + sqrt(5)) / 2;
    const double& φ = golden_ratio;
    const double& phi = golden_ratio;

    const double silver_ratio = sqrt(2) + 1;
    const double& σ = silver_ratio;
 
    const double supergolden_ratio = ((1 + cbrt((29 + 3 * sqrt(93)) / 2) + cbrt((29 - 3 * sqrt(93)) / 2)) / 3);
    const double& ψ = supergolden_ratio;

    const double imaginary_number = sqrt(-1);
    const double& i = imaginary_number;
    // will show as nan

    const double connective_constant_for_the_hexagonal_lattice = sqrt(2 + sqrt(2));
    const double& µ = connective_constant_for_the_hexagonal_lattice;
}
namespace consts = constants;
namespace shapes{
    namespace two_dimensional{
        // 0/1 sides
        namespace circle{
            double circumference(double r){
                return 2 * constants::pi * r;
            }
            double area(double r){
                return constants::pi * pow(r, 2);
            }
        } 
        namespace ellipse{
            double circumference(double a, double b){
                return constants::pi * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
            }
            double area(double a, double b){
                return constants::pi * a * b;
            }
        }
        namespace oval = ellipse;
        // 3 sides
        namespace triangle{
            double side_c(double a, double b, double angle_in_degrees){
                double angle_in_radians = angle_in_degrees * (constants::pi / 180.0);
                return sqrt(pow(a, 2) + pow(b, 2) - 2 * a * b * cos(angle_in_radians));
            }
            double perimeter(double a, double b, double c){
                return a + b + c;
            }
            double perimeter(double base, double height){
                return base + 2 * sqrt(pow(height, 2) + pow(base / 2, 2));
            }
            double area(double base, double height){
                return 0.5 * base * height;
            }
            double area(double a, double b, double c){
                double s = (a + b + c) / 2;
                return sqrt(s * (s - a) * (s - b) * (s - c));
            }
            double area(double a, double b, double angle_in_degrees){
                double angle_in_radians = angle_in_degrees * (constants::pi / 180.0);
                return 0.5 * a * b * sin(angle_in_radians);
            }
        }
        // 4 sides
        namespace quadrilateral{
            double perimeter(double a, double b, double c, double d){
                return a + b + c + d;
            }
            double area(double a, double b, double c, double d, double angle_in_degrees){
                double angle_in_radians = angle_in_degrees * (constants::pi / 180.0);
                return 0.5 * (a * b * sin(angle_in_radians) + c * d * sin(angle_in_radians));
            }
            double area(double a, double b, double c, double d, double angle1_in_degrees, double angle2_in_degrees){
                double angle1_in_radians = angle1_in_degrees * (constants::pi / 180.0);
                double angle2_in_radians = angle2_in_degrees * (constants::pi / 180.0);
                return 0.5 * (a * b * sin(angle1_in_radians) + c * d * sin(angle2_in_radians));
            }
            double area(double a, double b, double c, double d, double angle1_in_degrees, double angle2_in_degrees, double angle3_in_degrees){
                double angle1_in_radians = angle1_in_degrees * (constants::pi / 180.0);
                double angle2_in_radians = angle2_in_degrees * (constants::pi / 180.0);
                double angle3_in_radians = angle3_in_degrees * (constants::pi / 180.0);
                return 0.5 * (a * b * sin(angle1_in_radians) + c * d * sin(angle2_in_radians) + a * d * sin(angle3_in_radians));
            }
            double area(double a, double b, double c, double d, double angle1_in_degrees, double angle2_in_degrees, double angle3_in_degrees, double angle4_in_degrees){
                double angle1_in_radians = angle1_in_degrees * (constants::pi / 180.0);
                double angle2_in_radians = angle2_in_degrees * (constants::pi / 180.0);
                double angle3_in_radians = angle3_in_degrees * (constants::pi / 180.0);
                double angle4_in_radians = angle4_in_degrees * (constants::pi / 180.0);
                return 0.5 * (a * b * sin(angle1_in_radians) + c * d * sin(angle2_in_radians) + a * d * sin(angle3_in_radians) + b * c * sin(angle4_in_radians));
            }
            double area(double diagonal, double perpendicular_to_diagonal1, double perpendicular_to_diagonal2){
                return 0.5 * diagonal * (perpendicular_to_diagonal1 + perpendicular_to_diagonal2);
            }
            namespace square{
                double perimeter(double side_length){
                    return 4 * side_length;
                }
                double area(double side_length){
                    return pow(side_length, 2);
                }
            }   
            namespace rectangle{
                double perimeter(double length, double width){
                    return 2 * (length + width);
                }
                double area(double length, double width){
                    return length * width;
                }
            }
            namespace parallelogram{
                double perimeter(double base, double side_length){
                    return 2 * (base + side_length);
                }
                double area(double base, double height){
                    return base * height;
                }
            }
            namespace rhomboid = parallelogram;
            namespace rhombus{
                double perimeter(double side_length){
                    return 4 * side_length;
                }
                double area(double base, double height){
                    return base * height;
                }
            }
            namespace diamond = rhombus;
            namespace trapezoid{
                double area(double base1, double base2, double height){
                    return 0.5 * (base1 + base2) * height;
                }
            }
            namespace kite{
                double perimeter(double side1, double side2){
                    return 2 * (side1 + side2);
                }
                double area(double diagonal1, double diagonal2){
                    return 0.5 * diagonal1 * diagonal2;
                }
            }
        }
        namespace quad = quadrilateral;
        // n sides
        namespace polygon{
            double perimeter(const std::vector<double>& sides){
                double perimeter = 0;
                for(double side : sides){
                    perimeter += side;
                }
                return perimeter;
            }
            double perimeter(double side_length, int number_of_sides){
                return side_length * number_of_sides;
            }
            double area(const std::vector<double>& sides, const std::vector<double>& angles_in_degrees){
                if(sides.size() != angles_in_degrees.size()){
                    throw std::invalid_argument("Number of sides and angles must be equal.");
                }
                double area = 0;
                for(size_t i = 0; i < sides.size(); ++i){
                    double angle_in_radians = angles_in_degrees[i] * (constants::pi / 180.0);
                    area += 0.5 * pow(sides[i], 2) * sin(angle_in_radians);
                }
                return area;
            }
        }
        using polygon = std::vector<int>;
    }
    namespace two_dee = two_dimensional;
    namespace three_dimensional{    
        namespace sphere{
            double surface_area(double r){
                return 4 * constants::pi * pow(r, 2);
            }
            double volume(double r){
                return (4.0 / 3.0) * constants::pi * pow(r, 3);
            }
        }
        namespace cube{
            double surface_area(double side_length){
                return 6 * pow(side_length, 2);
            }
            double volume(double side_length){
                return pow(side_length, 3);
            }
        }
        namespace cuboid{
            double surface_area(double length, double width, double height){
                return 2 * (length * width + length * height + width * height);
            }
            double volume(double length, double width, double height){
                return length * width * height;
            }
        }
    }
    namespace three_dee = three_dimensional;
}

#endif