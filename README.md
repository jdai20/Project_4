# Project-4
Reading GPS Data: Tour de France

Introduction: Tour de France

In this final project (great work this semester!), you will be reading in data recorded on a GPS receiver attached to the bicycles of Tour de France (TDF) racers. The Tour de France is the most prestigious bike race in the world, where about 180 elite athletes race close to 3,500 km over 23 days in July. The Tour is composed of individual Stages on each day, sometimes requiring the cyclist to race for close to 6 hours to ride over 200 km up and down some of the highest alpine passes in Europe, only to wake up the next morning and do it all over again. The average overall speed for the tour is close to 40 km/h (i.e. about 25 mph), which is incredibly fast, especially for the terrain the riders are tackling.

Note: the Tour de France does not currently have a counterpart for athletes who identify as female, and it was difficult to find GPS data for women's bike races. However, I encourage you to read about Kristin Armstrong, a three-time olympic gold medalist in the time trial cycling event. You may also be interested in this article, which discusses the struggles of developing a top-flight European stage-race for women.

The datasets provided to you for this project are as follows [a summary for each of the rides can be found by clicking on the links and creating a free account on Strava (not a sponsor).]:

Stage 12 of the 2017 Tour de France for Romain Bardet
Stage 12 of the 2018 Tour de France for Robert Gesink
Stage 17 of the 2018 Tour de France for Thomas DeGendt
Stage 19 of the 2018 Tour de France for Romain Bardet


Programming Tasks
Level 0
(50 pts - all test case details visible)

Setup the following formatted input prompt and output print statements. These print statements will be further developed and more output statements will be added in higher level tasks. For now, this should give a nice initial structure to main().
Enter the filename:
Rider:
Race:
Time Interval is
Total GPS Datapoints:
Level 1
(25 pts - all test case details visible)

Prompt the user to enter a filename and open that file for reading. If a file with the user-inputted filename cannot be found or there was a problem opening the file, print the message "Could not open file." and terminate the program immediately.
If the file is opened properly, then read in the data stored in the file, making sure to continually check for the end-of-file, at which point the program should stop trying to read-in data from the file. There are 4 files used in the test cases, which are all provided to you for download, by simply clicking on the Download button just above the coding box below. All have a filename similar to TDF18_Stage12.txt, where the two 2-digit numbers representing the year and stage number vary for the different data sets. It is recommended that you download at least one of the files, open it up, and take a look at the content. The files contain a header with key information before the position data. All files have the following format:
The rider's name (first and last) on the first two lines
The race and stage name on the next two lines
The fifth line contains an integer representing the time interval for the data in the file (i.e. the main data of the file is actually the average position recordings over constant time segments given by this value).
The sixth line contains the titles long, lat, and elev for the data stored in the remainder of the file
The remainder of the file consists of many lines, each having three floating-point numbers, representing the longitude, latitude, and elevation data for the rider throughout the race, each separated in time by the time interval found in the header of the data file.
As the data is read in, keep track of the total number of GPS position data points in the file. Then, use the count of the total number of GPS position data points in the file together with the time interval to calculate the total length of time for the bike race. Note: you should not store the data read-in from the file in arrays. Instead, the counting done here and the calculations that follow should be completed by updating the quantities of interest as each data point is read in.
Print to screen the rider's name, the race & stage name, the time interval, the total number of GPS data points, and the total time in seconds for the bike race, in the following format (this sample output is the result when the user inputs TDF18_Stage12.txt):
Rider: Robert Gesink
Race: TDF2018 Stage12
Time Interval is 15 seconds

Total GPS Datapoints: 1371
Total Time: 20565 s
Level 2
(17 pts - all test case details visible, except for some unit testing of the user-defined functions)

