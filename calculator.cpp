#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

// Simple recursive-descent expression calculator
// Supports: + - * /, parentheses, unary +/-, decimal numbers
class Calculator {
public:
    explicit Calculator(const std::string& expr) : expr_(expr), pos_(0) {}

    double evaluate() {
        skipSpaces();
        double result = parseExpression();
        skipSpaces();
        if (pos_ != expr_.size()) {
            throw std::runtime_error("unexpected character at position " + std::to_string(pos_));
        }
        return result;
    }

private:
    const std::string& expr_;
    size_t pos_;

    void skipSpaces() {
        while (pos_ < expr_.size() && std::isspace(static_cast<unsigned char>(expr_[pos_]))) {
            ++pos_;
        }
    }

    bool match(char c) {
        if (pos_ < expr_.size() && expr_[pos_] == c) {
            ++pos_;
            return true;
        }
        return false;
    }

    double parseNumber() {
        skipSpaces();
        size_t start = pos_;
        while (pos_ < expr_.size() &&
               (std::isdigit(static_cast<unsigned char>(expr_[pos_])) || expr_[pos_] == '.')) {
            ++pos_;
        }
        if (start == pos_) {
            throw std::runtime_error("expected a number at position " + std::to_string(pos_));
        }
        return std::stod(expr_.substr(start, pos_ - start));
    }

    // factor := number | '(' expression ')' | ('+'|'-') factor
    double parseFactor() {
        skipSpaces();
        if (match('+')) return parseFactor();
        if (match('-')) return -parseFactor();
        if (match('(')) {
            double value = parseExpression();
            skipSpaces();
            if (!match(')')) {
                throw std::runtime_error("missing closing parenthesis");
            }
            return value;
        }
        return parseNumber();
    }

    // term := factor (('*'|'/') factor)*
    double parseTerm() {
        double value = parseFactor();
        while (true) {
            skipSpaces();
            if (match('*')) {
                value *= parseFactor();
            } else if (match('/')) {
                double divisor = parseFactor();
                if (divisor == 0.0) {
                    throw std::runtime_error("division by zero");
                }
                value /= divisor;
            } else {
                break;
            }
        }
        return value;
    }

    // expression := term (('+'|'-') term)*
    double parseExpression() {
        double value = parseTerm();
        while (true) {
            skipSpaces();
            if (match('+')) {
                value += parseTerm();
            } else if (match('-')) {
                value -= parseTerm();
            } else {
                break;
            }
        }
        return value;
    }
};

int main() {
    std::cout << "Simple C++ Calculator\n";
    std::cout << "Enter an expression (e.g. (1+2)*3/4), or 'q' to quit.\n";
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "q" || line == "quit" || line == "exit") break;
        if (line.empty()) continue;
        try {
            double result = Calculator(line).evaluate();
            std::cout << "= " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    std::cout << "Bye!\n";
    return 0;
}
