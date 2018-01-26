#include "PublicHead.h"

int main()
{
    vector<Phrase> Sentence,FixedSentence;
    vector<Phrase> Chords;
    vector<int> Root,FixedRoot;
    vector<map<int,int> > NoteMapInPhrase;
    vector<int> PTunes;

    initializ();

    inputSentence(Sentence);
    GetRoot(Sentence,Root); //获得根音模进
    PrintRoot(Root);        //显示根音模进

    transformMovableDoh2FixedDoh(Sentence,Root,FixedSentence,FixedRoot);

    getPTunes(Sentence,PTunes);

    ChordsAnalize(FixedSentence,NoteMapInPhrase);
    PrintNoteMapInPhrase(NoteMapInPhrase,FixedRoot);

    GenerateChordProgress(FixedSentence,NoteMapInPhrase,PTunes,Chords);

    for(size_t i=0;i<Chords.size();i++)
    {
        cout<<"---------- Chord"<<i+1<<" ----------"<<endl;
        cout<<"|  "<<transform2NoteName(FixedRoot[i])<<"  |";
        Chords[i].output();
    }
    return 0;
}
