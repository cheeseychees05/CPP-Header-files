#ifndef MOREBASES_HPP
#define MOREBASES_HPP

#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

template <int base>
struct digit {
    static_assert(base >= 2, "base must be at least 2");

private:
    int value;

    void normalize(long long v) {
        v %= base;
        if (v < 0) v += base;
        value = static_cast<int>(v);
    }

public:
    digit(long long v = 0) : value(0) {
        normalize(v);
    }

    digit& operator=(int v) {
        normalize(v);
        return *this;
    }

    digit& operator+=(int v) {
        normalize(static_cast<long long>(value) + v);
        return *this;
    }

    digit& operator-=(int v) {
        normalize(static_cast<long long>(value) - v);
        return *this;
    }

    digit& operator*=(int v) {
        normalize(static_cast<long long>(value) * v);
        return *this;
    }

    digit& operator/=(int v) {
        if (v == 0) throw std::domain_error("digit division by zero");
        normalize(value / v);
        return *this;
    }

    digit& operator%=(int v) {
        if (v == 0) throw std::domain_error("digit modulo by zero");
        normalize(value % v);
        return *this;
    }

    digit& operator++() {
        normalize(static_cast<long long>(value) + 1);
        return *this;
    }

    digit& operator--() {
        normalize(static_cast<long long>(value) - 1);
        return *this;
    }

    digit operator++(int) {
        digit previous = *this;
        ++*this;
        return previous;
    }

    digit operator--(int) {
        digit previous = *this;
        --*this;
        return previous;
    }

    operator int() const {
        return value;
    }
};

template <int base>
class base_int {
    static_assert(base >= 2, "base must be at least 2");

private:
    // Digits are stored least-significant first.
    std::vector<digit<base>> value;
    bool negative = false;

    void normalize() {
        while (!value.empty() && static_cast<int>(value.back()) == 0) {
            value.pop_back();
        }
        if (value.empty()) negative = false;
    }

    static int compare_magnitude(const base_int& lhs, const base_int& rhs) {
        if (lhs.value.size() != rhs.value.size()) {
            return lhs.value.size() < rhs.value.size() ? -1 : 1;
        }
        for (std::size_t i = lhs.value.size(); i > 0; --i) {
            int left_digit = lhs.value[i - 1];
            int right_digit = rhs.value[i - 1];
            if (left_digit != right_digit) {
                return left_digit < right_digit ? -1 : 1;
            }
        }
        return 0;
    }

    static std::vector<digit<base>> add_magnitudes(
        const std::vector<digit<base>>& lhs,
        const std::vector<digit<base>>& rhs
    ) {
        std::vector<digit<base>> result;
        const std::size_t length = lhs.size() > rhs.size() ? lhs.size() : rhs.size();
        long long carry = 0;

        for (std::size_t i = 0; i < length || carry != 0; ++i) {
            long long sum = carry;
            if (i < lhs.size()) sum += lhs[i];
            if (i < rhs.size()) sum += rhs[i];
            result.emplace_back(sum % base);
            carry = sum / base;
        }
        return result;
    }

