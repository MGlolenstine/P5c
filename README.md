# P5c
A C++ alternative to Processing (Java)

Current features:
  * working:
    * size
    * map
    * random
    * name(sets title of the window)
    * framerate
    * background
    * ellipse
    * rect
    * translate
    * pushMatrix
    * popMatrix
    * beginShape
    * endShape
    * vertex
    * dataDirectory(gives you path to folder data inside of running directory)
    * sketchDirectory(gives you path to running directory)
    * PVector
    * Color
    * PImage
    * Image loading from file
    * PImage#flip() to turn your image upside-down
    * endsWith(checks if char array ends with another char array)
    * startsWith(checks if char array starts with another char array)
    * Text(prints out text at wanted coordinates, it's colored by fill color)
  * not working curtasy of C language properties:
    * print(not working because you can't concatenate two strings with operator +)
    * println(not working because you can't concatenate two strings with operator +)
    * event functions(they do work, but you have to set them first in the setup)
      * keyPressed(can be set with setKeyPressed)
      * keyReleased(can be set with setKeyReleased)
      * mousePressed(can be set with setMousePressed)
      * mouseReleased(can be set with setMouseReleased)
      
      
