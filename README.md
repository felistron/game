# Game of life in c
This is my own implementation of [Conway's game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), made with C and [raylib](https://github.com/raysan5/raylib).

<div>
  <figure>
    <img src="/images/conway-gol.png" width="400">
  </figure>
  <img src="/images/conway-gol-1.png" width="400">
</div>

## Requirements
### Linux
- C compiler (CC)
- Make
- Raylib 5.0

### Windows and MacOS
Not implemented yet

## Setup
```bash
make
./build/main
```

## Controls
- [SPACE] Pause/Play generation
- [G] Enable/Disable grid
- [H] Enable/Disable heatmap
- [R] Restart and fill with random cells
- [C] Clean all the cells
- [ENTER] Next generation
- [LEFT_CLICK] Put a live cell
