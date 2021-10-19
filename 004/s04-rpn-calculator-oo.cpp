#include "RPN_calculator.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <math.h>

static auto pop_top(std::stack<double>& stack) -> double
{
    if (stack.empty()) throw std::logic_error{"empty stack"};

    auto element = std::move(stack.top());
    stack.pop();
    return element;
}

namespace student { 
    namespace rpn_calculator {
        Element::~Element()
        {}

        Literal::Literal(double const v) : value{v}
        {}

        auto Literal::evaluate(stack_type& stack) const -> void
        {
            stack.push(value);
        }

        auto Print::evaluate(stack_type& stack) const -> void
        {
            std::cout << stack.top() << "\n";
        }

        auto Addition::evaluate(stack_type& stack) const -> void
        {
            if (stack.size() < 2) {
                throw std::logic_error{"not enough operands for +"};
            }
            auto const b = pop_top(stack);
            auto const a = pop_top(stack);
            stack.push(a + b);
        }

        auto Subtraction::evaluate(stack_type& stack) const -> void
        {
            if (stack.size() < 2) {
                throw std::logic_error{"not enough operands for +"};
            }
            auto const b = pop_top(stack);
            auto const a = pop_top(stack);
            stack.push(a - b);
        }

        auto Multiplication::evaluate(stack_type& stack) const -> void
        {
            if (stack.size() < 2) {
                throw std::logic_error{"not enough operands for +"};
            }
            auto const b = pop_top(stack);
            auto const a = pop_top(stack);
            stack.push(a * b);
        }

        auto Division::evaluate(stack_type& stack) const -> void
        {
            if (stack.size() < 2) {
                throw std::logic_error{"not enough operands for +"};
            }
            auto const b = pop_top(stack);
            auto const a = pop_top(stack);
            stack.push(a / b);
        }

        auto IntDivision::evaluate(stack_type& stack) const -> void
        {
            if (stack.size() < 2) {
                throw std::logic_error{"not enough operands for +"};
            }
            auto const b = pop_top(stack);
            auto const a = pop_top(stack);
            stack.push(floor(a / b));
        }

        auto Modulo::evaluate(stack_type& stack) const -> void
        {
            if (stack.size() < 2) {
                throw std::logic_error{"not enough operands for +"};
            }
            auto const b = pop_top(stack);
            auto const a = pop_top(stack);
            stack.push(std::fmod(a, b));
        }

        auto Power::evaluate(stack_type& stack) const -> void
        {
            if (stack.size() < 2) {
                throw std::logic_error{"not enough operands for +"};
            }
            auto const b = pop_top(stack);
            auto const a = pop_top(stack);
            stack.push(pow(a, b));
        }

        auto SquareRoot::evaluate(stack_type& stack) const -> void
        {
            auto const a = pop_top(stack);
            stack.push(sqrt(a));
        }

        auto Percentage::evaluate(stack_type& stack) const -> void
        {
            if (stack.size() < 2) {
                throw std::logic_error{"not enough operands for +"};
            }
            auto const b = pop_top(stack);
            auto const a = pop_top(stack);
            stack.push(a * b / 100);
        }

        Calculator::Calculator(stack_type s) : stack{std::move(s)}
        {}

        auto Calculator::push(std::unique_ptr<Element> op) -> void
        {
            ops.push(std::move(op));
        }

        void Calculator::push(std::string op) 
        {
            //?
        }

        auto Calculator::evaluate() -> void
        {
            while (not ops.empty()) {
                auto op = std::move(ops.front());
                ops.pop();

                op->evaluate(stack);
            }
        }
    }
}


auto make_args(int argc, char* argv[], bool const with_exec = false)
    -> std::vector<std::string>
{
    auto args = std::vector<std::string>{};
    auto const offset = static_cast<size_t>(not with_exec);
    std::copy_n(argv + offset, argc - offset, std::back_inserter(args));
    return args;
}

auto main(int argc, char* argv[]) -> int
{
    using student::rpn_calculator::Calculator;
    auto calculator = Calculator{};

    for (auto const& each : make_args(argc, argv)) {
        try {
            using student::rpn_calculator::Addition;
            using student::rpn_calculator::Subtraction;
            using student::rpn_calculator::Multiplication;
            using student::rpn_calculator::Division;
            using student::rpn_calculator::Addition;
            using student::rpn_calculator::IntDivision;
            using student::rpn_calculator::Modulo;
            using student::rpn_calculator::Power;
            using student::rpn_calculator::SquareRoot;
            using student::rpn_calculator::Percentage;
            using student::rpn_calculator::Literal;
            using student::rpn_calculator::Print;

            if (each == "p") {
                calculator.push(std::make_unique<Print>());
            } else if (each == "+") {
                calculator.push(std::make_unique<Addition>());
            } else if (each == "-") {
                calculator.push(std::make_unique<Subtraction>());
            } else if (each == "*") {
                calculator.push(std::make_unique<Multiplication>());
            } else if (each == "/") {
                calculator.push(std::make_unique<Division>());
            } else if (each == "//") {
                calculator.push(std::make_unique<IntDivision>());
            } else if (each == "%") {
                calculator.push(std::make_unique<Modulo>());
            } else if (each == "**") {
                calculator.push(std::make_unique<Power>());
            } else if (each == "sqrt") {
                calculator.push(std::make_unique<SquareRoot>());
            } else if (each == "%%") {
                calculator.push(std::make_unique<Percentage>());
            } else {
                calculator.push(std::make_unique<Literal>(std::stod(each)));
            }
        } catch (std::logic_error const& e) {
            std::cerr << "error: " << each << ": " << e.what() << "\n";
        }
    }

    try {
        calculator.evaluate();
    } catch (std::logic_error const& e) {
        std::cerr << "error: during evaluation: " << e.what() << "\n";
    }

    return 0;
}
