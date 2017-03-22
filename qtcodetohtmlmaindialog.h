#ifndef QTCODETOHTMLMAINDIALOG_H
#define QTCODETOHTMLMAINDIALOG_H

//#include <string>
//#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "codetohtmlfiletype.h"
#include "codetohtmlsnippettype.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QPlainTextEdit;

namespace Ui {
  class QtCodeToHtmlMainDialog;
}

namespace ribi {
namespace c2h {

class QtCodeToHtmlMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtCodeToHtmlMainDialog(QWidget *parent = 0) noexcept;
  QtCodeToHtmlMainDialog(const QtCodeToHtmlMainDialog&) = delete;
  QtCodeToHtmlMainDialog& operator=(const QtCodeToHtmlMainDialog&) = delete;
  ~QtCodeToHtmlMainDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *) noexcept;

private:
  Ui::QtCodeToHtmlMainDialog *ui;

  ///Display the HTML code as web page and plain text
  void Display(const std::vector<std::string>& v) noexcept;

  ///Convert a QPlainTextEdit to std::vector<std::string>
  static std::vector<std::string> EditToVector(const QPlainTextEdit * const edit) noexcept;

private slots:

  ///Obtain the selected header type
  //c2h::PageType GetPageType() const noexcept;

  ///Obtain the selected technical info type
  //c2h::TechInfoType GetTechInfo() const noexcept;

  ///Obtain the selected source type
  //c2h::FileType GetContentType() const noexcept;

  ///Respond to click on Convert button
  void on_button_convert_clicked() noexcept;

  void on_tab_source_currentChanged(int index) noexcept;

  ///Respond to a change in the edit containing the source file or source folder
  void on_edit_source_textChanged(QString ) noexcept;
};

} //~namespace c2h
} //~namespace ribi

#endif // QTCODETOHTMLMAINDIALOG_H
