#ifndef CODETOHTMLFILETYPE_H
#define CODETOHTMLFILETYPE_H

namespace ribi {
namespace c2h {

///The type of file
enum class FileType
{
  cpp,          //.cpp file
  license_txt,  //license.txt file
  png,          //.png image file
  pri,          //.pri file
  pro,          //.pro file
  py,           //.py file
  sh,           //.sh file
  txt,          //.txt file, to be renamed to txt
  n_types       //Used for debugging
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLFILETYPE_H
