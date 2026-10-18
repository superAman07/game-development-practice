#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ============================================================================
// 👾 GAME ENTITY: ENEMY STRUCT
// ============================================================================
struct Enemy {
    string name;
    int health;
    float posX;
    bool isAlive;

    Enemy(string n, int hp, float x) 
        : name(n), health(hp), posX(x), isAlive(true) {}
};

// ============================================================================
// 🎯 TASK 1: SPAWN ENEMIES & RESERVE MEMORY
// ============================================================================
// GOAL: 
// Ek vector of enemies create karke return karna hai.
// 
// REQUIREMENTS:
// 1. Ek vector banao: `vector<Enemy> enemyList;`
// 2. Performance Rule: Vector ko reallocate hone se bachane ke liye 
//    `enemyList.reserve(count);` use karo.
// 3. Loop chalao (0 se count-1 tak):
//    - Har step par ek naya Enemy create karke vector mein add karo.
//    - Name format: "Goblin_" + to_string(i + 1)
//    - Health: 100
//    - PosX: i * 10.0f
// 4. `enemyList` return karo.
vector<Enemy> spawnEnemies(int count) {
    // 👇 YAHAN APNA CODE LIKHIYE (Start to Finish khud likhiye):
    vector<Enemy> enemyList;
    enemyList.reserve(count);  // new keyword for me so far.. i have not used it much..
    for(int i=0;i<=count-1; ++i){
        enemyList.push_back(Enemy("Goblin_" + to_string(i + 1),100, i * 10.0f));
    }
    return enemyList;
}

// ============================================================================
// 🎯 TASK 2: GAME LOOP UPDATE (Iterating with Reference)
// ============================================================================
// GOAL:
// Saare alive enemies ko frame update mein move karna aur damage dena.
// 
// REQUIREMENTS:
// 1. Vector ke saare enemies par loop chalao.
//    ⚠️ CRITICAL GAME DEV RULE: Loop mein 'Enemy&' (Reference) use karna zaroori hai!
//    Agar aap sirf 'Enemy e' likhenge, toh C++ har enemy ki COPY bana dega aur 
//    original vector modify nahi hoga!
// 2. Har enemy ke liye:
//    - Agar enemy alive hai (`e.isAlive == true`):
//      - Uska posX 'moveSpeed' se badhao (`e.posX += moveSpeed;`)
//      - Uska health 'damage' se ghatao (`e.health -= damage;`)
//      - Agar health <= 0 ho jaye, toh `e.isAlive = false;` mark karo aur health 0 set karo.
void updateEnemies(vector<Enemy>& enemies, float moveSpeed, int damage) {
    // 👇 YAHAN APNA CODE LIKHIYE:
    for(size_t i= 0; i<enemies.size(); ++i){
        if(enemies[i].isAlive == true){
            enemies[i].posX += moveSpeed;
            enemies[i].health -= damage;
            if(enemies[i].health <= 0){
                enemies[i].isAlive = false;
                enemies[i].health = 0;
            }
        }
    }

}

// ============================================================================
// 🎯 TASK 3: GAME DEV TRICK - "SWAP AND POP" (O(1) Fast Dead Enemy Removal)
// ============================================================================
// GOAL:
// Normal 'erase' poori array ko shift karta hai (slow). Game dev mein agar order 
// matter nahi karta, toh hum dead entity ko LAST element se swap karke .pop_back() kar dete hain!
//
// REQUIREMENTS:
// 1. Loop chalao vector ke elements par (e.g., standard index loop: for (size_t i = 0; i < enemies.size(); ))
// 2. Agar current enemy dead hai (`!enemies[i].isAlive`):
//    - Use vector ke aakhri element (`enemies.back()`) se replace karo:
//      `enemies[i] = enemies.back();`
//    - Aakhri element ko delete karo: `enemies.pop_back();`
//    - NOTE: Index 'i' ko increment MAT karo, kyunki nayi jagah par jo element aaya hai use bhi check karna hai!
// 3. Agar enemy alive hai:
//    - Normal 'i++' karo.
void removeDeadEnemiesFast(vector<Enemy>& enemies) {
    // 👇 YAHAN APNA CODE LIKHIYE:
    for(size_t i =0; i<enemies.size();){
        if(!enemies[i].isAlive){
            enemies[i] = enemies.back();
            enemies.pop_back();
        }else {
            ++i;
        }
    }

}

// ============================================================================
// 🧪 AUTOMATED TESTS (Yeh check karega ki aapka code sahi hai ya nahi)
// ============================================================================
int main() {
    cout << "=================================================\n";
    cout << "  🎮 LESSON 0.3: DATA STRUCTURES & CACHE LOCALITY \n";
    cout << "=================================================\n\n";

    // ------------------------------------------------------------------------
    // TEST 1: Spawn & Reserve Test
    // ------------------------------------------------------------------------
    cout << "--> [TEST 1] Spawning 5 Enemies...\n";
    vector<Enemy> wave = spawnEnemies(5);

    if (wave.size() == 5 && wave.capacity() >= 5) {
        cout << "  ✅ SUCCESS: 5 Enemies spawned! (Capacity: " << wave.capacity() << ")\n";
        cout << "  Sample: " << wave[0].name << " at X: " << wave[0].posX << ", HP: " << wave[0].health << "\n";
    } else {
        cout << "  ❌ FAILED: Enemies count expected 5, got " << wave.size() << "\n";
    }

    // ------------------------------------------------------------------------
    // TEST 2: Update Loop Test (References vs Copies)
    // ------------------------------------------------------------------------
    cout << "\n--> [TEST 2] Updating Enemies (Move + 40 Damage)...\n";
    updateEnemies(wave, 5.0f, 40);

    if (!wave.empty() && wave[0].posX == 5.0f && wave[0].health == 60) {
        cout << "  ✅ SUCCESS: Wave 1 took damage and moved correctly!\n";
    } else {
        cout << "  ❌ FAILED: Health or Position not updated! (Did you forget Enemy& reference?)\n";
    }

    // Deal lethal damage to Goblin 2 (index 1) and Goblin 4 (index 3)
    if (wave.size() >= 4) {
        cout << "\n--> [Inflicting lethal damage to some enemies]...\n";
        updateEnemies(wave, 0.0f, 70); // Remaining HP drops below 0 -> isAlive = false
    }

    // ------------------------------------------------------------------------
    // TEST 3: Swap & Pop Removal Test
    // ------------------------------------------------------------------------
    cout << "\n--> [TEST 3] Removing Dead Enemies with Swap & Pop...\n";
    removeDeadEnemiesFast(wave);

    bool allAlive = true;
    for (const auto& e : wave) {
        if (!e.isAlive) allAlive = false;
    }

    if (allAlive && wave.empty()) {
        cout << "  ✅ SUCCESS: All dead enemies cleaned up efficiently! Remaining alive count: " << wave.size() << "\n";
    } else if (allAlive) {
        cout << "  ✅ SUCCESS: Only alive enemies remain! Count: " << wave.size() << "\n";
    } else {
        cout << "  ❌ FAILED: Dead enemies still found in list!\n";
    }

    cout << "\n=================================================\n";
    cout << "  TEST RUN FINISHED                              \n";
    cout << "=================================================\n";

    return 0;
}
