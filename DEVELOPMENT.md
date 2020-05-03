# Development

- **4/16/2020** Fixed my SDK error that would not let me
build my cinder project. I had to delete cmake-build-debug 
and reload cmake.

- **4/18/2020** Implemented gflags and nlohmann libraries 
into the CMakeLists.txt files. 
    - Still need to show a working example using nlohmann
    library
    
- **4/19/2020** Created a JSON file and used methods from
the nlohmann library to demonstrate a working example to
store name and scores. But I have decided to switch to a
database instead and implemented the SQLiteModernCpp 
and SQLite3 libraries into CMakeLists.txt files. I created
a database and made a leaderboard table. I wrote in queries
to add names and scores to the table. 
    - Still need to start writing functionality for recognizing
    mouse clicks
    
- **4/20/2020** Overrode the mouseDown function to recognize 
mouse click locations. I drew my two circle blocks and had
them move around the screen for the game. Made functionality
for checking when the mouse click is at the same location
as one of the circle blocks. 
    - Still need to create the engine and write some tests

- **4/21/2020** Created a GameEngine class and moved some
functionality from my_app to this and made a screen to 
display choices of game mode. 
    - still need to write tests for GameEngine

- **4/22/2020** Wrote tests for GameEngine class. 
Created functionality recognizing choice of game mode and
a timer for when the game ends. Made methods for drawing
ending screen.
    - Still need to load background images 
    - Still need todisplay current player's score and top 
    scores of the leader board
    - Still need to write tests for recognizing which game
     mode was picked
    
- **4/24/2020** Made 3 tables for each of the 3 game modes.
Depending on the game, the ending screen shows the top 3
scores of that leader board. Wrote more tests for GameEngine
to check which game mode was clicked.
    - Still need to load background images

- **4/25/2020** Loaded 3 different background images 
for each of the 3 screens. Made sure the color of the circle
did not bleed into the background picture. I had to disable
depthRead and depthWrite and color white before drawing my
image and blocks. 
    - Still need to add an item to the game
    - Still need to add background music

- **4/26/2020** Added comments to my files. I also replaced some of my magic 
numbers and adjusted how I obtain my circle radius. Made a 
getter in the Circle class.
    - Still need to add an item to the game
    - Still need to add background music
    
- **4/28/2020** Replaced more of my magic numbers and 
added more tests and comments to my test file. Wrote 
functionality for drawing two potion items to the game.
Added background music.
    - Still need to implement functionality once an item
    is clicked.
    - Need to finish a method in GameEngine that checks
    if an item was clicked.

- **4/30/2020** Added the PROPOSAL.md file to my 
project repo.
    - Still need to add effects of items.
    - Need to write more tests for item clicking method.
    
- **5/02/2020** Finished adding item effects to the game.
I changed my poison potion image and wrote tests for 
the method that checks if an item was clicked. 
    - Still need to fill out the README.md file.

---