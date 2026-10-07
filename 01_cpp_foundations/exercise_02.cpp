#include <iostream>
#include <string>
#include <memory> // <-- Smart Pointers (unique_ptr, shared_ptr) ke liye yeh header zaroori hai!

using namespace std;

// ============================================================================
// 1. EK SIMPLE WEAPON STRUCT JISME DESTRUCTOR BHI HAI
// ============================================================================
// Destructor (~Weapon): Yeh tab apne aap chalta hai jab weapon memory se delete hota hai.
struct Weapon {
    string name;
    int damage;

    // Constructor (Jab weapon banta hai)
    Weapon(string weaponName, int weaponDamage) : name(weaponName), damage(weaponDamage) {
        cout << "  [Created] ⚔️ " << name << " (Damage: " << damage << ")\n";
    }

    // Destructor (Jab weapon memory se gayab hota hai)
    ~Weapon() {
        cout << "  [Destroyed] 💥 " << name << " memory se clean ho gaya!\n";
    }
};

// ============================================================================
// TASK 1: std::unique_ptr (Akela Maalik)
// ============================================================================
// Goal: unique_ptr ka use karke ek weapon banana aur uska damage print karna.
void task1_unique_ptr_demo() {
    cout << "\n--- TASK 1: std::unique_ptr Demo ---\n";

    // TODO 1: make_unique ka use karke ek weapon banao: "Dragon Sword", damage: 150
    // Syntax example:
    // unique_ptr<Weapon> sword = make_unique<Weapon>("Dragon Sword", 150);
    
    // Yahan apna code likhiye:
    unique_ptr<Weapon> sword = make_unique<Weapon> ("Dragon Sword", 150); // <--- Isko replace kijiye make_unique se!

    // TODO 2: Agar sword null nahi hai, toh arrow (->) operator se uska name aur damage print karo
    if (sword != nullptr) {
        cout << "Hero is holding: " << sword->name << " with damage " << sword->damage << "\n";
    }

    cout << "Exiting task1 function...\n";
    // NOTE: Jaise hi yeh function khatam hoga, sword apne aap delete ho jayegi!
    // Aapko 'delete' likhne ki bilkul zaroorat nahi hai. Magic!
}

// ============================================================================
// TASK 2: std::shared_ptr (Shared Ownership - Dost log milkar share karte hain)
// ============================================================================
// Goal: shared_ptr create karna aur dekhna ki kitne log use share kar rahe hain (.use_count())
void task2_shared_ptr_demo() {
    cout << "\n--- TASK 2: std::shared_ptr Demo ---\n";

    // TODO 1: make_shared ka use karke ek shared weapon banao: "Magic Bow", damage: 80
    // Syntax example:
    // shared_ptr<Weapon> bow = make_shared<Weapon>("Magic Bow", 80);

    shared_ptr<Weapon> bow = make_shared<Weapon> ("Magic Bow", 80); // <--- Isko replace kijiye make_shared se!

    if (bow != nullptr) {
        cout << "Current owners count: " << bow.use_count() << " (Expected: 1)\n";
    }

    {
        cout << "  --> Entering inner room (Player 2 arrives):\n";
        
        // TODO 2: Ek aur shared_ptr banao 'player2Bow' jo 'bow' ko share kare
        // Syntax example:
        // shared_ptr<Weapon> player2Bow = bow;
        shared_ptr<Weapon> player2Bow = bow; // <--- Isko bow ke barabar kijiye!

        if (bow != nullptr && player2Bow != nullptr) {
            cout << "  --> Current owners count inside room: " << bow.use_count() << " (Expected: 2)\n";
        }
        cout << "  --> Exiting inner room (Player 2 leaves):\n";
    }

    // Yahan Player 2 gayab ho gaya, toh owners count wapas 1 ho jana chahiye!
    if (bow != nullptr) {
        cout << "Current owners count after player 2 left: " << bow.use_count() << " (Expected: 1)\n";
    }
    cout << "Exiting task2 function...\n";
}

int main() {
    cout << "========================================\n";
    cout << "  🎮 LESSON 0.2: SMART POINTERS PLAYGROUND\n";
    cout << "========================================\n";

    task1_unique_ptr_demo();
    task2_shared_ptr_demo();

    cout << "\n========================================\n";
    cout << "           ALL TASKS FINISHED           \n";
    cout << "========================================\n";

    return 0;
}
