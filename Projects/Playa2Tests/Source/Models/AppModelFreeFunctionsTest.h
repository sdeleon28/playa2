#pragma once

#include <juce_core/juce_core.h>
using namespace juce;

#include "../TestUtils.h"
#include "../UnitTest.h"

class AppModelFreeFunctionsTest : public thmstudio::UnitTest
{
public:
    AppModelFreeFunctionsTest() : UnitTest ("AppModelFreeFunctionsTest") {}

    virtual void runTest() override;
    void testBasicModelCreation();
};

static AppModelFreeFunctionsTest appModelFreeFunctionsTest;
