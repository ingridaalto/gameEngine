#include "Singleton.h"
#include "Object.h"
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "ObjectManager.h" // Ensure ObjectManager is included
#include <ctime>
#include <iostream>
#include <algorithm> // For std::remove

int main(int argc, char* args[]) {
    // Initialize the game engine
    Singleton& singleton = Singleton::getInstance();
    singleton.initializeAllManagers();

    GraphicsManager& graphicsManager = singleton.getGraphicsManager();
    ObjectManager& objectManager = singleton.getObjectManager();
    PhysicsManager& physicsManager = singleton.getPhysicsManager();
    InputManager& inputManager = singleton.getInputManager();

    // Random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Game variables
    bool quit = false;
    SDL_Event e;
    int tearsCaught = 0;
    int tearsMissed = 0;
    const int maxMissed = 5;
    const int winningScore = 30;
    Uint32 lastSpawnTime = SDL_GetTicks();
    const Uint32 spawnDelay = 1500;

    // Create the vase
    Object* vase = new Object(300, 550, "C:/gameEngines/01/03-media/bowl.png", graphicsManager.getRenderer());
    objectManager.addObject(vase);

    // Function to create a new tear
    auto createTear = [&]() {
        Object* tear = new Object(rand() % 800, 0, "C:/gameEngines/01/03-media/tearSmall.png", graphicsManager.getRenderer());
        tear->SetVelocity(0, 5); // Set default downward velocity
        tear->setOnCollision([&, tear]() {
            tearsCaught++;
            std::cout << "Tears caught: " << tearsCaught << "\n";
            objectManager.getObjects().erase(
                std::remove(objectManager.getObjects().begin(), objectManager.getObjects().end(), tear),
                objectManager.getObjects().end()
            );
            delete tear;
            });
        objectManager.addObject(tear);
        };

    // Add initial tears
    for (int i = 0; i < 3; ++i) {
        createTear();
    }

    std::cout << "Game started! Catch the tears!\n";

    // Game loop
    while (!quit) {
        // Event handling
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }

        // Handle input for the vase
        inputManager.UpdateKeyStates();
        int direction = inputManager.GetDirection();
        vase->SetVelocity(direction * 10, 0);

        // Update positions of all objects
        physicsManager.UpdatePositions(objectManager.getObjects());

        // Handle collisions
        physicsManager.CheckCollisions(objectManager.getObjects());

        // Process missed tears
        auto& objects = objectManager.getObjects();
        for (auto it = objects.begin(); it != objects.end();) {
            Object* obj = *it;

            // Check if object is a tear and has fallen off-screen
            if (obj->GetY() > 600) {
                tearsMissed++;
                std::cout << "Tears missed: " << tearsMissed << "\n";

                // Remove missed tear
                it = objects.erase(it);
                delete obj;

                // Check loss condition
                if (tearsMissed >= maxMissed) {
                    std::cout << "You lose! Tears missed: " << tearsMissed << "\n";
                    quit = true;
                }
            }
            else {
                ++it; // Move to the next object
            }
        }

        // Check win condition after handling collisions and misses
        if (tearsCaught >= winningScore) {
            std::cout << "You win! Tears caught: " << tearsCaught << "\n";
            quit = true;
        }

        // Spawn new tears at intervals
        if (SDL_GetTicks() - lastSpawnTime > spawnDelay && objectManager.getObjects().size() < 10) {
            createTear();
            lastSpawnTime = SDL_GetTicks();
        }

        // Render all objects
        graphicsManager.clear();
        objectManager.renderAll(graphicsManager.getRenderer());
        graphicsManager.present();
    }

    // Cleanup
    delete vase;
    singleton.shutdownAllManagers();
    return 0;
}
