//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "codetohtmlfiletypes.h"

#include <cassert>
#include <stdexcept>

#include <boost/xpressive/xpressive.hpp>

#include "codetohtmlfiletype.h"


#pragma GCC diagnostic pop

ribi::c2h::FileTypes::FileTypes()
{

}

bool ribi::c2h::FileTypes::CanStrToFileType(const std::string& s) const noexcept
{
  try
  {
    StrToFileType(s);
    return true;
  }
  catch (std::logic_error&)
  {
    return false;
  }
}

ribi::c2h::FileType ribi::c2h::FileTypes::DeduceFileType(const std::string& filename) const noexcept
{
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(png)\\>") ) )
  {
    return FileType::png;
  }
  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(pri)\\>") ) )
  {
    return FileType::pri;
  }
  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(pro)\\>") ) )
  {
    return FileType::pro;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(c|cpp|h|hpp)\\>") ) )
  {
    return FileType::cpp;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(sh)\\>") ) )
  {
    return FileType::sh;
  }
  else if(filename == "Licence.txt" || filename == "License.txt")
  {
    return FileType::license_txt;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(txt)\\>") ) )
  {
    return FileType::txt;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(py)\\>") ) )
  {
    return FileType::py;
  }
  //return FileType::other;
  return FileType::txt;
}

std::string ribi::c2h::FileTypes::FileTypeToStr(const FileType t) const noexcept
{
  switch (t)
  {
    case FileType::cpp: return "cpp";
    case FileType::license_txt: return "license_txt";
    case FileType::png: return "png";
    case FileType::pri: return "pri";
    case FileType::pro: return "pro";
    case FileType::py: return "py";
    case FileType::sh: return "sh";
    case FileType::txt: return "txt";
    case FileType::n_types:
      assert(!"Should never use FileType::n_types");
      throw std::logic_error("Must never use FileType::n_types");
  }
  assert(!"Should not get here");
  throw std::logic_error("c2h::FileTypeToStr");
}

std::vector<ribi::c2h::FileType> ribi::c2h::FileTypes::GetAllFileTypes() const noexcept
{
  const std::vector<FileType> v {
    FileType::cpp,
    FileType::license_txt,
    FileType::png,
    FileType::pri,
    FileType::pro,
    FileType::py,
    FileType::sh,
    FileType::txt
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(FileType::n_types));
  return v;
}

ribi::c2h::FileType ribi::c2h::FileTypes::StrToFileType(const std::string& s) const noexcept
{
  if (s == "cpp") return FileType::cpp;
  if (s == "license_txt") return FileType::license_txt;
  if (s == "png") return FileType::png;
  if (s == "pri") return FileType::pri;
  if (s == "pro") return FileType::pro;
  if (s == "py") return FileType::py;
  if (s == "sh") return FileType::sh;
  if (s == "txt") return FileType::txt;
  if (s == "n_types")
  {
    assert(!"Should not use FileType::n_types");
    throw std::logic_error("Must not use FileType::n_types");
  }
  assert(!"StrToFileType: should not get here");
  throw std::logic_error("Invalid string in StrToFileType");
}
