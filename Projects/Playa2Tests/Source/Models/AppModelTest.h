#pragma once

#include <juce_core/juce_core.h>
using namespace juce;

#include "../TestUtils.h"
#include "../UnitTest.h"

class AppModelTest : public thmstudio::UnitTest
{
public:
    AppModelTest() : UnitTest ("AppModelTest") {}

    virtual void runTest() override;
    void testSetCurrentEntry();
};

static AppModelTest appModelTest;
