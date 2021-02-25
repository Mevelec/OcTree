#include "pch.h"
#include "CppUnitTest.h"

#include <OcTreeDefault.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OcTreeTests
{
	TEST_CLASS(OcTreeTests)
	{
	public:
		
		TEST_METHOD(OcTree)
		{
			OcTree::OcTreeDefault<int> a;
			a.set(1, 1, 1, 1);
			Assert::AreEqual(1, a.get( 1, 1, 1));
		}
	};
}
