#include "main.hpp"
#include "./extern/includes/beatsaber-hook/shared/utils/hooking.hpp"
#include "./extern/includes/beatsaber-hook/shared/utils/logging.hpp"
#include "hooks.hpp"
#include "modloader/shared/modloader.hpp"

#include "extern/includes/questui/shared/QuestUI.hpp"
#include "extern/includes/questui/shared/BeatSaberUI.hpp"

using namespace QuestUI::BeatSaberUI;

void DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {

    if(firstActivation) {
        
        UnityEngine::GameObject *container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "Test Mod");
    }
}

//                                           MAKE 1.17.1 PORT ASAP // Yeah no, screw 1.17.1 kiddos lmfao

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

    QuestUI::Init();
    QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);

    getLogger().info("Installing hooks...");

    auto& logger = getLogger();
    Hooks::InstallHooks(logger);

    getLogger().info("Installed all hooks!");
}