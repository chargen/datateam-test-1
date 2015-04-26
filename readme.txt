usage:

compile:
make
./analyze file1.txt queries1.txt output.txt

parameters:
1. input file
2. a file containing queries in the specified format line by line (see spec or queries1.txt)
3. output file


desing decisions:

if i had gotten this specification in a real project i would insist on clarifying some things before implementation.
most of all what is considered import and is it really not perofrmance critical?
raw import would be simply reading the file into memory, everything further can be considered parsing.
so i decided as part of my parsing i create muliple indexes on every column to ensure a relyable analyzing speed.
this is obviously not the best way to do it in the real world but it fits the desctiption of the assessment.

strings are being replaced by a int id that is a alias for the string.
that makes working with the data much easier and is a great boost for performance.
consider it a step of normalization.
(stringAlias.cpp)

the memory storage of the data in Rows.cpp is done via vectors. this may result in poor performace for huge data, but since it is not critical i did not optimize it.
i think one should only do performace optimization if its neccessery after measurement or if it is explicitly asked for, like for the analyzing step.

theoretically the rows data could be thrown away after it is "parsed" into indexes.

the described problem is very specific thats why i designed the indexes specifically for the given problems.
for example i do not need to know in which row a certain value is stored in order to calculate the average.

we talked about the binary index in the interview, and at first i thought it might be a way to do the assessment, 
but i could not come up with a query in the form of AVG/MIN/MAX - group by that would benefit from a binary index.
if you want me to write a example of a binary index let me know.

i tried to make the types a little generic, but with only 2 types its rather difficult, not to be specific.
i ended up with some generic expandable functions in types.h/types.cpp
the only specific implementation left is in Rows.cpp and it should maybe not be part of types.cpp but rather a seperate type parsing module.


if this would be the actual base of a expandable parser / analyzer, i would have created a more abstract implementation for the indexes.
something that handles cleanup better and consist of more than of recursive typedefs.
simply to be more flexible and more safe when playing with it.
for this specific implementation i am satisfied with a straigt forward algorithm implementation.



here are a few shortcuts i took:

assuming the files are valid (like described in the assessment)
i contain the row values in a vector.
if a row happens to have less values than column in the header the program will crash


everything is int unless its string
i saved some type work on handling errors from unknown types


type flexibility
the different parsing of int and string are within Rows.cpp. for future more types a seperate module would be recommended.


slow parsing to gain little more speed in analyzing
the parser was not at all designed to be very fast. since it was not part of the assignment and the speed focus is on analyizing alone.
i marked some spots in Rows.cpp that are obv. candidates for more optimization


no support for aggregate and group-by to be the same column
group by must be a different column than the aggregate


copy paste in analyzing functions (analyze.cpp)
the analyzing functions
doAvg, doMin, doMax
have a lot of copy paste code in them
at this point it is more readable that way but generic functions would be a good idea when extending it

average calculation assums the sum of values fits into an integer
this could easily be the caus of an error when millions of rows are used with higher than 2 decimal int numbers


stdout contains output as well as error and status messages 
the real output is the output file
