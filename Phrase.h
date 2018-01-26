#ifndef PHRASE_H_INCLUDED
#define PHRASE_H_INCLUDED

#include "PublicHead.h"

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;
int transform2OneOct(int num);
string transform2NoteName(int num);
int random(int lower_bound,int uper_bound);


class Phrase
{
public:
    vector<Note> notes;
    int Groove1,Groove2;
    int Phrasetune;
    map<int,int> NoteMap;
    Phrase(int groove1=4,int groove2=4,int phrasetune=1)
    {
        Groove1=groove1;
        Groove2=groove2;
        Phrasetune=phrasetune;
    }
    Phrase(const Phrase &other)
    {
        Groove1=other.Groove1;
        Groove2=other.Groove2;
        Phrasetune=other.Phrasetune;
        NoteMap=other.NoteMap;
        notes.clear();
        notes.insert(notes.begin(),other.notes.begin(),other.notes.end());
    }
    void operator=(const Phrase &P)
    {
        Groove1=P.Groove1;
        Groove2=P.Groove2;
        Phrasetune=P.Phrasetune;
        NoteMap=P.NoteMap;
        notes.clear();
        notes.insert(notes.begin(),P.notes.begin(),P.notes.end());
        //notes=P.notes;
    }
    Phrase operator*(Phrase &other)
    {
        Phrase PTemp;
        size_t bon=size()<other.size()? size():other.size();
        int DERIVE_FROM_OTHER=random(0,1);

        if(DERIVE_FROM_OTHER)
        {
            PTemp.AddNote(other.notes[0].tune,16);
            for(size_t i=1;i<bon;i++)
            {
                PTemp.AddNote(notes[i].tune,16);
            }
        }
        else
        {
            PTemp.AddNote(notes[0].tune,16);
            for(size_t i=1;i<bon;i++)
            {
                PTemp.AddNote(other.notes[i].tune,16);
            }
        }
        return PTemp;
    }
    size_t size()
    {
        return notes.size();
    }
    int isComplete()
    {
        int sum=0;
        for(size_t i=0;i<notes.size();i++)
            sum+=notes[i].value;
        int goal=64*Groove1/Groove2;
        return sum-goal;
    }
    void AddNote(int tune=0,int value=16)
    {
        Note note(tune,value);
        notes.push_back(note);
    }
    void output()
    {
        cout<<"|  ";
        for(size_t i=0;i<notes.size();i++)
        {
            printf("%-4s",transform2NoteName(notes[i].tune).data());
        }
        cout<<"|"<<endl;
    }
    void GenerateNoteMap()
    {
        for(size_t i=0;i<notes.size();i++)
        {
            int index=transform2OneOct(notes[i].tune);
            if(index==0) continue;
            NoteMap[index]+=notes[i].value;
        }
    }
    map<int,int> GetNoteMap()
    {
        return NoteMap;
    }
};

#endif // PHRASE_H_INCLUDED
