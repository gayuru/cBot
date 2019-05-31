# cBot [![CodeFactor](https://www.codefactor.io/repository/github/gayuru/cbot/badge/master)](https://www.codefactor.io/repository/github/gayuru/cbot/overview/master)


:video_game: cBot is a command-line game inspired by the board game Qwirkle written in C++. <br><br>
In the implemented Game Qwirkle,
  - A maximum of 4 players can get involved in playing
  - The players will get a randomly shuffled hand of 6 tiles
  - The tile bag takes the role of shuffling its 72 tiles which includes two tiles of the each type.

## Gameplay ##

:small_orange_diamond: Players begin the game with **six blocks**. The start player places blocks of a single matching attribute (color or shape but not both) on the table. Thereafter, a player adds blocks adjacent to at least one previously played block. <br>
:small_orange_diamond: The blocks must all be played in **a line and match, without duplicates, either the color or shape of the previous block**. Players score one point for each block played plus all blocks adjacent. It is possible for a block to score in more than one direction. <br>
:small_orange_diamond: If a player completes a line containing all six shapes or colors, an additional six points are scored. The player then refills his hand to six blocks. <br>
:small_orange_diamond: The game ends when the draw bag is depleted and one player plays all of his remaining blocks, earning a six point bonus. <br>
<br>
:clap: The player with the high score wins :clap:

For more game rules :arrow_right: [Qwirkle Game Rules](https://www.ultraqwirkle.com/game-rules.php)

## Installation ##

- Do following commands and all should be good..

```sh 
$ cd src
$ make all
```

- Then run the game using the following command;

```sh
$ ./qwirkle
```
and you should be welcomed with the following screen :bulb:
![cBot1](https://imgur.com/Ui7FWkT.jpg)

- A Preloaded Game
![cBot1](https://imgur.com/aGhju6l.png)

Developers
---
- [Gayuru Gunawardena](https://gayurug.com)
- [Minh Le](https://github.com/rmit-s3722599-Minh-Le)
- [Sean Lokke](https://github.com/seanlokeee)
- [Drew Holland](https://github.com/drewlholland)

License
----
:key: MIT



   
