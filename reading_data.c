// This program will read a text file for data extracted and formatted from the Tour de France
// then it will calculate the total time of the stage of a race, total distance traveled,
// elevation gained.
// This will be printed out along with the rider name, race, stage, and interval between data
// points.

// Code written by Alex Dai
// CS 107
// 04 December 2018

#include <stdio.h>
#include <math.h>
#include <string.h>

const double RADIUS_EARTH = 6368.0; //global variable to be used in LatLongsToDist()

//----------------------------------------------------------------------------------------
// LatLongsToDist: calculates distance between two gps points
// [in] lat1, long1: latitude and longitude of first point in degrees
// [in] lat2, long2: latitude and longitude of second point in degrees
// [out] returns double: distance between two points in kilometers
double LatLongsToDist(double lat1, double long1, double lat2, double long2){

	//initializing pi value using acos function
	double pi = acos(-1);
	//conversion constant to be use to convert degrees to radians
	double dToR = pi / 180;
	//converting parameters to radians
	double latA = lat1 * dToR, lonA = long1 * dToR;
	double latB = lat2 * dToR, lonB = long2 * dToR;

	//calculating distance between two points
	double d = RADIUS_EARTH * acos(cos(latA)*cos(latB)*cos(lonB-lonA) + sin(latA)*sin(latB));

	return d;
}
//----------------------------------------------------------------------------------------
// getFormattedTime: calculates the number of hours, minutes, and seconds from total seconds
// [in] totSec: total time in seconds
// [in] *hours: pointer to number of hours
// [in] *minutes: pointer to number of minutes
// [in] *seconds: pointer to number of seconds
// [out] void: returns void, updates parameters using pointers
void getFormattedTime(int totSec, int* hours, int* minutes, int* seconds){

	*hours = totSec / 3600;
	*minutes = (totSec % 3600) / 60;
	*seconds = totSec % 60;
}
//----------------------------------------------------------------------------------------
int main() {

	FILE* outFile;
	FILE* inFile;
	char fileName[100];
	char fileName2[100];
	char* stringPos = NULL;
	char first[20];
	char last[20];
	char race[20];
	char stage[20];
	char position[3][10];
	int interval;
	int counter = 0; //counts number of items
	double longitude, prevLong;
	double lat, prevLat;
	double elev;
	double maxElev = 0.0;
	double elevGain = 0.0;
	double prevElev = 0.0;
	double elevDiff = 0.0;
	double distance = 0.0;
	//variables to be used for hours, minutes and seconds
	int h = 0, m = 0, s = 0;

	//prompting user for file name
	printf("Enter the filename: \n");
	scanf("%s", fileName);
	//copies the filename for reading
	strcpy(fileName2, fileName);
	//calculates the position to append file name
	int len = strlen(fileName) - 4;
	//appends file name to be written to
	strcpy(&fileName2[len], "_DistElev.txt");
	printf("%s\n%s\n",fileName, fileName2);

	//opening file for reading
	inFile = fopen(fileName, "r");
	if(inFile == NULL){
		printf("Could not open file.\n");
		return -1;
	}
	//opening file for writing
	outFile = fopen(fileName2, "w");
	if(outFile == NULL){
		printf("Could not write file.\n");
		return -1;
	}
	//reading and assigning file data to variables
	if(fscanf(inFile, "%s", first) != EOF){
		printf("Rider: %s", first);
		++counter;
	}
	if(fscanf(inFile, "%s", last) != EOF){
		printf(" %s\n", last);
		++counter;
	}
	if(fscanf(inFile, "%s", race) != EOF){
		printf("Race: %s", race);
		++counter;
	}
	if(fscanf(inFile, "%s", stage) != EOF){
		printf(" %s\n", stage);
		++counter;
	}
	if(fscanf(inFile, "%d", &interval) != EOF){
		printf("Time Interval is %d seconds\n\n", interval);
		++counter;
	}
	//reading gps locations
	for(int i = 0; i < 3; ++i){
		if(fscanf(inFile, "%s", position[i]) != EOF){
			++counter;
		}else{
			break;
		}
	}
	//reading in gps location points
	int i = 0; // reinitializing variable to zero
	while(!feof(inFile)){
		fscanf(inFile, "%lf %lf %lf", &longitude, &lat, &elev);
		//findind max elevation
		if(elev > maxElev){
			maxElev = elev;
		}
		if(i == 0){
			//starting point of output file
			fprintf(outFile,"%0.2lf, %0.1lf\n", 0.00, elev);
		}
		if(i > 0){
			//calculates elevation gained
			elevDiff = elev - prevElev;
			if(elevDiff > 0.0){
				elevGain += elevDiff;
			}
			//calculating total distance
			distance +=  LatLongsToDist(prevLat, prevLong, lat, longitude);
			//prints distance traveled and elevation to output file
			fprintf(outFile,"%0.2lf, %0.1lf\n", distance, elev);
		}
		//updating previous elevation
		prevElev = elev;
		prevLong = longitude;
		prevLat = lat;
		//counts total number of data points
		i++;
	}
	counter += (3 * i);

	fclose(inFile);
	fclose(outFile);
	//printing data
	printf("Total GPS Datapoints: %d\n", i);
	printf("Total Time: %d s\n", i * interval);
	printf("Max Elevation: %0.1lf m\n", maxElev);
	printf("Elevation Gained: %0.1lf m\n", elevGain);
	printf("Distance Biked: %0.1lf km\n", distance);
	//call to getFormattedTime function
	getFormattedTime(i*interval, &h, &m, &s);
	printf("Formatted Total Time: %02d:%02d.%02d\n", h, m, s);

	//do not mind, the following is just for me ;)
	printf("\nNumber of items: %d\n", counter);
	printf("%s %s %s\n", position[0], position[1], position[2]);
	printf("Last line is...%lf %lf %lf\n", longitude, lat, elev);

	return 0;
}
