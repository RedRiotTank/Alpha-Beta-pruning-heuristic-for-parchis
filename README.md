# Alpha-Beta pruning + heuristic for a simplified parchis game.

This repository is a practice I did for the subject **Artificial Intelligence** in my second year of the Computer Engineering Degree at UGR. It consists of the creation of an artificial intelligence capable of playing the famous *Parcheesi* game.

**Note:** We simplified some of the rules of the game to avoid going into its technicalities, since our interest was to show the algorithms and how to create the heuristics and not the game in particular.

You can check the core of the game [here](https://github.com/ugr-ccia-IA/practica3).

My work consisted of implementing:
- The **Minimax** Algorithm.
- The **Alpha–beta pruning** (Minimax algorithm improvement).
- **Heuristic** system for evaluations on the board for the *parcheesi* game.

![minimax](https://user-images.githubusercontent.com/64831934/214606584-8bfcf4d4-53f8-499e-9981-430de7a6b54c.png)

<sub> Simple example of the Minimax algorithm. </sub>

You can see some of the results here, for example here yellow creates a barrier behind a blues' barrier to force him to break it.

![06d8bfd0-e288-4f92-a964-1b72b6434db6](https://user-images.githubusercontent.com/64831934/214609522-5956aef0-2e10-43d0-a661-9d541367368f.gif)

**To execute it:** remember to install dependencies:

- Ubuntu/Debian: `sudo apt install libsfml-dev`
- Arch: `sudo pacman -S sfml`
- Fedora/CentOS/Suse: `sudo dnf -y install SFML-devel o sudo yum -y install SFML-devel`

Execute the game in the root but not on the bin, otherwise it won't be able to load the textures. Also don't change the IA ID, there is just one implementhed and it's the number 0, it will dump a core if you change it.

**WARNING:** The objective of distributing this software is to help future classmates with the subject or any other person to whom it may be helpful. For redistribution, use or any questions, consult the **MIT license** that you can find in this repository. This software is offered **without any type of guarantee**, it was used for **academic** use, so it may contain bad practices or even errors.

