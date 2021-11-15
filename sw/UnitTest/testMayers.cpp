#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include <memory>

#include "Factory.h"
#include "Mayers.h"
// #include "Widget.h"

// Important!
using ::testing::_;
using ::testing::An;
using ::testing::AtLeast;

// ---- TEST FIXTURE ----
class EventHandlerTest : public testing::Test
{
public:

    // Before Each Test
    void SetUp()
    {
        p = std::make_unique<Mayers::Mayers>(42);
        p_template = std::make_unique<Mayers::Mayers>(42);
        // Test Widget
        // p_widget = std::make_unique<Mayers::Widget>(42);

        // FACTORY
        // Common::Factory::Factory::getInstance();

    }
    // After Each Test
    void TearDown()
    {

    }

std::unique_ptr<Mayers::MayersIf> p;
std::unique_ptr<Mayers::Mayers> p_template;
// std::unique_ptr<Mayers::Widget> p_widget;
};

// ITEM: 1 - Case 1 : ParamType is a Reference or Pointer, but not a Universal Reference
// ----
TEST_F(EventHandlerTest, DISABLED_Case_1_Case_NOTConst)
{
    /*
    template<typename T>
    void f(ParamType param)
    */

    // [Case 1] : paramType - T& is a Reference but not a Universal Reference
    // [Case 1.1]
    // T is int, param's type is int&
    int x = 0;
    p_template->f(x);
    // x changed value to 27
    std::cout << "Test x = " << x << '\n';

    // [Case 1.2]
    // T is const int (Unable to change cx value)
    const int cx = x;
    // error: assignment of read-only reference ‘param’
    // p_template->f(cx);

    // [Case 1.3]
    // IMPORTANT: T is const int&, NOT const int &&
    const int& rx = x;
    // error: assignment of read-only reference ‘param’
    // p_template->f(rx);

    // In case of T& -> const T& - const contT& -> const T& (Two const reduction in one const)
    // Everything is the same for ...(T* param) 
}

TEST_F(EventHandlerTest, DISABLED_Case_1_Case_Const)
{
    /*
    template<typename T>
    void f(ParamType param)
    */

    // [Case 1] : param is now a ref-to-const
    // [Case 1.1]
    // T is int, param's type is const int&
    int x = 0;
    p_template->ff(x);

    /*
    IMPORTANT: For case 1.2 and 1.3:
    If we change the type of f’s parameter from T& to const T&, things change a little, but
    not in any really surprising ways. The constness of cx and rx continues to be respected,
    but because we’re now assuming that param is a reference-to-const, there’s no
    longer a need for const to be deduced as part of T
    */

    // [Case 1.2]
    // T is int, param's type is const int&
    const int cx = x;

    // [Case 1.3]
    // T is int, param's type is const int&
    const int& rx = x;
}

// ITEM: 1 - Case 2 : ParamType is a Universal Reference
TEST_F(EventHandlerTest, DISABLED_Case_2)
{
    /*
    template<typename T>
    void f(ParamType param)
    */

    // [Case 2] : paramType is a Universal Reference
    // [Case 2.1]
    // IMPORTANT: Here is reduction (int&)& to int& because x is lvalue
    // x is lvalue, so T is int&, param's type is also int&
    int x = 0;
    p_template->fff(x);
    // x changed value to 27
    std::cout << "Test x = " << x << '\n';

    // [Case 2.2]
    // cx is lvalue, so T is const int&, param's type is also const int&
    const int cx = x;
    // error: assignment of read-only reference ‘param’
    // p_template->fff(cx);

    // [Case 2.3]
    // rx is lvalue, so T is const int&, param's type is also const int&
    const int& rx = x;
    // error: assignment of read-only reference ‘param’
    // p_template->f(rx);

    // [Case 2.4]
    // 27 is rvalue, so T is int, param's type is therefore int&&
    p_template->fff(27);

    // SUMMARY: Type deduction distinquish between lvalue and rvalue args
}

// ----
TEST_F(EventHandlerTest, DISABLED_test0) 
{ 
    p->toString();
    p->testItem10_0();

    Common::Factory::Factory::getInstance();
}

TEST_F(EventHandlerTest, DISABLED_test1) 
{ 
    p->toString();
    p->testItem10_0();

    Common::Factory::Factory::getInstance();
}