# [Quick Click]

Author: [Chandrachur Kesana]

My final project will be a game that consists of trying to click on moving objects/blocks on the screen. Each block will be worth one point and points will be kept track of for the end of the game. The game will last for twenty - thirty seconds. My plan is to use some of the Cinder functionality to be able to recognize mouse clicks on the screen. Some of the methods are explained [here](https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html). I do not have too much background for this project, but I feel more comfortable using Cinder after the Snake MP, and I believe that I can understand how movements were used to figure out some logic to check that the mouse and block location are the same. 

I plan to use the SQLiteModernCpp + SQLite3 libraries. These will serve as my external library for the project. I will be setting up a database that includes multiple leaderboard tables for different game modes, such as easy, medium, and hard. Furthermore, I will be using the audio [Voice API](https://libcinder.org/docs/guides/audio/index.html) from Cinder to include background music and sounds when an object is clicked. 

My motivation for this game is that I have always wanted to create some sort of game that others could play. I am also very interested in working with data bases and expand my knowledge with SQL. On my own, I have already worked on learning the SQL language a few months back. I think a key challenge will be figuring out how to support multiple block movements all at the same time on the screen. Keeping track of many objects can be difficult especially while trying to move all of them quickly.

Timeline:

* Week 1: 
  - Get the SQL libraries set up in Cmake.
  - create a method for drawing the blocks
  - Write functionality for recognizing mouse clicking
  
* Week 2:
  - Adding a timer to keep track of the time left
  - Write functionality for moving the blocks.
  - Write functionality for recognizing when the mouse click is in the same location as a block at that time. 

* Week 3:
  - Write functionality for changing speed of blocks
  - Write functionality for Background Music
  - Write functionality for keeping score and displaying that at the end of the game
  
If I end up finishing earlier than expected, I can add items to the game to act as powerups or poison. 

---
