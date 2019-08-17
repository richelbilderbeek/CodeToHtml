#include "codetohtmldialog.h"

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <fstream>
#include "fileio.h"
#include "container.h"
#include "codetohtmlfile.h"
#include "codetohtmlheader.h"
#include "codetohtmlfooter.h"

using namespace ribi;
using namespace ribi::c2h;

BOOST_AUTO_TEST_CASE(c2h_dialog_extract_page_name)
{
  const Dialog d;

  BOOST_CHECK(d.ExtractPageName("X") == "X");
  BOOST_CHECK(d.ExtractPageName("/X") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/X") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B/X") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B/C/X") == "X");
  BOOST_CHECK(d.ExtractPageName("/X/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/X/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B/X/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B/C/X/") == "X");

  BOOST_CHECK(d.ExtractPageName("\\X") == "X");
  BOOST_CHECK(d.ExtractPageName("\\A\\X") == "X");
  BOOST_CHECK(d.ExtractPageName("\\A\\B\\X") == "X");
  BOOST_CHECK(d.ExtractPageName("\\A\\B\\C\\X") == "X");
  BOOST_CHECK(d.ExtractPageName("\\X\\") == "X");
  BOOST_CHECK(d.ExtractPageName("\\A\\X\\") == "X");
  BOOST_CHECK(d.ExtractPageName("\\A\\B\\X\\") == "X");
  BOOST_CHECK(d.ExtractPageName("\\A\\B\\C\\X\\") == "X");

  BOOST_CHECK(d.ExtractPageName("/X") == "X");
  BOOST_CHECK(d.ExtractPageName("/A\\X") == "X");
  BOOST_CHECK(d.ExtractPageName("/A\\B/X") == "X");
  BOOST_CHECK(d.ExtractPageName("\\A\\B/C/X") == "X");
  BOOST_CHECK(d.ExtractPageName("\\X/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A\\X/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B\\X/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B\\C/X/") == "X");

  BOOST_CHECK(d.ExtractPageName("main.cpp") == "");
  BOOST_CHECK(d.ExtractPageName("/X/main.cpp") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/X/main.cpp") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B/X/main.cpp") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B/C/X/main.cpp") == "X");
  BOOST_CHECK(d.ExtractPageName("/X/main.cpp/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/X/main.cpp/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B/X/main.cpp/") == "X");
  BOOST_CHECK(d.ExtractPageName("/A/B/C/X/main.cpp/") == "X");

  BOOST_CHECK(d.ExtractPageName("/home/richel/ProjectRichelBilderbeek/Tools/CodeToHtml")
    == "CodeToHtml");

}

BOOST_AUTO_TEST_CASE(c2h_dialog)
{
  const Dialog d;

  //GetProFiles
  {
    //Always first remove the temp file
    const std::string filename = fileio::FileIo().GetTempFileName() + ".pro";
    if (ribi::fileio::FileIo().IsRegularFile(filename)) { ribi::fileio::FileIo().DeleteFile(filename); }
    BOOST_CHECK(!ribi::fileio::FileIo().IsRegularFile(filename));

    const std::size_t n = d.GetProFilesInFolder("").size();
    {
      std::ofstream f(filename.c_str());
      f << "tmp";
      f.close();
    }
    const std::size_t p = d.GetProFilesInFolder("").size();
    BOOST_CHECK(n == p - 1);
    ribi::fileio::FileIo().DeleteFile(filename);
    BOOST_CHECK(!ribi::fileio::FileIo().IsRegularFile(filename));
    const std::size_t q = d.GetProFilesInFolder("").size();
    BOOST_CHECK(n == q);
  }
  //Check that .PNG files are
  {
    const std::string tmp_filename{fileio::FileIo().GetTempFileName(".png")};
    { std::ofstream f(tmp_filename); }
    BOOST_CHECK(fileio::FileIo().IsRegularFile(tmp_filename));
    const boost::shared_ptr<File> content { new File(tmp_filename) };
    const std::vector<std::string> w = content->GetHtml();
    BOOST_CHECK(w.size() == 8);
    BOOST_CHECK(w[0].substr(0,4) == "<h2>");
    BOOST_CHECK(w[1] == "<p>&nbsp;</p>");
    BOOST_CHECK(w[2].substr(0,11) == "<p><img src");
    BOOST_CHECK(w[3] == "<p>&nbsp;</p>");
    fileio::FileIo().DeleteFile(tmp_filename);
  }
  //DeduceFolderType

  //Check if Info is added

  //Check if CodeToHtml creates a clean HTML file when it converts itself
  #ifndef _WIN32
  BOOST_CHECK(IsTidyInstalled() && "While I know I have tidy installed");
  if (IsTidyInstalled())
  {
    const std::string filename = "../CodeToHtml/qtmain.cpp";
    if (ribi::fileio::FileIo().IsRegularFile(filename))
    {
      std::vector<std::string> v;
      {
        const auto w = Header::ToHtml(HeaderType::cpp,filename);
        std::copy(std::begin(w),std::end(w),std::back_inserter(v));
      }
      {
        const auto w = d.FileToHtml(filename);
        std::copy(std::begin(w),std::end(w),std::back_inserter(v));
      }
      {
        const auto w = Footer::ToHtml();
        std::copy(std::begin(w),std::end(w),std::back_inserter(v));
      }
      if (!IsCleanHtml(v))
      {
        std::ofstream f("tmp_to_check.htm");
        f << Container().Concatenate(v,"\n");
      }
      BOOST_CHECK(IsCleanHtml(v) && "Assume tidy HTML, inspect tmp_to_check.htm");
    }
    else
    {
      std::clog << "Warning: CodeToHtml has not tested itself on its own code upon construction";
    }
  }
  else
  {
    std::clog << "WARNING: 'tidy' not found, check if CodeToHtml generates clean HTML code is skipped";
  }
  #endif
}


BOOST_AUTO_TEST_CASE(c2h_dialog_convert_folder)
{
  #ifdef FIX_ISSUE_1
  if (IsTidyInstalled())
  {
    const std::string path = "../CodeToHtml";
    if (ribi::fileio::FileIo().IsFolder(path))
    {
      std::vector<std::string> v;
      {
        //const auto w = Header::ToHtml(HeaderType::cpp,path);
        //std::copy(std::begin(w),std::end(w),std::back_inserter(v));
      }
      {
        const auto w = d.FolderToHtml(path);
        std::copy(std::begin(w),std::end(w),std::back_inserter(v));
      }
      {
        //const auto w = Footer::ToHtml(FooterType::cpp);
        //std::copy(std::begin(w),std::end(w),std::back_inserter(v));
      }
      if (!IsCleanHtml(v))
      {
        std::ofstream f("tmp_to_check.htm");
        f << Container().Concatenate(v,"\n");
      }
      BOOST_CHECK(IsCleanHtml(v) && "Assume tidy HTML, inspect tmp_to_check.htm");
    }
    else
    {
      std::clog << "Warning: CodeToHtml has not tested itself on its own code upon construction";
    }
  }
  else
  {
    std::clog << "WARNING: 'tidy' not found, check if CodeToHtml generates clean HTML code is skipped";
  }
  #endif // FIX_ISSUE_1
}
