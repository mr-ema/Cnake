# Cnake
Snake game implemented in C using the raylib library, with vim motions by default for movement.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/cnake/blob/main/assets/banner.svg"
    alt="Banner"
    title="Banner"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

</br>
</br>

## Resources
- [raylib](https://www.raylib.com)
- [raylib snake game example](https://github.com/raysan5/raylib-games/blob/master/classics/src/snake.c)

</br>
</br>

## Features
- [x] Basic Title Screen
- [x] Score tracking to keep track of the player's progress
- [x] Randomized food spawning
- [x] Snake grows longer when it eats food
- [x] Game over condition when the snake collides with the boundaries or itself
- [ ] Options menu
- [ ] Configurable controls at run-time [Options menu]
- [ ] Configurable mode (easy - normal - hard) [Options menu)
 
</br>
</br>

## Demo
![Demo](https://github.com/mr-ema/cnake/blob/main/assets/demo.gif)

</br>
</br>

## How To Build
Before you start, make sure you have the required dependencies for
raylib installed. Refer to the official [raylib - build and installation
guide](https://github.com/raysan5/raylib#build-and-installation) for
instructions on setting up the necessary environment.

```
git clone --recurse-submodules https://github.com/mr-ema/cnake
cd cnake/
zig build
```

</br>
</br>

## Acknowledgements
This game was developed using [raylib](https://www.raylib.com/),
a simple and easy-to-use game development library. raylib provides
a rich set of functionality and is well-suited for creating 2D games
and interactive applications.

