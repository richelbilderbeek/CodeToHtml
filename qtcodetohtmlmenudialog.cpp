#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtcodetohtmlmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "codetohtmlinfo.h"
#include "codetohtmlmenudialog.h"
#include "qtaboutdialog.h"
#include "qtcodetohtmlmaindialog.h"

#include "qthideandshowdialog.h"

#include "ui_qtcodetohtmlmenudialog.h"
#pragma GCC diagnostic pop

ribi::c2h::QtCodeToHtmlMenuDialog::QtCodeToHtmlMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtCodeToHtmlMenuDialog)
{
  ui->setupUi(this);
}

ribi::c2h::QtCodeToHtmlMenuDialog::~QtCodeToHtmlMenuDialog() noexcept
{
  delete ui;
}

void ribi::c2h::QtCodeToHtmlMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_about_clicked() noexcept
{
  ribi::About a = CodeToHtmlMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_start_clicked() noexcept
{
  QtCodeToHtmlMainDialog d;
  ShowChild(&d);
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_test_1_clicked()
{
  Info::TestIfAllCreatedPagesAreValid();
  ui->button_test_1->setText("PASSED!");
  ui->button_test_1->setEnabled(false);
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_test_2_clicked()
{
  //ribi::c2h::CodeToHtmlMenuDialog::TestAllProgramsHaveInfo();
  ui->button_test_2->setText("Does nothing");
  ui->button_test_2->setEnabled(false);
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_test_3_clicked()
{
  ui->button_test_3->setText("PASSED!");
  ui->button_test_3->setEnabled(false);
}
