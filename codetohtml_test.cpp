#include "codetohtml.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::c2h;

BOOST_AUTO_TEST_CASE(c2h_codetohtml)
{
  //Test SortedFiles
  {
    const std::vector<std::string> result
      =
      {
        "a.pro",
        "b.pro",
        "c.pro",
        "d.pro",
        "e.pro",
        "a.pri",
        "b.pri",
        "a.h",
        "a.cpp",
        "b.h",
        "b.cpp",
        "c.h",
        "c.cpp",
        "d.h",
        "d.cpp",
        "e.h",
        "e.cpp",
        "a.sh",
        "b.sh",
        "c.sh",
        "d.sh",
        "e.sh"
      };
    std::vector<std::string> v = result;
    v.push_back("x.txt"); //Text files should be filtered away
    v.push_back("y.txt"); //Text files should be filtered away
    std::random_shuffle(std::begin(v),std::end(v));
    v = SortFiles(FilterFiles(v));
    BOOST_CHECK(v == result);
  }
}
