#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <csignal>
#include <iostream>

#include <QApplication>

#include "codetohtml.h"
#include "qtcreatorprofile.h"
#include "qtcodetohtmlmenudialog.h"
#include "codetohtmldialog.h"
#include "fileio.h"

#pragma GCC diagnostic pop

/*
void OnAbort(int)
{
  std::cerr << "Application called OnAbort" << std::endl;
  std::exit(1);
}
*/

int main(int argc, char *argv[])
{
  //Connect the abort signal to the OnAbort, to obtain informative
  //screen output with 'Projects | Run | Run in terminal' unchecked
  //std::signal(SIGABRT,OnAbort);

  QApplication a(argc, argv);
  try
  {
    #ifndef _WIN32
    assert(ribi::c2h::IsTidyInstalled() && "I really want to be sure that tidy is installed");
    #endif

    #ifndef NDEBUG
    ribi::fileio::FileIo();
    assert( ribi::fileio::FileIo().IsRegularFile(argv[0]));
    assert(!ribi::fileio::FileIo().IsFolder(argv[0]));
    #endif

    ribi::c2h::QtCodeToHtmlMenuDialog w;
    w.show();
    return a.exec();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception thrown: " << e.what() << std::endl;
    return 1;
  }
}
