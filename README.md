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
      * currently only working on Linux, multiplatform using P5c IDE
    * sketchDirectory(gives you path to running directory)
      * currently only working on Linux, multiplatform using P5c IDE
    * PVector
    * Color
    * PImage
    * Image loading from file
    * PImage#flip() to turn your image upside-down
    * endsWith(checks if char array ends with another char array)
    * startsWith(checks if char array starts with another char array)
    * Text(prints out text at wanted coordinates, it's colored by fill color)
    * noFill(Sets the fill color's alpha to 0)
    * noStroke(Sets the stroke color's alpha to 0)
    * noise(function accepts 1(1D), 2(2D) or 3(3D) arguments)
    * event functions
      * keyPressed
      * keyReleased
      * mousePressed
      * mouseReleased
    * PString a very general string implementation
    * print(prints text)
      * takes PString as an argument, so if you're using normal literals, don't forget adding 's' after quotation marks
    * println(prints text and goes to new line)
      * takes PString as an argument, so if you're using normal literals, don't forget adding 's' after quotation marks
