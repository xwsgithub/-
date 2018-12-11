#pragma once
#include<iostream>
using namespace std;
template<typename T>
class m_stack
{
    T m_array[100];
    int count;
public:
    m_stack();
    ~m_stack();
    T top();
    T pop();
    void print();
    void push(T item);
    bool empty();
};
template<typename T>
m_stack<T>::m_stack()
{
    
    count = -1;
}
template<typename T>
m_stack<T>::~m_stack()
{
}
template<typename T>
T m_stack<T>::top()
{
    if (count == -1)
        cout << "Underflow!!!";
    return m_array[count];
}
template<typename T>
T m_stack<T>::pop()
{
    if (count <= -1)
    {
        cout << "Underflowab!!!";
        return ' ';
    }
    count--;
    return m_array[count+1];
}
template<typename T>
void m_stack<T>::push(T item)
{
    if (count >= 99)
    {
        cout << "Overflow!!!";
        return;
    }
    m_array[count+1] = item;
    count++;
}
template<typename T>
bool m_stack<T>::empty()
{
    return (count == -1 ? true : false);
}
template<typename T>
void m_stack<T>::print()
{
    for (int i = 0; i <= count; i++)
        cout << m_array[i] << "  ";
}

