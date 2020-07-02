#include "string"
#include "stdio.h"
#include "iostream"
#include "stack"

using namespace std;

int getSyntax(int *res, int *p, const string &data)
{

    string tmp;
    while (*p < data.length())
    {
        char c = data.c_str()[*p];

        if (c == ' ')
        {
            *p = *p + 1;
            continue;
        }
        else if ('0' <= c && c <= '9')
        {
            tmp += c;
            *p = *p + 1;
        }
        else
        {
            if (tmp.size() > 0)
            {
                *res = atoi(tmp.c_str());
                return 0;
            }
            *p = *p + 1;
            *res = -1 * (int)c;
            return 0;
        }
    }

    if(tmp.size() >0){
        *res = atoi(tmp.c_str());
                return 0;
    }

    return -1;
}

void calulate(stack<char> &oper, stack<int> &num)
{
    if (num.size() < 2)
        return;
    if (oper.top() == '+')
    {
        int op1 = num.top();
        num.pop();
        int op2 = num.top();
        num.pop();
        num.push(op1 + op2);
        oper.pop();
    }
    else if (oper.top() == '-')
    {
        int op1 = num.top();
        num.pop();
        int op2 = num.top();
        num.pop();
        num.push(op2 - op1);
        oper.pop();
    }
    else if (oper.top() == '*')
    {
        int op1 = num.top();
        num.pop();
        int op2 = num.top();
        num.pop();
        num.push(op1 * op2);
        oper.pop();
    }
    else if (oper.top() == '/')
    {
        int op1 = num.top();
        num.pop();
        int op2 = num.top();
        num.pop();
        num.push(op2 / op1);
        oper.pop();
    }
}

long evaluate(const string &expression)
{
    stack<char> oper;
    oper.push('#');
    stack<int> num;
    long result;
    int pos = 0;
    int syntax;

    while ((getSyntax(&syntax, &pos, expression)) >= 0)
    {
        if (0 <= syntax)
        {
            num.push(syntax);
        }
        else
        {
            char op = (char)(-1 * syntax);
            switch (op)
            {
            case '(':
            {
                oper.push('(');
            }
            break;
            case ')':
            {
                while (oper.top() != '(')
                {
                    calulate(oper, num);
                }

                if (oper.top() == '(')
                {
                    oper.pop();
                }
            }
            break;
            case '+':
            case '-':
                while (oper.top() == '*' || oper.top() == '/' || oper.top() == '+' || oper.top() == '-')
                {
                    calulate(oper, num);
                }
                oper.push(op);
                break;
            case '*':
            case '/':
                while (oper.top() == '*' || oper.top() == '/')
                {
                    calulate(oper, num);
                }
                oper.push(op);
                break;
            default:
                break;
            }
        }
    }
    while (oper.top() != '#')
    {
        calulate(oper, num);
    }
    return num.top();
}

int main(int argc, char const *argv[])
{
    cout << "result: " << evaluate("5 * 5 * (    2+    2)*(4+1)   /     5") << endl;
    cout << "result: " << evaluate("5 * (2+2)*(4+1)") << endl;
    return 0;
}
