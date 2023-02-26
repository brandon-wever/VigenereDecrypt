// Author: Brandon Wever
// Purpose: To create a program that decrypts a vigenere cipher
// Date: 2/15/22

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

const char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

int findKeyLength(string ctext, int shiftItter) {
	int clength = ctext.length();
	int numSimilarities = 0;

	for (int i = 0; i < clength; i++) {
		if ((i + shiftItter) >= clength)
			break;
		if (ctext[i] == ctext[i + shiftItter])
			numSimilarities++;
	}

	return numSimilarities;
}

void freqAnalysis(string ctext, int cLength, int predictedKeyLen, int positionNum) {
	int chars[26];
	int numItters = 0;
	for (int p = 0; p < 26; p++)
		chars[p] = 0;

	for (int i = positionNum; i < cLength; i += 5) {
		for (int j = 0; j < 26; j++) {
			if (ctext[i] == alphabet[j]) {
				chars[j] += 1;
			}
		}
		numItters++;
	}//increase each for loop iteration 5 times in order to do frequency analysis

	//print results
	cout << "Frequency Analysis for position " << positionNum << endl;
	for (int k = 0; k < 26; k++) {
		double frequency = (double)chars[k] / numItters;
		cout << alphabet[k] << ": " << chars[k] << "/" << numItters << " = " << frequency << endl;
	}
}

string decryptCipher(string ctext, char predictKey, int position, int predictedKeyLen) {
	//loop through key to get values
	int keyVal = 0;
	for (int i = 0; i < 26; i++) {
		if (predictKey == alphabet[i]) {
			keyVal = i;
			break;
		}
	}

	for (int j = position; j < ctext.length(); j+= predictedKeyLen) {
		for (int k = 0; k < 26; k++) {
			if (ctext[j] == alphabet[k]) {
				int shiftVal = 0;
				shiftVal = (((k - keyVal) % 26) + 26) % 26; //shift letter value
				ctext[j] = alphabet[shiftVal];
				break;
			}
		}
	}

	return ctext;
}	

int main() {
	string text;
	ifstream MyReadFile("vig.txt");
	while (getline(MyReadFile, text)) {
		//cout << text << endl; //ensure ciphertext read in correctly
	}
	MyReadFile.close();

	
	int sims;
	for (int i = 1; i < text.length(); i++) {
		sims = findKeyLength(text, i);
		cout << "Shift "<< i << ": " << sims << endl;
	} //find amount of similarities in shifted ciphertext to get key length


	int predictedKeyLen;
	cout << "What is the predicted key length? : ";
	cin >> predictedKeyLen;
	cout << endl;

	int cTextLen = text.length();
	for(int posNum = 0; posNum < predictedKeyLen; posNum++)
		freqAnalysis(text, cTextLen, predictedKeyLen, posNum);


	string predictedKey;
	cout << endl << "What is the predicted key based on the frequency analysis?: ";
	cin >> predictedKey;
	cout << endl;

	//decypher text in positional increments, then print
	//NOTE: In this problem, predicted key length is 5, code would have to be modified if it was different than 5
	string pos1decypher = decryptCipher(text, predictedKey[0], 0, predictedKeyLen);
	string pos2decypher = decryptCipher(pos1decypher, predictedKey[1], 1, predictedKeyLen);
	string pos3decypher = decryptCipher(pos2decypher, predictedKey[2], 2, predictedKeyLen);
	string pos4decypher = decryptCipher(pos3decypher, predictedKey[3], 3, predictedKeyLen);
	string pos5decypher = decryptCipher(pos4decypher, predictedKey[4], 4, predictedKeyLen);
	cout << pos5decypher << endl;
	
	return 0;
}