# Cub3D Project Plan — 42 Lisboa Mandatory Version

**Project area:** Project architecture, Git workflow / task division, Makefile / build setup, testing, evaluation preparation.

---

## 1. Goal

Set up Cub3D as a manageable two-person project before writing code.

The goal for this kickoff is **not** to start raycasting immediately. The goal is to agree on:

- a clean architecture,
- clear ownership between parser and renderer,
- a safe data model,
- milestones toward a mandatory-complete project,
- a Git workflow that avoids breaking each other’s work,
- a testing strategy suitable for 42 peer evaluation.

Your first real deliverable should be a **compiling empty skeleton** with a Makefile, headers, source folders, cleanup functions, error handling conventions, and a clear interface between parsing and rendering.

---

## 2. What You Need to Understand

Cub3D is really four projects glued together:

1. **Parser**
   - Reads the `.cub` file.
   - Validates texture paths, floor/ceiling colors, map layout, and player position.
   - Produces a clean internal representation.

2. **Engine / Runtime State**
   - Stores MLX pointers, images, textures, map, player state, and config.
   - Owns all allocated memory and knows how to free it.

3. **Raycasting / Rendering**
   - Uses the validated map and player data.
   - Shoots one ray per screen column.
   - Determines wall distance, wall side, texture coordinate, and draws vertical wall slices.

4. **Events / Movement**
   - Handles keyboard input.
   - Moves player with collision.
   - Rotates camera.
   - Exits cleanly on ESC or window close.

The dangerous mistake is mixing these responsibilities too early.

For example, the renderer should **not** care how the `.cub` file was parsed. It should receive a validated `t_map`, `t_config`, and `t_player`.

Likewise, the parser should **not** know anything about MiniLibX images or raycasting math.

Think of the project like this:

```text
.cub file
   |
   v
parser + validator
   |
   v
validated scene data
   |
   v
mlx init + texture loading
   |
   v
game loop
   |
   v
movement + raycasting + rendering
```

---

## 3. Recommended Approach

### Milestone 0 — Repository Skeleton

Create the project structure first.

Suggested layout:

```text
cub3d/
├── Makefile
├── README.md
├── includes/
│   └── cub3d.h
├── libft/
├── mlx/
├── src/
│   ├── main.c
│   ├── init/
│   │   ├── init_data.c
│   │   ├── init_mlx.c
│   │   └── init_textures.c
│   ├── parsing/
│   │   ├── parse_file.c
│   │   ├── parse_elements.c
│   │   ├── parse_map.c
│   │   ├── parse_rgb.c
│   │   └── validate_map.c
│   ├── rendering/
│   │   ├── render_frame.c
│   │   ├── raycast.c
│   │   ├── draw_column.c
│   │   └── texture_pixel.c
│   ├── movement/
│   │   ├── movement.c
│   │   ├── rotation.c
│   │   └── collision.c
│   ├── hooks/
│   │   ├── hooks.c
│   │   └── key_state.c
│   ├── cleanup/
│   │   ├── free_data.c
│   │   ├── free_map.c
│   │   └── exit_error.c
│   └── utils/
│       ├── ft_split_free.c
│       ├── str_utils.c
│       └── color_utils.c
└── maps/
    ├── valid/
    └── invalid/
```

Do not overbuild. This is just enough structure to keep files small and responsibilities separated.

---

### Milestone 1 — Build System and Empty Program

Before parser or MLX, make sure this works:

```bash
make
./cub3D maps/valid/basic.cub
make clean
make fclean
make re
make bonus
```

At this stage, `bonus` can simply depend on `all` because you are doing mandatory only.

Important: the subject requires the target to exist, not that you implement bonus.

Your first `main` can do only:

```text
check argument count
check file extension
initialize main struct
call cleanup
return success/failure
```

No raycasting yet.

---

### Milestone 2 — Parser Contract

Your colleague should build the parser so it returns a fully validated scene.

