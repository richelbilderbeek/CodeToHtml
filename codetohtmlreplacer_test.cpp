#include "codetohtmlreplacer.h"

#include <iostream>
#include <boost/test/unit_test.hpp>

#include "codetohtmlreplacements.h"

using namespace ribi::c2h;

BOOST_AUTO_TEST_CASE(c2h_replacer)
{
  Replacer().GetReplacementsCpp();
  Replacer().GetReplacementsPro();
  Replacer().GetReplacementsTxt();


  //Test for correct replacements
  {
    const std::vector<std::pair<std::string,std::string> > v {
      { "C++ Builder", "<a href=\"CppBuilder.htm\">C++ Builder</a>" },
      { "BeerWanter", "<a href=\"GameBeerWanter.htm\">BeerWanter</a>" },
      { "int main()", "<b><a href=\"CppInt.htm\">int</a></b> <a href=\"CppMain.htm\">main</a>()" },
      { "boenken", "<a href=\"GameBoenken.htm\">boenken</a>" },
      { "; ++i)", "; <a href=\"CppOperatorIncrement.htm\">++</a>i)" },
      { "C++11", "<a href=\"Cpp11.htm\">C++11</a>" },
      { "C++0x", "<a href=\"Cpp0x.htm\">C++0x</a>" },
      { "C++", "<a href=\"Cpp.htm\">C++</a>" },
      { "++", "<a href=\"CppOperatorIncrement.htm\">++</a>" },
      { "--", "<a href=\"CppOperatorDecrement.htm\">--</a>" }
    };
    std::for_each(v.begin(),v.end(),
      [](const std::pair<std::string,std::string>& p)
      {
        const std::string& s = p.first;
        const std::string t = Replacer().MultiReplace(s,Replacer().GetReplacementsCpp().Get());
        const std::string expected = p.second;
        BOOST_CHECK(t == expected);
      }
    );
  }
  {
    std::stringstream s;
    s << "Number of C++ replacements: " << Replacer().GetReplacementsCpp().Get().size();
    std::clog << s.str();
  }
  {
    std::stringstream s;
    s << "Number of .pro file replacements: " << Replacer().GetReplacementsPro().Get().size();
    std::clog << s.str();
  }
}
