#include "./extern/includes/beatsaber-hook/shared/utils/hooking.hpp"
#include "./include/hooks.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
//#include "main.cpp"


MAKE_AUTO_HOOK_MATCH(SoloButtonChanger, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    SoloButtonChanger(self, firstActivation, addedToHierarchy, screenSystemEnabling); 

    UnityEngine::UI::Button *soloMenuButton = self->soloButton;
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();

    //UnityEngine::UI::Button *
    
    // Set the text to "Skill Issue"
    soloMenuText->SetText("Skill Issue");
}

