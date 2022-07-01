#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "GlobalNamespace/DlcPromoPanelModel.hpp"

#include "hooks.hpp"

MAKE_AUTO_HOOK_MATCH(promoButton, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){

    promoButton(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *promoMenuButton = self->musicPackPromoButton;
    UnityEngine::GameObject *promoObject = promoMenuButton->get_gameObject();
    promoObject->SetActive(false);
}