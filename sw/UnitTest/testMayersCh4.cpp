#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include <memory>

// #include "Factory.h"
#include "MayersCh4.h"

// Important!
using ::testing::_;
using ::testing::An;
using ::testing::AtLeast;

// ---- TEST FIXTURE ----
class MayersCh4Test : public testing::Test
{
public:

    // Before Each Test
    void SetUp()
    {
        testInst = std::make_unique<Mayers::MayersCh4>(42);
        testInst_templ = std::make_unique<Mayers::MayersCh4>(42);

    }
    // After Each Test
    void TearDown()
    {

    }

std::unique_ptr<Mayers::MayersIf> testInst;
std::unique_ptr<Mayers::MayersCh4> testInst_templ;
};

// CH4 : ITEM: 18 Case: 0
// ----
TEST_F(MayersCh4Test, DISABLED_CH4_Item18_0)
{
    std::cout << " ==== This is Chapter 4 test ==== " << '\n';

    // Test : 1
    // IMPORTANT: Order of arguments is important
    /*
    template<typename ...Ts, typename U, typename=void>
    void valid(U, Ts...);     // OK: can deduce U
    // void valid(Ts..., U);  // Can't be used: Ts... is a non-deduced context in this position
    */
    testInst_templ->makeInvestment("Stock", 0);
}

