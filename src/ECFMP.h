#pragma once

#include <memory>
#include <string>

#pragma warning(push, 0)
#include "EuroScopePlugIn.h"
#pragma warning(pop)

namespace ecfmp {
class ECFMP : public EuroScopePlugIn::CPlugIn {
   public:
    ECFMP();
    ~ECFMP();

    void DisplayMessage(const std::string &message, const std::string &sender = "ECFMP");
};
}  // namespace ecfmp
