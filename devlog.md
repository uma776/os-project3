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
# May 10 3:22pm
a. since the last session, i thought about how to start implementing the search_file() function. i can go ahead and start on the file checking part and checking if the file is empty. i dont think i can do the tree traversal part until after i finish the insert_file() but for now, i can just place print statements to make sure the code is working. i can do the same for the print_file() function. for the load_file() and extract_file() functions, i will have to do file checking as well for the index file and the input/output file respectively. i will also have to parse through the input file in load_file() and write to the output file in extract_file(). 
b. the goal of this session is to set up the functionalities of the remaining functions and leaving default print statements in places where tree traversal or the insert_file() function would be used. i also want to double check that everything i have written so far works. 

# May 10 4:35pm
a. i reached my goal for this session. i was able to set up the remaining functions and write temporary print statements to check whether the code is executed for each of the functions. i realized that load_file and extract_file have similar code while search_file and print_file are similar. this made it a bit easier to write since some of the code was repeated from other functions. i didnt get a chance to run the code so far and test if the temp print statements are being printed yet. next session, i will run the current code i have and start working on the insert function and tree traversal for the functions i already started. 
---------------------------------------
# May 10 11:22pm
a. since the last session, i thought about how to start working on the tree traversal and insert function. i think i will try the tree traversal first so that i can finish up the functions i already started working on. 
b. the goal of this session is to first test out the current code i have to make sure the user inputs are being executed properly. then i will start working on tree traversal in search_file() and print_file(). 

# May 10 1:01am
a. i tried to run main() but ran into some errors when it comes to char* to unsigned int conversions. to fix this error, i made the values of type uint64_t (unsigned long long) which ended up working. i tested out the user inputs to make sure the correct temporary values were being printed. after this, i started working on implementing the tree traversal. i think i was able to do the tree traversal for search and print. i created a new struct for a b-tree node and a new function called print_traversal() to make it easier for the print_file function. i also learned what goto is in c++, and i used it for the first time. i didnt get time to test out if my code works at this point. i still need to implement the read_node() function i left in the search and print functions tho. for this function, it will read the current node so that it is easier to access the different attributes of the node within the search and print functions. next session, i plan on finishing the read_node() function and testing out how my code works so far. 
---------------------------------------
# May 11 6:14pm
a. since the last session, i thought about how to finish implementing the read_node() function. the main purpose of this function is to make the tree traversal easy to read and to get all of the tree node's attributes before using it in tree traversal. 
b. the goal of this session is to finish the read_node() function and review all parts of the code. if i still have time, i will test out the code and debug any issues i have. 

# May 11 7:04pm
a. i finished writing the read_node() function. i really had to keep in mind the structure of the index files when implementing this because of the offset and being consious about how many bytes i am reading with each call. now, that i finish up all the code and skimmed thru the rest of the exisiting code, i will test out the functionality of my code so far. i completely forgot about the insert_file() function, so i will work on that now first. 

# May 11 8:49pm
a. i think i finished the insert_file() function and some helper functions. i didnt have enough time to check my work yet. i will check it next session later today. i didnt implement the split nodes yet and im not sure if i will have time to but hopefully everything else works. 
---------------------------------------
