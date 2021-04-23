# Initial-Repository
Initial Repository

What did you do particularly well?

The user interface and flow was built well and handles invalid input appropriately.
Even given multiple characters when expecting a number, the program is able to dump the garbage output and recover.
Also, I added if statements to catch null pointers rather than the program crashing due to a failed pointer assignment.
In addition, to make this program more adaptable and modular, I wouldn't hard code the file names, but allow a parameter to be input and passed instead.
Lastly, I would love to work on allowing input to be more flexible by ignoring singular/plural names and searching substrings of input to find the best match possible and suggest it to the user for a better and smoother user experience.

Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

If I were to continue this project, I would structure the Python code into a class rather than independent functions. 
Also, since passing code back and forth was arbitrary for academic purposes, I would keep data the printing of that data consistent in C++ or Python.
Likely, I would have the menu display in C++, but any and all data displayed in Python.

Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

One of the challenging parts was getting the program to recover from multiple character input when it was supposed to be an integer.
I'm still not 100% satisfied, since the last getline pauses to get input and requires the user to press any key an extra time.
Also, debugging why the C++ functions were failing when the reason was because of Python's method syntax was difficult to realize. 
To overcome much of my debugging, I used print statements and commented out portions of code to discover where the error was occurring.

What skills from this project will be particularly transferable to other projects or course work?

Valuable information includes understanding how C++ and Python work together and what functions to call.
Skills relating to invalid input handling, using the right language for the job, and structuring the program appropriately will be useful to me in the future as well.

How did you make this program maintainable, readable, and adaptable?

It is maintainable and readable through the comments, clearly named variables based on purpose, and code grouping by not jamming too much functionality in a single line and using appropriate spacing. 
The program is adaptable by nature in that any list, not just groceries, could be tracked for inventory purposes 
Also, my search feature tries to be lenient by ignoring upper/lower case input.
