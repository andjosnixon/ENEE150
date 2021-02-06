	/* Project 1: Evaluation of Sorting Algorithms
	
	Andrew Nixon
	March 2, 2020
	
	ENEE150
	
	Project description: 
	--------------------
	Implement three sorting functions: insertion sort, merge sort and quicksort and compare their efficiency. 
	The inpur of the program will be a file that contains multiple lists of unsorted numbers. The program should sort these numbers with each respective sorting algorithm and output these sorted numbers to an output file as well as information about the performance of the algorithm. Performance is measured by: average number of comparisons and average times that the numbers need to be copied. 
	
	Program Requirements:
	---------------------
	should run with the command line arguments: 
	a.out inputNumbers.txt k outputFile.txt
		a.out: executable
		
		inputNumbers.txt: input file
			25 lines of 25 integers seperated by one whitespace
			numbers may be positive, zero, or negative, and may be duplicates
		k: integer that represents the sorting algorithm to be used
			1: bubblesort 
				must copy and paste from the projects directory
			2: insertion sort
			3: merge sort
			4-6: quicksort
				4: last array element is pivot value
				5: first array element is pivot value
				6: use random array element as pivot value
			if not 1-6, print an error message and exit. 
		outputFile.txt: output filename. 
			first 25 lines are the sorted 25 lines from the input file, all seperated by a whitespace, except the last number which ends with a newline
			second part will report average number of comparisons and average number of data copies
			output file will be compared with the expected output using the diff command
			format of the output file is very important. 
		
	argv[] position in command line:
	|   0  |   	 	1        |      2     |       3        |
	  a.out		input_file	    	k		  output_file
		
	*/
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	
	#define maxLength 100
	#define numsPerArray 25
	
	float num_copies = 0;
	float num_comparisons = 0;

	//--------------program declarations------------------------//
		void bubble_sort(int a[]); 
		void insertion_sort(int a[]);
		void merge(int a[], int s, int m, int t);
		void merge_sort(int a[], int s, int t);
		void quick_sort(int a[], int s, int t, int quick_choice);
		void swap(int a[], int s, int t);
		int partition_last(int a[], int s, int t);
		int partition_first(int a[], int s, int t);
		int partition_rand(int a[], int s, int t);
	//----------------------------------------------------------//
	
	//definition of functions
	
	
	//given script. 
	void bubble_sort(int a[]){
		int i, j, tmp;
		for(i=0;i<25;i++){
			for(j=24;j>=i+1;j--){
				//iterate for following if statement
				num_comparisons++;
				if(a[j] < a[j-1]){
					tmp = a[j];
					a[j]=a[j-1];
					a[j-1]=tmp;
					//iterate three times for the rearrangement
					num_copies += 3;
				}
			}
		}
	}

	void insertion_sort(int a[]){
		int i, j, key; 
		for(i=1; i<numsPerArray; i++){
			//iterate for the following key statement
			num_copies++;
			//designating key has to happen no matter what, and this is important because 
			//it will be used in repositioning key to a[j+1] if a swap needs to be made. 
			key = a[i];
			//this positions j into the right place
			j = i - 1; 
			
			//an initial comparison is made no matter what. at the start of each loop, 
			//j will always be greater than 0, so therefore key will always be compared.
			num_comparisons++;		
			//here the main action of insertion_sort happens. 
			while(j>=0 && key < a[j]){
				//now do a comparison and copy for every time the while loop runs. 
				num_comparisons++;
				num_copies++;
				a[j+1] = a[j];
				j--;
			}
			if(j<0){
				//in the case that the a new number has been placed at the beginning of the 
				//array and the while loop has run out, then decrease the number of comparisons
				//by 1 because there was a double comparison when it first enters the while loop.
				num_comparisons--;
			}
			//only set a[j+1] to key if j is not directly behind i, which is the case where no 
			//swap would have happened in the first place. 
			if(j+1 != i){
				num_copies++;
				a[j+1] = key;
			}			
		}
	}
	
	void merge(int a[], int s, int m, int t){
		// s: leftmost start point 
		// m: "middle" or (s+t)/2 
		// t: rightmost end point
		int n1 = m-s+1; 
		int n2 = t-m;
		
		int L[n1], R[n2], i, j, k;
		for(i=0; i<n1; i++){
			//each time the for loop movies is a copy
			num_copies++;
			L[i] = a[s+i];
		}
		for(j=0; j<n2; j++){
			//also a copy every time the for loop moves
			num_copies++;
			R[j] = a[m+1+j];
		}
		k=s; 
		i=0;
		j=0; 
		
		while(i<n1 && j<n2){
			//comparing array elements is a comparison
			num_comparisons++;
			if(L[i] <= R[j]){
				//if it's true, do a copy
				num_copies++;
				a[k] = L[i];
				i++;
			}
			else{
				//if it's not true, also do a copy
				num_copies++;
				a[k] = R[j];
				j++;
			}
			k++;
		}
		while(i<n1){
			//if that's true, then iterate the copy
			num_copies++;
			a[k] = L[i];
			i++;
			k++;
		}
		while(j<n2){
			//also here is a copy
			num_copies++;
			a[k] = R[j];
			j++;
			k++;
		}
	}
	
	void merge_sort(int a[], int s, int t){
		//no copies or comparisons here. 
		int mid;
		if(s<t){
			mid = (s+t)/2;
			merge_sort(a, s, mid);
			merge_sort(a, mid+1, t);
			merge(a, s, mid, t);
		}
	}
	
	void swap(int a[], int s, int t){
		int temp;
		//similar to bubble sort, iterate copies three times
		temp = a[s];
		a[s] = a[t];
		a[t] = temp;
		num_copies+=3;
	}
	
	int partition_last(int a[], int s, int t){
		int j; 
		//must iterate copies here because need to set the last array element to pivot
		num_copies++;
		int x = a[t];
		int i = s-1;
		for(j=s; j<=t-1; j++){
		//a comparison is done every time the for loops runs no matter what
			num_comparisons++;
			if(a[j] < x){
		//if a smaller value is found, then move i
				i++;
				if(i!=j){
		//there is often a case where i was directly behind j, and after it iterates, it will be 
		//at the same position as j. if i==j, then a[i]==a[j], and there's no need to swap. but because
		//counters are being compared, dont increase the comparison counter.
					swap(a, i, j);
				}
			}
		}
		//at the end after the array is organized properly, the last thing to do is put the pivot
		//in the position it needs to be in. but this should only be done if a[i+1] and a[t] are not the
		//same number. this increases comparisons by 1 but saves 3 copies for a swap, so it's worth it. 
		num_comparisons++;
		if(a[i+1]!= a[t]){
			swap(a, i+1, t);
		}
		return i+1;
	}
	
	int partition_first(int a[], int s, int t){
		//this function is similar to partition_last
		int j, x = a[s];
		num_copies++;
		//and iterate copies
		int i = s+1;
		for(j=s+1; j<t+1; j++){
			//a comparison is made no matter what.
			num_comparisons++;
			if(a[j] <= x){
				//when a smaller value is found in the for loop, and 
				//i and j are not on the same position, then swap. 
				//however, if they are on the same spot, then no need to swap. 
				swap(a, i, j);
				i++;
			}
		}
		//at the end, swap the values again, only if the values are not already the same. 
		//this will use a comparison to save 3 copies. 
		//num_comparisons++;
		//if(a[s] != a[i-1]){
			swap(a, s, i-1);
		//}
		return i-1;
	}
	
	int partition_rand(int a[], int s, int t){
		//this function's purpose is to move a random pivot value to the end, and then call 
		//partition_last on it. 
		int k;
		//use a random pivot value with srand().
		srand(time(NULL));
		int i, j;
		int random = s + rand()%(t-s+1);
		swap(a, random, t);
		return partition_last(a, s, t);
	}
		
	void quick_sort(int a[], int s, int t, int quick_choice){
		int m, i;
		//this function is where quicksort is mainly called. I added a fourth parameter 
		//which represents whatever value of k was chosen in the command line. 
		//this value will go unchanged throughout the program. 
		//no comparisons or copies are needed here in the body of this program. 
		if(s<t){
			switch(quick_choice){
				//calling the last partition function
				case (4):
					m = partition_last(a, s, t);
					quick_sort(a, s, m-1, quick_choice);
					quick_sort(a, m+1, t, quick_choice);
					break;
				//calling the first partition function
				case (5):
					m = partition_first(a, s, t);
					quick_sort(a, s, m-1, quick_choice);
					quick_sort(a, m+1, t, quick_choice);
					break;
				//calling the random partition function
				default:
					m = partition_rand(a, s, t);
					quick_sort(a, s, m-1, quick_choice);
					quick_sort(a, s, m-1, quick_choice);
					quick_sort(a, m+1, t, quick_choice);
				break;
			}
		}
	}
	
	int main(int argc, char *argv[]){
		
		//initialize the array to be 0.
		int input_array[numsPerArray][numsPerArray] = {0};
		int i, j;
		
		//check to see if the correct number of arguments were provided. 
		if(argc != 4){ 
			printf("Incorrect number of arguments provided.\n");
			printf("Usage: a.out, input file, k, outputFile\n");
			exit(0);
		}
		
		FILE *input_file;
			input_file = fopen(argv[1], "r");
		
		int input_selection = atoi(argv[2]);
		
		//safety check for k
		
		if(input_selection < 0 || input_selection > 6){
			printf("Invalid choice for K\n");
			exit(0);
		}
		
		FILE *output_file; 
			output_file = fopen(argv[3], "w");
			
		//safety check for the input file	
		if(input_file == NULL){
			printf("%s could not be opened properly.\n", argv[1]); 
			exit(0);
		}
			
		//safety check for the output file	
		if(output_file == NULL){
			printf("%s could not be opened properly.\n", argv[3]); 
			exit(0);
		}
		
		//collect numbers before the file runs out
		while(!feof(input_file)){	
			for(j = 0; j<25; j++){
				//every time a number is stored, that is a new copy.
				num_copies++;
				fscanf(input_file, "%d ", &input_array[i][j]);
			}
			i++;
		}
	
		//all the switch statements based on input selection
		//and when the array elements are written to the output file. 
		switch(input_selection){
			case 1: 
				for(i=0; i<numsPerArray; i++){
					bubble_sort(input_array[i]);
					for(j=0;j<numsPerArray;j++){
						fprintf(output_file, "%d", input_array[i][j]);
						if(j==24){
							//they're all the same, but they should match the output exactly.
							fprintf(output_file, "\n");
						}
						else{
							fprintf(output_file, " ");
						}
					}
				}
				break;
			case 2:
				for(i=0; i<numsPerArray; i++){
					insertion_sort(input_array[i]);
					for(j=0;j<numsPerArray;j++){
						fprintf(output_file, "%d", input_array[i][j]);
						if(j==24){
							fprintf(output_file, "\n");
						}
						else{
							fprintf(output_file, " ");
						}
					}

				}
				break;
 			case 3: 
				for(i=0; i<numsPerArray; i++){
					merge_sort(input_array[i], 0, 24);
					for(j=0;j<numsPerArray;j++){
						fprintf(output_file, "%d", input_array[i][j]);
						if(j==24){
							fprintf(output_file, "\n");
						}
						else{
							fprintf(output_file, " ");
						}
					}
				}
				break;
			case 4:
				for(i=0; i<numsPerArray; i++){
					quick_sort(input_array[i], 0, 24, 4);
					for(j=0;j<numsPerArray;j++){
						fprintf(output_file, "%d", input_array[i][j]);
						if(j==24){
							fprintf(output_file, "\n");
						}
						else{
							fprintf(output_file, " ");
						}
					}
				}
				break;
			case 5: 
				for(i=0; i<numsPerArray; i++){
					quick_sort(input_array[i], 0, 24, 5);
					for(j=0;j<numsPerArray;j++){
						fprintf(output_file, "%d", input_array[i][j]);
						if(j==24){
							fprintf(output_file, "\n");
						}
						else{
							fprintf(output_file, " ");
						}
					}
				}
				break;
			default:
				for(i=0; i<numsPerArray; i++){
					quick_sort(input_array[i], 0, 24, 6);
					for(j=0;j<numsPerArray;j++){
						fprintf(output_file, "%d", input_array[i][j]);
						if(j==24){
							fprintf(output_file, "\n");
						}
						else{
							fprintf(output_file, " ");
						}
					}
				}
				break;
		}
		
		//calculate the number of comparisons and copies
		float average_comparisons = num_comparisons / 25;
		float average_copies = num_copies / 25;
	
		//print them to the output file. 
		fprintf(output_file, "The average number of comparisons is %.2f.\n", average_comparisons);
		fprintf(output_file, "The average number of copies is %.2f.\n", average_copies);
		
		//as always, close the input files at the very end. 
		fclose(input_file);
		fclose(output_file);
		
		return 0;
		
	}
