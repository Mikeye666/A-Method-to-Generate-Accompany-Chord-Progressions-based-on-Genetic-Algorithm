#ifndef PUBLICHEAD_H_INCLUDED
#define PUBLICHEAD_H_INCLUDED

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<map>
#include<cmath>
#include<ctime>
#include"Note.h"
#include"Phrase.h"
#include"ScoreRecord.h"


#define PI 3.14159
#define ThreshCordination 20

/*
#define C1   1
#define C#1  2
#define D1   3
#define D#1  4
#define E1   5
#define F1  6
#define F#1  7
#define G1   8
#define G#1  9
#define A1   10
#define A#1  11
#define B1   12

#define C2   13
#define C#2  14
#define D2   15
#define D#2  16
#define E2   17
#define F2   18
#define F#2  19
#define G2   20
#define G#2  21
#define A2   22
#define A#2  23
#define B2   24

#define C3   25
#define C#3  26
#define D3   27
#define D#3  28
#define E3   29
#define F3   30
#define F#3  31
#define G3   32
#define G#3  33
#define A3   34
#define A#3  35
#define B3   36
*/

//音程定义
#define Perfect_Unision 0
#define Minor_Second 1
#define Major_Second 2
#define Minor_Third 3
#define Major_Third 4
#define Perfect_Fourth 5
#define Aug_Fourth_Dim_Fifth 6
#define Perfect_Fifth  7
#define Minor_Sixth 8
#define Major_Sixth 9
#define Minor_Seventh 10
#define Major_Seventh 11
#define Perfect_Octave 12

#define MinFractualValue 64
#define GroupSize 100
#define GenerationNumBon 1e3
#define MutateRate  0.05
#define HarmonicRate 0.80

#define NoteNumInScale 7

using namespace std;

void initializ();
void PrintRoot(vector<int> &Root);
void inputSentence(vector<Phrase> &Sentence);
void GetRoot(vector<Phrase> &sentence,vector<int> &root);
void ChordsAnalize(vector<Phrase> &sentence,vector<map<int,int> > &NoteMapInPhrase);
void PrintNoteMapInPhrase(vector<map<int,int> > &NoteMapInPhrase,vector<int> &Root);
void PrintNoteMap(map<int,int> &NoteMap,int Root);
void GenerateChordProgress(vector<Phrase> &sentence,vector<map<int,int> > &NoteMapInPhrase,vector<int> PTunes,vector<Phrase> &chords);
void GenerateChord(Phrase &Melody,map<int,int> &NoteMap,int PTune,Phrase &Chord);
int getPitchDifference(Note &note1,Note &note2);
int random(int lower_bound,int uper_bound);
string transform2NoteName(int num);
string transform2Progression(int num);
int transform2OneOct(int num);
void transformMovableDoh2FixedDoh(vector<Phrase> &MovableSentence,vector<Phrase> &FixedSentence);
void transformMovableDoh2FixedDoh(vector<Phrase> &MovableSentence,vector<int> &MovableRoot,
                                  vector<Phrase> &FixedSentence,vector<int> &FixedRoot);
int getHarmonicLevel(Note &note1,Note &note2);


int GetChordScore(Phrase &Chord,map<int,int> &NoteMap);
void ChordGroup_Sort(Phrase ChordGroup[],ScoreRecord ScoreBoard[]);
void ChordGroup_Breed(Phrase ChordGroup[]);
void ChordGroup_Breed(Phrase ChordGroup[],ScoreRecord ScoreBoard[]);
bool isChordAllTheSame(Phrase &Chord);

void getPTunes(vector<Phrase> &sentence,vector<int> &PTunes);
bool isNoteInScale(int CurrentScaleNotes[NoteNumInScale],Note n);
void ChordMaintaining(Phrase &Chord);
void ChordMutate(Phrase &Chord);


#endif // PUBLICHEAD_H_INCLUDED
