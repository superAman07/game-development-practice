#include <iostream>
#include <string>
using namespace std;

// Ek simple Player struct (Character)
struct Player {
    std::string name;
    int health;
    int experience;
    float posX;
    float posY;
};

// ============================================================================
// TASK 1: Reference (&) ka use karke XP badhana
// ============================================================================
// Goal: Function ke andar player ko XP dena hai.
// Kyunki yahan 'Player& p' (reference) use hua hai, toh original player modify hoga.
void addExperience(Player& p, int xpGained) {
    // TODO: p ka experience 'xpGained' se badhao (e.g. p.experience += xpGained;)
    // Aur ek simple print statement daal do ki kitna XP mila.
    p.experience += xpGained;
    cout << "Gained XP: " << xpGained << "\n";
    return;
}

// ============================================================================
// TASK 2: Pointer (*) ka use karke Teleport karna
// ============================================================================
// Goal: Player ko nayi position (newX, newY) par bhejna.
// IMPORTANT: Pehle check karo ki 'p' null toh nahi hai!
void teleportPlayer(Player* p, float newX, float newY) {
    // TODO 1: Pehle check karo: if (p == nullptr) toh print karo "No player found!" aur return kar jao.
    if(p == nullptr){
        cout<<"No player found!"<<endl;
        return;
    }
    
    // TODO 2: Agar p valid hai, toh p->posX = newX aur p->posY = newY karo.
    // Aur print karo ki player teleport ho gaya.
    p->posX = newX;
    p->posY = newY;
    cout << "Player Teleported\n";
    return;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "       🎮 EXERCISE 01: HANDS-ON         " << std::endl;
    std::cout << "========================================\n" << std::endl;

    // Ek hero create karte hain
    Player myHero = {"Warrior_Max", 100, 0, 10.0f, 20.0f};

    std::cout << "[Initial State] Name: " << myHero.name 
              << " | XP: " << myHero.experience 
              << " | Pos: (" << myHero.posX << ", " << myHero.posY << ")" << std::endl;

    // Test 1: XP Badhana
    std::cout << "\n--> Testing Task 1 (Add XP):" << std::endl;
    addExperience(myHero, 50);
    std::cout << "Current XP: " << myHero.experience << " (Expected: 50)" << std::endl;

    // Test 2: Teleport karna (Valid pointer)
    std::cout << "\n--> Testing Task 2 (Teleport):" << std::endl;
    teleportPlayer(&myHero, 100.0f, 250.0f);
    std::cout << "New Pos: (" << myHero.posX << ", " << myHero.posY << ") (Expected: 100, 250)" << std::endl;

    // Test 3: Null pointer safety check
    std::cout << "\n--> Testing Task 2 Safety (Null Pointer):" << std::endl;
    Player* deadPlayer = nullptr;
    teleportPlayer(deadPlayer, 50.0f, 50.0f); // Crash nahi hona chahiye!

    std::cout << "\n========================================" << std::endl;
    std::cout << "             TEST COMPLETE              " << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
