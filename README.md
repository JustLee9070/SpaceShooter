# Space Shooter

A 2D space shooter game built with **C++ and SDL3**. The project focuses on learning game development fundamentals such as game loops, delta time, player movement, projectile systems, collision detection, sprite animations, and real-time rendering.

The game is currently **under development**, with the core player movement, shooting, and background systems implemented.

## Features

### Currently Implemented

* 2D game window and rendering using SDL3
* Player spaceship movement
* Left/right movement controls
* Window boundary constraints
* Delta-time based movement
* Bullet firing system
* Shooting cooldown
* Bullet movement and cleanup
* Scrolling starfield background
* Randomized star positions and speeds
* Player spaceship texture rendering
* Game reset functionality
* SDL event handling

### Planned Features

* Enemy spaceship spawning
* Enemy movement
* Enemy rendering
* Bullet-to-enemy collision detection
* Enemy health and destruction
* Player health system
* Player destruction animation
* Game-over screen
* Restart functionality
* Score system
* Health bar
* Enemy shooting
* Multiple enemy types
* Increasing difficulty
* Sound effects and background music
* Additional visual effects and polish

## Tech Stack

* **C++**
* **SDL3**
* **SDL3_image**
* **MinGW / GCC**
* **Visual Studio Code**

## Controls

| Key     | Action     |
| ------- | ---------- |
| `←`     | Move left  |
| `→`     | Move right |
| `Space` | Shoot      |

## Project Structure

```text
Space-Shooter/
│
├── assets/
│   ├── images/
│   │   └── playerShip.png
│   │
│   └── animation/
│       └── playerShipDestruct.png
│
├── main.cpp
└── README.md
```

## How It Works

The game uses a continuous game loop consisting of several main stages:

```text
Input
  ↓
Update
  ↓
Collision Detection
  ↓
Game Logic
  ↓
Rendering
  ↓
Repeat
```

### Delta Time

Movement is calculated using delta time rather than fixed per-frame movement. This allows movement speed to remain consistent across different frame rates.

```cpp
playerShipX -= playerShipSpeed * deltaTime;
```

### Bullet System

Bullets are stored in a `std::vector` and updated every frame according to their speed and delta time. Bullets that leave the screen are removed from the vector.

### Starfield

The background consists of randomly generated stars with different sizes and movement speeds. When a star moves beyond the bottom of the screen, it is repositioned at the top with a new random horizontal position.

## Build & Run

Make sure SDL3 and SDL3_image are installed and configured in your C++ development environment.

Compile the project with the appropriate SDL3 libraries and include paths for your system.

Example with MinGW:

```bash
g++ main.cpp -o SpaceShooter -lSDL3 -lSDL3_image
```

Run:

```bash
./SpaceShooter
```

> The exact compilation command may vary depending on your SDL3 installation and environment configuration.

## Development Goals

This project is being developed as a hands-on game development project to strengthen my understanding of:

* C++ programming
* SDL3
* Game loops
* Real-time input handling
* Delta time
* 2D rendering
* Object management
* Collision detection
* Game state management
* Sprite-sheet animation
* Basic game architecture

## Future Improvements

After completing the core gameplay loop, the project will be expanded with additional enemies, combat mechanics, sound effects, visual effects, UI elements, and progressively increasing difficulty.

## Status

**In Development**

The core player and shooting systems are functional. Enemy mechanics, collision systems, player destruction, scoring, and game-over functionality are currently being developed.
