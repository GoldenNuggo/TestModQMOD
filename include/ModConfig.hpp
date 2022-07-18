#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(SoloText, std::string, "Solo Button Text", "SOLO!");
    CONFIG_VALUE(VarA, std::string, "Name", "Solo!");
    CONFIG_VALUE(VarB, bool, "Enable DLC Screen", true);  
 
    CONFIG_INIT_FUNCTION(
    
        CONFIG_INIT_VALUE(SoloText);
        CONFIG_INIT_VALUE(VarA);
        CONFIG_INIT_VALUE(VarB);
    )
)