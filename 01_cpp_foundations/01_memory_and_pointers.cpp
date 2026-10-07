/**
 * ============================================================================
 * LESSON 0.1: Memory, Pointers, and References for Game Developers
 * ============================================================================
 * 
 * In Web Development (JavaScript/TypeScript):
 * - Variables are either primitives (passed by value) or objects (passed by reference-like pointers under the hood).
 * - Memory is managed automatically by V8's Garbage Collector.
 * 
 * In Game C++:
 * - YOU control the memory address.
 * - Passing large objects by value creates a full copy every single frame (slashing your FPS).
 * - Passing by reference or pointer is instant (0 byte copy overhead).
 */

#include <iostream>
#include <string>

// A typical Game Structure
struct Player {
    std::string name;
    int health;
    float posX;
    float posY;
};

// ----------------------------------------------------------------------------
// 1. Pass-by-Value (THE WEB DEV PITFALL)
// ----------------------------------------------------------------------------
// This creates a completely new CLONE of the player on the stack!
// Any damage dealt here is done to the clone and LOST when the function ends.
void takeDamageByValue(Player p, int damage) {
    p.health -= damage;
    std::cout << "  [Inside takeDamageByValue] Clone Health: " << p.health << std::endl;
}

// ----------------------------------------------------------------------------
// 2. Pass-by-Reference (THE IDIOMATIC GAME DEV WAY)
// ----------------------------------------------------------------------------
// The '&' means 'p' is NOT a copy; it is an alias directly to the original memory!
// Zero memory copied, modifications affect the original caller.
void takeDamageByReference(Player& p, int damage) {
    p.health -= damage;
    std::cout << "  [Inside takeDamageByReference] Modified original health directly!" << std::endl;
}

// ----------------------------------------------------------------------------
// 3. Pass-by-Const-Reference (READ-ONLY ZERO COST)
// ----------------------------------------------------------------------------
// In games, we constantly read player stats, transforms, and matrices.
// 'const Player&' gives 0 copy cost + guarantees the function cannot accidentally modify it.
void printPlayerStatus(const Player& p) {
    // p.health = 999; // COMPILE ERROR! Const protects it.
    std::cout << "  [Player Status] Name: " << p.name 
              << " | HP: " << p.health 
              << " | Pos: (" << p.posX << ", " << p.posY << ")" 
              << " | Address in RAM: " << &p << std::endl;
}

// ----------------------------------------------------------------------------
// 4. Pointers: Direct Memory Addresses
// ----------------------------------------------------------------------------
// A pointer stores a memory address (e.g., 0x0061ff10).
// In Unreal Engine, every Actor (`AActor*`) and Component (`UActorComponent*`) is a pointer!
void healWithPointer(Player* p, int amount) {
    if (p == nullptr) { // Crucial: Pointers can be null! Always check before use.
        std::cout << "  [Warning] Null pointer passed! Cannot heal." << std::endl;
        return;
    }
    // '->' is the arrow operator: it dereferences the pointer and accesses the member
    p->health += amount;
    std::cout << "  [healWithPointer] Healed via pointer address " << p << std::endl;
}

int main() {
    std::cout << "=========================================================" << std::endl;
    std::cout << " 🎮 LESSON 0.1: MEMORY LAYOUT & POINTERS DEMO           " << std::endl;
    std::cout << "=========================================================\n" << std::endl;

    // --- A. STACK ALLOCATION ---
    // Fast, contiguous, cleaned up automatically when main() exits.
    Player hero = {"Kaelen the Knight", 100, 15.0f, 30.0f};

    std::cout << ">>> 1. Initial State:" << std::endl;
    printPlayerStatus(hero);

    std::cout << "\n>>> 2. Testing Pass-by-Value (Notice the bug!):" << std::endl;
    takeDamageByValue(hero, 25);
    // Notice hero.health is still 100!
    std::cout << "  [After function] Real Hero Health: " << hero.health << " (Unchanged!)" << std::endl;

    std::cout << "\n>>> 3. Testing Pass-by-Reference (&):" << std::endl;
    takeDamageByReference(hero, 25);
    std::cout << "  [After function] Real Hero Health: " << hero.health << " (Now 75!)" << std::endl;

    std::cout << "\n>>> 4. Testing Pointers (* and &):" << std::endl;
    // '&' gets the memory address
    Player* heroPtr = &hero; 
    std::cout << "  heroPtr stores address: " << heroPtr << std::endl;
    std::cout << "  Size of Player struct : " << sizeof(Player) << " bytes" << std::endl;
    std::cout << "  Size of Pointer       : " << sizeof(heroPtr) << " bytes (just an address!)" << std::endl;

    healWithPointer(heroPtr, 15);
    printPlayerStatus(hero);

    std::cout << "\n>>> 5. Handling Null Pointers (Crucial for Unreal Engine):" << std::endl;
    Player* emptyPtr = nullptr; // Represents "No player selected / target lost"
    healWithPointer(emptyPtr, 50); // Gracefully handled without crashing!

    std::cout << "\n=========================================================" << std::endl;
    std::cout << " Demonstration finished successfully!                    " << std::endl;
    std::cout << "=========================================================" << std::endl;
    return 0;
}
