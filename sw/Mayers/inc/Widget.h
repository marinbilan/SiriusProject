#pragma once
#include "MayersIf.h"


namespace Mayers
{

class Widget : public MayersIf
{
public:
	Widget(int id);

    // RULE OF THREE: Destructor, Copy Constructor, Assignment Operator
    // 1] Destructor
    ~Widget();

    // 2] Copy Constructor
    Widget(const Widget& other); 

    // 3] Assingment Operator
    Widget& operator=(const Widget& other);

    // RULE OF FIVE: Move Constructor, Move Assignment Operator
    // 4] Move Constructor
    Widget(Widget&& other);

    // 5] Move Assignment Operator
    Widget& operator=(Widget&& other);

    int getId() const;

    void toString() const;

private:	
int m_Id;
int* m_dataPtr;
int m_size; 
};


class TestClass : public MayersIf
{
public:
    TestClass(int id);

    ~TestClass();

    void f(Mayers::Widget w);

private:    
int m_Id;
};
} // End of namespace

