#include "codetohtmlreplacer.h"

#include <algorithm>
#include <cassert>
#include <sstream>
#include <iostream>

#include "codetohtmlreplacements.h"



boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::Replacer::m_replacements_cpp {};
boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::Replacer::m_replacements_pro {};
boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::Replacer::m_replacements_txt {};

ribi::c2h::Replacer::Replacer()
{
  #ifndef NDEBUG
  Test();
  #endif
}

const ribi::c2h::Replacements& ribi::c2h::Replacer::GetReplacementsCpp()
{
  if (!m_replacements_cpp)
  {
    m_replacements_cpp.reset(
      new Replacements(
        ribi::c2h::Replacer::CreateCppReplacements()));
  }
  assert(m_replacements_cpp);
  return *m_replacements_cpp;
}

const ribi::c2h::Replacements& ribi::c2h::Replacer::GetReplacementsPro()
{
  if (!m_replacements_pro)
  {
    m_replacements_pro.reset(
      new Replacements(
        ribi::c2h::Replacer::CreateProReplacements()));
  }
  assert(m_replacements_pro);
  return *m_replacements_pro;
}

const ribi::c2h::Replacements& ribi::c2h::Replacer::GetReplacementsTxt()
{
  if (!m_replacements_txt)
  {
    m_replacements_txt.reset(
      new Replacements(
        std::vector<std::pair<std::string,std::string> >()));
  }
  assert(m_replacements_txt);
  return *m_replacements_txt;
}

std::string ribi::c2h::Replacer::MultiReplace(const std::string& line, const std::vector<std::pair<std::string,std::string> >& replacements)
{
  std::string s(line);
  typedef std::vector<std::pair<std::string,std::string> >::const_iterator Iterator;
  const Iterator j = replacements.end();
  for (Iterator i = replacements.begin(); i!=j; ++i)
  {
    const std::string from = i->first;
    const std::string to = i->second;
    s = ReplaceAll(s,from,to);
  }
  return s;
}

//From http://www.richelbilderbeek.nl/CppReplaceAll.htm
std::string ribi::c2h::Replacer::ReplaceAll(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat)
{
  while(1)
  {
    const size_t pos = s.find(replaceWhat);
    if (pos==std::string::npos) break;
    s.replace(pos,replaceWhat.size(),replaceWithWhat);
  }
  return s;
}

#ifndef NDEBUG
void ribi::c2h::Replacer::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
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
        const std::string t = Replacer().MultiReplace(s,GetReplacementsCpp().Get());
        const std::string expected = p.second;
        assert(t == expected);
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
#endif

std::vector<std::string> ribi::c2h::Replacer::ToHtml(
  const std::vector<std::string>& text,
  const FileType file_type
  ) noexcept
{
  std::function<const Replacements&()> get_replacements;
  switch (file_type)
  {
    case FileType::cpp:
      get_replacements = &ribi::c2h::Replacer::GetReplacementsCpp;
      break;
    case FileType::py:
    case FileType::sh:
    case FileType::txt:
      get_replacements = &ribi::c2h::Replacer::GetReplacementsTxt;
      break;
    case FileType::pri:
    case FileType::pro:
      get_replacements = &ribi::c2h::Replacer::GetReplacementsPro;
      break;
    case FileType::png:
      assert(!"Do not HTML-ify FileType::png, display it instead");
      throw std::logic_error("Never HTML-ify FileType::png, display it instead");
    case FileType::license_txt:
      assert(!"Do not HTML-ify FileType::license_txt");
      throw std::logic_error("Never HTML-ify FileType::license_txt");
    case FileType::n_types:
      assert(!"Never use FileType::n_types");
      throw std::logic_error("Never use FileType::n_types");
  }

  std::vector<std::string> v { text };
  for (std::string& s: v)
  {
    s = MultiReplace(s,get_replacements().Get());
  }
  return v;
}