    // Requires |lhs| >= |rhs|.
    static std::vector<digit<base>> subtract_magnitudes(
        const std::vector<digit<base>>& lhs,
        const std::vector<digit<base>>& rhs
    ) {
        std::vector<digit<base>> result;
        long long borrow = 0;

        for (std::size_t i = 0; i < lhs.size(); ++i) {
            long long difference = static_cast<int>(lhs[i]) - borrow;
            if (i < rhs.size()) difference -= static_cast<int>(rhs[i]);
            if (difference < 0) {
                difference += base;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.emplace_back(difference);
        }
        return result;
    }

    template <typename Integer>
    using enable_integer = typename std::enable_if<
        std::is_integral<Integer>::value &&
        !std::is_same<typename std::remove_cv<Integer>::type, bool>::value
    >::type;

public:
    base_int() = default;

    template <typename Integer, typename = enable_integer<Integer>>
    base_int(Integer number) {
        unsigned long long magnitude;

        if (number < 0) {
            negative = true;
            magnitude = static_cast<unsigned long long>(-(number + 1));
            ++magnitude;
        } else {
            magnitude = static_cast<unsigned long long>(number);
        }

        while (magnitude != 0) {
            value.emplace_back(static_cast<long long>(magnitude % static_cast<unsigned long long>(base)));
            magnitude /= static_cast<unsigned long long>(base);
        }
        normalize();
    }

    base_int& operator+=(const base_int& rhs) {
        *this = *this + rhs;
        return *this;
    }

    base_int& operator-=(const base_int& rhs) {
        *this = *this - rhs;
        return *this;
    }

    base_int& operator*=(const base_int& rhs) {
        *this = *this * rhs;
        return *this;
    }

    base_int operator-() const {
        base_int result = *this;
        if (!result.value.empty()) result.negative = !result.negative;
        return result;
    }

    friend base_int operator+(const base_int& lhs, const base_int& rhs) {
        base_int result;
        if (lhs.negative == rhs.negative) {
            result.value = add_magnitudes(lhs.value, rhs.value);
            result.negative = lhs.negative;
        } else {
            int order = compare_magnitude(lhs, rhs);
            if (order >= 0) {
                result.value = subtract_magnitudes(lhs.value, rhs.value);
                result.negative = lhs.negative;
            } else {
                result.value = subtract_magnitudes(rhs.value, lhs.value);
                result.negative = rhs.negative;
            }
        }
        result.normalize();
        return result;
    }

    friend base_int operator-(const base_int& lhs, const base_int& rhs) {
        return lhs + (-rhs);
    }

    friend base_int operator*(const base_int& lhs, const base_int& rhs) {
        base_int result;
        if (lhs.value.empty() || rhs.value.empty()) return result;

        result.value.resize(lhs.value.size() + rhs.value.size());
        for (std::size_t i = 0; i < lhs.value.size(); ++i) {
            long long carry = 0;
            for (std::size_t j = 0; j < rhs.value.size(); ++j) {
                std::size_t position = i + j;
                long long product =
                    static_cast<long long>(lhs.value[i]) * static_cast<int>(rhs.value[j]) +
                    static_cast<int>(result.value[position]) + carry;
                result.value[position] = static_cast<int>(product % base);
                carry = product / base;
            }

            std::size_t position = i + rhs.value.size();
            while (carry != 0) {
                long long sum = static_cast<int>(result.value[position]) + carry;
                result.value[position] = static_cast<int>(sum % base);
                carry = sum / base;
                ++position;
                if (position == result.value.size() && carry != 0) {
                    result.value.emplace_back(0);
                }
            }
        }

        result.negative = lhs.negative != rhs.negative;
        result.normalize();
        return result;
    }

    friend bool operator==(const base_int& lhs, const base_int& rhs) {
        return lhs.negative == rhs.negative && lhs.value == rhs.value;
    }

    friend bool operator!=(const base_int& lhs, const base_int& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const base_int& lhs, const base_int& rhs) {
        if (lhs.negative != rhs.negative) return lhs.negative;
        int order = compare_magnitude(lhs, rhs);
        return lhs.negative ? order > 0 : order < 0;
    }

    friend bool operator>(const base_int& lhs, const base_int& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const base_int& lhs, const base_int& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const base_int& lhs, const base_int& rhs) {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& out, const base_int& number) {
        if (number.negative) out << '-';

        if (number.value.empty()) return out << '0';

        for (std::size_t i = number.value.size(); i > 0; --i) {
            int current_digit = number.value[i - 1];
            if (base <= 36) {
                out << "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[current_digit];
            } else {
                out << '[' << current_digit << ']';
            }
        }
        return out;
    }
};

#endif
