#include "codetohtmlfiletypes.h"

#include <boost/test/unit_test.hpp>

#include "codetohtmlfiletype.h"

using namespace ribi::c2h;

BOOST_AUTO_TEST_CASE(c2h_filetypes)
{
  FileTypes f;
  //Test conversion between
  {
    const auto v = f.GetAllFileTypes();
    for (const auto& t:v)
    {
      BOOST_CHECK(f.StrToFileType(f.FileTypeToStr(t)) == t);
    }
  }
  //Be gentle
  BOOST_CHECK(f.DeduceFileType("tmp.png") == FileType::png);
  BOOST_CHECK(f.DeduceFileType("tmp.pro") == FileType::pro);
  BOOST_CHECK(f.DeduceFileType("tmp.c"  ) == FileType::cpp);
  BOOST_CHECK(f.DeduceFileType("tmp.cpp") == FileType::cpp);
  BOOST_CHECK(f.DeduceFileType("tmp.h"  ) == FileType::cpp);
  BOOST_CHECK(f.DeduceFileType("tmp.hpp") == FileType::cpp);
  BOOST_CHECK(f.DeduceFileType("tmp.sh" ) == FileType::sh);
  BOOST_CHECK(f.DeduceFileType("tmp.txt") == FileType::txt);
  BOOST_CHECK(f.DeduceFileType("tmp.py" ) == FileType::py);
  BOOST_CHECK(f.DeduceFileType("tmp.xyz") == FileType::txt);
  //Be nasty
  BOOST_CHECK(f.DeduceFileType("cpp.pro") == FileType::pro);
  BOOST_CHECK(f.DeduceFileType("h.c"    ) == FileType::cpp);
  BOOST_CHECK(f.DeduceFileType("hpp.cpp") == FileType::cpp);
  BOOST_CHECK(f.DeduceFileType("sh.h"   ) == FileType::cpp);
  BOOST_CHECK(f.DeduceFileType("txt.hpp") == FileType::cpp);
  BOOST_CHECK(f.DeduceFileType("py.sh"  ) == FileType::sh);
  BOOST_CHECK(f.DeduceFileType("xyz.txt") == FileType::txt);
  BOOST_CHECK(f.DeduceFileType("pro.py" ) == FileType::py);
  BOOST_CHECK(f.DeduceFileType("c.xyz"  ) == FileType::txt);
}
