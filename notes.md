Keeping these old notes just to look back at them

=> Currently I am writing the whole thing in one file.
-> I think OOP would already have done me some good right now since I am defining Player 1 and Player 2 Properties. (I was wrong, having structs is definitely the way too go... OOP just would have made this take longer to write, especially for such a small game its overkill)
? Is there any reason to use variable types such as short for compactness of memory? I made an Unsigned Short and I might keep doing these BS implementations (Maybe for Netcode this might be a good idea... )
=> Made a simple copy or quick reference version for if I use SDL for other projects and don't want to be confused. Refactoring the code now.
* Added Start Up Checks
* Separated Chunks into their own Functions
-> So we moved the pointers to be global variables probably a good idea.
* Finished Refactoring, Feel Like I did a good job but we are not even close to actual progress
=> I made a basic version of the ball, and collision conditions, massive revamps in order later.... All game libraries at the end of the day end up being the same, when it comes to game logic you have to eventually get your hands dirty, uptill now SDL reminds me a lot of Pygame, heck it basically feels like I am using Pygame again... except I like how the code is presented more than I did with Pygame

=> Games basically done all basic functionality is present, collisions, ball movement, scoring. I could touch it up and then if I want to go crazy with the game design and try some stuff to liven Pong up but we basically have a version similar to the classic original game, maybe next I'll remake Flicky.
* Added Randomized increases to speed on collions and directions to the ball

So I think I might try to implement some form of multiplayer, see how far I can get... So this would need to be peer to peer, meaning on the app we need ~~client/server~~ (Sending, recieving) functionality on both sides. this will have to be done using WinApi and its web sockets possibly

Our Packets would require the following information, the YPosition of the opposing player. and quite possibly if we want them to be in sync the ball position information, and even then... I assume we don't even need that. So both games need to sync up and then its just opposing player info that needs to be sent.

So we did implement Peer to Peer, Currently all our packets send are our players Y position so that it can be updated on the other players end. (The ball on collision randomly changes its direction so both games are going to look different due to that randomness)

the player in multiplayer is being decided by if the port is even or odd, don't as long as its working I am fine with it (which won't be for long... depending on if I come back to this)

===COMPILATION=== 
gcc main.c net.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lws2_32 -o netcode.exe          
                                                                                        * This only works for Windows Devices, since netcode is written using WinApi

