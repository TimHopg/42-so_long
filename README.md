# so_long

A 2D game developed using the `MiniLibX` library for 42 School Lisboa

![so_long_demo](https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExbWdsYW1lNDlqZzJqZTNvemU0Nmlqdndmamw5Njd5anlkdzJmNDd6bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Od0XMgLsmJhGL4kAa9/giphy.gif)

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
  - [Maps](#maps)
- [Implementation](#implementation)
  - [Parsing](#parsing)
  - [Graphics](#graphics)
  - [Animation](#animation)
  - [Random](#random)
- [Improvements](#improvements)
- [Tips](#tips)
- [Resources](#resources)

## Introduction

MiniLibX is an add-on library which makes developing in the X-Window (X11) system more approachable. `so_long` is a 2D game developed using this library and is our first graphical project. The objective of the game is to collect all collectibles (fortune cookies) and then reach the treasure chest without being caught by the zombie.

Tested on Ubuntu 22 on Linux.

## Installation

Git clone the repository:

```shell
https://github.com/TimHopg/42-so_long.git
```

If the `mlx` folder/library is not present, run `make download` from within the directory.  
Run `make` to compile the game.  
`make clean` will remove object files.  
`make fclean` will remove program and object files.  

## Usage

```shell
./so_long [map_file]
```

`so_long` takes 1 mandatory argument. It should be the map file in `.ber` format.

`WASD` are used for controls. `esc` or the close icon can be used to exit the game.

### Maps

- `1` - a wall
- `0` - a background/empty tile
- `P` - the player (there must be only one)
- `C` - collectible (fortune cookie)
- `E` - the exit (there must be only one)
- `B` - a bad guy (zombie) (there must be a maximum of one)

All maps should be rectangular and have wall tiles around the perimeter. All coins and the exit should be reachable.  
A selection of maps are available in the `/maps` directory.

## Implementation

Memory management was taken care of throughout development (not at the end of the project) otherwise it can become harder to manage. All structures and data was intialised using `ft_bzero()` or `ft_calloc()`.

### Parsing

A recursive flood fill function was used to check the validity of the map.

### Graphics

`xpm` file format was used for all graphics. This is a human readable interpretation of images with each different colour in the image's pallette assigned a different code character.
Transparency issues were avoided by creating a bespoke image processing function that scanned line by line and ignored any pixels that were set to transparent.

All graphics used were found at [itch.io](http://itch.io).  
CREDIT: [pixel-boy](https://pixel-boy.itch.io/ninja-adventure-asset-pack)

Graphics were used for the move counter at the bottom of the screen.
A Game Over, winning/losing splash is displayed if an end state is reached.

### Animation

The player cannot walk through wall tiles but if they do attempt to the character will turn (the movement counter will not increase). When all collectibles are collected, the chest begins a short animation sequence.

The Zombie animation continues on a loop with a few repetitions of the idle animation before the attack animation in a random direction.

### Random

`rand()` was used to randomise the enemy movement. `srand(time(0))` was the seed used – without it the zombie's movement would be pseudo-random and the same sequence would be used on each launch.

The possible movement directions are calculated and then a random direction is selected.

## Improvements

- Instead of re-rendering the entire playable area of the screen on each change, only the section being updated could be rendered to save resources.
- Include multiple enemies.
- Other enemies could move towards the player.
- Add player idle animation.

## Tips

- Remember to `make re` when changing certain aspects of the game.
- `keysym` is more abstract than `keycode` (which is hardware specific) and thus more portable. Use it. (`X11/keysym.h`)
- `destroy_display()` is necessary on Linux architecture (after `destroy_window()`). And `free(mlx.ptr)` too.
- This was the first time I developed on a virtual machine using `ssh` through `VSCode` so I could maintain my usual environment.

## Resources

- [Harm Smits 42 Docs](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html)
- [42 Cursus Gitbook](https://42-cursus.gitbook.io/guide/rank-02/so_long/understand-so_long)
- [Reactive.so Guide](https://reactive.so/post/42-a-comprehensive-guide-to-so_long)
- [Transparency](https://pulgamecanica.herokuapp.com/posts/mlx-transparency)
