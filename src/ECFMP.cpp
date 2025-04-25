#include "ECFMP.h"

#include "Version.h"

namespace ecfmp {
ECFMP::ECFMP()
    : EuroScopePlugIn::CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, PLUGIN_NAME, PLUGIN_VERSION, PLUGIN_AUTHOR,
                               PLUGIN_LICENSE) {}
ECFMP::~ECFMP() {}

}  // namespace ecfmp