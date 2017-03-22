#include "qtcodetohtmlmaindialog.h"

void ribi::c2h::QtCodeToHtmlMainDialog::Test() noexcept
{
  {
    QtCodeToHtmlMainDialog d;
    for (int index = 0; index != 2; ++index)
    {
      d.ui->tab_source->setCurrentIndex(index);
      for (const std::string& s:
        {
          "/home/richel/ProjectRichelBilderbeek/Tools/ToolTestAbout",
          "D:/Projects/Tools/ToolTestAbout",
          "D:\\Projects\\Tools\\ToolTestAbout",
          "D:/Projects/Test/ToolTestAbout",
          "D:\\Projects\\Test\\ToolTestAbout",
          //"../../Tools/ToolCodeToHtml",
          "..\\..\\Tools\\ToolTestAbout",
          "../../Tools/ToolTestAbout",
          "..\\..\\Tools\\ToolTestAbout",
          "/home/richel/ProjectRichelBilderbeek/Test/ToolTestAbout"
        }
      )
      {
        d.ui->edit_source->setText(s.c_str());
        if (d.ui->button_convert->isEnabled())
        {
          d.on_button_convert_clicked();
        }
      }
    }
  }
}
