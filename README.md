
# SFMLTraffic

SFMLTraffic is a 2D Microscopic Traffic Simulator that utilizes the Intelligent Driver Model (IDM) and is implemented using the C++ SFML library, along with the ImGui library for the User Interface (UI).

Wiki: [https://en.wikipedia.org/wiki/Intelligent_driver_model](https://en.wikipedia.org/wiki/Intelligent_driver_model)
Reference research: [https://journals.aps.org/pre/abstract/10.1103/PhysRevE.62.1805](https://journals.aps.org/pre/abstract/10.1103/PhysRevE.62.1805)

## Installation

To run the simulator, download and execute the `main.exe` file.

## Features

-   Live simulation of cars, roads, intersections, and traffic lights.
    -   Cars dynamically avoid each other at intersections.
    -   Traffic lights have configurable green and red phases, which can be manipulated by the user.
-   Tile-based grid system for efficient editing and reusability.
-   Create, modify, and save new tiles using the JSON format.

## Usage

-   Main window:
    
    -   `Map input` window:
        -   `Reset all`: Clears the board and restarts the simulation.
        -   `Clear JSON`: Deletes all saved tiles in the JSON file.
        -   `Open map editor`: Launches the map editor window.
    -   `Tilemap` window: Displays a 5x7 grid to modify the **tile IDs**, ranging from 0-9.
    -   `Settings` window:
        -   `Set FPS`: Adjusts the simulation's frames per second (FPS).
-   Map window:
    
    -   `Map editor` window:
        -   Rectangle plot: Represents a single tile. **This is where you draw**.
        -   `Status`: Ranges from 0-3.
            -   `0`: **Draw straight road**: Left-click to create a node, press `Escape` to finish drawing the road.
            -   `1`: **Draw curved road**: Left-click on two different points to create a curved road using a quadratic [Bezier curve](https://en.wikipedia.org/wiki/B%C3%A9zier_curve). Drag the controller point to adjust the curve. Press `Escape` to finish drawing the road.
            -   `2`: **Intersection Manager**:
                -   `Intersection status`: Values range from 0 to 1.
                    -   `0`: **Viewing mode**: Auto-calculates and marks intersections with red dots. Left-click to delete intersections.
                        -   `Recalculated Intersection`: Deletes all intersections and triggers auto recalculation.
                    -   `1`: **Traffic controller mode**: Assigns each intersection to a phase, with a universal timer for each tile. Right-click on an intersection to add a road to a phase.
                        -   `Add phase`: Adds additional phases to the controller.
                        -   `Duration`: Adjusts the green light duration for the selected phase.
            -   `3`: **Connection Manager**:
                -   `Intra-connection`: Manages connections between roads within a tile, based on road IDs.
                -   `Inter-connection`: Manages connections from a road to the outside of a tile, based on ports. Each side of the tile has 20 ports. Choose the appropriate side, port, and whether it should be an input or output for cars.
                -   `Connect`: Adds the specified connection.
        -   `Connection Status`: Displays all intra-connections and inter-connections.
            -   `Intra-connection`: Left-click to merge the end of the first road with the start of the second road, right-click to delete.
            -   `Inter-connection`: Left-click to merge the start/end of a road with the defined port.
        -   `Road status`: Shows all created roads.
        -   `Action`:
            -   `Save tile to map`: Saves the currently created tile to the JSON file.
            -   `Clear tile`: Clears everything in the tile.
