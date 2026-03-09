A fast-paced 2D arcade shooter built using C++ and the olcPixelGameEngine. Navigate your ship, dodge obstacles, and blast through enemies!

🎮 Features
Dynamic Gameplay: Smooth controls and explosive combat.

Cross-Platform: Includes build scripts for both Windows and Linux.

Visuals: Custom sprites for ships, bullets, and explosions.

How to Build and Run
Prerequisites
To compile this game, you will need a C++ compiler (like g++ or MSVC) and the standard development libraries required by the olcPixelGameEngine (e.g., X11 and GL on Linux).

Windows
Ensure you have a C++ compiler installed (like MinGW or Visual Studio).

Double-click or run the following in your terminal:

Bash
./compile_windows.sh
Run the generated game.exe.

Linux
Open your terminal in the project directory.

Give the script execution permissions:

Bash
chmod +x compile_linux.sh
Run the script:

Bash
./compile_linux.sh
Execute the output file: ./game

File Structure
game.cpp: The main source code for the game logic.

olcPixelGameEngine.h: The engine header file.

assets/: Contains sprites like ship.png, bullet.png, and explosion.png.

Credits
Engine: OneLoneCoder (olcPixelGameEngine)
Developer: Rain-604

control
Arrow to control
