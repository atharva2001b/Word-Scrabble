// Project1.cpp : 
// Your names
//


#include <iostream>
#include <vector>
#include "Project1.h"
using namespace std;


//locations : all the location where the word was found in letters
//letter	: matrix of char [size][size], where you look for the word
//size		: the size of the matrix: size X size
//word		: the word you are searching for
//
//the word can be either horizontally or vertically
//
// Location.score: each word you find in letters, can have a different score.
//                 each letter will have a score, that you sum to calculate the 
//                 score of the word you found in letters
//                 the score is based on 100%. 
//                 Each letter of word has a maximum score of 100 / word.length
//                 If the letter has the same case (uppercase, lowercase), the letter
//                 has 100 / word.length. If the case is not the case, it has (100 / word.length) / 2 for score.
//				   If the word you are searching for is 4 letters, each
//				   letter you match will be 25%. If a letter match, but not its case, it is 12.5%.
//
// If you find a word, its score > 50% to be added locations.
/*
	Grading       : 
	                10 unit tests x 7 pts each           = 70
					4 additional unit tests x 5 pts each = 20 -- must check additional cases
					program structure                    = 10
					total                                = 100
	Your grade will be calculated on the last test your program manage to successfully execute, based on the 
	order in Project1Test.
	
	Program that do not compile will receive a grade of 0.

	Submission    : one submission per team
*/

int findMatchHorizontal(vector<Location*>* locations, char* letters, int size, string word) {
	int score = 0;                   // total score to output
	int count1 = 0;                  // to keep the count of all relevant letter instances 
	int countCase = 0;               // to keep the count of same letters with matching cases
	int countNoCase = 0;             // to keep the count of same letters with different cases 
	int count2 = 0;                  // used as index of the locations vector
	int finalScore = 0;              // used to assign specific score as per word in Location object

	for (int i = 0; i < size; i++) {                                // iterate over rows
		for (int j = 0; j < size - word.length() + 1; j++) {        // iterate over columns
			for (int indx = 0; indx < word.length(); indx++) {      // iterate over letters of word

				if (word[indx] == *(letters + i * size + indx + j)) {      // check if the letters match
					count1++;                                              // if match increment count
					countCase++;                                           // increment same case counter
				}
				else {
					if ((toupper(word[indx]) == *(letters + i * size + j + indx)) ||
						(tolower(word[indx]) == *(letters + i * size + j + indx))) {      //if cases dont match but letters match
						count1++;                                         // increment count
						countNoCase++;                                    // increment nocase count
					}

				}

			}
			  
			if (count1 == word.length()) {                          // check if the complete word is found
				locations->push_back(new Location);                 // add Location object to the vector
				(*locations)[count2]->ptr = letters + i * size + j; // assign the pointer in the relevant Location object
				(*locations)[count2]->horizontal = true;            // done horizontal scan 
				finalScore = countCase * 100 / word.length() + countNoCase * 50 / word.length(); //calculate the score
				score += finalScore;                                //update total score
				(*locations)[count2]->score = finalScore;           // assign indivitual score to the object
				count2++;                                           // point to next element in the vector
			}
			count1 = 0;                    // word is added to the vector so reset letter count
			countNoCase = 0;               // and remaining relevant counters.                        
			countCase = 0;                 // 

		}
	}
	return score;
}

int findMatchVertical(vector<Location*>* locations, char* letters, int size, string word) {
	int score = 0;                         //  |   
	int count1 = 0;                        //  | 
	int countCase = 0;                     //  |-- same as was for horizontal
	int countNoCase = 0;                   //  |
	int count2 = 0;                        //  |
	int finalScore = 0;                    //  |

	
	for (int i = 0; i < size; i++) {                             // iterate over columns
		for (int j = 0; j < size - word.length() + 1; j++) {     // iterate over rows

			for (int indx = 0; indx < word.length(); indx++) {   // iterate over word

				if (word[indx] == *(letters + i + indx * size + j * size)) {  // check if letters match
					count1++;                                    // increment the counter
					countCase++;                                 // increment the same case counter
				}
				else {
					if ((toupper(word[indx]) == *(letters + i  + j * size + indx * size)) ||
						(tolower(word[indx]) == *(letters + i  + j * size + indx * size))) {  // check for matching letters but with different case
						
						count1++;                                // increment the counter
						countNoCase++;                           // increment no case counter
					}

				}

			}

			


			if (count1 == word.length()) {                          // check if the exact word is present
				 
				locations->push_back(new Location);                 // add Location object to the vector
				(*locations)[count2]->ptr = letters + i + j * size; // add the pointer to the location of the word found
				(*locations)[count2]->horizontal = false;           // scanning vertically :)
				finalScore = countCase * 100 / word.length() + countNoCase * 50 / word.length(); // calculate word score
				score += finalScore;                                // update total score
				(*locations)[count2]->score = finalScore;           // add the invidual score to the Location object
				
				count2++;                                           // point to next vector element
			}
			count1 = 0;                //   |
			countNoCase = 0;           //   |-- reset relevant counters 
			countCase = 0;             //   |

		}
	}

	return score;
}

int findMatch(vector<Location *>  * locations, char *letters, int size, string word) {

	int score = findMatchHorizontal(locations, letters, size, word);        // scan horizontally 
	score += findMatchVertical(locations, letters, size, word);             // scan vertically

	return score;
}
