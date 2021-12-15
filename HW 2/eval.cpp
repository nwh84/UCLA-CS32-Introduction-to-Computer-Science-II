//
//  eval.cpp
//  CS32Homework2
//
//  Created by Noela Wheeler on 4/24/21.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result)
{
    if (infix=="")
    {return 1;}
    postfix="";
    stack<char> opStack;
    char previous=' ';
    for (int i=0;i<=infix.size()-1;i++)
    {
        char ch=infix[i];
        switch (ch)
        {
            case 'T':
                if(previous=='T' || previous=='F')
                    return 1;
                previous='T';
                postfix+=ch;
                break;
            case 'F':
                if(previous=='T' || previous=='F')
                    return 1;
                previous='F';
                postfix+=ch;
                break;
            case '(':
                if(previous=='T' || previous=='F' || previous==')')
                    return 1;
                previous='(';
                opStack.push(ch);
                break;
            case ')':
                if(previous=='!'||previous=='('||previous=='^'||previous=='&')
                    return 1;
                previous=')';
                while (opStack.top()!='(')
                {
                    postfix+=opStack.top();
                    opStack.pop();
                }
                opStack.pop();
                break;
            case '^':
                if(previous=='^'||previous=='&'||previous=='!'||previous=='(')
                    return 1;
                previous='^';
                while (!opStack.empty() && opStack.top()!='(' && ch>=opStack.top())
                {
                    postfix+=opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                break;
            case '&':
                if (previous=='&' || previous=='^' || previous=='!'||previous=='(')
                    return 1;
                previous='&';
                while (!opStack.empty() && opStack.top()!='(' && ch>=opStack.top())
                {
                    postfix+=opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                break;
            case '!':
                if (i==infix.size()-1)
                    return 1;
                previous='!';
                while (!opStack.empty() && opStack.top()!='(' && ch>=opStack.top())
                {
                    postfix+=opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                break;
            case ' ':
                break;
            default:
                return 1;
        }
    }
    while (!opStack.empty())
    {
        postfix+=opStack.top();
        previous=opStack.top();
        opStack.pop();
    }
    int numOperand=0;
    for(int i=0;i<=postfix.size()-1;i++)
    {
        //further check that prefix notation was correct
        if (postfix[i]=='('||postfix[i]=='(')
            return 1;
        if(postfix[i]=='T'||postfix[i]=='F')
            numOperand++;
    }
    if (numOperand==0)
        return 1;
    if (postfix.size()==2 && infix[1]!= '!')
        return 1;
    
    //evaluation of postfix expression
    stack<int> opStack2;
    for (int i=0;i<=postfix.size()-1;i++)
    {
        char ch=postfix[i];
        int operand1=0;
        int operand2=0;
        if (ch=='F')
            opStack2.push(0);
        if (ch=='T')
            opStack2.push(1);
        if (ch=='&'|| ch=='^')
        {
            // set operand2 to the top of the operand stack and pop the stack
            operand2=opStack2.top();
            opStack2.pop();
            //set operand1 to the top of the operand stack and pop the stack
            operand1=opStack2.top();
            opStack2.pop();
            //apply the operation that ch represents to operand1 and
            //operand2, and push the result onto the stack
            int r=0;
            if (ch=='&')
            {r=operand1 & operand2;}
            if (ch=='^')
            {r=operand1 ^ operand2;}
            opStack2.push(r);
        }
        if (ch=='!')
        {
            if(opStack2.top()==1)
            {
                opStack2.pop();
                opStack2.push(0);
            }
            else
            {
                opStack2.pop();
                opStack2.push(1);
            }
        }
    }
    result=opStack2.top();
    return 0;
}



int main()
{
string pf;
bool answer;
assert(evaluate("T^F&F", pf, answer) == 0  &&  answer);
assert(evaluate("T^", pf, answer) == 1);
assert(evaluate("F F", pf, answer) == 1);
assert(evaluate("TF", pf, answer) == 1);
assert(evaluate("()", pf, answer) == 1);
assert(evaluate("()T", pf, answer) == 1);
assert(evaluate("T(F^T)", pf, answer) == 1);
assert(evaluate("T(&T)", pf, answer) == 1);
assert(evaluate("(T&(F^F)", pf, answer) == 1);
assert(evaluate("T|F", pf, answer) == 1);
assert(evaluate("", pf, answer) == 1);
assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
                       &&  pf == "FF!TF&&^"  &&  !answer);
assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);

cout << "Passed all tests" << endl;
    return 0;
}


