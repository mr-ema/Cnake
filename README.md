# Cnake
Snake game implemented in C using the raylib library, with vim motions for movement.

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
- Vim motions (J, K, L, H)
- Basic Title Screen
- Score tracking to keep track of the player's progress
- Randomized food spawning
- Snake grows longer when it eats food
- Game over condition when the snake collides with the boundaries or itself
 
</br>
</br>

## Demo
![Demo](https://github.com/mr-ema/cnake/blob/main/assets/demo.gif)

</br>
</br>

## Run And Play
```
git clone --recurse-submodules https://github.com/mr-ema/cnake
```

```
cd cnake/
```

```
zig build run
```

</br>

>__Note__\
>\
> If the snake speed is too fast, [here is a link to raylib snake game example with a solution](https://github.com/raysan5/raylib-games/blob/master/classics/src/snake.c#L176).

</br>
</br>

## Acknowledgements
This game was developed using [raylib](https://www.raylib.com/),
a simple and easy-to-use game development library. raylib provides
a rich set of functionality and is well-suited for creating 2D games
and interactive applications.

