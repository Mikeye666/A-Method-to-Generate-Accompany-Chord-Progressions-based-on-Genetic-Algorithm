#include "PublicHead.h"

//数值方法函数

int random(int lower_bound,int uper_bound)
{
    if(uper_bound>lower_bound)
        return lower_bound+rand()%(uper_bound-lower_bound+1);
    else
        return 0;
}

void ChordGroup_Sort(Phrase ChordGroup[],ScoreRecord ScoreBoard[])
{
     vector<ScoreRecord> VSB(ScoreBoard,ScoreBoard+GroupSize);
     vector<Phrase> VCG(ChordGroup,ChordGroup+GroupSize);
     make_heap(VSB.begin(),VSB.end());
     sort_heap(VSB.begin(),VSB.end());
     /*
     for(size_t i=0;i<GroupSize;i++)
        cout<<VSB[i].score<<endl;
    */
     for(int i=0;i<GroupSize;i++)
     {
         VCG[i]=ChordGroup[VSB[GroupSize-i-1].ID];
         ScoreBoard[i]=VSB[GroupSize-i-1];
     }
     for(int i=0;i<GroupSize;i++)
     {
         ChordGroup[i]=VCG[i];
     }
}
