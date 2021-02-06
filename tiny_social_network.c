	/* Project 2

		Andrew Nixon
		ENEE150
		Spring2020
		March 27 2020

		Project Description: 

		My Tiny Social Network (MyTSN)
			Design a simple social network. Read in information from an input file, then provide the user
			with a simple interface to manage the MyTSN database. Input file will only have userID and friendship 
			information. The menu should have options for: 
				(1) search for a user
				(2)	list a user's friends
				(3)	add a new friend to a user
				(4) add a new user
				(5)	remove a friendship
				(6)	remove a user
				(0) exit the program
		
			should execute with: a.out user_database.txt update.txt

		input file: 
			each user has a 6-digit ID. (<> not included, this just represents that UID is a number)
			<UID>, e.g. 789264

			each ID should be padded with 0's if it does not have 6 full digits
			e.g. 000123

			friendships will be denoted: 
			<UID1> <UID2>

		output file: 
			this will contain all updates made to the input file by the time the program exits.
			output file will list all the friends of each user in the format: 
				<UID>#	if the user has no friends
				<UID>: <UID1>, <UID2>, ... , <UIDk>: if the user has k friends. 
	
		Menu Description: 
			(1) search for a user
					User <UID> found or
					User <UID> not found
			(2)	list a user's friends
					Prompt user to enter UID. If does not exist and fails after 3 attempts, return to main menu.
					User <UID> does not exist, Enter the user ID or
					User <UID> has no friends. or
					User <UID>'s friends: <UID1>, <UID>2>, ... , <UIDk>. 
			(3)	add a new friend to a user
					Prompt user to enter user IDs of the two friends (assume they're both valid):
					Print that they are now friends or 
					Print that <UID1> and <UID2> are already friends.
			(4) add a new user
					Prompt user to enter an ID
					Check the UID to make sure it's digits are 0-9 and no more than 6 digits, and that it is 
					not already in the MyTSN database.
					If there's a violation, print either: 
						<UID> can only have up to 6 digits
						<UID> already exists
					If the user fails after 3 attempts, return to main menu.
			(5)	remove a friendship
					Promt user to enter 2 UID's, assume they are both valid. 
					If they are not already friends, print out: 
						Users <UID1> and <UID2> are not friends.
					If they are, remove the friendship and print: 
						Users <UID1> and <UID2> are no longer friends. 
			(6)	remove a user
					Prompt user to enter UID to be removed. Assume UID is valid. Remore the UID from all 
					other friendships and print out: 
						User <UID> has been removed from MyTSN
			(0) exit
					Print out "Thank you for using MyTSN!"
					Print the last copy of the database to an output file
					Exit the program. 
		Bonus Points: 
			If the UID's in the output file are printed in ascending order and so are each of their friends. 
			*/ 


	#include <stdio.h>
	#include <stdlib.h>


	//Global variable declarations-----------------
	int numUsers, mostFriends;
	const int input_columns = 20;
	const int lenUID = 6;

	//Custom program descriptions-------------------
		void printMenu();
		int checkDigits(int* a);
		void printUserNum(int* a);
		int* convertToNumber(char* a);
		char* convertToChar(int* a);
		int checkIfValid(char* a);
		int** extractFriends(char* a);
		int checkIfSame(int* a, int* b);
		void printFriendships(int*** fships, int** usrs, int* numfships, int numUsrs, int mostFrnds);
		int searchForUser(int** usrs, char* a, int numUsrs);
		int getPosition(int** usrs, char* a, int numUsrs);
		int*** addFriendship(int*** frnds, int** usrs, int* thisUsrsFrnds, char* friend1, char* friend2, int numUsrs, int maxFrnds);
		void printThisPersonsFriends(int*** friendsList, int** usrs, int* numFrnds, char* a, int pos, int numUsrs);
		int changeMostFriends(int** usrs, int* thisUsrsFrnds, int numUsrs, int maxFrnds, int change);
		int* changeNumFriends(int** usrs, int* thisUsrsFrnds, char* newfrnd1, char* newfrnd2, int numUsrs, int change);
		int checkIfAlreadyFriends(int*** frnds, int** usrs, int* thisUsrsFrnds, char* newfrnd1, char* newfrnd2, int numUsrs);
		int*** removeFriendship(int*** frnds, int** usrs, int* thisUsrsFrnds, char* newfrnd1, char* newfrnd2, int numUsrs);
		int exponential(int a, int b);
		int intFromPointer(int* a);
		int* userIntArray(int** usrs, int numFrnds);
		int* sortArray(int* arr, int n);
	//---------------------------------------

	//print out the main menu so the user knows what choices they have
	void printMenu(void) {
		printf("\tMain Menu\n\n");
		printf("\t1. search for a user\n");
		printf("\t2. list a user's friends\n");
		printf("\t3. add a new friend to a user\n");
		printf("\t4. add a new user\n");
		printf("\t5. remove a friendship\n");
		printf("\t6. remove a user\n");
		printf("\t0. exit the program.\n\n");
	}

	//ensure that the stored UID has legal values for each number
	int checkDigits(int *a) {
		int i;
		int legal = 1;
		for (i = 0; i < lenUID; i++) {
			if (a[i] > 9 || a[i] < 0) {
				legal = 0;
			}
		}
		return legal;
	}

	//take in the pointer to the UID and print it out to the screen
	void printUserNum(int* a) {
		int i;
		for (i = 0; i < lenUID; i++) {
			printf("%d", a[i]);
		}
	}

	//take in the character array of numbers, convert them to integers
	//and return a pointer to the new integer array
	int* convertToNumber(char* a) {
		int* convertedNumber;
		convertedNumber = (int*)malloc(6 * sizeof(int));
		int i;

		for (i = 0; i < lenUID; i++) {
			convertedNumber[i] = a[i] - 48;
		}

		return convertedNumber;
	}

	//take in an integer array and return a pointer to the converted 
	//characters
	char* convertToChar(int* a) {
		char* convertedChar;
		convertedChar = (char*)malloc(6 * sizeof(char));
		int i; 
		for (i = 0; i < lenUID; i++) {
			convertedChar[i] = a[i] + 48;
		}

		return convertedChar;
	}

	//similar to checkDigits, ensure that a character array 
	//has valid entries for each number
	int checkIfValid(char a[]) {
		int flg = 1, i = 0;
		while(a[i] != '\0') {
			i++;
		}
	
		if (i != 6) {
			flg = 0;
			return flg;
		}
		for (i = 0; i < lenUID; i++) {
			if (a[i] > 57 || a[i] < 48) {
				flg = 0;
				return flg;
			}
		}
		return flg;
	}

	//for use in the input file, take in a character array and extract
	//the two UIDs that were in that line, save pointers to each of those 
	//lines, and return a pointer to both of those pointers.
	int** extractFriends(char* a) {
		int** twoNewFriends = NULL;
		int* friendStrtoInt;
		int i, cnt;

		twoNewFriends = (int**)malloc(2 * sizeof(int*));
		twoNewFriends[0] = (int*)malloc(lenUID * sizeof(int));
		twoNewFriends[1] = (int*)malloc(lenUID * sizeof(int));
		friendStrtoInt = (int*)malloc(lenUID * sizeof(int));

		for (i = 0; i < lenUID; i++) {
			friendStrtoInt[i] = a[i] - 48;
		}

		twoNewFriends[0] = friendStrtoInt;
	 
		friendStrtoInt = (int*)calloc(6, sizeof(int));
		i++;
		cnt = 0;
		while(i < 7+lenUID) {
			friendStrtoInt[cnt] = a[i] - 48;
			cnt++;
			i++;
		}

		twoNewFriends[1] = friendStrtoInt;

		return twoNewFriends;
	}

	//check to see if two pointers contain the same numbers, and
	//therefore represent the same UID. return a 1 or 0 to 
	//indicate true false, depending on the situation.
	int checkIfSame(int* a, int* b) {
		int cnt = 0, flag;
		for (cnt = 0; cnt < lenUID; cnt++) {
			if (a[cnt] != b[cnt]) {
				flag = 0;
				return flag;
			}
			else {
				flag = 1;
			}
		}
		return flag;
	}

	//print out the entire database. users will be printed on the left, and their friends 
	//will be printed in the same line on the right. 
	void printFriendships(int*** fships, int** usrs, int* numfships, int numUsrs, int mostFrnds) {
		int cnt, cnt2, i;

		printf("USERS\t\tFRIENDS\n");
	
		printf("------  \t");
		for (i = 0; i < mostFrnds; i++) {
			printf("------   ", i + 1);
		}
		printf("\n");
		for (cnt = 0; cnt < numUsrs; cnt++) {
			printUserNum(usrs[cnt]);
			printf(": ");
			if (numfships[cnt] == 0) {
				printf("\t#\n");
			}
			else {
				printf("\t");
				for (cnt2 = 0; cnt2 < numfships[cnt]; cnt2++) {
					printUserNum(fships[cnt][cnt2]);
					printf("   ");
				}
				printf("\n");
			}
		}
	}

	//return a 1 or 0 to indicate true false if a user is contained 
	//in the database
	int searchForUser(int** usrs, char* a, int numUsrs) {
		int i, j, cnt;
		int searchFlag = 0;
		int* tempConvertP;
		tempConvertP = convertToNumber(a);
	
		for (i = 0; i < numUsrs; i++) {
			cnt = 0;
			for (j = 0; j < lenUID; j++) {
				if (tempConvertP[j] == usrs[i][j]) {
					cnt++;
				}
			}
			if (cnt == j) {
				searchFlag = 1;
				break;
			}
		}
		return searchFlag;
	}

	//return the value of the counter where a user is located in the list 
	//of users. this value will be 0-offset. 
	int getPosition(int** usrs, char* a, int numUsrs) {
		int i, j, cnt, thisFriend = -1;
		int* tempConvertP;
		tempConvertP = convertToNumber(a);
		for (i = 0; i < numUsrs; i++) {
			cnt = 0;
			for (j = 0; j < lenUID; j++) {
				if (tempConvertP[j] == usrs[i][j]) {
					cnt++;
				}
			}
			if (cnt == j) {
				thisFriend = i;
				break;
			}
		}
		return thisFriend;
	}

	//similar to printFriendships, print the user and their friends for only one single user. 
	//this follows to comma/period style as indicated in the instructions.
	void printThisPersonsFriends(int*** friendsList, int** usrs, int* numFrnds, char* a, int pos, int numUsrs) {
		int i;
		int* tmpFrnd;
		tmpFrnd = malloc(lenUID * sizeof(int));
		tmpFrnd = convertToNumber(a);
		printf("user ");
		printUserNum(tmpFrnd);
		if (searchForUser(usrs, a, numUsrs) == 0) {
			printf(" does not exist.\n");
		}
		else if (numFrnds[pos] == 0) {
			printf(" has no friends.\n");
		}
		else {
			printf("'s friends: ");
			for (i = 0; i < (numFrnds[pos]-1); i++) {
				printUserNum(friendsList[pos][i]);
				printf(", ");
			}
			printUserNum(friendsList[pos][i]);
			printf(".\n");
		}
		printf("\n");
	}

	//add a friendship to the database. two users are entered in as parameters, and they are first 
	//each added to each other as friends, which updates the database in both locations. the 
	//new friendship database is then returned.
	int*** addFriendship(int*** frnds, int** usrs, int* thisUsrsFrnds, char* friend1, char* friend2, int numUsrs, int maxFrnds) {
		int** buds;
		int p;
		buds = (int**)malloc(2 * sizeof(int*));
		buds[0] = (int*)malloc(lenUID * sizeof(int));
		buds[1] = (int*)malloc(lenUID * sizeof(int));
		buds[0] = convertToNumber(friend1);
		buds[1] = convertToNumber(friend2);
		for (p = 0; p < numUsrs; p++) {
			if (checkIfSame(usrs[p], buds[0])) {
				frnds[p] = realloc(frnds[p], (thisUsrsFrnds[p] * sizeof(int*)));
				frnds[p][thisUsrsFrnds[p] - 1] = buds[1];
			}
		}
		for (p = 0; p < numUsrs; p++) {
			if (checkIfSame(usrs[p], buds[1])) {
				frnds[p] = realloc(frnds[p], (thisUsrsFrnds[p] * sizeof(int*)));
				frnds[p][thisUsrsFrnds[p] - 1] = buds[0];
			}
		}
		return frnds;
	}

	//there are cases when friendships are added or removed and this changes the maximum number of friends
	//held by one user. this function is mainly for stylistic reasons, because I wrote the program to 
	//print out "------" up above to match all the columns of friends. this function doesn't really 
	//serve a real purpose besides that.
	int changeMostFriends(int** usrs, int* thisUsrsFrnds, int numUsrs, int maxFrnds, int change) {
		int p, check = 0;
		if (change) {
			for (p = 0; p < numUsrs; p++) {
				if (thisUsrsFrnds[p] > maxFrnds) {
					maxFrnds++;
				}
			}
			return maxFrnds;
		}
		else {
			for (p = 0; p < numUsrs; p++) {
				if (thisUsrsFrnds[p] > check) {
					check = thisUsrsFrnds[p];
				}
			}
			return check;
		}
	}
	
	//check to see if two characters arrays are present in each of the other's friendships data. 
	//if they are, return a	1, if not, return a 0.
	int checkIfAlreadyFriends(int*** frnds, int** usrs, int* thisUsrsFrnds, char* newfrnd1, char* newfrnd2, int numUsrs) {
		int i, j, flag = 0, pos1, pos2; 
		int** buds;
		buds = (int**)malloc(2 * sizeof(int*));
		buds[0] = (int*)malloc(lenUID * sizeof(int));
		buds[1] = (int*)malloc(lenUID * sizeof(int));
		buds[0] = convertToNumber(newfrnd1);
		buds[1] = convertToNumber(newfrnd2);

		for (i = 0; i < numUsrs; i++) {
			if (checkIfSame(usrs[i], buds[0])) {
				pos1 = i; 
				break;
			}
		}
		for (i = 0; i < numUsrs; i++) {
			if (checkIfSame(usrs[i], buds[1])) {
				pos2 = i;
				break;
			}
		}
		for (i = 0; i < thisUsrsFrnds[pos1]; i++) {
			if (checkIfSame(frnds[pos1][i], buds[1])) {
				flag = 1;
			}
		
		}
		for (i = 0; i < thisUsrsFrnds[pos2]; i++) {
			if (checkIfSame(frnds[pos2][i], buds[0])) {
				flag = 1;
			}
		}
		return flag;
	}

	//whenever friendships are added or removed, update the array that stores information about number of 
	//friends each user has at that position. return the new array.
	int* changeNumFriends(int** usrs, int* thisUsrsFrnds, char* newfrnd1, char* newfrnd2, int numUsrs, int change) {
		int i;
		int** buds;
		buds = (int**)calloc(2, sizeof(int*));
		buds[0] = (int*)malloc(lenUID * sizeof(int));
		buds[1] = (int*)malloc(lenUID * sizeof(int));
		buds[0] = convertToNumber(newfrnd1);
		buds[1] = convertToNumber(newfrnd2);
		if (change) {
			for (i = 0; i < numUsrs; i++) {
				if (checkIfSame(usrs[i], buds[0])) {
					thisUsrsFrnds[i]++;
					break;
				}
			}
			for (i = 0; i < numUsrs; i++) {
				if (checkIfSame(usrs[i], buds[1])) {
					thisUsrsFrnds[i]++;
					break;
				}
			}
		}
		else {
			for (i = 0; i < numUsrs; i++) {
				if (checkIfSame(usrs[i], buds[0])) {
					thisUsrsFrnds[i]--;
					break;
				}
			}
			for (i = 0; i < numUsrs; i++) {
				if (checkIfSame(usrs[i], buds[1])) {
					thisUsrsFrnds[i]--;
					break;
				}
			}
		}
		return thisUsrsFrnds;
	}

	//similar to addFriendship, removeFriendship removes each of two input character arrays from the friendship 
	//database of the other. returns the new updated friendship database. 
	int*** removeFriendship(int*** frnds, int** usrs, int* thisUsrsFrnds, char* newfrnd1, char* newfrnd2, int numUsrs) {
		int** buds;
		int testArray[6] = { 1, 0, 0, 0, 0, 0 };
		int p, q, t, i, flag1 = 0, flag2 = 0;
		buds = (int**)malloc(2 * sizeof(int*));
		buds[0] = (int*)malloc(lenUID * sizeof(int));
		buds[1] = (int*)malloc(lenUID * sizeof(int));
		buds[0] = convertToNumber(newfrnd1);
		buds[1] = convertToNumber(newfrnd2);
		//removing newfrnd2 from newfrnd1's list of friends
		p = 0;
		t = 0;
		flag1 = 0;
		flag2 = 0;
		while (!flag1) {
			if (checkIfSame(usrs[p], buds[0])) {
				q = 0;
				while (!flag2) {
					if (checkIfSame(frnds[p][q], buds[1])) {
						if (thisUsrsFrnds[p] == 1) {
							for (i = 0; i < lenUID; i++) {
								frnds[p][q][i] = testArray[i];
							}
							flag1 = 1;
							flag2 = 1;
							break;
						}
						else {
							for (t = q; t < thisUsrsFrnds[p] - 1; t++) {
								for (i = 0; i < lenUID; i++) {
									frnds[p][t][i] = frnds[p][t + 1][i];
								}
							}
							flag1 = 1;
							flag2 = 1;
							break;
						}
					}
					q++;
				}
			}
			p++;
		}
		//removing newfrnd1 from newfrnd2's list of friends
		p = 0;
		t = 0;
		flag1 = 0;
		flag2 = 0;
		while (!flag1) {
			if (checkIfSame(usrs[p], buds[1])) {
				q = 0;
				while (!flag2) {
					if (checkIfSame(frnds[p][q], buds[0])) {
						if (thisUsrsFrnds[p] == 1) {
							for (i = 0; i < lenUID; i++) {
								frnds[p][q][i] = testArray[i];
							}
							flag1 = 1;
							flag2 = 1;
							break;
						}
						else {
							for (t = q; t < thisUsrsFrnds[p] - 1; t++) {
								for (i = 0; i < lenUID; i++) {
									frnds[p][t][i] = frnds[p][t + 1][i];
								}
							}
							flag1 = 1;
							flag2 = 1;
							break;
						}
					}
					q++;
				}
			}
			p++;
		}
		return frnds;
	}

	//I didn't know if we were allowed to use math.h, but I assumed we weren't.
	//this function takes a to the power of b and returns the result. 
	int exponential(int a, int b) {
		int i;
		
		if (b == 0) {
			return 1;
		}

		if (b == 1) {
			return a;
		}

		else {
			b--;
			a = a * exponential(a, b);
		}
	}
	
	//this function converts a pointer to a 6-digit number to the 
	//actual 6-digit number, and returns it. this is for the extra credit
	int intFromPointer(int* a){
		int i, answer = 0, place = 5;
		for (i = 0; i < lenUID; i++) {
			answer = answer + a[place] * exponential(10, i);
			place--;
		}
		return answer;
	}

	//this converts the 2D user information into an array of
	//users as integers. again this is for the extra credit.
	int* userIntArray(int** usrs, int numUsrs) {
		int i, j;
		int* sortedArray;
		sortedArray = malloc(numUsrs * sizeof(int));
		for (i = 0; i < numUsrs; i++) {
			sortedArray[i] = intFromPointer(usrs[i]);
		}
		return sortedArray;
	}

	//this uses bubble sort to sort an array of integers of size n
	//and returns the array. used for extra credit
	int* sortArray(int* arr, int n) {
		int i, j, temp;
		for (i = 0; i < (n-1); i++) {
			for (j = 0; j < (n - i - 1); j++) {
				if (arr[j] > arr[j + 1]) {
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j + 1] = temp;
				}
			}
		}
		return arr;
	}

	//this function takes in an unsorted and sorted version of the 
	//same array. it then stores the information about the location 
	//of the integer in the unsorted array and the sorted one.
	//this is used for the extra credit. 
	int** getNewPos(int* unsorted, int* sorted, int numUsrs) {
		int i, j;
		int** posArr;
		posArr = malloc(numUsrs * sizeof(int*));
		for (i = 0; i < numUsrs; i++) {
			posArr[i] = malloc(2 * sizeof(int));
		}
		for (i = 0; i < numUsrs; i++) {
			posArr[i][0] = i;
			for (j = 0; j < numUsrs; j++) {
				if (unsorted[i]== sorted[j]) {
					posArr[i][1] = j;
				}
				break;
			}
		}
		return posArr;
	}


	int main(int argc, char* argv[]) {

		char ch;
		int input_columns = 20;
		int lenUID = 6;
		int userResponse, i, j, k, f, s, p;
		int num_lines_from_input, numUsers = 0, flagmain = 0;
		int* thisUsersNumberOfFriends;
		thisUsersNumberOfFriends = malloc(sizeof(int));
		thisUsersNumberOfFriends[0] = 0;
		
		//error check the command line
		if (argc != 3) {
			printf("Incorrect number of input arguments.\n");
			printf("Format: a.out, input, output\n");
			exit(0);
		}

		FILE* input_file;
		input_file = fopen(argv[1], "r");

		FILE* output_file;
		output_file = fopen(argv[2], "w");

		if (input_file == NULL) {
			printf("%s could not be opened.\n", argv[1]);
			exit(0);
		}

		if (output_file == NULL) {
			printf("%s could not be opened.\n", argv[2]);
			exit(0);
		}
		i = 0;

		char** input_array;
		input_array = malloc(sizeof(char*));
		if (input_array == NULL) {
			printf("problem allocating\n");
			exit(0);
		}

		//store in all the information from the input file 
		//friendships are stored using a 3D array of characters. 
		//first pointer = points to all the users, where each line represents a UID.
		//second pointer = points to the friends held by the user at that line.
		//third pointer = points to the UID of that particular friend
		//users are stored using a 2D array of characters. 
		//first pointer = points to all the users, where each line represents a UID.
		//second pointer = points to the actual user at that location.
		do {
			input_array = (char**)realloc(input_array, (i + 1) * sizeof(char*));
			input_array[i] = (char*)malloc(input_columns * sizeof(char));
			if (input_array[i] == NULL) {
				printf("error in input_array\n");
				exit(0);
			}
			fgets(input_array[i], input_columns, input_file);
			i++;
		} while (!feof(input_file));

		num_lines_from_input = i - 1;
		int** users = NULL;
		int*** friendships = NULL;
		int** newBuds = NULL;
		users = malloc(sizeof(int*));
		friendships = malloc(sizeof(int**));
		newBuds = malloc(sizeof(int*));

		j = 0;
		k = 0;
		p = 0;

		//store all the input file information into the array
		for (i = 0; i < num_lines_from_input; i++) {
			if (input_array[i][6] == '#') {
				numUsers++;
				users = realloc(users, ((j + 1) * sizeof(int*)));
				users[j] = malloc(lenUID * sizeof(int));
				users[j] = convertToNumber(input_array[i]);
				friendships = realloc(friendships, ((j + 1) * sizeof(int**)));
				friendships[j] = malloc(sizeof(int*));
				thisUsersNumberOfFriends = realloc(thisUsersNumberOfFriends, (j + 1) * sizeof(int));
				thisUsersNumberOfFriends[j] = 0;
				j++;

			}

			else {
				newBuds = NULL;
				newBuds = (int**)calloc(2, sizeof(int*));
				newBuds[0] = (int*)malloc(lenUID * sizeof(int));
				newBuds[1] = (int*)malloc(lenUID * sizeof(int));
				newBuds = extractFriends(input_array[i]);
				for (p = 0; p < numUsers; p++) {
					if (checkIfSame(users[p], newBuds[0])) {
						thisUsersNumberOfFriends[p]++;
						friendships[p] = realloc(friendships[p], (thisUsersNumberOfFriends[p] * sizeof(int*)));
						friendships[p][thisUsersNumberOfFriends[p] - 1] = newBuds[1];
						if (thisUsersNumberOfFriends[p] > mostFriends) {
							mostFriends++;
						}
					}
				}
				for (p = 0; p < numUsers; p++) {
					if (checkIfSame(users[p], newBuds[1])) {
						thisUsersNumberOfFriends[p]++;
						friendships[p] = realloc(friendships[p], (thisUsersNumberOfFriends[p] * sizeof(int*)));
						friendships[p][thisUsersNumberOfFriends[p] - 1] = newBuds[0];
						if (thisUsersNumberOfFriends[p] > mostFriends) {
							mostFriends++;
						}
					}
				}
			}
		}

		//enter the main part of the program where the user interacts

		printf("\n\n\tWelcome to MyTSN!\n\n");

		printf("\n\n");

		while (!flagmain) {
			char userInputUID[lenUID];
			char* buf;
			buf = calloc(99, sizeof(char));
			int* friend1num;
			int* tempPrintNum;
			char* charPointer;
			int tempPos, flag2 = 0, flag4 = 0;
			char* friend1char;
			char* friend2char;
			printMenu();
			//figure out which option the user wants to do
			printf("please choose a menu option: ");
			scanf("%d", &userResponse);
			ch = getchar();
			//check for errors if they dont enter a valid response
			if (userResponse > 6 || userResponse < 0) {
				printf("invalid response. must be between 0 and 6.\n");
			}
			//if it's valid, enter the switch statement
			else {
				switch (userResponse) {
					//check to see if the user exists in the database
					case 1:
						printf("enter user ID to search: ");
						gets(buf);
						if (checkIfValid(buf)) {
							for (i = 0; i < lenUID; i++) {
								userInputUID[i] = buf[i];
							}
						}
						else {
							printf("invalid entry\n");
							break;
						}
						//they will either be found....
						if (searchForUser(users, userInputUID, numUsers)) {
							printf("User ");
							tempPrintNum = convertToNumber(userInputUID);
							printUserNum(tempPrintNum);
							printf(" found\n\n");
						}
						//....or they will not be found
						else {
							printf("User: ");
							tempPrintNum = convertToNumber(userInputUID);
							printUserNum(tempPrintNum);
							printf(" not found\n\n");
						}
						break;
					//list a users friends, and give them three attempts to enter the ID correctly.
					case 2:
						while (flag2 < 3) {
							printf("enter the user ID: ");
							gets(buf);
							if (checkIfValid(buf)) {
								for (i = 0; i < lenUID; i++) {
									userInputUID[i] = buf[i];
								}
								tempPos = getPosition(users, userInputUID, numUsers);
								printThisPersonsFriends(friendships, users, thisUsersNumberOfFriends, userInputUID, tempPos, numUsers);
								break;
							}
							//show a message telling them how many chances they have left.
							else {
								printf("invalid entry, you have %d attempts left.\n", (2 - flag2));
								flag2++;
							}
						}
						break;
					//add a friendship
					case 3:
						printf("enter the user IDs of the two friends. friend 1: ");
						friend1char = calloc(8, sizeof(char));
						friend2char = calloc(8, sizeof(char));
						gets(buf);
						if (searchForUser(users, buf, numUsers)) {
							for (i = 0; i < lenUID; i++) {
								friend1char[i] = buf[i];
							}
						}
						//return an error if the first user doesn't exist.
						else {
							printf("user %s does not exist.\n", buf);
							break;
						}
						printf("enter the user IDs of the two friends. friend 2: ");
						buf = calloc(99, sizeof(char));
						gets(buf);
						if (searchForUser(users, buf, numUsers)) {
							for (i = 0; i < lenUID; i++) {
								friend2char[i] = buf[i];
							}
						}
						//return an error if hte second user doesn't exist. 
						else {
							printf("user %s does not exist\n", buf);
							break;
						}
						int* frnd1int3 = calloc(lenUID, sizeof(int));
						int* frnd2int3 = calloc(lenUID, sizeof(int));
						frnd1int3 = convertToNumber(friend1char);
						frnd2int3 = convertToNumber(friend2char);
						//make sure users cant be friends of themselves
						if (checkIfSame(frnd1int3, frnd2int3)) {
							printf("users cannot be friends of themselves\n.");
							break;
						}
						//make sure they aren't already friends, and return error message if they are.
						if (checkIfAlreadyFriends(friendships, users, thisUsersNumberOfFriends, friend1char, friend2char, numUsers)) {
							printf("User: ");
							printUserNum(frnd1int3);
							printf(" and ");
							printUserNum(frnd2int3);
							printf(" are already friends.\n");
						}
						//add them if they pass all the checks.
						else {
							thisUsersNumberOfFriends = changeNumFriends(users, thisUsersNumberOfFriends, friend1char, friend2char, numUsers, 1);
							mostFriends = changeMostFriends(users, thisUsersNumberOfFriends, numUsers, mostFriends, 1);
							friendships = addFriendship(friendships, users, thisUsersNumberOfFriends, friend1char, friend2char, numUsers, mostFriends);
						}
						break;
					//add a new UID, give the user 3 chances to enter it correctly.
					case 4:
						while (flag4 < 3) {
							printf("enter a user ID: ");
							char* newUserID;
							char* testingArray;
							int* newUserNum;
							testingArray = malloc(20 * sizeof(char));
							gets(buf);
							for (i = 0; buf[i] != '\0'; i++) {
								testingArray[i] = buf[i];
							}
							int leng = i - 1;
							int rest = 6 - i;
							int end = lenUID - 1;
							//check to make sure it doesn't have more than 6 digits
							if (i > 6) {
								printf("<UID> can only have up to 6 digits.\n");
								flag4++;
								printf("you have %d chances left\n", 3 - flag4);
							}
							//check to make sure the user doesn't already exist
							else if (searchForUser(users, buf, numUsers)) {
								printf("user: ");
								printf("%s ", buf);
								printf("already exists\n.");
								flag4++;
								printf("you have %d chances left\n", 3 - flag4);
							}
							//store the information in a new UID array.
							else {
								newUserID = calloc(20, sizeof(char));
								//fill in the entered UID with 0's to make it a valid UID.
								for (i = leng; i > -1; i--) {
									newUserID[end] = testingArray[i];
									end--;
								}
								for (i = 0; i < rest; i++) {
									newUserID[i] = '0';
								}
								//check to make sure it doesn't have any non-integer characters
								if (checkIfValid(newUserID)) {
									//add it to the database if it doesn't and print out the database showing it was added
									newUserNum = malloc(lenUID * sizeof(int));
									newUserNum = convertToNumber(newUserID);
									numUsers++;
									users = realloc(users, numUsers * sizeof(int*));
									users[numUsers - 1] = malloc(lenUID * sizeof(int));
									users[numUsers - 1] = newUserNum;
									thisUsersNumberOfFriends = realloc(thisUsersNumberOfFriends, numUsers * sizeof(int));
									thisUsersNumberOfFriends[numUsers - 1] = 0;
									friendships = realloc(friendships, numUsers * sizeof(int**));
									friendships[numUsers - 1] = malloc(1 * sizeof(int*));
									break;
								}
								else {
									//print an error message if the user is not valid. 
									printf("invalid input, can only be digits 0-9\n");
									flag4++;
									printf("you have %d chances left\n", 3 - flag4);
								}
							}
						}
						break;
					//remove a friendship	
					case 5:
						printf("enter the user IDs of the two friends. friend 1: ");
						friend1char = malloc(lenUID * sizeof(char));
						friend1num = malloc(lenUID * sizeof(int));
						int* friend2num;
						friend2char = malloc(lenUID * sizeof(char));
						friend2num = malloc(lenUID * sizeof(int));
						gets(buf);
						//check to make sure it's valid, show and error message if not
						if (checkIfValid(buf)) {
							for (i = 0; i < lenUID; i++) {
								friend1char[i] = buf[i];
							}
						}
						else {
							printf("invalid entry\n");
							break;
						}
						friend1num = convertToNumber(friend1char);
						printf("enter the user IDs of the two friends. friend 2: ");
						buf = calloc(99, sizeof(char));
						gets(buf);
						//check to make sure it's valid, show and error message if not
						if (checkIfValid(buf)) {
							for (i = 0; i < lenUID; i++) {
								friend2char[i] = buf[i];
							}
						}
						else {
							printf("invalid entry\n");
							break;
						}
						friend2num = convertToNumber(friend2char);
						//make sure that they were friends before
						if (checkIfAlreadyFriends(friendships, users, thisUsersNumberOfFriends, friend1char, friend2char, numUsers)) {
							friendships = removeFriendship(friendships, users, thisUsersNumberOfFriends, friend1char, friend2char, numUsers);
							thisUsersNumberOfFriends = changeNumFriends(users, thisUsersNumberOfFriends, friend1char, friend2char, numUsers, 0);
							mostFriends = changeMostFriends(users, thisUsersNumberOfFriends, numUsers, mostFriends, 0);
							//print out a message showing they're no longer friends. 
							printf("Users ");
							printUserNum(friend1num);
							printf(" and ");
							printUserNum(friend2num);
							printf(" are no longer friends.\n");
							break;
						}
						//return an error message if not. 
						else {
							printf("Users ");
							printUserNum(friend1num);
							printf(" and ");
							printUserNum(friend2num);
							printf(" were not already friends.\n");
							break;
						}
					//remove a UID
					case 6:
						printf("enter the user ID of the user you want to remove: ");
						friend1char = malloc(lenUID * sizeof(char));
						friend1num = malloc(lenUID * sizeof(int));
						gets(buf);
						//check to make sure it's valid, show and error message if not
						if (checkIfValid(buf)) {
							for (i = 0; i < lenUID; i++) {
								friend1char[i] = buf[i];
							}
						}
						else {
							printf("invalid entry\n");
							break;
						}
						//remove the friend from all areas of the database. 
						int* frnd1int;
						int* frnd2int;
						char* frnd2char;
						int i, p, t, q, cnt, chk, flag6 = 0;
						frnd1int = malloc(lenUID * sizeof(int));
						frnd1int = convertToNumber(friend1char);
						p = 0;
						while (!flag6) {
							//remove the friendships whenever they were friends with another UID
							if (checkIfSame(users[p], frnd1int)) {
								i = 0;
								cnt = thisUsersNumberOfFriends[p];
								while (i < cnt) {
									frnd2char = calloc(lenUID, sizeof(char));
									frnd2int = calloc(lenUID, sizeof(int));
									frnd2int = friendships[p][0];
									frnd2char = convertToChar(frnd2int);
									friendships = removeFriendship(friendships, users, thisUsersNumberOfFriends, friend1char, frnd2char, numUsers);
									thisUsersNumberOfFriends = changeNumFriends(users, thisUsersNumberOfFriends, friend1char, frnd2char, numUsers, 0);
									mostFriends = changeMostFriends(users, thisUsersNumberOfFriends, numUsers, mostFriends, 0);
									i++;
								}
								//in the case they were last on the users list, just truncate them off
								if (p == (numUsers - 1)) {
									numUsers--;
									users = realloc(users, sizeof(int) * numUsers);
									friendships = realloc(friendships, sizeof(int**) * numUsers);
									thisUsersNumberOfFriends = realloc(thisUsersNumberOfFriends, sizeof(int) * numUsers);
								}
								//if not, move every UID up a position and every friends list up a position. 
								else {
									for (i = p; i < (numUsers - 1); i++) {
										users[i] = users[i + 1];
										thisUsersNumberOfFriends[i] = thisUsersNumberOfFriends[i + 1];
										if (thisUsersNumberOfFriends[i+1] == 0) {
											friendships[i] = calloc(1, sizeof(int*));
										}
										else{
											friendships[i] = realloc(friendships[i], sizeof(int*) * thisUsersNumberOfFriends[i]);
											for (t = 0; t < thisUsersNumberOfFriends[i]; t++) {
												friendships[i][t] = friendships[i + 1][t];
											}
										}
									}
									//truncate the last UID and friendships list off, which was a duplicate anyway. 
									numUsers--;
									users = realloc(users, sizeof(int) * numUsers);
									friendships = realloc(friendships, sizeof(int**) * numUsers);
									thisUsersNumberOfFriends = realloc(thisUsersNumberOfFriends, sizeof(int) * numUsers);
								}

								flag6 = 1;
								break;
							}
							else {
								p++;
							}
						}
						//print out the database to prove they were removed. 
						printFriendships(friendships, users, thisUsersNumberOfFriends, numUsers, mostFriends);
						printf("user ");
						printUserNum(frnd1int);
						printf(" has been removed.\n\n");
						break;
					//exit the program and sort the database into ascending order, while maintaining friendships.	
					case 0:
						printf("Thank you for using MyTSN!!\n\n\n");
						int** positions;
						positions = malloc(numUsers * sizeof(int*));
						for (i = 0; i < numUsers; i++) {
							positions[i] = malloc(2 * sizeof(int));
						}
						int* unsorted;
						unsorted = malloc(numUsers * sizeof(int));
						unsorted = userIntArray(users, numUsers);
						for (i = 0; i < numUsers; i++) {
							positions[i][0] = unsorted[i];
						}
						int* sorted;
						sorted = malloc(numUsers * sizeof(int));
						sorted = sortArray(unsorted, numUsers);
						for (i = 0; i < numUsers; i++) {
							positions[i][1] = sorted[i];
						}

						int** sortedFriends;
						int* tempUnsorted;
						int* tempSorted;
						int* newNumberOfFriends;
						newNumberOfFriends = malloc(numUsers * sizeof(int));
						sortedFriends = malloc(numUsers * sizeof(int*));

						for (i = 0; i < numUsers; i++) {
							tempUnsorted = calloc(thisUsersNumberOfFriends[i], sizeof(int));
							for (j = 0; j < thisUsersNumberOfFriends[i]; j++) {
								tempUnsorted[j] = intFromPointer(friendships[i][j]);
							}
							tempSorted = calloc(thisUsersNumberOfFriends[i], sizeof(int));
							tempSorted = sortArray(tempUnsorted, thisUsersNumberOfFriends[i]);
							for (j = 0; j < numUsers; j++) {
								if (positions[i][0] == positions[j][1]) {
									sortedFriends[j] = calloc(thisUsersNumberOfFriends[i], sizeof(int));
									sortedFriends[j] = tempSorted;
									newNumberOfFriends[j] = thisUsersNumberOfFriends[i];
								}
							}
						}
						//print the sorted arrays to the output file
						for (i = 0; i < numUsers; i++) {
							fprintf(output_file, "%06d", sorted[i]);
							if (newNumberOfFriends[i] == 0) {
								fprintf(output_file, "%c", '#');
							}
							else {
								fprintf(output_file, "%s", ": ");
								for (j = 0; j < (newNumberOfFriends[i] - 1); j++) {
									fprintf(output_file, "%06d, ", sortedFriends[i][j]);
								}
								fprintf(output_file, "%06d.", sortedFriends[i][j]);
							}
							fprintf(output_file, "%c", '\n');
						}

						flagmain = 1;
						break;
					//default to showing this error message if the user didn't type in 0-6 originally.
					default:
						printf("Invalid choice, must be an integer between 0 and 6. Please try again\n\n\n");
						break;
				}
			}
		}
		//close the files. 
		fclose(input_file);
		fclose(output_file);
		return 0;
	}
