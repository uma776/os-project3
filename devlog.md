# May 4 7:23pm
a. i have finally got the time to start this project. however finals and everything are coming up later this week so i think my consistency with working on this project will be a bit all over the place. i understand the concept of b-trees so i shouldn't have much trouble figuring out what the project wants me to do. i do wish we didnt have 2 hws due around the same time as this, but i will try my best to make progress.
b. the goal of this session is to understand the project requirements and figure out what backrgound research i need to do in order to work on this project.

# May 4 7:56pm
a. from what i understand, i am using a b-tree to create and manage index files. there are specific formats for the index files, the nodes of the b-tree, and the header of index files. additionally, there are 6 main functions/commands that the user can do. to prep for the next session, i will refresh on code implementation of b-trees. i think the first thing i want to implement is reading the command line inputs and making sure it is valid and handled properly. after this, i will move onto b-tree structure implementation, then file i/o handling. 
---------------------------------------
# May 9 11:43pm
a. since the last session, i thought about how to start implementing the project. i didnt get time to work on this the whole week due to 3 exams and the other 2 os hws that were due around the same time as this project is due.
b. the goal of this session is to implement reading the command line inputs and creating the basic structure of the code when it comes to performing the actions that the user wants to perform. 

# May 9 12:40am
a. i reached the goal of this session by setting up the main() function and the separate functions i need to implement. i also included the prof's code for the bytes to big-endian order conversions. next session, i plan on starting the create function and figuring out how to use the prof's code while implementing the create_file() function. 
---------------------------------------
# May 10 1:11pm
a. since the last session, i thought about how to start implementing the create_file(). i wanted to test if the commands are being read properly before moving on to implementing the create_file() function. i think i will start with the magic number and checking if the file already exists or not. if the file doesnt exist, then i will create a new file and copy over the magic number, root node block, and the next block.
b. the goal of this session is to finish implementing the create_file() function and start with one of the other functions. i think insert would be the hardest/most time consuming function so i will start with other simplier functions so that i can get more things done today. 

# May 10 2:26pm
a. i think i finished implementing the create_file() and using the functions the professor gave us for the byte conversions. i was not able to start the other functions, but my plan of action is to start the search, print, laod, and extract, in that order. i also changed some variable assignments in main() to make it simplier and take up less memory.
---------------------------------------