The renderer should be able to trust:

```text
scene.config.no_path exists
scene.config.so_path exists
scene.config.we_path exists
scene.config.ea_path exists
scene.config.floor_color is valid
scene.config.ceiling_color is valid
scene.map.grid is valid
scene.map has exactly one player
scene.player has valid position and direction
```

The parser should reject:

- missing texture paths,
- duplicated `NO`, `SO`, `WE`, `EA`, `F`, or `C`,
- invalid RGB values,
- invalid map characters,
- zero player positions,
- multiple player positions,
- open maps,
- map appearing before all required elements,
- anything after the map except, depending on your interpretation, no extra meaningful content,
- texture paths that cannot be opened/read,
- wrong file extension,
- empty file,
- file with no map.

The subject says map must be last. Be strict here during validation.

---

### Milestone 3 — MiniLibX Smoke Test

You should independently create a tiny MLX branch that:

```text
opens window
creates image buffer
fills image with ceiling/floor colors
puts image to window
ESC exits cleanly
window close exits cleanly
```

No map, no raycasting.

This teaches you:

- `mlx_init`,
- `mlx_new_window`,
- `mlx_new_image`,
- `mlx_get_data_addr`,
- writing pixels manually,
- hooks,
- destroy order.

Do this before raycasting. MiniLibX mistakes are easier to debug without raycasting code involved.

---

### Milestone 4 — Untextured Raycaster

Before textures, render walls as plain colors.

You want to prove:

- player direction works,
- camera plane works,
- DDA works,
- wall distance is correct,
- no fish-eye distortion,
- movement/collision works.

At this milestone:

```text
ceiling = configured C color
floor = configured F color
north/south/east/west walls = temporary debug colors
```

This is not final subject-complete behavior, but it is the best debugging step.

---

### Milestone 5 — Texture Loading and Texture Mapping

Only after raycasting works with solid colors:

- load `NO`, `SO`, `WE`, `EA` textures,
- store each as an image buffer,
- choose texture based on wall side and ray direction,
- calculate `tex_x`,
- step vertically through texture pixels,
- draw textured wall slices.

Texture selection is often where students introduce subtle bugs, so isolate it.

---

### Milestone 6 — Hardening

Before evaluation:

- run invalid maps,
- run Valgrind,
- run Norminette,
- test ESC and window close,
- test missing files,
- test weird maps,
- test bad RGB,
- test duplicated identifiers,
- test maps with spaces,
- test long lines,
- test empty files,
- test movement into walls,
- test repeated opening/closing.

Do not leave hardening until the final day. Cub3D bugs often hide in cleanup paths.

---

## 4. Pseudocode

### Main Program Flow

```text
main(argc, argv)
    declare t_cub cub

    if argc is not 2
        print Error + message
        return failure

    init_cub(&cub)

    if parse_scene(argv[1], &cub.scene) fails
        free_cub(&cub)
        return failure

    if init_mlx(&cub) fails
        free_cub(&cub)
        return failure

    if load_textures(&cub) fails
        free_cub(&cub)
        return failure

    setup_hooks(&cub)

    render_frame(&cub)

    mlx_loop(cub.mlx.ptr)

    free_cub(&cub)
    return success
```

Important: `free_cub` should be safe to call even if initialization failed halfway.

That means every pointer starts as `NULL`.

---

### Data Ownership Model

Recommended high-level structs:

```text
t_cub
    mlx data
    scene data
    runtime/player data
    images/textures
    input/key state

t_scene
    config
    map
    player starting info

t_config
    NO path
    SO path
    WE path
    EA path
    floor color
    ceiling color

t_map
    char **grid
    int width
    int height

t_player
    double x
    double y
    double dir_x
    double dir_y
    double plane_x
    double plane_y

t_img
    void *img
    char *addr
    int bits_per_pixel
    int line_length
    int endian
    int width
    int height

t_texture
    t_img img
```

