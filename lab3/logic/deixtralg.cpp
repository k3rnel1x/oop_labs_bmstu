#include "deixtralg.hpp"

#include <iostream>
#include <map>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cfloat>

using namespace std;

typedef enum {
    Other,
    Number,
    Operator,
    OpenBracket,
    CloseBracket
} TokenType;

int tokenPrior(const char token);
TokenType typeOfToken(const char token);
string getNumber(const string& str, size_t& i);
bool validInfix(string infix);

const map<char, int> operators = {
    {'(', 0},
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3},
    {'~', 4}
};

TokenType typeOfToken(const char token)
{
    if(isdigit(token) || token == '.' || token == 'e')
        return Number;

    if(token == '(')
        return OpenBracket;

    if(token == ')')
        return CloseBracket;

    if(operators.find(token) != operators.end())
        return Operator;

    return Other;
}

int tokenPrior(const char token)
{
    return operators.at(token);
}

string getNumber(const string& str, size_t& i)
{
    string token = "";
    int dotCount = 0;
    int eCount = 0;

    if(str[i] == '.')
        throw runtime_error("invalid number");
    
    while((isdigit(str[i]) || str[i] == '.' || str[i] == 'e') && dotCount < 2 && eCount < 2)
    {
        if(str[i] == 'e')
        {
            if(!(isdigit(str[i-1]) && isdigit(str[i+1])))
                throw runtime_error("invalid number");
                
            eCount++;
        }

        if(str[i] == '.')
        {
            if(!(isdigit(str[i-1]) && isdigit(str[i+1])))
                throw runtime_error("invalid number");
                
            dotCount++;
        }
        token += str[i++];
    }

    if(dotCount > 1 || eCount > 1)
        throw runtime_error("invalid number");
    --i;
    return token;
}

bool validInfix(string infix)
{
    if(infix.empty())
        return false;

    bool firstValidation = false;

    for(char* c = infix.data(); *c; ++c) {
        if((operators.find(*c) != operators.end()) && *(c+1) != '-' && *c != '(' && *c != ')')
            *c = 'o';

        if(isdigit(*c))
        {
            if(!firstValidation)
                firstValidation = true;
            *c = 'd';
        }
    }

    // cout << infix << firstValidation << endl;
    bool secondValidation = (infix.find("oo") == string::npos);

    return firstValidation && secondValidation;
}

string toPostfix(const string infix)
{
    if(!validInfix(infix))
        throw invalid_argument("invalid infix form");

    stack<char> operators_stack;
    string postfix = "";

    for (size_t i = 0; i < infix.size(); ++i)
    {
        char c = infix[i];

        TokenType token_type = typeOfToken(c);
        switch (token_type)
        {
        case Number:
            postfix += getNumber(infix, i) + " ";
            break;

        case Operator:
            if(c == '-' && (i == 0 || i > 1 && operators.find(infix[i-1]) != operators.end()))
                c = '~';

            while(!operators_stack.empty() && tokenPrior(operators_stack.top()) >= tokenPrior(c)) {
                postfix += operators_stack.top();
                operators_stack.pop();
            }
            operators_stack.push(c);
            break;

        case OpenBracket:
            operators_stack.push(c);
            break;

        case CloseBracket:
            while(!operators_stack.empty() && operators_stack.top() != '(') {
                postfix += operators_stack.top();
                operators_stack.pop();
            }

            if(operators_stack.empty()) {
                return "";
            }

            operators_stack.pop();
            break;
        case Other:
            break;
        }
    }

    while(!operators_stack.empty()) {
        if(operators_stack.top() == '(') {
            return "";
        }
        postfix += operators_stack.top();
        operators_stack.pop();
    }

    return postfix;
}

double execOperation(char operation, double a, double b)
{
    // validate operation byte
    operators.find(operation);

    double result = 0;
    switch(operation)
    {
    case '+':
        if (a > DBL_MAX - b) {
            throw runtime_error("number overflow");
        }
        result = a + b;
        break;

    case '-':
        result = a - b;
        break;

    case '*':
        if (fabs(a) > DBL_MAX / fabs(b)){
            throw runtime_error("number overflow");
        }
        result = a * b;
        break;

    case '/':
        if(b == 0)
            throw runtime_error("zero dividing");
        result = a / b;
        break;

    case '^':
        result = pow(a, b);
        if(result == INFINITY)
            throw runtime_error("number overflow");
        break;

    default:
        break;
    }
    // cout << "Operation: " << a << " " << operation << " " << b << endl;

    return result;
}

double calcInPostfix(const string postfix)
{
    if(postfix.empty())
        throw invalid_argument("postfix is empty");
        
    stack<double> numbers;

    for (size_t i = 0; i < postfix.size(); ++i)
    {
        char c = postfix[i];
        if(c == ' ')
            continue;

        TokenType token_type = typeOfToken(c);
        switch (token_type)
        {
            case Number:
            {
                string str = getNumber(postfix, i);
                char* end;
                double num = strtod(str.data(), &end);
                if(num == HUGE_VALL)
                    throw runtime_error("huge value");

                if(!end)
                    throw runtime_error("calculating error");

                numbers.push(num);
                break;
            }

            case Operator:
            {
                if(c == '~') {
                    double num = numbers.top();
                    numbers.pop();
                    numbers.push(-num);
                    break;
                }

                double b = numbers.empty()? 0 : numbers.top();
                if (!numbers.empty()) numbers.pop();

                double a = numbers.empty()? 0 : numbers.top();
                if (!numbers.empty()) numbers.pop();

                numbers.push(execOperation(c, a, b));
                break;
            }
        }
    }

    
    return numbers.top();
}

// int main()
// {
//     // string infix = "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))"; 
//     string infix = "1.7e308 + 1.7e308"; 
        
//     cout << "infix = " << infix << endl;
    
//     double res;
//     string postfix;
//     try{
//         postfix = toPostfix(infix);
//         res = calcInPostfix(postfix);

//     } catch(exception& e) {
//         cout << "Error! " << e.what() << endl;
//         return 1;
//     }

//     cout << "postfix = " << postfix << endl;
//     cout << "calculated: " << res << endl;
//     return 0;
// }