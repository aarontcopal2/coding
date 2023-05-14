// https://leetcode.com/problems/basic-calculator/
// Questions:
// 1. Will the expression be valid?
// 2. Will the input contain float nums?
// 3. What are the list of expected operators?
// 4. Precedence relationship: BODMAS meaning
// Brackets, Order, Division/Multiplication, Addition/Subtraction.
// 5. Any time or space complexity constraints that I need to be aware of?

#include <cassert>              // assert
#include <ctype.h>              // isdigit
#include <math.h>               // pow
#include <stack>
#include <stdexcept>            // runtime_error
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    double calculate(const std::string &s, const int &start_index=0, int* end_index=nullptr) {
        // Break the string into tokens, where:
        // token = {num, symbol}, and
        // symbol: {+, -, *, /, ^, (, )}
        std::vector<std::string> tokens;

        for(int i = start_index; i<s.size(); i++) {
            char c = s[i];
            if (isdigit(c)) {
                int j = i+1;
                while (isdigit(s[j])) {
                    j++;
                }
                tokens.push_back(s.substr(i, j-i));
                i = j-1;
            } else if (is_operator(c)) {
                tokens.push_back(std::string(1, c));
            } else {
                // The remaining chars can be paranthesis, or unsupported chars.
                // We ignore unsupported chars.
                if (c == '(') {
                    int paranthesis_end;
                    double paranthesis_result = calculate(s, i+1, &paranthesis_end);
                    std::string result_str = std::to_string(paranthesis_result);
                    if (paranthesis_result == (int)paranthesis_result) {
                        result_str = std::to_string((int)paranthesis_result);
                    }
                    printf("paranthesis result:: %f:: %s\n", paranthesis_result, result_str.c_str());
                    tokens.push_back(result_str);
                    i = paranthesis_end;
                } else  if (c == ')') {
                    *end_index = i;
                    return evaluate_atomic_expression(tokens);
                }
            }
        }
        return evaluate_atomic_expression(tokens);
    }

private:
    // TODO: Convert this into a static variable.
    std::unordered_map<char, uint16_t> precedence = {
        // Precedence relationship: BODMAS meaning 
        // Brackets, Order, Division/Multiplication, Addition/Subtraction.
        {'+', 0} , {'-', 0},
        {'*', 1} , {'/', 1},
        {'^', 2} ,
        {'(', 3}, {')', 3}
    };

    bool is_operator(const char &token) {
        return (token == '+' || token == '-' || token == '*' || token == '/' || token == '^');
    }

    uint16_t get_precedence(const char &op) {
        return precedence[op];
    }

    void execute_prev_operation(std::stack<double> &prev_operands, std::stack<char> &prev_operators) {
        // perform prev_operation, and push the result to operand stack.
        char optr = prev_operators.top();       prev_operators.pop();
        double op2 = prev_operands.top();          prev_operands.pop();
        double result;
        if (!prev_operands.empty()) {
            double op1 = prev_operands.top();          prev_operands.pop();
            result = perform_operation(op1, op2, optr);
        } else {
            // An atomic expression has the syntax of op1 <optr> op2.
            // The exception to this rule is the negation of a operand.
            // i.e <optr> op1 -> -op1
            if (optr == '-') result = -op2; 
        }
        
        prev_operands.push(result);
    }

    double perform_operation(const double &op1, const double &op2, const char &optr) {
        printf("Operation: %.2f %c %.2f\n", op1, optr, op2);
        if (optr == '+') return op1 + op2;
        else if (optr == '-') return op1 - op2;
        else if (optr == '*') return op1 * op2;
        else if (optr == '/') return op1 / op2;
        else if (optr == '^') return pow(op1, op2);
        else throw std::runtime_error(std::string("Unsupported operation"));
    }

    double evaluate_atomic_expression(const std::vector<std::string> &tokens) {
        // An atomic expression is an expression enclosed in paranthesis.
        std::stack<double> prev_operands;
        std::stack<char> prev_operators;
        for (const std::string &token: tokens) {
            if (isdigit(token.c_str()[0]) || (token.length() > 1)) {
                // A token is a number if the starting character is a digit, or
                // If the number is negative, the above condition will fail.
                // In that case, the token will have two chars atleast.
                // Hence we check if the token has more than two characters in the 2nd condition.
                double num = atof(token.c_str());
                prev_operands.push(num);
            } else if (is_operator(token.c_str()[0])) {
                // Why do we check for precedence(curr_operator) <= get_precedence(prev_operator)?
                // If the precedence is equal, we need to execute the expression in left to right fashion.
                // Hence we execute previous operation if current op's precedence is less than or equal to 
                // previous op's precedence.
                if (!prev_operators.empty() && (get_precedence(token.c_str()[0]) <= get_precedence(prev_operators.top()))) {
                    execute_prev_operation(prev_operands, prev_operators);
                }
                prev_operators.push(token.c_str()[0]);
            }
        }
        while (!prev_operators.empty()) {
            execute_prev_operation(prev_operands, prev_operators);
        }
        return prev_operands.top();
    }
};


static void print_helper(Solution* obj, const std::string &s, const double &expected) {
    double val = obj->calculate(s);
    printf("Expr: %s:: expected: %.2f, actual: %.2f\n\n", s.c_str(), expected, val);
    assert(val == expected);
}

int main() {
    Solution* obj = new Solution();

    std::string s;
    double val;
    print_helper(obj, "1 + 1", 2);
    print_helper(obj, " 2-1 + 2 ", 3);
    print_helper(obj, "(1+(4+5+2)-3)+(6+8)", 23);
    print_helper(obj, "(1+(4+5+2)*3)+(6+8)", 48);
    print_helper(obj, "2147483647", 2147483647);
    print_helper(obj, "1-(     -2)", 3);
}
