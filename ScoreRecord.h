#ifndef SCORERECORD_H
#define SCORERECORD_H


class ScoreRecord
{
    public:
        ScoreRecord(unsigned int ID=0,int score=0) {this->ID=ID;this->score=score;}
        ScoreRecord(const ScoreRecord& other) {ID=other.ID;score=other.score;}
        void operator=(ScoreRecord other) {ID=other.ID;score=other.score;}
        bool operator<(ScoreRecord other) {return score<other.score;}
        unsigned int ID;
        int score;
};

#endif // SCORERECORD_H
