#include "modloader/shared/modloader.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "GlobalNamespace/DlcPromoPanelModel.hpp"

#include "ModConfig.hpp"
#include "hooks.hpp"

// MUST ADD BUTTON PLACEMENT FIX TO FILL GAP LEFT BY PROMOTIONS
MAKE_AUTO_HOOK_MATCH(promoButton, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){

    promoButton(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *promoMenuButton = self->musicPackPromoButton;
    UnityEngine::GameObject *promoObject = promoMenuButton->get_gameObject();

    if (getModConfig().DLCRemover.GetValue() == true) {
        promoObject->SetActive(false);
    }

    else {
        promoObject->SetActive(true);
    }
}