#include "PublicHead.h"

//音符处理函数
string transform2NoteName(int num)
{
    num=transform2OneOct(num);
    switch(num)
    {
        case 0 : return "X";
        case 1 : return "C";
        case 2 : return "C#";
        case 3 : return "D";
        case 4 : return "D#";
        case 5 : return "E";
        case 6 : return "F";
        case 7 : return "F#";
        case 8 : return "G";
        case 9 : return "G#";
        case 10 : return "A";
        case 11 : return "A#";
        case 12 : return "B";
        default : return "err";
    }

}
string transform2Progression(int num)
{
    if(num==0) return "0";
    switch((num-1)%12+1)
    {
        case 1 : return "1";
        case 2 : return "1#";
        case 3 : return "2";
        case 4 : return "2#";
        case 5 : return "3";
        case 6 : return "4";
        case 7 : return "4#";
        case 8 : return "5";
        case 9 : return "5#";
        case 10 : return "6";
        case 11 : return "6#";
        case 12 : return "7";
        default : return "err";
    }
}
int transform2OneOct(int num)
{
    if(num==0) return 0;
    return(num-1)%12+1;
}

void transformMovableDoh2FixedDoh(vector<Phrase> &MovableSentence,
                                  vector<Phrase> &FixedSentence)
{
    FixedSentence=MovableSentence;
    for(size_t i=0;i<FixedSentence.size();i++)
    {
        for(size_t j=0;j<FixedSentence[i].notes.size();j++)
        {
            int n=FixedSentence[i].notes[j].tune;
            FixedSentence[i].notes[j].tune=(n+FixedSentence[i].Phrasetune-1)%36+1;
        }
        FixedSentence[i].Phrasetune=1;
    }
}

void transformMovableDoh2FixedDoh(vector<Phrase> &MovableSentence,vector<int> &MovableRoot,
                                  vector<Phrase> &FixedSentence,vector<int> &FixedRoot)
{
    FixedSentence=MovableSentence;
    FixedRoot.clear();
    FixedRoot.insert(FixedRoot.begin(),MovableRoot.begin(),MovableRoot.end());
    //FixedRoot=MovableRoot;
    for(size_t i=0;i<FixedSentence.size();i++)
    {
        int pt=FixedSentence[i].Phrasetune;
        FixedRoot[i]=(FixedRoot[i]+pt-2)%12+1;
        for(size_t j=0;j<FixedSentence[i].notes.size();j++)
        {
            int n=FixedSentence[i].notes[j].tune;
            if(n>0) FixedSentence[i].notes[j].tune=(n+pt-2)%12+1;
        }
        FixedSentence[i].Phrasetune=1;
    }
}

int getPitchDifference(Note &note1,Note &note2)
{
    return (int)fabs(note1.tune-note2.tune);
}

int getHarmonicLevel(Note &note1,Note &note2)
{
    /*
    开放的协和————纯五度纯八度
    中性————纯四度
    柔和的协和————大小三度，大小六度
    轻度的不协和————大二度小七度
    尖锐的不协和————小二度大七度
    性质游离不稳定————三全音（增四度或减五度）
    */
    int PD=getPitchDifference(note1,note2)%12;
    if(PD==Perfect_Unision)
        return 7;
    else if(PD==Perfect_Fourth||PD==Perfect_Fifth)
        return 6;
    else if(PD==Major_Third||
            PD==Minor_Third)
        return 6;
    else if(PD==Major_Sixth||
            PD==Minor_Sixth)
        return 5;
    else if(PD==Major_Second||PD==Minor_Seventh)
        return 3;
    else if(PD==Minor_Second||PD==Major_Seventh)
        return 2;
    else if(PD==Aug_Fourth_Dim_Fifth)
        return 1;
    else
        return 0;
}
