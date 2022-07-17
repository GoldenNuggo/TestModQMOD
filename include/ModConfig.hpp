#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(VarA, std::string, "Name", "Value");

    CONFIG_VALUE(VarVector2, UnityEngine::Vector2, "Vector2 Example Lul", UnityEngine::Vector2(1, 2));
    CONFIG_VALUE(VarVector3, UnityEngine::Vector3, "Vector3 Example Lul", UnityEngine::Vector3(1, 2, 3));
    CONFIG_VALUE(VarVector4, UnityEngine::Vector4, "Vector4 Example Lul", UnityEngine::Vector4(1, 2, 3, 4));
    
    CONFIG_INIT_FUNCTION(
    
        CONFIG_INIT_VALUE(VarA);
        CONFIG_INIT_VALUE(VarVector2);
        CONFIG_INIT_VALUE(VarVector3);
        CONFIG_INIT_VALUE(VarVector4);
    )
)