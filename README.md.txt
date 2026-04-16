# Game Engine (C++ / SDL)

This project is a simple 2D game engine developed in C++ using SDL and Visual Studio.  
It was created as part of a Game Engines course project.

The engine is designed with a manager-based architecture and supports basic game functionality such as rendering, input handling, object management, and simple physics.

## Overview

The goal of this project was to understand how a game engine works internally by building core systems from scratch.  

The engine allows running small games built on top of it and demonstrates how different systems interact during the game loop.

## Features

- Basic 2D rendering using SDL  
- Input handling (keyboard and mouse)  
- Object management system  
- Time management  
- Simple physics handling (collisions)  
- Manager-based architecture  
- Singleton pattern usage  

## Architecture

The engine is built using multiple managers:

- **Graphics Manager** – handles rendering and drawing objects  
- **Input Manager** – processes keyboard and mouse input  
- **Object Manager** – manages game objects  
- **Time Manager** – handles timing and updates  
- **Physics Manager** – manages collisions and physics logic  

Additional core components:

- `Object.cpp` – base object structure  
- `Texture.cpp` – texture handling  
- `Singleton` – used for managing global access to systems  

## Games built with the engine

### 1. Kill the Bed Bugs

A fast-paced game where the player must click on bed bugs before too many appear on the screen.  
If the number of bugs grows too large, the player loses.

This game was inspired by a real-life experience in Madrid.

### 2. Catch My Tears

A more emotional and symbolic game where the player controls a vase that catches falling tears.  
The goal is to catch as many tears as possible before they hit the ground.

## Technologies

- C++  
- SDL (Simple DirectMedia Layer)  
- Visual Studio  

## How to run

1. Open the project in Visual Studio  
2. Build the solution  
3. Run the project  

Make sure SDL is properly configured in your environment.

## Project presentation

You can view the project presentation here:  
<GameEngineFinal.pdf>

## Learning outcomes

This project helped me understand:

- How a game loop works  
- How different systems (graphics, input, physics) interact  
- Manager-based architecture in game development  
- Basic rendering and event handling with SDL  
- Structuring a larger C++ project  

## Future improvements

- Better physics system  
- More advanced collision detection  
- Improved graphics and animations  
- Sound system  
- Cleaner architecture and optimization  

## Author

Ingrid Aalto  

## Notes

This project was developed as part of a university course on game engine development.