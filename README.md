# C++ Rain Game

A fast-paced 2D space shooter game built with C++ and the **olcPixelGameEngine**.

## Overview

In this game, you control a spaceship at the bottom of the screen that must survive waves of incoming enemies (shooters) descending from above. Destroy enemies with your plasma weapons before they eliminate you with their bullets.

## Gameplay

- **Objective**: Survive as long as possible by destroying enemy shooters
- **Player Ship**: Controlled spaceship in the lower portion of the screen
- **Enemies**: Shooters that spawn at the top and descend downward while firing bullets
- **Weapons**: Plasma projectiles that fire upward from your ship to destroy enemies

## Controls

| Key | Action |
|-----|--------|
| ← / → | Move ship left/right |
| ↑ / ↓ | Move ship up/down |
| Mouse Click | Fire (in development) |
| R | Reset/Restart the game |
| ESC | Exit game |

## Features

- **Physics System**: Ship acceleration, deceleration, and max speed mechanics
- **Collision Detection**: 
  - Bullets hitting the player ship
  - Plasma weapons hitting enemy shooters
- **Enemy AI**: Enemy shooters with timed fire rates and bullet patterns
- **Screen Wrapping**: Player bounded to screen edges with velocity reset on collision
- **Performance Monitoring**: FPS counter and entity count display

## Project Structure

```
C++ Rain Game/
├── game.cpp                    # Main game source code
├── olcPixelGameEngine.h        # Game engine header
├── compile_windows.sh          # Windows compilation script
├── compile_linux.sh            # Linux compilation script
├── background.png              # Game background
├── ship.png                    # Player ship sprite
├── shooter.png                 # Enemy shooter sprite
├── bullet.png                  # Enemy bullet sprite
├── plasma.png                  # Player weapon sprite
├── explosion.png               # Explosion animation sprite
└── README.md                   # This file
```

## Building & Running

### Windows
```bash
./compile_windows.sh
```

### Linux
```bash
./compile_linux.sh
```

## Dependencies

- **olcPixelGameEngine**: A lightweight 2D graphics engine for pixel-based games
- C++11 or later
- Standard graphics libraries (depends on platform)

## Game Elements

### Player (Ship)
- Controlled by arrow keys
- Has acceleration and deceleration mechanics
- Can be destroyed by enemy bullets
- Can respawn by pressing R

### Enemies (Shooters)
- Spawn at regular intervals (every 2 seconds)
- Descend from the top of the screen
- Fire bullets in a circular pattern (10 bullets)
- Fire at 0.25 Hz rate
- Destroyed when hit by plasma weapons

### Projectiles
- **Bullets**: Fired by enemies in circular pattern, travel downward
- **Plasma**: Fired by player, travel upward to destroy enemies

## Game Statistics

- **Window Size**: 1280 × 720 pixels
- **Enemy Spawn Rate**: Every 2 seconds
- **Bullet Pattern**: 10 bullets per shot in circular formation
- **Enemy Fire Rate**: 0.25 Hz (fires every 4 seconds)

## Future Enhancements

- [ ] Score system
- [ ] Multiple difficulty levels
- [ ] Power-ups and upgrades
- [ ] Boss battles
- [ ] Sound effects and music
- [ ] Particle effects
- [ ] Game menu and UI
- [ ] Improved graphics and animations

## License

This is a personal project. Feel free to use and modify as needed.

## Notes

- Sprite files (PNG images) are required for the game to run
- Game state is printed to console for debugging (enemy/bullet counts)
- Click detection is implemented but not yet functional in gameplay
