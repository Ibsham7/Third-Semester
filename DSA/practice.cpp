#include <iostream>
#include<stack>
using namespace std;


bool validateExp(string expression){
    stack<char> s;

    for(char ch : expression){
        if( ch == '(' || ch == '{' || ch == '['){
            s.push(ch);
        }
        else if ( ch == ')' || ch == '}' || ch == ']'){
            char temp = s.top();
            if ((temp == '(' && ch == ')') ||(temp == '{' && ch == '}') || (temp == '[' && ch == ']') )
                s.pop();
            else 
            return false;
        }
    }
    return s.empty() ? 1 : 0;
}

int main() { 

cout << validateExp("{ x + (y – [a +b]) }")<<endl;
cout << validateExp("{a+b}")<<endl;


return 0 ;}