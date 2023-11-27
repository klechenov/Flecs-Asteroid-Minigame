# Game Template

## How to build

This project makes use of CMake to build.

### VS

If you're using Visual Studio, more info on how to build the project is available [here](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio).

The workflow is the following:
- Open the launcher for VS.
- Click on "Open a local folder" and select the folder of the repository you cloned.
- It should open the "CMake Overview Pages", and logs should be written in the "Output" tab at the bottom.
- Wait for "CMake generation finished." to be shown in the logs.
- Click on the dropdown arrow next to "Select Startup Item..." at the top, and select "minigame.exe".
- Click on the "Play" green arrow at the top, and the game should boot up.

### CLion (JetBrains)

The workflow is the following:
- Click "Open" on the welcome window in the top right-hand corner.
- Choose the folder you just cloned (you should see a black square icon on top of the folder icon).
- Wait for CMake to load all the dependencies.
- Click on the "Play" green arrow at the top, and the game should boot up.

## Tech Stack
- Flecs
  - [Source](https://github.com/SanderMertens/flecs)
  - [Documentation](https://www.flecs.dev/flecs)
  - [Examples](https://github.com/SanderMertens/flecs/tree/master/examples/cpp)
- Raylib
  - [Source](https://github.com/raysan5/raylib)
  - [Documentation](https://www.raylib.com/cheatsheet/cheatsheet.html)
  - [Examples](https://www.raylib.com/examples.html)
- ImGui
  - [Source](https://github.com/ocornut/imgui)
  - [Documentation](https://github.com/ocornut/imgui/wiki)
  - [Examples](https://github.com/ocornut/imgui/blob/master/imgui_demo.cpp)
