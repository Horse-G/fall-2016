ADAM HADAR - anh2130
Computer Vision, COMS4731
Fall 2016
Hw 1, Due 2016-09-20

The files I touched in this assignment were 'runHw1.m', 'hw1_walkthrough2.m',
and 'hw_walkthrough3.m'. The final version of the program also generated
the files 'collage.png' and 'output_nyc.png', as prescribed in the prompt.

I touched 'runHw1.m' in order to include my name in the Academic Honesty
signing section. Otherwise untouched.

I touched 'hw1_walkthrough2.m' in order to clean out all the test code and
comments. I also attempted to optimize (read: reduce) the code, and thus
I have implemented it in 7 lines of code. The first creates loads the image
in memory, the second creates the collage data structure to be printed out,
the next three push in the correct values in their corresponding color
channels. Instead of pushing the original image into the collage, I had each
individual color channel push their color into that portion of the collage
as well. This reduced that code from 4 to 3 lines. The last two lines are
boilerplate that print the image to the screen and to the requisite file.

I touched 'hw1_walkthrough3.m' in order to clean out all the test code and
comments. I also attempted to optimize (read: reduce) the code, and thus
I have implemented it in 30 lines of code. On top of that, I noticed that
the code only printed to the red channel for all the content in the 
'I <3 N Y' logo, and I thought that that seemed less than ideal. So I wrote
in some additional code, stuck on a toggle boolean called 'is_all_red'. Id
true then the code will implement what the prompt requested. If false then
the code will write each of the channels from the logo file into the final
image. This alternate version is less readable, but I think it presents my
understanding of the work at a more advanced level.