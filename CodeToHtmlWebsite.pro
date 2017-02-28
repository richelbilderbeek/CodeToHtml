
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../WebApplication.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Specific, console
include(../../Classes/CppCodeToHtml/CppCodeToHtml.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppQrcFile/CppQrcFile.pri)
include(../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri)

#Specific
include(ToolCodeToHtmlWebsite.pri)

SOURCES += wtmain.cpp

# Fixes
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals
