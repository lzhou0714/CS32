//
//  eval.cpp
//  Hw2
//
//  Created by Lily Zhou on 1/30/22.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;
int convertToPostfix(string infix, const Map& values, string& postfix);
bool isOperand(char a);
void removeSpace(string& infix)
{
    string temp = "";
    for (int i =0;i<infix.size();i++)
    {
        if (!isspace(infix[i]))
            temp+= infix[i];
    }
    infix = temp;
}
int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    removeSpace(infix);
    int returnvalue = convertToPostfix(infix, values, postfix);
    if (returnvalue !=0)
        return returnvalue;
    
    //evaluate postfix
    stack<int> calcStack;
    int v;
    for (int i= 0;i<postfix.size();i++)
    {
        if (isalpha(postfix[i]))
        {
            values.get(postfix[i], v);
            calcStack.push(v);
        }
        else
        {
            int op2 = calcStack.top();
            calcStack.pop();
            int op1 = calcStack.top();
            calcStack.pop();
            switch (postfix[i])
            {
                case '+':
                    calcStack.push(op2+op1);
                    break;
                case '-':
                    calcStack.push(op1-op2);
                    break;
                case '*':
                    calcStack.push(op2*op1);
                    break;
                case '/':
                {
                    if (op2 ==0)
                        return 3;
                    else
                        calcStack.push(op1/op2);
                    break;

                }
            }
        }

    }
    result = calcStack.top();
    cerr << "answer; "  << result<< endl;
    calcStack.pop();
    return returnvalue;
}

bool isOperand(char a)
{
    switch (a) {
        case '/':
        case '*':
        case '+':
        case '-':
            return true;
            break;
            
        default:
            return false;;
    }
}
int convertToPostfix(string infix, const Map& values, string& postfix)
{
    if (isOperand(infix[0]) || infix[0] == ')'||infix.size()==0)
        return 1;
    int i;
    postfix = "";
    stack<char> opStack;
    int returnvalue = 0;
    for (i= 0;i<infix.size();i++)
    {
        if (islower(infix[i]))
        {
            if (!values.contains(infix[i]))
                returnvalue =  2;
            postfix += infix[i];
            cerr << "postfix1: " << postfix<< endl;
            //char must be proceeded by operand or ( and successed by operand or )
            if (i-1>=0 && !isOperand(infix[i-1]) && infix[i-1] != '(')
                return 1;
            if (i+1<infix.size() && !isOperand(infix[i+1]) && infix[i+1] != ')')
                return 1;

        }
        else if (infix[i] == '(')
        {
            //proceeded by operand or ( and succeeded by number

            if (i-1>=0 && !isOperand(infix[i-1]) && infix[i-1] != '(')
                return 1;
            if (i+1<infix.size() && !islower(infix[i+1]) && infix[i+1] != '(')
                return 1;
            
            opStack.push(infix[i]);

        }
        else if (infix[i] == ')')
        {
            //proceeded by ) or number, succeeded by operand or )
            if (i-1>=0 && !islower(infix[i-1]) && infix[i-1] != ')')
                return 1;
            if (i+1<infix.size() && !isOperand(infix[i+1]) && infix[i+1] != ')')
                return 1;
            
            while (!opStack.empty() && opStack.top()!='('  )
            {
                postfix += opStack.top();
                opStack.pop();
                cerr << "postfix2: " << postfix<< endl;
            }
            if (opStack.empty())
                return 1; //no ( in stack, invalid format
            opStack.pop();
        }
        else if (isOperand(infix[i]))
        {
            //proceeded by number or )
            if (i-1>=0 && !islower(infix[i-1]) && infix[i-1] != ')')
                return 1;
            //succeeded by number or (
            if (i+1<infix.size() && !islower(infix[i+1]) && infix[i+1] != '(')
                return 1;
            if (i==infix.size()-1) //infix ends with operand invalid
                return 1;
            
            while (!opStack.empty() && opStack.top() != '(')
            {
                if ((infix[i] == ('*') || infix[i] == ('/')) && (opStack.top() == '+' || opStack.top() == '-'))
                    break;
                postfix += opStack.top();
                opStack.pop();
                cerr << "postfix3: " << postfix<< endl;
            }
            

            opStack.push(infix[i]);
        }
        else
        {
            if (!isspace(infix[i]))
                returnvalue = 1;
        }
    }
    while (!opStack.empty())
    {
        if (!isalpha(opStack.top()) && opStack.top()!= '(' && opStack.top()!= ')')
        {
            postfix += opStack.top();
            cerr << "postfix4: " << postfix<< endl;

            opStack.pop();
        }
        else //extra remaining brc
        {
            cerr << "postfix5: " << postfix<< endl;
            cerr << "invalid syntax character: "<< opStack.top()<< endl;
            return 1;
        }
    }

    return returnvalue;
}
int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer = 0;
    assert(evaluate("(a+(i-(o)))", m, pf, answer) == 0  &&  answer == 7);

    evaluate("(i+   o)   *(a+e/i)-u", m, pf, answer);
    assert(evaluate("(((((a*a*a/a*a*a/a+a+a-a+a-a+a*a/a)))))*(((((e)))))", m, pf, answer) == 0 && answer == -297);
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
                            pf == "ae+"  &&  answer == -6);

    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+     ", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(*o*)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("((((((((((((a+)", m, pf, answer) == 1  &&  answer == 999);

    assert(evaluate("(a+(i-(o))))", m, pf, answer) == 1  &&  answer == 999);

      // unary operators not allowed:
//    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
                            pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                            pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                            pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
                            pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
                            pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}
