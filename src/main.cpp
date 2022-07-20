#include "main.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "hooks.hpp"
#include "modloader/shared/modloader.hpp"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

#include "ModConfig.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace QuestUI::BeatSaberUI;

DEFINE_CONFIG(ModConfig);

// CREATES UI BUTTONS
void DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {

    if(firstActivation) {
        
        //UnityEngine::GameObject *container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());
        UnityEngine::GameObject *mainContainer = QuestUI::BeatSaberUI::CreateScrollView(self->get_transform());

        // QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "Test", UnityEngine::Vector2(-20.0f, 20.0f), UnityEngine::Vector2(20.0f, 10.0f), []() {});

        

        QuestUI::BeatSaberUI::CreateText(mainContainer->get_transform(), "------------------------------- DLC MENU -------------------------------");

        AddConfigValueToggle(mainContainer->get_transform(), getModConfig().DLCRemover)->get_gameObject();

        QuestUI::BeatSaberUI::CreateText(mainContainer->get_transform(), "--------------------------- SOLO BUTTON MENU ---------------------------");
        
        AddConfigValueToggle(mainContainer->get_transform(), getModConfig().SoloRemover)->get_gameObject(); // Removes Solo Button


        AddConfigValueToggle(mainContainer->get_transform(), getModConfig().SoloTextSwitch)->get_gameObject();

        Transform* parent = mainContainer->get_transform();
        auto layout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(parent);  layout->GetComponent<UnityEngine::UI::LayoutElement *>()->set_preferredWidth(60.0f); 
        layout->set_childControlWidth(true); 
        auto layoutParent = layout->get_transform();

        auto stringSetting = AddConfigValueStringSetting(layoutParent, getModConfig().SoloText); // Creates Input Field






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

    // REGISTERS MOD IN BOTH MOD MENUS
    QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);
    QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);

    il2cpp_functions::Init();

    getModConfig().Init(modInfo);

    getLogger().info("Installing hooks...");

    auto& logger = getLogger();
    Hooks::InstallHooks(logger);

    getLogger().info("Installed all hooks!");
}