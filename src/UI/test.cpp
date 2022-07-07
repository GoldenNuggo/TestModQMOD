//#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
//#include "extern/includes/questui/shared/QuestUI.hpp"
#include "extern/includes/questui/shared/BeatSaberUI.hpp"

using namespace QuestUI::BeatSaberUI;

void DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if(firstActivation) {
        UnityEngine::GameObject *container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "Hello World!");
    }
}