Find and print the maximum elevation for the rider during the race (see sample output below for required format). Again, do not use arrays to store the data and analyze later. Instead, update quantities on-the-fly as the data is read-in.
Calculate and print the total elevation gain for the rider during the race (see sample output below for required format). The elevation gain is the accumulated quantity of only the positive changes in elevation from one data point to the next. That is, if the rider goes up 10 m between data points, then the elevation gain increases by 10. But, if the rider goes down by 10 m, there is no change to the elevation gain. Again, do not use arrays to store the data and analyze later. Instead, update quantities on-the-fly as the data is read-in.
Write the function LatLongsToDist() that takes in two pairs of (latitude, longitude) coordinates and returns the great-circle-distance between the points on the surface of the Earth, which is calculated using the formula:
d = R acos[ cos(latA)cos(latB)cos(lonB-lonA) + sin(latA)sin(latB) ] where (latA,lonA) and (latB,lonB) are the RADIAN coordinates for the two points, R is the radius of the EARTH (provided in the template as a global variable), d is the distance between the points, and acos() is the inverse cosine function. Note that the (latitude, longitude) coordinates stored in the data files are in DEGREES, so you will need to convert from DEGREES to RADIANS in order to use the formula.
Write the void function, getFormattedTime(), which converts a time given in only seconds to the associated number of hours, minutes, and remaining seconds (see sample output below for an example). Note: you have not been provided with the required function prototype, so careful attention must be given to the following instructions to ensure you have the correct format for the function. The function does not return any quantity directly. Instead, the function must have four parameters, in the following order:
an integer representing the input total number of seconds
a pointer to an integer representing the output number of hours
a pointer to an integer representing the output number of minutes
a pointer to an integer representing the output number of seconds
Note: the bigger the time interval for the GPS data, the larger the underestimation of the total distance and elevation gain statistics compared to the actual true values.

Level 3
(8 pts - limited test case details visible)

While the data is read-in, keep track of the total distance biked during the race by repeatedly calling LatLongsToDist(). Once all data has been read in, print out the total distance biked (see sample output below for required format).
Using a call to your getFormattedTime() function, convert the total number of seconds for the race to the proper format in hours, minutes, and seconds (see sample output below for required format, where hours, minutes, and seconds each use two spaces padded with zeros if necessary).
The following sample output for all Task Levels is the result when the user inputs TDF18_Stage12.txt:
Enter the filename: 

Rider: Robert Gesink
Race: TDF2018 Stage12
Time Interval is 15 seconds

Total GPS Datapoints: 1371
Total Time: 20565 s
Max Elevation: 2199.8 m
Elevation Gained: 5345.4 m
Distance Biked: 170.8 km
Formatted Total Time: 05:42.45 
Level 3+
(up to 10 pts extra credit - 5 pts for autograded test case, 5 pts for document submitted to Blackboard)

Have your program open a separate file for writing with a filename that is identical to the user-input filename (for the GPS data .txt file) with _DistElev appended to the back. For example, if the user inputs TDF18_Stage12.txt, then the new file should have the filename TDF18_Stage12_DistElev.txt. As another example, if the user inputs Apple.txt, then the new file should have the filename Apple_DistElev.txt. This must be programmed generally, for any filename entered by the user.
Write to the new file the distance and elevation data for all GPS data points, in two columns separated by a comma. Each distance value should be the total distance traveled up to that point from the start of the bike race. Format the data written to the file with 2 decimal places for distance and 1 decimal place for elevation. Here are a few lines from the output file, TDF18_Stage12_DistElev.txt, for Robert Gesink's TDF2018 Stage12 race (this is test case #47):

25.40, 569.4 
25.63, 566.2 
25.83, 565.2 
26.01, 561.8 
26.22, 558.6 
26.44, 556.2

You will need to run your code outside of zyBooks to have access to the files that are written. Once you have done so, import the TDF17_Stage12_DistElev.txt file into Excel (using a comma as a delimiter) and create a scatter/line plot of Elevation vs. Distance for Stage 12 of the 2017 Tour de France. Search the web for a comparable official elevation plot for this Stage. Put your plot and the official plot in a single .pdf document and submit it to Blackboard. Repeat the entire process for Stage 12 of the 2018 Tour de France. Your submission should therefore include two of your plots, and two official elevation figures for comparison.
LAB
