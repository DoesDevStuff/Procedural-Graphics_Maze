# Procedural-Graphics_Maze
![image](https://user-images.githubusercontent.com/74312830/169811734-1300e73d-1604-4b4e-a0a6-c6f60f693117.png)

# Introduction
The objective of this project demo was to showcase the use of DirectX 11 and the DirectX Toolkit to create a 3D game with procedurally generated content. The project made use of a variety of inbuilt libraries such as the SimpleMath library to assist in adding features within the project.The full working project was built within Visual Studio 2019 and made use of the directxtk framework (2015) which included support for post processing handling as well.<br>
The inspiration for the project came from the game twisty little passages which is a dungeon crawler and hence the attempt to recreate the same.<br>
The game demo submitted has a skybox, and lighting through the use of a point light (Blinn-Phong). There is a minimap camera in the scene as well. The player can move in 6 directions, up, down, left, right, forwards and backwards.<br>
The actual dungeon that the player traverses through is made up of cells or boxes that are arranged using a grid. The objective is to make your way through this generated maze to the collectible, for every successful collectible you get a set score. Bear in mind you have to avoid hitting the walls of the maze as you get penalised for this. On collision, the player returns to the original spawn point. You can also regenerate the maze layout at any point, which will auto change when the player reaches the collectible.<br>
There are 2 post processing effects that the player can toggle with, one is Bloom extract and the other being the Blur effect. Both of these are applied to the main render target.<br>

# User Input Controls
The following are the controls for movement and scene interaction :
## Keyboard Inputs
1. W Key: Move forward 
2. S Key: Move backward 
3. A Key: Yaw left (rotate about the y axis) 
4. D Key: Yaw right 
5. Left shift Key: Move vertically upwards 
6. Left Ctrl Key: Move vertically downward
7. C Key : Mini Camera view
8. N Key : Generate new cellular Automata Layout
9. B Key : Blur effect
10. F Key : Bloom Extract effect
11. Space Key : Floor terrain generation
12. Z Key : Smoothen the floor terrain
13. Esc Key : Exit the game

<br>

# Implementation
This game has been modified and adapted from the tutorials covered during the module as well as from the DirectXTK resource page maintained by Microsoft (Walbourn, 2022).
<br>

## User Input
In order to get the effects to be toggled by the player, the Input handler files (input.cpp and input.h) were used. This input class handled all the functions of player movement and interaction which was later passed onto the Game class. This allowed for adding extra input functionalities quite easily.
<br>

## Cellular Automata
The lectures in week 5 introduced the idea of procedurally generated dungeons and allowed for exploration of Cellular automata which was covered in the previous semester in another module. The idea here is to have the maze walls as cell objects that are procedurally generated identical to that of Conway's Game of Life.<br>
There are a couple of rules in doing so :<br>
1. The wall obstacle cells live on a grid
2. Each cell is given an alive or dead state and is part of a neighbourhood
3. Depending on its neighbouring and the subsequent current state algorithm calculates the new state to be assigned to that cell.
4. This is then used for all further procedural generations.
<br>

To make life easy code abstraction was done by having two different cpp files, one that handled the grid creation namely the Grid class, and another that handled all the information for the individual cells in the grid, which was the Cell class.
<br>
The grid class initialised a 2D matrix of cells where the cells were placed randomly using the inbuilt random function into cell states (alive or dead).
<br>

## Gameplay integration
To integrate the game aspect with the cellular generation, the logic was modified to have the player and the collectible item also added to the grid. This was done by using an array, and also a check was put in place to see that they were generated exactly once per generation.<br>
Moore neighbourhood was used to calculate the neighbouring cell states since we are making use of a 2D matrix. The Moore neighbourhood of a cell is the cell itself and the cells at a Chebyshev distance of 1 (Moore neighbourhood - LifeWiki, 2022).<br>

## A* Search
In order to check if the dungeon was actually solvable, A* search was also implemented. This was done over other algorithms like BFS due to being more efficient as well as being suggested by the lecturer (Matthew Bett).<br>
A* algorithm works by assigning a cost value to the cells and selects a path with the minimum cost.<br>
To find the cost we have the equation f(n) = g(n)+h(n). Here f(n) is the total cost to reach a target cell. g(n) is the actual cost to reach the target cell from the initial position. And h(n) is the estimated cost or heuristic.<br>
We then created a separate class for the A star algorithm logic and calculation. This is the instanced in the grid code. Also the cell code was modified to handle the new variables being used to calculate the distance for the A* algorithm.<br>
The pathfinding was implemented from the Geeks for Geeks resource page (Belwariar, 2022). This approach uses two lists, open and closed and it also makes use of a boolean hash table to store these values.<br>
The distance calculated in this game is by use of Manhattan distance<br>
![image4](https://user-images.githubusercontent.com/74312830/182279742-fc5fe143-e864-47cb-b6d9-eea525387dc1.png)
<br>
Alternatively one can also use Euclidean distance as well,
![image10](https://user-images.githubusercontent.com/74312830/182279776-4ac1d323-9859-4c42-aa44-69f8fc1f0486.png)
<br>

## Collision Check
Collison was handled by the AABB (Axis- Aligned Bounding Boxes) and was done in two different functions. One to check the collision between the Player and the collectible box and also to see if the player collides with the actual cell wall obstacles. The algorithm for the collision was understood through the MDN implementation of the same (3D collision detection - Game development | MDN, 2022).<br>

## Post Processing
For post processing the effects were created by the use of the BasicPostProcess provided by the directxtk library (Walbourn, 2022). There were two effects that were implemented and a third that was commented out (monochrome).<br>
Both these effects can be toggled on and off using Keyboard inputs and follow roughly the same format. A separate function was created for each and then called in code when the flag for toggle was set to true.<br>
The function first renders the target objects to the render to texture target and then reset the render target to the first back buffer. All post processing is applied after this resetting of the target. This allows for applying more than one post process effect to be layered together before the final image can be rendered.<br>
The blur is implemented through GaussianBlur_5x5, which performs a Gaussian blur with a 5x5 kernel (Walbourn, 2022). While the BloomExtract, Performs a bloom extract, which is the first pass in implementing a bloom effect(Walbourn, 2022).<br>
There is an option to set parameters to further finetune the effects applied like so <br>
![image1](https://user-images.githubusercontent.com/74312830/182280282-eafccc04-df6a-49ce-9b56-9ad22c7cb92d.png)
<br>

| Normal Render  | With Effect |
| ------------- | ------------- |
| No Blur <br> ![image2](https://user-images.githubusercontent.com/74312830/182280782-557c225c-3323-4ef2-bf1c-d72c4600e5a7.png) | Blur <br> ![image9](https://user-images.githubusercontent.com/74312830/182280874-e7b12e52-f09a-4156-88b4-892c422598a4.png) |
| No Bloom Extract <br> ![image2](https://user-images.githubusercontent.com/74312830/182281070-ce33cebd-06d4-457a-a9e3-3e9325be891f.png) | With Bloom Extract <br>  ![image7](https://user-images.githubusercontent.com/74312830/182281133-c22f7022-f8a4-4a58-a0ac-bbebb5b876f4.png) |

<br>

## Terrain Generation
Along with the procedurally generated dungeon maze the floor terrain can also be altered. For the final demo this was done through midpoint displacement sheerly due to it being easier and can also be smoothened. The terrain was also manipulated using Perlin noise but was not used in the final version. For midpoint displacement the general process involves - Initialising the corners of the map to random values, then setting a midpoint to each edge as an average of the corners it is between +/- a random amount and set the centre of the square to the average of those edge midpoints, and then iterate over to reducing jitter.<br>

![image11](https://user-images.githubusercontent.com/74312830/182281594-326169cd-d1d3-4886-a346-9171cb43a084.png)

**(terrain with midpoint displacement)**
<br>

![image5](https://user-images.githubusercontent.com/74312830/182281872-4d4c623b-4f6b-4289-871f-43eadbdc828d.png)

**(after smoothening)**
<br>

# Evaluation
The demo application managed to fulfil all the objectives of the assessment brief. A large amount of time was spent in ensuring that code management was handled using clear and object oriented programming wherever possible. The code is commented with different highlights and points including areas where changes were made as code design was modified. This includes author points and reference guides. For future work sound effects and acoustic feedback for when the player collects / loses points will be attempted.<br>
A large part of the challenges during implementation can be attributed to the A* search to ensure that the generated maze is solvable. While it has its limitations the current outputs are still good. The generated maze requires a fairly good amount of focus and dexterity and is engaging and fun to play. The implemented skybox also provides the boxed in feeling that the game was designed to be.<br>

## Limitations
As it stands there are a few limitations, due to the player being able to move upwards it is possible to “cheat the system” however it’s been ensured that collision check is still enabled so that it’s not an entire bug. There is a slight bug with the check for solvability considering it uses the player’s last known position in the grid, so there is a possibility that either player is boxed in or the maze isn’t solvable, albeit being very rare.<br>

# Reflection & Conclusion
Time management and knowing when to keep pushing with an idea or when it needs major change were the largest learning outcomes. A large bit of time for this project was focused on having perlin noise generation and having it work with the cellular automation and collision code. There was also trial and error with implementation of marching cubes and audio effects. While some of the above aren’t in the submission there was a lot of learning involved and allowed for better clarity of the various theory concepts learned through the course of this module. Applying the basics and also implementing the A* star search in C++ was certainly a challenge but was very useful in polishing C++ skills. Audio limitations occurred due to time and library limitations while the work for marching cubes was moreso a personal limitation. The time frame for the project as a whole was split into design, research and implementation with research in procedural cellular automata generation implementations getting a large amount of attention. In the end the simplistic approaches were selected to achieve a more polished demo feel.<br>

Special thanks to Matthew Bett for his teaching and assistance during this project and module<br>

# References
- Belwariar, R., 2022. A* Search Algorithm - GeeksforGeeks. [online] GeeksforGeeks. Available at: <https://www.geeksforgeeks.org/a-search-algorithm/> [Accessed 13 April 2022].
- Conwaylife.com. 2022. Moore neighbourhood - LifeWiki. [online] Available at: <https://conwaylife.com/wiki/Moore_neighbourhood> [Accessed 28 April 2022].
- Developer.mozilla.org. 2022. 3D collision detection - Game development | MDN. [online] Available at: <https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection> [Accessed 4 April 2022].
- Shiffman, D., 2012. The Nature of Code. [online] Natureofcode.com. Available at: <https://natureofcode.com/book/chapter-7-cellular-automata/> [Accessed 16 May 2022].
- O'Neal, B., 2018. std::string_view: The Duct Tape of String Types. [Blog] C++ Team Blog, Available at: <https://devblogs.microsoft.com/cppblog/stdstring_view-the-duct-tape-of-string-types/> [Accessed 19 April 2022].
- Walbourn, C., 2022. BasicPostProcess · microsoft/DirectXTK Wiki. [online] GitHub. Available at: <https://github.com/microsoft/DirectXTK/wiki/BasicPostProcess> [Accessed 12 May 2022].
- Walbourn, C., 2022. Using DeviceResources · microsoft/DirectXTK Wiki. [online] GitHub. Available at: [Accessed 12 May 2022]. 
