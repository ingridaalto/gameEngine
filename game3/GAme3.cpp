#include "Singleton.h"
#include "Object.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include <iostream>
#include <ctime>
#include <algorithm> // For std::remove

int main(int argc, char* args[]) {
    // Initialize the game engine
    Singleton& singleton = Singleton::getInstance();
    singleton.initializeAllManagers();

    GraphicsManager& graphicsManager = singleton.getGraphicsManager();
    InputManager& inputManager = singleton.getInputManager();
    ObjectManager& objectManager = singleton.getObjectManager();

    // Game variables
    bool quit = false;
    SDL_Event e;
    int objectsClicked = 0; // Number of objects successfully clicked
    const int winScore = 15; // Click 15 objects to win
    const int maxObjectsOnScreen = 10; // Lose if 10 or more objects are on the screen
    Uint32 lastSpawnTime = SDL_GetTicks();
    const Uint32 spawnInterval = 500; // Spawn a new object every second

    std::cout << "Click the objects! Reach 15 clicks to win, but don't let 10 bugs appear!\n";

    // Game loop
    while (!quit) {
        // Event handling
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            // Update mouse state
            inputManager.UpdateMouseState(e);

            // Check for mouse click on objects
            if (inputManager.IsMouseLeftClicked()) {
                int mouseX, mouseY;
                inputManager.GetMousePosition(mouseX, mouseY);

                auto& objects = objectManager.getObjects();
                for (auto it = objects.begin(); it != objects.end();) {
                    Object* obj = *it;

                    // Check if mouse click is inside the object bounds
                    if (mouseX >= obj->GetX() && mouseX <= obj->GetX() + obj->GetWidth() &&
                        mouseY >= obj->GetY() && mouseY <= obj->GetY() + obj->GetHeight()) {
                        // Object clicked
                        objectsClicked++;
                        std::cout << "Objects clicked: " << objectsClicked << std::endl;
                        it = objects.erase(it);
                        delete obj;

                        // Check win condition
                        if (objectsClicked >= winScore) {
                            std::cout << "You win! Final score: " << objectsClicked << std::endl;
                            quit = true;
                            break;
                        }
                    }
                    else {
                        ++it;
                    }
                }
            }
        }

        if (quit) {
            break;
        }

        // Spawn new objects periodically
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastSpawnTime >= spawnInterval) {
            if (objectManager.getObjects().size() < maxObjectsOnScreen) {
                int x = rand() % 700; // Random x position (screen width - object width)
                int y = rand() % 500; // Random y position (screen height - object height)
                Object* newObject = new Object(x, y, "C:/gameEngines/01/03-media/bug1.jpg", graphicsManager.getRenderer());
                newObject->SetVelocity(0, 0); // Objects remain static
                objectManager.addObject(newObject);
                lastSpawnTime = currentTime;
            }
        }

        // Check lose condition
        if (objectManager.getObjects().size() >= maxObjectsOnScreen) {
            std::cout << "You lose! The bugs won!" << std::endl;
            quit = true;
            break;
        }

        // Render all objects
        graphicsManager.clear();
        objectManager.renderAll(graphicsManager.getRenderer());
        graphicsManager.present();
    }

    // Cleanup
    auto& objects = objectManager.getObjects();
    for (auto obj : objects) {
        delete obj;
    }
    singleton.shutdownAllManagers();
    return 0;
}
