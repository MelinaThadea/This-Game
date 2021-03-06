IMPORTANT NOTE: Please run the program with Release instead of Debug.

APPLICATION REPORT 




INTRODUCTION-------------------------------------------------------------------------------------------------

This document is an application report for the project ‘Gather the Fruits Game’. It contains the descriptions of components that make up the game such as the ideas, the structure, and the algorithm. This project is created as a Programming Project for Computing for Graphics and Animation Level 5.

The aim of this project is to showcase the design and implementation of a computer graphics application written in C++ using SDL and NGL to build a Maze Collecting Game. This project features a keyboard-controlled trolls, fruit counts, steps counts, three levels, maze-like walls, and a power up (extra steps).

This project is inspired by the classic arcade game Pac-Man, which was originally released by Namco in 1980. As well as classic Snake Game, which was originate from the arcade game Blockade in 1976, which then popularize by Nokia mobile phones in 1998. Both these games heavily inspired the maze system and the collecting objects to gather scores in this project. 

This game is a single-player game where the player controls a troll with the purpose to all the fruits before the step count is up. This game features three levels, with different environments and different amount of fruit to gather. When the player hits the fruit, he will gather score in form of fruit counts. When the player walks, they will lose a step. However, the game also provides a power step in form of extra steps count, this will occur when the player hits the first fruit in the second and/or third level.

To enable the troll to walk, the troll is controlled by SDL which allows the UP, DOWN, LEFT, RIGHT buttons to control the troll directions. The source code of this project is based on Game Repository written by Jon Macey (https://github.com/NCCA/NGLLabs/tree/master/Game).

This program is based on the concept of Object-Oriented Design, which is a planning design which is defined by interaction of objects within it. Object Oriented Design breaks down structure into classes. The techniques used in this paradigm are mostly involve writing in structure classes such as: sequencing - where code are executed per line; iteration - such as for and while ; and conditional - such as if, else, case. Object-Oriented concept proves to be effective for this project because it has the benefit to be detailed and easy to modify.

This program then implements the Object-Oriented Concept and render them into 3D Projection, by using NGL. NGL is a library which implements 2D concept into 3D Projection without the complexity of writing our own 3D Render Algorithms. 






IMPLEMENTATION--------------------------------------------------------------------------------------------------

As mentioned previously, the source code of this program is based on Game Repository which is a base of game with function like walking and collision detection, which then modified and developed into a Maze Collecting game. Below are problems and solutions found in modifying and developing the game base.

Firstly, to create fruit which able to disappear when Player touch it. To create fruit, I created duplicated the Arena functions and load different map which complements the existing arena map. To make them disappear, I added conditional function of collision detection whenever the player moving and collides with item name Fruit, the fruit will turn to ‘empty’ space.  Additionally, I also added a counter whenever the player touches the fruit, the fruit counts go up.

Secondly, to create different environment for different levels. Since the game base already provide with the first map along with collision detection function, all needed to be done is to add a conditional function then duplicate the drawing functions and but replace the image with a different map. Furthermore, I used the same technique to ‘level up’ which basically changing the map of Arena and Fruit into different ones according to a conditional function if all the fruit are gathered (without spending all the step counts).

Thirdly, to rotate the player hence he can face wherever he is going to. To solve this, I modify the setRotation function in the Player draw and added a place-holder which can be easily modify in Arena. Then in Arena, under the conditional function whenever the player’s direction is not zero, it will set the rotation according to where the player is directing. For example, if the player is moving to the direction of positive X, the rotation of player is set to 90, whilst when the player is moving to the direction of negative X, the rotation is set to -90. 

The fourth challenge is to readjust 3D rendered elements to make them more appealing. To do this, I added setScale function to the draw class of each elements. In addition, I also had to adjust the position of the Y-axis of each element so they all still in the same level.

The fifth challenge is to add Win or Lose function. The challenging part to add a function where the game does not quit but the player will know that he loses. Hence, I created a function to make the Player disappear if he wins or loses. This then put into a conditional function where to Win the Player needs to gather 100 fruits with 100 steps, while to Lose the Player needs to lose 100 steps. As a bonus, each level the first fruit adds extra steps to help the Player wins. 





END RESULT--------------------------------------------------------------------------------------------------------

Considering this program developing from a game basic, it successfully able to develop many functions such as keyboard-controlled troll, 3 different levels with different arena and fruit counts. However, in my opinion, there are definitely a number of aspects that can be improved from this program such as: the Win or Lose function, the user interface, and maybe add more feature which can randomize fruit position or add timer. Especially, since I am not able to print out text on the window, the player needs to see the console to see how many fruits were gathered or how many steps are left. 


