# Getting Started

## Prerequisites

* cmake \(3.15 or newer\)
* make
* unzip \(You can use 7z or other programs too\)

## Installation

**Note**: Installation is only supported on GNU/Linux PC. Successful build is not guaranteed work on Windows or macOS.

1. Unzip the downloaded file using unzip command on Linux or any other program on Windows.

```text
➔ unzip Spider-In-Hell.zip
```

2. Generate Makerfile using `cmake`:

```text
➔ mkdir build && cd build && cmake -S .. -B .
```

3. Compile the game using `make`:

```text
➔ make
```

4. Run the game and Have fun!

```text
➔ ./Spider_In_Hell
```

## How to Play?

This game can currently be run correctly only without GUI, a graphical version is under development. Each mode can be selected when you run the game.

```text
Run [g]raphic or remain in [t]erminal:t
```

When you finished deciding whether you want a GUI or not, it's time to choose the **game mode**. There are two game modes which will be explained throughout the rest of this document.

To see how things work, see here...

{% page-ref page="the-alogrithm.md" %}

{% hint style="info" %}
The first turn in every run is with the spider regardless of mode.
{% endhint %}

## Butterfly mode

If you're familiar with the [Greedy Spiders](http://greedyspiders.com/) game, this mode is almost the same as what you do in that game.

The computer moves the spider position to catch the butterflies and you have to avoid it by cutting the best edge!

{% hint style="info" %}
Be careful. If you choose an edge that doesn't exist, you'll get an error and asked to choose another edge.
{% endhint %}

Once you win or lose the game, the game loop will be terminated and you'll exit the game automatically.

## Spider Mode

Unlike the butterfly mode, you decide the next movement of the spider, and the computer cuts the best edge to liberate the butterflies. It means that the computer and you swap roles in Spider Mode.

Each time you have to move the spider position to catch a butterfly. Once done, you win the game.

{% hint style="info" %}
Be careful. If you choose a vertex which spider can't go to, you'll get an error and asked to choose another vertex.
{% endhint %}

If no route to any butterfly remains, the butterflies are liberated and you lose.

Once you win or lose the game, the game loop will be terminated and you'll exit the game automatically.



### Play in GUI

As in terminal, the game modes are pretty similar.

Once entered, you'll be asked to choose a mode for a game. Hit **Left Click** to select Guardian \(Butterfly\) mode or **Right Click** to select Spider mode. 

If entered in Spider mode, you just need to Click on a vertex for the spider to move. 

However if entered in Guardian mode, first hit the **Start button** for spider to make his first move. Then by _left-clicking_ select a node and by _right-clicking_ select another. The program will automatically remove the link between them.

{% hint style="info" %}
On each mode, once game finished, you'll be redirected to Win or Lose screen!
{% endhint %}

Have fun and read more about the game if interested!

