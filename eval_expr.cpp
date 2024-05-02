/**
 * Implementation of the functions to evaluate arithmetic expressions
 * The implementation should use the Stack data structure
 */
//You should always comments to each function to describe its PURPOSE and PARAMETERS
#include "stack.h"
#include "eval_expr.h"
#include <string.h>
#include <math.h>

float equation(float x, float y, char c) {
    float z;
    switch (c) {

    case '+':
        z = x + y;
        cout << "::equ +: " << z <<"| ";
        return z;
        break;

    case '-':
        z = x - y;
        cout << "::equ -: " << z << "| ";
        return z;
        break;

    case '*':
        z = x * y;
        cout << "::equ *: " << z << "| ";
        return z;
        break;

    case '/':
        if (y == 0) {
            return 0;
        }
        else
        z = x / y;
        cout << "::equ /: " << z << "| ";
        return z;
        break;

    case '^':
        z = pow(x, y);
        return z;
        break;

    default:
        // If the operator is other than +, -, * or /, error message is shown
        cout << "Error! operator is not correct"<<endl;
        break;
    }
    return 0;
}

bool operatorCheck(char s) {
    cout << "::OP Chk Check top";
    switch (s) {

    case '+': case '-': case '*': case '/': case '^':
        cout << "::OP Chk";
        return true;
        break;

    default:
        //cout << "::OP Chk Check default";
        cout << "::Error! operator is not correct\n";
        return false;
        break;

    }
    return 0;
}

/**
 * @brief Evaluate a postfix expression
 * @param postfix_expr The input expression in the postfix format.
 * @param result gets the evaluated value of the expression (by reference).
 * @return true if expression is a valid postfix expression and evaluation is done without error, otherwise false.
 */
bool evalPostfixExpr(string postfix_expr, float& result) {
    Stack <float> nums;
    cout <<"Postfix: "<< postfix_expr << endl;
    for (size_t i = 0; i < postfix_expr.size(); i++) {
        cout << "\nstep " << i+1;
        if (postfix_expr.at(i) >= '0' && postfix_expr.at(i) <= '9') {
            cout << "::nums Push::val:" << postfix_expr.at(i);
            nums.push(postfix_expr.at(i)-'0');
        }
        else if (operatorCheck(postfix_expr.at(i)) == false) {
            result = 0;
            return false;
        }
        else if(operatorCheck(postfix_expr.at(i)) == true) {
            if (nums.size() < 2) {
                result = 0;
                return false;
            }
            cout << "::operCheck::val: " << postfix_expr.at(i);
            float x, y;
            //nums.displayAll();
            nums.pop(y);
            //nums.displayAll();
            nums.pop(x);
            //nums.displayAll();
            if (y == 0 && postfix_expr.at(i) == '/') {
                result = 0;
                return false;
            }
            float a = equation(x,y, postfix_expr.at(i));
            nums.push(a);
        }
    }
    nums.displayAll();
    if (nums.size() == 1) {
        float n;
        nums.pop(n);
        result = n;
        return true;
    }
    else

    return false;
}

/**
 * @brief Convert an infix expression to an equivalent postfix expression
 * @param infix_expr The input expression in the infix format.
 * @return the converted postfix expression. If the input infix expression is invalid, return an empty string "";
 */
