# Checkers

# PS4b: Checkers

## Contact
Name: Truong-Thinh Huynh
Section: 201
Time to Complete: 13 Hours


## Description
Explain what the project does.

ps4b is the extention to ps4a where we implement the UI, but in ps4b, we had to implement the gameplay for checkers. First of all, we have to allow the piece selected for the current player to be able to move diagonally to the left or right, but also skip over the enemy piece diagonally if it is possible. This will cause the enemy piece to be captured. Then if pawn is to cross over to the other side, it will be crowned, which means it can move in forward and backwards, while pawns can only move forwards. But both pawn and crown can captured each others. When either side has no pieces left, then the other side win.

### Features
Describe what your major decisions were and why you did things that way.

The first biggest decision were to utilize a vector of string to store the game state. This is because instead of setting the possition of the sprite every single time it move or captured. I could just use the vector of string as a matrix to calculate the position and set it there. Not only that, by storing the game state in a vector of matrix, it can be use as a debugger, which is very useful to see where the piece is going and what happen when it got captured, etc.

The second biggest and probably the worst decision was I decided to do everything in main. I didn't realized that in cpplint, there is an error if your main has over 500 lines. So I decided to write the main core of the program in main as I feel like it would be easier to retrieve and sent information. Not only that, I feel like it is easier to see the whole game in one file. But as a result, the overall lines is way too long, so I decided to double up each lines with code. 

The third biggest decision was how I would managed the pieces of both side. So I seperated the black pawn, black king, red pawn, and red king in their own seperate vector of sprite. This way when either pawn is crowned, I just pop the vector of pawn and push the vector of king. And when either pawn or king is captured, then I pop them. This way is much easier than having one vector sprite that manage everything.

How To Use:
./Checkers

### Memory
Describe how you stored the game board including if you used smart pointers.

I didn't use any smart pointers, but I did use a lot of vector to store the game board. First of all, I've stored all of my texture as a data member of the class. This way, I can just load it to use it in the sprite rather than making a new texture. But how I stored the game board is split into multiple components. The background grid is stored as a vector of string, and the actually game board grid is also stored as a vector of string. But the background grid is only storing whether or not it is a black square, red square, or the border square. But the game board grid is actually storing whether or not at that position is a game piece or empty. When it is a red piece, it is stored as 'r', while black piece is stored as 'b', empty space is stored as '.' and the border piece is stored as '*'. But this is not all, the actually sprite is stored in it own seperate vector of sprite, with black and red separate. Same way as Ps4a.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I utilized any_of in the algorithm function that takes the beginning of the string to the end of the string to check for any character that represented as pieces in my game state. Not only that, the any_of also takes a lambda as parameter that actually return true or false when it dectects that there is such characters inside the string. This entire is use to check for winner dectection as to look for if there any pawn of king left on either side.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

Everything works to how I expected it to work and it should match the requirement set in the rubric. But that's being said, there is a lot of cases that is needed to be tested, and it there might well be a few cases where it could fail. However, I tested all of the cases I can think of and it works, especially those that is layout in the rubric.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

I didn't do anything extra credit in this program

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Font: Aller_Rg.ttf
fontsquirrel.com
https://www.fontsquirrel.com/fonts/list/popular

Image: Skulls in pixel art 64x64
deviantart.com
https://www.deviantart.com/suchanames/art/Skull-in-pixel-art-64X64-905035597
