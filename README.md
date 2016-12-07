Final Project:

I N T E R S T I C E
A Simple Puzzle.

Jose Canizares
CSCI4229/5229 Fall 2016

Run into the random objects and move them around!
Hold 'G' as you run into an object to grab onto them. Drag them around.
Drag the smallest object (on the far left) to the blue square to turn it red.
Keep dragging subsequently larger objects to the blue squares in ascending order.
Collect all 16 rectangles.
Notice you can use multiple keys and drag the screen around with the mouse.
All objects are hand-made. (The textures are the only things not mine).
Use 'F' to switch to "sand" mode.


Instructions:

MAC: brew install sdl2

LINUX: sudo apt-get update
       apt-get install freeglut3-dev
       apt-get install libsdl2-dev
make
./final


If there is a problem with installing SDL2 on MAC:
brew install sdl2
sudo chown root:wheel /usr/local/bin/brew
sudo brew link sdl2

If there is a problem with installing SDL2 for LINUX:
make sure to sudo apt-get update
you might need to sudo apt-get upgrade



Key Bindings
  a         move left
  d         move right
  w         move forward
  s         move backward
  arrows    camera up, down, left, right
  z         zoom out
  x         zoom in
  drag mouse horizontal   camera left or right
  drag mouse vertical     camera up or down
  g         grab object
  2         save progress
  f         change to "sand" mode


  ESC        Exit
