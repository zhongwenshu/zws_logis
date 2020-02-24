//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)
//这是免费软件，可以更改源码，但请保留此头部说明，谢谢

//logistics expression
//%railway(zhongtong6666 + yuantong(8888 + 5641)) + %airline(JD0001-1-1)
//it is freeware, you could edit the source code, but please remain this header, thank you

#pragma once
#include <memory>
#include "cppunit\TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"




class LogisExprTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(LogisExprTest);
   CPPUNIT_TEST(test);
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void test();
};