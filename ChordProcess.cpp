#include "PublicHead.h"

int BreedNum[GroupSize]={0};
int CurrentScaleNotes[NoteNumInScale]={0};
int p=4;

//和弦处理函数
void GetRoot(vector<Phrase> &sentence,vector<int> &root)
{
    for(size_t i=0;i<sentence.size();i++)
    {
        size_t j;
        int maxvalue=0;
        for(j=0;j<sentence[i].size();j++)
        {
            int Currentvalue=sentence[i].notes[j].value;
            if(Currentvalue>maxvalue&&sentence[i].notes[j].tune!=0)
                maxvalue=Currentvalue;
        }
        for(j=0;j<sentence[i].notes.size()&&sentence[i].notes[j].value!=maxvalue;j++);
        if(j<sentence[i].notes.size())
            root.push_back(transform2OneOct(sentence[i].notes[j].tune));
        else
            root.push_back(0);
    }
}
void ChordsAnalize(vector<Phrase> &sentence,vector<map<int,int> > &NoteMapInPhrase)
{
    for(size_t i=0;i<sentence.size();i++)
    {
        sentence[i].GenerateNoteMap();
        NoteMapInPhrase.push_back(sentence[i].GetNoteMap());
    }
}
void GenerateChordProgress(vector<Phrase> &sentence,vector<map<int,int> > &NoteMapInPhrase,vector<int> PTunes,vector<Phrase> &chords)
{
    for(int i=0;i<GroupSize/2;i++)
    {
        BreedNum[i]=round(PI*cos(i*PI/GroupSize));
    }
    for(size_t i=0;i<sentence.size();i++)
    {
        Phrase PTemp(sentence[i].Groove1,sentence[i].Groove2,sentence[i].Phrasetune);
        chords.push_back(PTemp);
        GenerateChord(sentence[i],NoteMapInPhrase[i],PTunes[i],chords[i]);
    }
}
void GenerateChord(Phrase &Melody,map<int,int> &NoteMap,int PTune,Phrase &Chord)
{
    int G1=Melody.Groove1,
        G2=Melody.Groove2,
        PT=Melody.Phrasetune;
    Phrase ChordGroup[GroupSize]={Phrase(G1,G2,PT)};
    ScoreRecord ScoreBoard[GroupSize];
    int NoteNum[GroupSize]={0};

    //群体初始化
    for(int i=0;i<GroupSize;i++)
    {
        //NoteNum[i]=random(2,4);
        NoteNum[i]=4;
    }
    for(int i=0;i<GroupSize;i++)
    {
        ChordGroup[i].Groove1=G1;
        ChordGroup[i].Groove2=G2;
        ChordGroup[i].Phrasetune=PT;
        do
        {
            ChordGroup[i].notes.clear();
            for(int j=0;j<NoteNum[i];j++)
            {
                ChordGroup[i].AddNote(random(13,24),16);
            }
        }while(isChordAllTheSame(ChordGroup[i]));
    }

    CurrentScaleNotes[0]=transform2OneOct(PTune);
    for(size_t i=1;i<NoteNumInScale;i++)
    {
        if(i!=3)CurrentScaleNotes[i]=transform2OneOct(CurrentScaleNotes[i-1]+2);
        else CurrentScaleNotes[i]=transform2OneOct(CurrentScaleNotes[i-1]+1);
    }

    //开始进化
    //主循环
    Phrase TheBestChord;
    TheBestChord=ChordGroup[0];

    int Thresh=0;
    for(map<int,int>::iterator itr=NoteMap.begin();itr!=NoteMap.end();itr++)
    {
        Thresh+=8*itr->second;
    }
    Thresh*=HarmonicRate;

    for(int Generation=0,k=0;Generation<GenerationNumBon&&GetChordScore(TheBestChord,NoteMap)<Thresh-k;Generation++)
    {
        if(Generation%500==0)
        {
            cout<<"Generation "<<Generation<<" : score : ";
            cout<<GetChordScore(TheBestChord,NoteMap)<<endl;
            TheBestChord.output();
            k+=3;
        }


        //群体算分
        for(int i=0;i<GroupSize;i++)
        {
            ScoreBoard[i].ID=i;
            ScoreBoard[i].score=GetChordScore(ChordGroup[i],NoteMap);
        }
        //群体排序
        ChordGroup_Sort(ChordGroup,ScoreBoard);
        TheBestChord=ChordGroup[0];
        //群体交叉
        ChordGroup_Breed(ChordGroup,ScoreBoard);
    }
    //TheBestChord.output();
    Chord=TheBestChord;
}