Ownership rule:

```text
parser owns temporary file lines
scene owns duplicated config paths
scene owns final map grid
mlx owns created MLX resources
free_cub destroys everything in reverse-safe order
```

Avoid ambiguous ownership like:

```text
config.no_path points directly into raw file line
```

That is dangerous because once the raw file lines are freed, the texture path becomes a dangling pointer.

Instead:

```text
config.no_path = ft_strdup(parsed_path)
```

Then `free_config` owns and frees it.

---

### Parser-to-Renderer Contract

The renderer should receive something equivalent to:

```text
scene.config.no_path = "textures/north.xpm"
scene.config.so_path = "textures/south.xpm"
scene.config.we_path = "textures/west.xpm"
scene.config.ea_path = "textures/east.xpm"

scene.config.floor_color = packed RGB int
scene.config.ceiling_color = packed RGB int

scene.map.grid =
[
    "111111",
    "100001",
    "10N001",
    "111111"
]

player.x = 2.5
player.y = 2.5
player.dir = north
```

Usually, player position should be centered inside the tile:

```text
player.x = map_col + 0.5
player.y = map_row + 0.5
```

The map grid can replace `N`, `S`, `E`, `W` with `0` after extracting player position. That makes collision simpler.

---

### Raycasting Frame Pseudocode

```text
render_frame(cub)
    draw ceiling and floor

    x = 0
    while x < screen_width
        camera_x = 2 * x / screen_width - 1

        ray_dir_x = player.dir_x + player.plane_x * camera_x
        ray_dir_y = player.dir_y + player.plane_y * camera_x

        map_x = integer player.x
        map_y = integer player.y

        calculate delta_dist_x
        calculate delta_dist_y

        calculate step_x, side_dist_x
        calculate step_y, side_dist_y

        perform DDA until wall hit

        calculate perpendicular wall distance

        calculate wall slice height
        calculate draw_start
        calculate draw_end

        choose wall texture
        calculate texture x coordinate
        draw textured vertical column

        x++
```

The key raycasting idea:

```text
player.dir = where the player looks
player.plane = camera width/peripheral vision
ray direction = dir + plane * camera_x
```

Do not think of rays as angles first. Think of them as vectors. That usually leads to cleaner C code.

---

## 5. Division of Work

### Me: Raycasting / Rendering / MiniLibX / Project Architecture

Your ownership:

- repository skeleton,
- Makefile structure,
- main `t_cub` data model,
- MLX initialization,
- image buffer handling,
- key hooks,
- movement and rotation,
- collision checks,
- raycasting DDA,
- wall rendering,
- texture loading,
- cleanup of MLX resources,
- integration with parser output.

Your first branch should probably be:

```text
feature/project-skeleton
```

Then:

```text
feature/mlx-smoke-test
feature/raycast-solid-walls
feature/player-movement
feature/textured-walls
```

---

### My Colleague: Parsing / Map Validation

Your colleague’s ownership:

- `.cub` file reading,
- extension validation,
- line storage,
- element parsing,
- RGB parsing,
- map extraction,
- duplicate/missing element detection,
- map-last validation,
- map character validation,
- player count validation,
- map closure validation,
- parser cleanup on all error paths.

Their branches could be:

```text
feature/parser-file-reading
feature/parser-elements
feature/parser-map-validation
feature/parser-error-cases
```

The parser should be testable without MLX. That is important.

A useful temporary parser test mode during development is a debug function that prints:

```text
NO path
SO path
WE path
EA path
floor color
ceiling color
map dimensions
player position
player direction
```

Remove or guard debug prints before final submission.

---

### Together: Integration / Testing / Code Review

You should pair on:

- final `t_scene` / `t_cub` struct definitions,
- ownership rules,
- cleanup conventions,
- error-message style,
- integration between parser and MLX,
- Valgrind sessions,
- Norminette sessions,
- evaluation dry runs,
- README.

