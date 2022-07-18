#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(SoloText, std::string, "Name", "Solo!");
    CONFIG_VALUE(DLCRemover, bool, "Disable DLC Screen", true);  
    CONFIG_VALUE(SoloRemover, bool, "Remove the Solo Button (Why)", false);
 
    CONFIG_INIT_FUNCTION(
    
        CONFIG_INIT_VALUE(SoloText);
        CONFIG_INIT_VALUE(DLCRemover);
        CONFIG_INIT_VALUE(SoloRemover);
    )
)