int GetChordScore(Phrase &Chord,map<int,int> &NoteMap)
{
    int ans=0;
    size_t size=Chord.size();


    /*
    ChordMaintaining(Chord);
    */

    for(size_t i=0;i<size;i++)
    {
        for(map<int,int>::iterator itr=NoteMap.begin();itr!=NoteMap.end();itr++)
        {
            int Tune=itr->first;
            int bonus=itr->second;
            Note NTemp(Tune);
            int score=getHarmonicLevel(Chord.notes[i],NTemp);
            if(!isNoteInScale(CurrentScaleNotes,Chord.notes[i]))
                score/=1.5;
            ans+=bonus*score;
        }
    }
    return (int)round(ans/size);
}

void ChordGroup_Breed(Phrase ChordGroup[])
{
    vector<Phrase> VCG(ChordGroup,ChordGroup+GroupSize);

    for(int i=0,j=0;i<GroupSize/2&&j<GroupSize;i++)
    {
        for(int k=1;k<=BreedNum[i];k++)
        {
            ChordGroup[j++]=VCG[i]*VCG[GroupSize/2-i-k];
            //和弦变异
            int isMutate=random(0,1000);
            if(isMutate<1000*MutateRate)
            {
                //cout<<isMutate<<endl;
                ChordMutate(ChordGroup[j]);
            }
        }
    }
}

void ChordGroup_Breed(Phrase ChordGroup[],ScoreRecord ScoreBoard[])
{
    vector<Phrase> VCG(ChordGroup,ChordGroup+GroupSize);

    int ScoreSum=0;
    for(int i=0;i<GroupSize;i++)
    {
        ScoreSum+=ScoreBoard[i].score;
    }

    for(int i=0;i<GroupSize/2;i++)
    {
        int r=random(0,ScoreSum);
        int m=0;
        for(size_t j=0;j<GroupSize;j++)
        {
            m+=ScoreBoard[j].score;
            if(m>=r)
            {
                VCG[i]=ChordGroup[j];
                break;
            }
        }
    }

    for(int i=0,j=0;i<GroupSize/2&&j<GroupSize;i++)
    {
        for(int k=1;k<=BreedNum[i];k++)
        {
            ChordGroup[j++]=VCG[i]*VCG[GroupSize/2-i-k];
            //和弦变异
            int isMutate=random(0,1000);
            if(isMutate<1000*MutateRate)
            {
                //cout<<isMutate<<endl;
                ChordMutate(ChordGroup[j]);
            }
        }
    }
}

bool isChordAllTheSame(Phrase &Chord)
{
    bool ALL_THE_SAME=true;
    for(size_t i=0;i<Chord.size();i++)
    {
        if(Chord.notes[0]!=Chord.notes[i])
        {
            ALL_THE_SAME=false;
            break;
        }
    }
    return ALL_THE_SAME;
}

void ChordMaintaining(Phrase &Chord)
{
    /*
    for(size_t i=0;i<Chord.size();i++)
    {
        string s=transform2NoteName(Chord.notes[i].tune);
        if(s=="X"||s=="err")
        {
            Chord.notes[i].tune=random(13,24);
            Chord.notes[i].value=16;
        }
    }
    */
    /*
    while(isChordAllTheSame(Chord))
    {
        for(size_t j=0;j<Chord.size();j++)
        {
            Chord.notes[j].tune=random(13,24);
        }
    }
    */
}

void getPTunes(vector<Phrase> &sentence,vector<int> &PTunes)
{
    PTunes.clear();
    for(size_t i=0;i<sentence.size();i++)
    {
        PTunes.push_back(sentence[i].Phrasetune);
    }
}

bool isNoteInScale(int CurrentScaleNotes[NoteNumInScale],Note n)
{
    int JudgingTune=transform2OneOct(n.tune);
    for(int i=0;i<NoteNumInScale;i++)
    {
        if(JudgingTune==CurrentScaleNotes[i])
            return true;
    }
    return false;
}

void ChordMutate(Phrase &Chord)
{
    size_t i=random(0,Chord.size()-1);

    for(size_t j=0;j<Chord.size();j++)
    {
        if(i==j) Chord.notes[j].tune=random(13,24);
    }
}
