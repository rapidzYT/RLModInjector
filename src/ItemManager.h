#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <map>

namespace RLTASMod {

// Item types in Rocket League
enum class ItemType {
    BODY,           // Car bodies
    DECAL,          // Car decals
    WHEELS,         // Wheels
    BOOST,          // Boost trails
    ANTENNA,        // Antennas
    TOPPER,         // Toppers
    TRAIL,          // Car trails
    GOAL_EXPLOSION, // Goal explosions
    PAINT_FINISH,   // Paint finishes
    ENGINE_AUDIO,   // Engine sounds
    BANNER,         // Player banners
    AVATAR_BORDER   // Avatar borders
};

struct Item {
    int id;
    std::string name;
    ItemType type;
    bool isUnlocked;
};

class ItemManager {
public:
    ItemManager();
    ~ItemManager();
    
    bool Initialize();
    void Shutdown();
    
    // Item spawning
    bool SpawnItem(int itemId);
    bool UnlockItem(int itemId);
    bool UnlockAllItems();
    bool UnlockAllByType(ItemType type);
    
    // Get item lists
    const std::vector<Item>& GetAllItems() const { return allItems; }
    std::vector<Item> GetItemsByType(ItemType type) const;
    
    // Search
    std::vector<Item> SearchItems(const std::string& query) const;
    
    // Popular item sets
    bool UnlockAllBodies();
    bool UnlockAllWheels();
    bool UnlockAllBoosts();
    bool UnlockAllGoalExplosions();
    bool UnlockChampionSeries();  // All Champion Series items
    
private:
    bool isInitialized = false;
    std::vector<Item> allItems;
    
    // Memory addresses (to be found with Cheat Engine or patterns)
    uintptr_t itemBaseAddress = 0;
    
    // Load item database
    void LoadItemDatabase();
    
    // Memory operations
    bool WriteItemUnlock(int itemId, bool unlocked);
};

// Helper: Get item type name
const char* GetItemTypeName(ItemType type);

} // namespace RLTASMod
