
Compiling
==================
There are three programs to compile:

 gcc -o drop7.cgi drop7.c drop7core.c
 gcc -o drop7display.cgi drop7display.c drop7core.c
 gcc -o permutations.cgi permutations.c


Finding A Sequence
==================

Single CORE
-----------
To figure out the optimal sequence for a given worksize number of
discs using a single core, run the following...this is for a
worksize of 8 discs:

  ./drop7.cgi -ws 8


Multiple COREs
--------------
Edit the $number_of_cpus and $worksize variables in manage_drop7_jobs.pl accordingly.
Then run:

  ./manage_drop7_jobs.pl

This can take a looooooooooong time to run when you start using worksizes above 10.
Every time you increase the worksize by 1 the amount of work to do grows by a factor of 7.


Building HTML to display a sequence
===================================
If you want to play a sequence by hand it helps to have have some detailed
output showing what the board should look like each step of the way.
To produce a webpage that shows how to play a seq do:

  ./drop7display.cgi -seq 1 2 4 4 3 7 > drop7.html


Lego Mindstorms NXT 
===================================
To get the NXT column and delay arrays for your BricxCC program run printNXTFile.pl.
You must tell it which html file to parse:
  ./printNXTFile.pl drop7.html

You'll cut-n-paste these arrays into your Drop7 BricxCC program.  The BricxCC
program tells the robot which column to move to and how long to sleep after dropping
the disc in that column.


