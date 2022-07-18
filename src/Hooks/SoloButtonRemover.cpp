#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "ModConfig.hpp"

#include "hooks.hpp"


MAKE_AUTO_HOOK_MATCH(testHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    testHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *soloButton = self->soloButton;
    UnityEngine::GameObject *gameObject = soloButton->get_gameObject();
    
    if (getModConfig().SoloRemover.GetValue() == true){
        gameObject->SetActive(false);
    }
    else{
        gameObject->SetActive(true);
    }
}

