#include <boost/test/unit_test.hpp>
#include <underwater_image_tools/Dummy.hpp>

using namespace underwater_image_tools;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    underwater_image_tools::DummyClass dummy;
    dummy.welcome();
}
