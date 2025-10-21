#include "ItemManager.h"
#include <algorithm>

namespace RLTASMod {

ItemManager::ItemManager() {
}

ItemManager::~ItemManager() {
    Shutdown();
}

bool ItemManager::Initialize() {
    if (isInitialized) return true;
    
    // Load item database
    LoadItemDatabase();
    
    // TODO: Find item base address (would use pattern scanning or Cheat Engine)
    // For now, this is a placeholder
    itemBaseAddress = 0;
    
    isInitialized = true;
    return true;
}

void ItemManager::Shutdown() {
    isInitialized = false;
}

void ItemManager::LoadItemDatabase() {
    allItems.clear();
    
    // Popular Car Bodies
    allItems.push_back({1, "Octane", ItemType::BODY, false});
    allItems.push_back({2, "Dominus", ItemType::BODY, false});
    allItems.push_back({3, "Fennec", ItemType::BODY, false});
    allItems.push_back({4, "Breakout", ItemType::BODY, false});
    allItems.push_back({5, "Batmobile", ItemType::BODY, false});
    allItems.push_back({6, "Skyline", ItemType::BODY, false});
    allItems.push_back({7, "Takumi", ItemType::BODY, false});
    allItems.push_back({8, "Jager", ItemType::BODY, false});
    allItems.push_back({9, "Endo", ItemType::BODY, false});
    allItems.push_back({10, "Mantis", ItemType::BODY, false});
    
    // Popular Wheels
    allItems.push_back({100, "Cristianos", ItemType::WHEELS, false});
    allItems.push_back({101, "Zomba", ItemType::WHEELS, false});
    allItems.push_back({102, "Draco", ItemType::WHEELS, false});
    allItems.push_back({103, "White Zomba", ItemType::WHEELS, false});
    allItems.push_back({104, "Black Dieci", ItemType::WHEELS, false});
    allItems.push_back({105, "Tunica", ItemType::WHEELS, false});
    allItems.push_back({106, "Sunburst", ItemType::WHEELS, false});
    allItems.push_back({107, "Apex", ItemType::WHEELS, false});
    allItems.push_back({108, "Stern", ItemType::WHEELS, false});
    allItems.push_back({109, "OEM", ItemType::WHEELS, false});
    
    // Popular Boosts
    allItems.push_back({200, "Alpha Boost (Gold Rush)", ItemType::BOOST, false});
    allItems.push_back({201, "White Sparkles", ItemType::BOOST, false});
    allItems.push_back({202, "Black Standard", ItemType::BOOST, false});
    allItems.push_back({203, "Flamethrower", ItemType::BOOST, false});
    allItems.push_back({204, "Lightning", ItemType::BOOST, false});
    allItems.push_back({205, "Plasma", ItemType::BOOST, false});
    allItems.push_back({206, "Ion", ItemType::BOOST, false});
    allItems.push_back({207, "Datastream", ItemType::BOOST, false});
    allItems.push_back({208, "Thermal", ItemType::BOOST, false});
    allItems.push_back({209, "Sacred", ItemType::BOOST, false});
    
    // Goal Explosions
    allItems.push_back({300, "Dueling Dragons", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({301, "Hellfire", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({302, "Fireworks", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({303, "Sub-Zero", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({304, "Electroshock", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({305, "Party Time", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({306, "Popcorn", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({307, "Atomizer", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({308, "Singularity", ItemType::GOAL_EXPLOSION, false});
    allItems.push_back({309, "Juiced", ItemType::GOAL_EXPLOSION, false});
    
    // Decals
    allItems.push_back({400, "Heatwave", ItemType::DECAL, false});
    allItems.push_back({401, "Dissolver", ItemType::DECAL, false});
    allItems.push_back({402, "Trigon", ItemType::DECAL, false});
    allItems.push_back({403, "Chameleon", ItemType::DECAL, false});
    allItems.push_back({404, "Fire God", ItemType::DECAL, false});
    allItems.push_back({405, "Mainframe", ItemType::DECAL, false});
    allItems.push_back({406, "Wet Paint", ItemType::DECAL, false});
    allItems.push_back({407, "Streamline", ItemType::DECAL, false});
    allItems.push_back({408, "20XX", ItemType::DECAL, false});
    allItems.push_back({409, "Bubbly", ItemType::DECAL, false});
}

bool ItemManager::SpawnItem(int itemId) {
    if (!isInitialized) return false;
    
    // TODO: Implement actual item spawning via memory manipulation
    // This would write to RL's memory to unlock the item
    // For now, this is a placeholder that updates our local state
    
    for (auto& item : allItems) {
        if (item.id == itemId) {
            item.isUnlocked = true;
            return WriteItemUnlock(itemId, true);
        }
    }
    
    return false;
}

bool ItemManager::UnlockItem(int itemId) {
    return SpawnItem(itemId);
}

bool ItemManager::UnlockAllItems() {
    if (!isInitialized) return false;
    
    bool success = true;
    for (auto& item : allItems) {
        if (!SpawnItem(item.id)) {
            success = false;
        }
    }
    
    return success;
}

bool ItemManager::UnlockAllByType(ItemType type) {
    if (!isInitialized) return false;
    
    bool success = true;
    for (auto& item : allItems) {
        if (item.type == type) {
            if (!SpawnItem(item.id)) {
                success = false;
            }
        }
    }
    
    return success;
}

std::vector<Item> ItemManager::GetItemsByType(ItemType type) const {
    std::vector<Item> filtered;
    for (const auto& item : allItems) {
        if (item.type == type) {
            filtered.push_back(item);
        }
    }
    return filtered;
}

std::vector<Item> ItemManager::SearchItems(const std::string& query) const {
    std::vector<Item> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    
    for (const auto& item : allItems) {
        std::string lowerName = item.name;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        
        if (lowerName.find(lowerQuery) != std::string::npos) {
            results.push_back(item);
        }
    }
    
    return results;
}

bool ItemManager::UnlockAllBodies() {
    return UnlockAllByType(ItemType::BODY);
}

bool ItemManager::UnlockAllWheels() {
    return UnlockAllByType(ItemType::WHEELS);
}

bool ItemManager::UnlockAllBoosts() {
    return UnlockAllByType(ItemType::BOOST);
}

bool ItemManager::UnlockAllGoalExplosions() {
    return UnlockAllByType(ItemType::GOAL_EXPLOSION);
}

bool ItemManager::UnlockChampionSeries() {
    // Champion Series items (popular crate items)
    // This would unlock all CS1, CS2, CS3, CS4 items
    
    std::vector<int> championSeriesIds = {
        103, // White Zomba
        101, // Zomba
        102, // Draco
        400, // Heatwave
        408, // 20XX
        409, // Bubbly
        // Add more Champion Series item IDs
    };
    
    bool success = true;
    for (int id : championSeriesIds) {
        if (!SpawnItem(id)) {
            success = false;
        }
    }
    
    return success;
}

bool ItemManager::WriteItemUnlock(int itemId, bool unlocked) {
    // TODO: Implement actual memory writing
    // This would need the correct memory address and offset for the item
    
    if (itemBaseAddress == 0) {
        // No memory address found yet
        // Items will show as unlocked in GUI but won't actually unlock in game
        return false;
    }
    
    // Placeholder for actual implementation:
    // uintptr_t itemAddress = itemBaseAddress + (itemId * ITEM_SIZE);
    // WriteProcessMemory(handle, itemAddress, &unlocked, sizeof(bool), nullptr);
    
    return false; // Return false until we have real addresses
}

const char* GetItemTypeName(ItemType type) {
    switch (type) {
        case ItemType::BODY: return "Car Body";
        case ItemType::DECAL: return "Decal";
        case ItemType::WHEELS: return "Wheels";
        case ItemType::BOOST: return "Boost";
        case ItemType::ANTENNA: return "Antenna";
        case ItemType::TOPPER: return "Topper";
        case ItemType::TRAIL: return "Trail";
        case ItemType::GOAL_EXPLOSION: return "Goal Explosion";
        case ItemType::PAINT_FINISH: return "Paint Finish";
        case ItemType::ENGINE_AUDIO: return "Engine Audio";
        case ItemType::BANNER: return "Banner";
        case ItemType::AVATAR_BORDER: return "Avatar Border";
        default: return "Unknown";
    }
}

} // namespace RLTASMod
