*This project has been created as part of the 42 curriculum by fgameiro, rucosta.*

# cub3D

## Description

cub3D is a raycasting engine written in C, inspired by the rendering technique used in the original *Wolfenstein 3D* (1992). The goal of the project is to build a simplified 3D first-person view out of a 2D map, without using any 3D graphics library — only [MiniLibX](https://github.com/42Paris/minilibx-linux) for window management and pixel drawing.

Given a `.cub` configuration file describing a map (walls, floor, ceiling colors, textures, and player spawn point), the program:

- Parses and validates the map (correct characters, closed/enclosed map via flood-fill, valid textures and colors, valid player orientation).
- Renders the scene in real time using raycasting: for each vertical strip of the screen, a ray is cast from the player's position and its intersection with a wall is used to compute wall height and texture sampling, using the DDA (Digital Differential Analysis) algorithm.
- Applies the correct wall texture depending on which face (North, South, East, West) is hit.
- Allows the player to move (forward/backward/strafe) and rotate the camera in real time, with collision detection against walls.
- Handles window close and `ESC` key to exit cleanly, freeing all allocated resources.

The project emphasizes strict memory management (no leaks, verified with Valgrind), robust error handling (invalid maps/files must never crash the program), and compliance with the 42 Norminette coding standard.

## Instructions

### Dependencies

- A Linux environment (developed and tested on CachyOS/Arch-based systems).
- [MiniLibX-Linux](https://github.com/42Paris/minilibx-linux), Xorg/X11 development libraries, and `libmlx`, `libXext`, `libX11` (`make` will attempt to build MiniLibX from the bundled source).

### Compilation

```bash
git clone <this-repo-url>
cd cub3D
make
```

This builds the `cub3D` executable. Other available targets:

```bash
make clean     # remove object files
make fclean    # remove object files and the executable
make re        # fclean + make
```

### Execution

```bash
./cub3D maps/test.cub
```

Replace `maps/test.cub` with the path to any valid `.cub` map file. A handful of sample maps are provided in the `maps/` directory, including intentionally invalid ones used for testing error handling.

### Controls

| Key | Action |
|---|---|
| `W` / `A` / `S` / `D` | Move forward / left / backward / right |
| `←` / `→` | Rotate camera left / right |
| `ESC` or window close button | Quit the program |

### Map file format (`.cub`)

A `.cub` file defines:

- `NO`, `SO`, `WE`, `EA`: paths to the North/South/West/East wall textures (`.xpm`).
- `F`, `C`: floor and ceiling RGB colors (`R,G,B`).
- The ASCII map grid itself, using `0` for empty space, `1` for walls, and `N`/`S`/`E`/`W` for the player's starting position and orientation. The map must be fully enclosed by walls.

## Resources

### Documentation & references

- [Lodev's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference used to understand and implement the DDA raycasting algorithm, perpendicular distance correction (fisheye fix), and texture mapping.
- [MiniLibX documentation (42Paris)](https://github.com/42Paris/minilibx-linux) — window/image management, event hooks, pixel buffer access.
- [Wolfenstein 3D on Wikipedia](https://en.wikipedia.org/wiki/Wolfenstein_3D) — historical/technical context on the original raycasting engine that inspired the project.
- 42's own cub3D subject PDF, used as the source of truth for mandatory requirements and the Norminette standard.

### AI usage disclosure

AI (Claude, by Anthropic) was used during development as a debugging and learning aid, not as a code-generation shortcut for graded logic. Specifically, it was used for:

- Explaining and diagnosing categories of raycasting bugs (fisheye distortion, texture "swimming", wall-side/texture-selection errors) to help understand *why* certain visual artifacts occurred, rather than being given ready-made fixes.
- Debugging a MiniLibX/XShm segfault on a modern Arch-based (CachyOS) system, tracing the root cause to a known incompatibility between minilibx-linux and modern Xorg/XCB stacks.
- Reviewing specific C functions (e.g. string/extension parsing helpers) to catch logic bugs such as inverted boolean return values from comparison functions.
- Drafting and structuring this README file.

All raycasting math, map parsing, memory management, and MiniLibX integration code was written and understood by the project authors; AI explanations were used to build understanding of underlying concepts and to speed up debugging, not to generate submitted algorithmic code wholesale.
