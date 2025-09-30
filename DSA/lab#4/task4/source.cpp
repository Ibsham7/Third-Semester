#include<iostream>
#include<string>
#include"LinkedList.h"
#include"student.h"
using namespace std;
template <typename T>

T getMax(const T& a, const T& b) {
	return (a < b) ? b : a;
}

int main()
{
	cout << "\n get max " << getMax(22.2, 44.0);
	cout << "\n get max  " << getMax(string("aabc"), string("aazy"));
	cout << " \n get max  " << getMax(3, 2);

	Student s1(1, "aimal", 2.4);
	Student s2(2, "rextin", 3.5);
	
	cout << "\n s1 is" << s1;
	cout << "\n s2 is " << s2;

	cout << "\n is equal " << (s1==s1);
	cout << "\n is less " << (s2 < s1);


	cout << "\n";
	LinkedList<float> list;
	list.addAtFront(2.4);
	list.addAtFront(5.3);
	list.printList();

	LinkedList<char> lc;
	lc.addAtFront('a');
	lc.addAtFront('c');
	lc.printList();

	LinkedList<string> ls;
	ls.addAtFront("Data");
	ls.addAtFront("Structures");
	ls.addAtFront("& Algorithms");
	ls.printList();

	LinkedList<Student> lst;
	lst.addAtFront(s1);
	lst.addAtFront(s2);
	lst.printList();
	
	return 0;
	
}