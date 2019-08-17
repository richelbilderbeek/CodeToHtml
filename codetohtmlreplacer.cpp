#include "codetohtmlreplacer.h"

#include <algorithm>
#include <cassert>
#include <sstream>
#include <iostream>
#include <functional>
#include "codetohtmlreplacements.h"
#include "codetohtmlreplacer.h"



boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::Replacer::m_replacements_cpp {};
boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::Replacer::m_replacements_pro {};
boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::Replacer::m_replacements_txt {};

ribi::c2h::Replacer::Replacer()
{

}

const ribi::c2h::Replacements& ribi::c2h::Replacer::GetReplacementsCpp()
{
  if (!m_replacements_cpp)
  {
    m_replacements_cpp.reset(
      new Replacements(
        ribi::c2h::CreateCppReplacements()));
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
        ribi::c2h::CreateProReplacements()));
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
      assert(false);
    case FileType::license_txt:
      assert(false);
    case FileType::n_types:
      assert(false);
  }

  std::vector<std::string> v { text };
  for (std::string& s: v)
  {
    s = MultiReplace(s,get_replacements().Get());
  }
  return v;
}

