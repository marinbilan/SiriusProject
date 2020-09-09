#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include <memory>

#include "Mayers.h"

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

    }
    // After Each Test
    void TearDown()
    {

    }

std::unique_ptr<Mayers::MayersIf> p;
};


TEST_F(EventHandlerTest, test0) 
{ 
    p->toString();
    p->testItem10_0();
}