Integration should happen only after both sides agree on the parser contract.

Avoid this situation:

```text
renderer expects padded rectangular map
parser returns ragged map
```

Decide early whether the final map grid is:

1. **ragged**, preserving original line lengths, or
2. **rectangular padded**, where short lines are padded with spaces.

I recommend **rectangular padded with spaces** for validation and indexing safety.

That means:

```text
"1111"
"100001"
"111"
```

becomes:

```text
"1111  "
"100001"
"111   "
```

Then, any movement/raycast access to a space should be treated as blocked/void, not walkable.

---

## 6. 42 Norm and Safety Checklist

### Function Length

Keep functions small from day one.

Good function size targets:

```text
parse_rgb()
validate_rgb_component()
is_map_line()
validate_map_closed()
init_player_direction()
cast_single_ray()
perform_dda()
draw_wall_column()
free_config()
free_map()
```

Bad function names/designs:

```text
parse_everything()
render_everything()
check_all_errors()
big_init()
```

Those become 100-line Norminette disasters.

---

### Variable Declarations

Depending on your Norm version, be conservative:

- declare variables at the top of the function,
- avoid too many local variables,
- split helpers when a function needs many temporary values,
- avoid clever one-line expressions,
- avoid deeply nested `if` blocks.

Raycasting functions naturally want many variables. Use a small `t_ray` struct for per-column state.

Example conceptually:

```text
t_ray
    double camera_x
    double ray_dir_x
    double ray_dir_y
    int map_x
    int map_y
    double side_dist_x
    double side_dist_y
    double delta_dist_x
    double delta_dist_y
    double perp_wall_dist
    int step_x
    int step_y
    int hit
    int side
    int line_height
    int draw_start
    int draw_end
```

This keeps raycasting code readable and helps with Norm limits.

Do not make one giant global struct with everything unrelated inside it just to avoid passing arguments. Use `t_cub` as the root runtime object, but keep sub-structs meaningful.

---

### Naming Clarity

Use names that help during evaluation.

Good names:

```text
validate_map_closed
load_wall_textures
cast_ray
draw_textured_column
handle_key_press
free_scene
exit_error
```

Bad names:

```text
check
doit
parse2
utils3
aaa
tmp_func
```

Peer evaluators will read your code quickly. Clear names matter.

---

### File Organization

Keep `.c` files grouped by responsibility.

Avoid dumping everything into:

```text
utils.c
parsing.c
render.c
```

A project with 20 small files is usually easier to defend than a project with 5 huge files.

---

### Forbidden Functions

You must check your exact subject PDF for the authorized functions list.

Do not assume functions are allowed because they worked in Minishell.

Common danger zones:

- `printf` may or may not be authorized depending on the subject version.
- `perror`, `strerror`, `exit`, `open`, `close`, `read`, `write`, `malloc`, `free` usually need checking against the subject.
- MiniLibX functions are authorized through the project requirement, but exact usage still depends on your campus setup.

When unsure, verify the PDF before using a function.

---

### Memory Leaks

Every allocated resource needs an owner.

Checklist:

```text
raw file lines freed after parser finishes
texture paths freed in free_config
map grid freed in free_map
MLX images destroyed before MLX connection is destroyed
window destroyed before MLX display cleanup where applicable
no double free if init fails halfway
no leak when parser fails midway
no leak when texture loading fails after one or two textures already loaded
```

Make `free_cub(&cub)` safe in all states.

This means:

```text
init_cub(&cub)
```

must initialize every pointer to `NULL`.

---

### No Segfaults

Common Cub3D segfault causes:

- accessing `map[y][x]` where `x` is past that row’s length,
- not padding ragged maps,
- raycasting into spaces/out-of-bounds,
- using MLX image address before `mlx_get_data_addr`,
- destroying an MLX image twice,
- using texture path pointer after freeing raw file lines,
- forgetting that `mlx_xpm_file_to_image` can fail,
- assuming the player exists before parser validates it.

