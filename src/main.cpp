#include "main.hpp"
#include "./extern/includes/beatsaber-hook/shared/utils/hooking.hpp"
#include "./extern/includes/beatsaber-hook/shared/utils/logging.hpp"
#include "./include/hooks.hpp"
#include "modloader/shared/modloader.hpp"

//                                           MAKE 1.17.1 PORT ASAP
// All Used Includes For Promo Button
#include "./include/hooks.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "GlobalNamespace/DlcPromoPanelModel.hpp"


// DISABLES PROMOTIONS BUTTON
MAKE_HOOK_MATCH(promoButton, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){

    promoButton(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *promoMenuButton = self->musicPackPromoButton;
    UnityEngine::GameObject *promoObject = promoMenuButton->get_gameObject();
    promoObject->SetActive(false);
}

// CHANGES SOLO BUTTON TEXT TO "SKILL ISSUE"
MAKE_HOOK_MATCH(soloButtonText, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    
soloButtonText(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *soloMenuButton = self->soloButton;
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();

    soloMenuText->SetText("Skill Issue");
}




static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");

    INSTALL_HOOK(getLogger(), soloButtonText)
    INSTALL_HOOK(getLogger(), promoButton)

    getLogger().info("Installed all hooks!");
}