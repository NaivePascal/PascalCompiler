#ifndef __TARGETCODE_H__
#define __TARGETCODE_H__
#include "Midcode.h"
#include <iostream>
#include <string>

enum Space {
	BYTE,//char
	SDWORD,//int
	REAL4,//float
	DWORD//unsigned int
};
struct Sentence {
	vector<string> words;

	Sentence(string word1, string word2) {
		words.push_back(word1);
		words.push_back(word2);
	}

	Sentence(string word1, string word2, string word3) {
		words.push_back(word1);
		words.push_back(word2);
		words.push_back(word3);
	}

	Sentence(string word1, string word2, string word3, string word4) {
		words.push_back(word1);
		words.push_back(word2);
		words.push_back(word3);
		words.push_back(word4);
	}

	friend ostream &operator<<(ostream &out, const Sentence & sentence) {
		bool first = true;
		for (string word : sentence.words) {
			if (!first)
				out << " ";
			first = false;
			out << word;
		}
		return out;
	}
};

struct Section {
	vector<Sentence> sentences;

	void append(const Sentence &sentence) {
		sentences.push_back(sentence);
	}

	void append(string word1, string word2) {
		sentences.push_back(Sentence(word1, word2));
	}

	void append(string word1, string word2, string word3) {
		sentences.push_back(Sentence(word1, word2, word3));
	}

	friend ostream &operator<<(ostream &out, const Section& section) {
		for (Sentence sentence : section.sentences) {
			out << sentence << endl;
		}
		return out;
	}
};

void GenTargetCode(const vector<midcode>&);
void declare(string name, nodeType *node);

void printTargetCode(ostream &os);

#endif // __TARGETCODE_H__