Treat any map access through a helper:

```text
is_wall_or_void(map, x, y)
```

This helper should safely return “blocked” for:

```text
x < 0
y < 0
x >= map width
y >= map height
map[y][x] == ' '
map[y][x] == '1'
```

Movement and raycasting should not directly trust raw indexing everywhere.

---

### Clean Error Handling

Subject requires:

```text
Error
explicit message
```

Recommended style:

```text
Error
Invalid RGB value in floor color
```

or:

```text
Error
Map is not closed
```

Keep one central helper:

```text
print_error(char *message)
```

But do not make it also free everything unless the ownership is extremely clear.

Better pattern:

```text
return (print_error("Map is not closed"), FAILURE);
```

Then the caller handles cleanup.

Avoid random `exit()` calls deep in parser or rendering code unless your subject allows it and your cleanup strategy is guaranteed. Returning failure is usually cleaner.

---

## 7. Git Workflow

### Branch Strategy

Start with:

```text
main
develop
```

Protect `main` mentally: only merge stable, evaluation-ready code there.

Daily work branches:

```text
feature/project-skeleton
feature/makefile
feature/parser-elements
feature/parser-map-validation
feature/mlx-smoke-test
feature/raycast-solid-walls
feature/textures
feature/movement-hooks
fix/leak-texture-loading
fix/map-space-validation
docs/readme
```

Recommended flow:

```text
branch from develop
commit small
push
open PR or review together
run make + norminette + basic tests
merge into develop
```

Then periodically:

```text
develop -> main
```

only when stable.

---

### Commit Strategy

Good commits:

```text
chore: add project skeleton and headers
build: add Makefile with libft and mlx rules
parser: read cub file into line array
parser: validate required texture identifiers
parser: validate floor and ceiling RGB
parser: extract and pad map grid
parser: reject open maps
mlx: create window and image buffer
render: draw floor and ceiling background
raycast: implement DDA with solid wall colors
movement: add WASD collision movement
hooks: exit cleanly on ESC and window close
textures: load wall XPM images
textures: draw textured wall columns
cleanup: free scene and mlx resources safely
test: add invalid cub files for parser validation
docs: add README with usage and AI disclosure
```

Bad commits:

```text
stuff
fix
final
parser
it works
```

A peer evaluator may not inspect your Git history, but clean history helps you debug and coordinate.

---

### Review Checklist Before Merging

For every PR/merge:

```text
make re succeeds
make does not relink unnecessarily
norminette passes for touched files
no obvious forbidden functions
new allocations have cleanup
new error paths free correctly
no debug prints left accidentally
branch does not break colleague’s work
at least one valid and one invalid test run
```

For parser branches, you review with your colleague.

For rendering branches, your colleague should still review basic safety:

```text
null checks
cleanup
map indexing
function length
naming
```

You do not need both people to understand every math detail immediately, but both should understand the failure paths.

---

## 8. Tests and Edge Cases

Create a `maps/valid/` and `maps/invalid/` directory early.

---

### Valid Maps

Start simple:

