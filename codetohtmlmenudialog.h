#ifndef CODETOHTMLMENUDIALOG_H
#define CODETOHTMLMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"
#include "codetohtmlfwd.h"

namespace ribi {
namespace c2h {

///GUI independent CodeToHtml menu dialog
struct CodeToHtmlMenuDialog final : public MenuDialog
{
  CodeToHtmlMenuDialog();
  ~CodeToHtmlMenuDialog() noexcept {}
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;

  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLMENUDIALOG_H
