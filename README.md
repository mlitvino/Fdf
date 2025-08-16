# Ffd

The FDF (Fil de Fer) project at 42 is a graphics programming task where you create a program in C to display a 3D wireframe map from a set of 2D coordinates.
The input is a file containing a grid of elevation points, and the program visualizes the map using isometric projection.

Key features of the project include:

* Parsing the map file: Read and interpret a grid of elevation values from a text file.
* Rendering: Convert the 2D grid data into a 3D representation with lines connecting the points to form a mesh.
* Isometric projection: Display the 3D map in a 2D isometric perspective to provide depth and structure.
* Controls: Implement interactivity for zooming, height changing, and allowing dynamic exploration of the map.

## Installation

    make
    ./fdf test.fdf
## Controls

* Move: W - up, A - left, S - down, D - right
* Zoom: mouse scroll up and mouse scroll down
