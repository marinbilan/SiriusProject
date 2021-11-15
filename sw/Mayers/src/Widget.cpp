#include "Widget.h"


// ---- Widget Class ----
Mayers::Widget::Widget(int id) : m_Id(id)
{
    // std::cout << "[Widget] Constructor called" << '\n';
};

// RULE OF FIVE: 1st RULE - Destructor
Mayers::Widget::~Widget()
{
    // std::cout << "[Widget] Destructor called" << std::endl;
    // delete[] m_dataPtr; // Vazno, polje mora biti inicijalizirano!
}

// RULE OF FIVE: 2nd RULE - Copy Constructor 
Mayers::Widget::Widget(const Widget& other) 
{
    std::cout << "[Widget] Copy Constructor called" << std::endl;

    // 1] Inicijalizirati/deklarirati member varijable 
    // 2] Kopirati member varijable 
    // other ostaviti kakav je 
    // m_dataPtr = new int[other.m_size]; 
    // std::copy(other.m_dataPtr, other.m_dataPtr + other.m_size, m_dataPtr); 
    // m_size = other.m_size; 
}

// RULE OF FIVE: 3th RULE - Assignment Operator
Mayers::Widget& Mayers::Widget::operator=(const Widget& other)
{
    std::cout << "[Widget] Assignment Operator called" << std::endl;

    // 1] Inicijalizirati/deklarirati member varijable 
    // 2] Kopirati member varijable 
    // other ostaviti kakav je 
    // m_dataPtr = new int[other.m_size]; 
    // std::copy(other.m_dataPtr, other.m_dataPtr + other.m_size, m_dataPtr); 
    // m_size = other.m_size; 
}

// RULE OF FIVE: 4th RULE - Move Copy Constructor
Mayers::Widget::Widget(Widget&& other) 
{
    std::cout << "[Widget] Move Constructor called" << std::endl;

    // 1] Inicijalizirati/deklarirati member varijable 
    // 2] Kopirati member varijable 
    // other ostaviti kakav je 
    // m_dataPtr = new int[other.m_size]; 
    // std::copy(other.m_dataPtr, other.m_dataPtr + other.m_size, m_dataPtr); 
    // m_size = other.m_size; 
}

// RULE OF FIVE: 5th RULE - Move Assignment Operator
// NOTE that there is not const (rvalue reference input)
Mayers::Widget& Mayers::Widget::operator=(Widget&& other)
{
    std::cout << "[Widget] Move Assignment Operator called" << std::endl;

}

int Mayers::Widget::getId() const
{
    return m_Id;
}


void Mayers::Widget::toString() const
{
    std::cout << "m_Id: " << m_Id << '\n';
}


// ---- Test Class ----
Mayers::TestClass::TestClass(int id) : m_Id(id)
{
    // std::cout << "[TestClass] Constructor called" << '\n';
};

Mayers::TestClass::~TestClass()
{
    // std::cout << "[TestClass] Destructor called" << std::endl;
}

void Mayers::TestClass::f(Mayers::Widget w)
{
    std::cout << "[TestClass] f method called ..." << std::endl;
}