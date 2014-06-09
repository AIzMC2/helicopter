/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_EH
#define _CXXTEST_ABORT_TEST_ON_FAIL
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ParenPrinter.h>
#include <cxxtest/Win32Gui.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::GuiTuiRunner<CxxTest::Win32Gui, CxxTest::ParenPrinter>  tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::GuiTuiRunner<CxxTest::Win32Gui, CxxTest::ParenPrinter>  >( tmp, argc, argv );
    return status;
}
bool suite_HelicopterTests_init = false;
#include "HelicopterTests.h"

static HelicopterTests suite_HelicopterTests;

static CxxTest::List Tests_HelicopterTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_HelicopterTests( "HelicopterTests.h", 17, "HelicopterTests", suite_HelicopterTests, Tests_HelicopterTests );

static class TestDescription_suite_HelicopterTests_testIsScriptRunning : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_HelicopterTests_testIsScriptRunning() : CxxTest::RealTestDescription( Tests_HelicopterTests, suiteDescription_HelicopterTests, 21, "testIsScriptRunning" ) {}
 void runTest() { suite_HelicopterTests.testIsScriptRunning(); }
} testDescription_suite_HelicopterTests_testIsScriptRunning;

static class TestDescription_suite_HelicopterTests_testVerticalTravel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_HelicopterTests_testVerticalTravel() : CxxTest::RealTestDescription( Tests_HelicopterTests, suiteDescription_HelicopterTests, 27, "testVerticalTravel" ) {}
 void runTest() { suite_HelicopterTests.testVerticalTravel(); }
} testDescription_suite_HelicopterTests_testVerticalTravel;

static class TestDescription_suite_HelicopterTests_testHorizontalTravel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_HelicopterTests_testHorizontalTravel() : CxxTest::RealTestDescription( Tests_HelicopterTests, suiteDescription_HelicopterTests, 52, "testHorizontalTravel" ) {}
 void runTest() { suite_HelicopterTests.testHorizontalTravel(); }
} testDescription_suite_HelicopterTests_testHorizontalTravel;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
