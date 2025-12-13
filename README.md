# C++ Game 
Making a game for a term project in C++

GitHub Repo: https://github.com/Eli-V-14/game-c-plus-plus

Initial Game Concept:
- Pixel Art Player
- Adventure & Dungeon Game

Sources of Information:
- https://www.freecodecamp.org/news/c-game-development-with-raylib/
- https://www.youtube.com/watch?v=Xp-zn1TyMjU&t=305s
- https://www.tutorials.vyeron.com/c-tutorial-how-to-correct-your-diagonal-movement/
- https://www.youtube.com/watch?v=UiZGTIYld1M&t=1s // Setting up VCPKG and Raylib
- https://easings.net/#

NEEDED TO MAKE PROJECT WORK
Setting Up vcpkg and raylib in CLion (with Visual Studio toolchain):
Part 1: Make sure Visual Studio / VS Code is installed
1. Install Visual Studio (not just VS Code).
   - During installation, make sure “Desktop development with C++” is checked. 
   - This installs the MSVC compiler, which CLion needs as a toolchain on Windows.

2. You may also install VS Code, but note:
   - CLion uses Visual Studio (MSVC) as the toolchain, not VS Code itself. 
   - VS Code is optional but often required by instructors or for debugging/editing elsewhere.

Part 2: Set Visual Studio as the toolchain in CLion
1. Open CLion.
2. Go to File → Settings.
3. Navigate to Build, Execution, Deployment → Toolchains.
4. Click the + button to add a new toolchain.
5. Select Visual Studio.
6. Make sure:
   - Toolchain is marked Valid (green checkmark). 
   - Compiler is set to MSVC.
7. Click Apply, then OK.

Part 3: Enable and install vcpkg in CLion
1. In CLion, click the three horizontal lines (“pancake menu”) in the top-left corner. 
2. Hover over View. 
3. Click Tool Windows. 
4. Scroll down and click Vcpkg. 
5. CLion will automatically begin downloading vcpkg and its dependencies. 
6. Once finished, a vcpkg icon (two stacked rectangles) will appear in the bottom-left corner of CLion.

Part 4: Create a vcpkg profile
1. Click the vcpkg icon in the bottom-left corner. 
2. Click the + button to add a new vcpkg configuration. 
3. Give it a name (for example: vcpkg-raylib). 
4. Make sure the following boxes are checked:
   - Add vcpkg integration into existing CMake profiles 
   - Debug (uses 'vcpkg')
5. Click OK. 
6. Your new vcpkg profile should now appear with a yellow icon.

Part 5: Install raylib using vcpkg
1. Click on your newly created vcpkg profile (yellow icon).
2. In the search bar on the right, type raylib.
3. Select raylib from the list.
4. Click Install.
5. Wait for the installation to complete (this may take a few minutes).

Part 6: Verify raylib is working
1. Make sure your CMake profile is using the vcpkg-enabled configuration.
2. Reload CMake when prompted.
3. Try building the project.
4. If everything is set up correctly, raylib should now be available to include and link in your project.