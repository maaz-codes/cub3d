# CUB3D: Our First RayCaster with miniLibX

## Table of Contents
1. [Overview](#overview)
2. [Goals](#goals)
3. [Features](#features)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Map File Format](#map-file-format)
6. [Credits](#credits)

---

## Overview
**cub3D** is a 3D raycasting project inspired by the classic game **Wolfenstein 3D**. The goal is to create a dynamic, first-person perspective view inside a maze using raycasting principles. This project is implemented in **C** using the **miniLibX** library for graphical rendering.

---

## Goals
- Learn and implement **raycasting** to create a 3D perspective.
- Improve skills in **graphic programming** (windows, colors, events, shapes, etc.).
- Use **mathematics** as a tool to create efficient algorithms.
- Develop a functional and interactive 3D maze exploration game.

---

## Features
- **Dynamic 3D Rendering**: Render a maze in 3D using raycasting.
- **Player Movement**: Use `W`, `A`, `S`, and `D` keys to move through the maze.
- **Camera Rotation**: Use the left and right arrow keys to look around.
- **Textured Walls**: Display different textures for walls based on their orientation (North, South, East, West).
- **Floor and Ceiling Colors**: Set custom colors for the floor and ceiling.
- **Map Parsing**: Load and parse a `.cub` file containing the maze layout and textures.
- **Error Handling**: Properly handle errors in map configuration and file parsing.

---

## Installation
1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/cub3D.git
   cd cub3D
2. **Compile the project**:
   ```bash
   make

---

## Usage
Run the program with a .cub map file as an argument:
```bash
./cub3D maps/example.cub
```
### Controls
- **Movement**: `W`, `A`, `S`, `D`
- **Camera Rotation**: Left and Right arrow keys
- **Exit**: ESC or click the window's close button

---

## Map File Format
The map file (`.cub`) must follow this structure:
```
NO ./path_to_north_texture  
SO ./path_to_south_texture  
WE ./path_to_west_texture  
EA ./path_to_east_texture  
F 220,100,0  # Floor color (R,G,B)  
C 225,30,0   # Ceiling color (R,G,B)  

# Map layout (1 = wall, 0 = empty space, N/S/E/W = player start position)  
111111  
100101  
101001  
110001  
111111
```

---

## Credits
Developed by Maaz Khan & Raphael Creer as part of the 42 Abu Dhabi curriculum.
- Github @maaz-codes
- Github @RaphCodes1

---
