# JAW Presents: Chinese Poker™

Group Members: William Hong, Anthony Hom, Jake Goldman
Period 4

## Project Description
Our project is a simulation of a game of Chinese Poker (also known as Big Two). It's designed to user networking, such that a server is set up for each game, and players can connect to that server from different machines.

## Instructions
Unfortunately, this project is extremely unfinished at this time. The following are instructions for viewing the currently working aspects of the project:
1. After cloning the repository and running `make`, run `./server` to set up a game
2. In four separate terminal sessions, run `./client` to connect to the server. The server will wait for four players to connect before starting the game. Note that the networking aspect of the project is working, but very buggy, due to limited testing abilities; to attempt to connect to a game from a different machine, run `./client <address>` with the IP address for the server. Be warned, this may be unsuccessful.
3. Once four players have connected, the player with the three of diamonds will be selected to go first, and will have their hand displayed to them (all hands will have already been dealt at this point). That player must hit enter, and then input "single", "double", or "combo" to indicate the type of hand they'd like to play. There is a high likelihood of the user being told this is an improper input, at which point that client program will continue to loop.
