include(../RibiLibraries/DesktopApplication.pri)
include(../RibiLibraries/Boost.pri)

include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralDesktop.pri)

include(../RibiClasses/CppContainer/CppContainer.pri)
include(CppCodeToHtml.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppQrcFile/CppQrcFile.pri)
include(../RibiClasses/CppQtCreatorProFile/CppQtCreatorProFile.pri)

include(CodeToHtmlDesktop.pri)

SOURCES += qtmain.cpp

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: ‘qInitResources_[*]__init_variable__’ defined but not used
# [*]: the resource filename
QMAKE_CXXFLAGS += -Wno-unused-variable

# Fixes
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals

RESOURCES += \
    ToolCodeToHtml.qrc