string convertInfixToPostfix(string infix_expr) {
    Stack <char> opers;
    string postfix_expr;
    int parenthOpen=0;
    int parenthClose = 0;
    cout << endl;
    for (size_t i = 0; i < infix_expr.size(); i++) {
        cout << "step " << i+1;
        if (infix_expr.at(i) >= '0' && infix_expr.at(i) <= '9') {
            cout << "::num Push::val:" << infix_expr.at(i) << endl;
            postfix_expr += infix_expr.at(i);
        }
        else if (opers.isEmpty() == true) {
            cout << "::oper->E Push::val:" << infix_expr.at(i) << endl;
            opers.push(infix_expr.at(i));
            if (infix_expr.at(i) == '(') {
                parenthOpen++;
            }
        }
        else{
            
            char s;
            cout << "::oper Push::val:" << infix_expr.at(i);
            switch (infix_expr.at(i)) {
                /*case opers.top() == 0:
                    opers.push(infix_expr.at(i));
                    parenthOpen++;
                    break;*/
                case '+': case '-':
                    cout << "::case:+ -";
                    switch (opers.top()) {
                        case '+': case '-': case '*': case '/': case '^':
                            opers.pop(s);//remove top from stack
                            cout << "::oper.Spop: " << s;
                            opers.push(infix_expr.at(i));//push onto operator stack
                            cout << "::oper.Ipush: " << infix_expr.at(i);
                            postfix_expr += s;//push onto output
                            cout << "::add string: " << s << endl;
                            s = 0;
                            break;
                        default:
                            opers.push(infix_expr.at(i));//push onto operator stack
                            cout << "::operDef.Ipush: " << infix_expr.at(i) << endl;
                            break;
                    }
                    break;

                case '*': case '/':
                    cout << "::case:* / \n";
                    switch (opers.top()) {
                        case '*': case '/': case '^':
                            opers.pop(s);//remove top from stack
                            cout << "::oper.Spop: " << s;
                            opers.push(infix_expr.at(i));//push onto operator stack
                            cout << "::oper.Ipush: " << infix_expr.at(i);
                            postfix_expr += s;//push onto output
                            cout << "::add string: " << s << endl;
                            s = 0;
                            break;
                        default:
                            opers.push(infix_expr.at(i));//push onto operator stack
                            cout << "::operDef.Ipush: " << infix_expr.at(i) << endl;
                            break;
                    }
                    break;

                case '^':
                    switch (opers.top()) {
                        case '^':
                            cout << "::case:^ \n";
                            opers.pop(s);//remove operator top from stack
                            cout << "::oper.Spop: " << s;
                            opers.push(infix_expr.at(i));//push string operator onto operator stack
                            cout << "::oper.Ipush: " << infix_expr.at(i);
                            postfix_expr += s;//push stack operator onto output
                            cout << "::add string: " << s << endl;
                            s = 0;
                            break;
                        default:
                            opers.push(infix_expr.at(i));//push onto operator stack
                            cout << "::operDef.Ipush: " << infix_expr.at(i) << endl;
                            break;
                    }
                    break;

                case '(': case '[': case '{': case '<':
                    cout << "::case:( \n";
                    opers.push(infix_expr.at(i));
                    cout << "::oper.Ipush: " << infix_expr.at(i);
                    parenthOpen++;
                    break;

                case ')': case ']': case '}':  case'>':
                    cout << "::case:) ";
                    opers.pop(s);
                    cout << "::oper.Spop: " << s;
                    while (s != '(' && s != '[' && s != '{' && s != '>') {
                        postfix_expr += s;
                        opers.pop(s);
                    }
                    //opers.pop(s);
                    s = 0;
                    parenthClose++;
                    cout << "::Open: " << parenthOpen << "close: " << parenthClose << endl;
                    if (parenthOpen != parenthClose) {
                        postfix_expr += infix_expr.at(i);
                        cout << "\nError! Parenthese error " << infix_expr.at(i) << endl;
                    }                        
                    break;

                default:
                    cout << "::DefDefStringPpush: " << infix_expr.at(i);
                    postfix_expr += infix_expr.at(i);
                    string x;
                    x += infix_expr.at(i);
                    cout << "\nError! operator not recognized " << infix_expr.at(i) << endl;
                    return x;
                    break;
            } 
        }
    }
    cout << "Opers: ";
    opers.displayAll();
    char x;
    while (opers.size() > 0) {
        opers.pop(x);
        postfix_expr += x;
    }
    cout << "OpersII: ";
    opers.displayAll();
    return postfix_expr;
}

/**
 * @brief Evaluate an infix expression. It's converted to a postfix expression first and then evaluated
 * @param infix_expr The input expression in the infix format.
 * @param result gets the evaluated value of the expression (by reference).
 * @return true if expression is valid and evaluation is done without error, otherwise false.
 */
bool evalInfixExpr(string infix_expr, float& result) {
    float n;
    string postfix_expr = convertInfixToPostfix(infix_expr);
    bool success = evalPostfixExpr(postfix_expr, n);

    result = n;


    return success;
}