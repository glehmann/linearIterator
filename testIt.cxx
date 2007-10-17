#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif
#include <iostream>
#include "itkTestMain.h"

#include "itkImageLinearIteratorTest.cxx"

void RegisterTests()
{
REGISTER_TEST(itkImageLinearIteratorTest );
}

