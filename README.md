# Quick Click Final Project

<img src="assets/gamescreen.png" width="700" height="500">

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Chandrachur Kesana - [`ckesan2@illinois.edu`](mailto:ckesan2@illinois.edu)

**Quick Click**:

* What is it? 

   - It is a game for users to click on moving objects for
    points with a time limit. 
    
   - Includes three different game modes 
   
   - Keeps a leader board for each difficulty
   
   - Includes two potion items that speed and slow 
   object movement.
 
   - Makes use of the Cinder, 
   [SQLiteModernCpp](https://github.com/SqliteModernCpp/sqlite_modern_cpp),
    and SQLite3 libraries
   
Here is an example of the screen during game play:

<img src="assets/gameaction.png" width="700" height="600">

---
**Installation:**

    - This is a Cmake Project. Cmake is necessary to 
    have installed!
    
    - The Cinder Library is also required to be installed.

**Cinder**:

- To download Cinder onto your machine, click 
[here](https://libcinder.org/download).

- **Important!!!**: For Windows Users, specifcally
Visual Studio 2015 is needed to download Cinder properly.

- [Here](https://libcinder.org/docs/guides/tour/hello_cinder_chapter1.html) 
is a basic tutorial on how Cinder works.

- Here is some Cinder 
[documentation](https://libcinder.org/docs/reference/index.html) 
on classes and utilities.

- _Quick Click_ specifically utilizes Texture2d for loading images
 and the [Voice](https://libcinder.org/docs/guides/audio/index.html) API
 for background music

- Furthermore, a huge aspect of this project is recognizing
mouse clicking with the use of Cinder. Here is 
documentation on the [mouse](https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html) 
methods.

**SQLLite**: 

- There is no need to install the 
[SQLiteModernCpp](https://github.com/SqliteModernCpp/sqlite_modern_cpp)
and SQLite3 libraries because they are already included
in the CMakeLists.txt file and added as dependencies.

- These libraries are used to create queries to 
create the leader board tables and display the 
top scores at the end of the game.

<img src="assets/endingpic.jpg" width="700" height="600">