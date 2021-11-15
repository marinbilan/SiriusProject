#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include <memory>

#include "Factory.h"
#include "Widget.h"

// Important!
using ::testing::_;
using ::testing::An;
using ::testing::AtLeast;

// ---- TEST FIXTURE ----
class WidgetTest : public testing::Test
{
public:

    // Before Each Test
    void SetUp()
    {
        p_testClass = std::make_unique<Mayers::TestClass>(42);
        // p_widget = std::make_unique<Mayers::Widget>(42);

    }
    // After Each Test
    void TearDown()
    {

    }

std::unique_ptr<Mayers::TestClass> p_testClass;
// std::unique_ptr<Mayers::Widget> p_widget;
};

// CASE 1 - Method argument is not reference, not pointer - f(Widget widget)
// ----
TEST_F(WidgetTest, TestCase_1)
{
    // std::unique_ptr<Mayers::Widget> p_widget = std::make_unique<Mayers::Widget>(42);
    Mayers::Widget widget_0(0);
    Mayers::Widget widget_1(0);

    // CASE : 1.1 - [ Move constructor ] called
    // Passing lvalue
    p_testClass->f(widget_0);

    // CASE : 1.2 - [ Assignment Operator ] called
    widget_1 = widget_0;

    // ----
    // CASE : 1.3 - [ Move Copy Constructor ] Called
    // Passing rvalue
    p_testClass->f(std::move(widget_0));

    // IMPORTANT CONST CASE:
    // This will not call MOVE COPY CONSTRUCTOR because we apply std::move on const object!
    // This will call COPY CONSTRUCTOR
    const Mayers::Widget constWidget(0);
    p_testClass->f(std::move(constWidget));

    // CASE : 1.4 - [ Move Assignmet Operator ] Called
    // Widget widget_1 is already moved, so it is not valid any more
    Mayers::Widget widget_2(0);
    Mayers::Widget widget_3(0);
    widget_2 = std::move(widget_3);
}


