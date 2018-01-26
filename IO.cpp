#include "PublicHead.h"

//I/O函数
void inputSentence(vector<Phrase> &Sentence)
{
    size_t n;
    cout<<"Please input the number of Phrase in ONE Sentence:";
    cin>>n;
    for(size_t i=0;i<n;i++)
    {
        cout<<"Phrase"<<i+1<<":"<<endl;

        int groove1,groove2,Ptune;
        cout<<"Please input the groove(groove1/groove2):"<<endl;
        cout<<"Groove1:";
        cin>>groove1;
        cout<<"Groove2:";
        cin>>groove2;
        cout<<"Please input the tune of Phrase"<<i+1<<":";
        cin>>Ptune;
        Phrase PTemp(groove1,groove2,Ptune);
        Sentence.push_back(PTemp);

        int tune=0,value=0,j=1;
        cout<<"Please input the notes:"<<endl;
        do
        {
            cout<<"note"<<j++<<":"&&
            cin>>tune>>value;
            if(tune>=0-1&&value>=0) Sentence[i].AddNote(tune,value);
        }while(Sentence[i].isComplete()<0&&tune!=-1&&value!=-1);
    }
}
void PrintRoot(vector<int> &Root)
{
    cout<<"Root Progression:";
    for(size_t i=0;i<Root.size();i++)
    {
        if(i>0) cout<<"->";
        cout<<transform2Progression(Root[i]);
    }
    cout<<endl;
}
void PrintNoteMapInPhrase(vector<map<int,int> > &NoteMapInPhrase,vector<int> &Root)
{
    cout<<"NoteMapInPhrase:\n";
    for(size_t i=0;i<NoteMapInPhrase.size();i++)
    {
        cout<<"---------- Phrase "<<i+1<<" ----------\n";
        PrintNoteMap(NoteMapInPhrase[i],Root[i]);
    }
}
void PrintNoteMap(map<int,int> &NoteMap,int Root)
{
    printf("%-15s%-10s\n","Note","Bouns");
    for(map<int,int>::iterator i=NoteMap.begin();i!=NoteMap.end();i++)
    {
        int NoteNum=i->first;
        string note=transform2NoteName(NoteNum);
        if(NoteNum==Root)
            note+="(Root)";
        printf("%-15s%-10d\n",note.data(),i->second);
    }
}