```text
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

Other valid cases:

```text
elements in different order
empty lines between elements
larger map
non-rectangular map that becomes padded
map with internal spaces that are enclosed properly
player facing N
player facing S
player facing E
player facing W
```

Be careful: spaces are allowed in maps, but they are not walkable floor. They usually represent void/outside.

---

### Invalid Parser Tests

You should have invalid files for:

```text
missing NO
missing SO
missing WE
missing EA
missing F
missing C
duplicated NO
duplicated F
invalid texture path
texture path is directory
RGB below 0
RGB above 255
RGB with missing component
RGB with too many components
RGB with letters
RGB with negative number
empty file
file with only config
file with only map
invalid map character
no player
two players
open map on top
open map on bottom
open map on left
open map on right
floor tile touching space
player tile touching space
content after map
map before config is complete
wrong extension
directory passed instead of file
```

Expected behavior for all invalid tests:

```text
prints Error
prints explicit message
exits cleanly
no leaks
no segfault
```

---

### Rendering Tests

Once MLX works:

```text
window opens
image fills correctly
ESC exits
window close exits
no leak after ESC
no leak after window close
```

For raycasting:

```text
walls appear straight
rotation is smooth
no fish-eye distortion
player cannot walk through walls
player cannot walk into spaces
view does not crash near corners
texture orientation is not obviously wrong
NO texture appears on north-facing walls
SO texture appears on south-facing walls
WE texture appears on west-facing walls
EA texture appears on east-facing walls
```

Texture orientation is a common peer-evaluation discussion point. You should be able to explain how you choose the texture based on ray hit side and ray direction.

---

### Valgrind Tests

Use Valgrind on parser failures and clean exits.

Examples:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/missing_no.cub
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/basic.cub
```

MiniLibX may produce library/internal leaks depending on the environment. You should still make sure your own allocations are clean.

For Linux MLX setups, destroy order matters more:

```text
destroy images
destroy window
destroy display if applicable
free mlx pointer if applicable
free scene
```

Check your local MiniLibX version and campus expectations here.

---

## 9. Evaluation Readiness

During peer evaluation, you should both be ready to justify the following areas.

---

### Architecture

You should explain:

```text
parser validates everything before rendering starts
renderer never parses raw file data
all allocations have one owner
free_cub handles partial initialization
map access is protected
```

A strong answer sounds like:

> “The parser returns a validated scene. After that, the engine assumes the map is valid, but map access helpers still guard against out-of-bounds and spaces to avoid crashes.”

---

### Parser

Your colleague should be able to explain:

```text
how identifiers are detected
how duplicates are rejected
how RGB is parsed
how map start is detected
why map must be last
how map closure is checked
how player position is extracted
what gets freed on error
```

You should also understand the parser enough to defend integration.

---

### Raycasting

You should be able to explain:

```text
what player direction means
what camera plane means
why there is one ray per screen column
how DDA steps through the grid
how perpendicular distance avoids fish-eye
how wall height is calculated
how texture x/y coordinates are selected
```

You do not need to derive everything like a math professor, but you need to show ownership of the implementation.

---

### MiniLibX

You should explain:

```text
why you render into an image buffer instead of drawing pixels directly to the window
when render_frame is called
how hooks are registered
how ESC and window close trigger cleanup
how textures are loaded
how image memory is accessed safely
```

---

### Mandatory-Only Scope

Do not accidentally implement bonus-only behavior unless you are confident it does not interfere with mandatory.

For now, avoid:

```text
minimap
mouse rotation
doors
animated sprites
collision with enemies
extra textures
```

Mandatory completion is the priority.

---

### README

Your README should include:

```text
project explanation
how to compile
how to run
example .cub file format
controls
resources used
known limitations if any
AI usage disclosure
```

For AI usage, keep it honest and simple:

```text
AI was used as a mentoring and review aid to discuss architecture, debugging strategy, raycasting concepts, testing ideas, and README wording. The implementation was written, reviewed, and tested by the project authors.
```

Adjust wording to match what you actually do.

---

## Recommended Immediate Next Steps

1. Create `develop` from `main`.
2. Create `feature/project-skeleton`.
3. Add folder structure, empty headers, basic `main.c`, `init_cub`, `free_cub`, and error helper.
4. Add Makefile with mandatory targets.
5. Add README placeholder.
6. Merge only after `make`, `make re`, and Norminette pass.
7. Then split into two parallel tracks:
   - your colleague starts parser file reading and config validation,
   - you start MLX smoke test on a separate branch.

The first code you write should prove this principle:

```text
The program can fail anywhere and still exit cleanly.
```

That mindset will save you many Cub3D debugging hours later.