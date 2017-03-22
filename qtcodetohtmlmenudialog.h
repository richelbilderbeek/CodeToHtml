#ifndef QTCODETOHTMLMENUDIALOG_H
#define QTCODETOHTMLMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtCodeToHtmlMenuDialog;
}

namespace ribi {
namespace c2h {

class QtCodeToHtmlMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtCodeToHtmlMenuDialog(QWidget *parent = 0) noexcept;
  QtCodeToHtmlMenuDialog(const QtCodeToHtmlMenuDialog&) = delete;
  QtCodeToHtmlMenuDialog& operator=(const QtCodeToHtmlMenuDialog&) = delete;
  ~QtCodeToHtmlMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtCodeToHtmlMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  void on_button_test_1_clicked();
  void on_button_test_2_clicked();
  void on_button_test_3_clicked();
};

} //~namespace c2h
} //~namespace ribi

#endif // QTCODETOHTMLMENUDIALOG_H
