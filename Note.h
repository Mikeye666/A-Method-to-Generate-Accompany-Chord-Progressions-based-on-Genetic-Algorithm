#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED

class Note
{
public:
    int value /*时长1~64,64代表一个全音符,1代表一个64分音符*/;
    int tune  /*音高0~36,单位为半音,范围三个八度,0为休止符*/;
    Note(int t=0,int v=16)
    {
        SetNote(t,v);
    }
    void SetNote(int t=0,int v=16)
    {
        value=v;
        tune=t;
    }
    bool operator<(Note n)
    {
        return tune<n.tune;
    }
    bool operator==(Note n)
    {
        return tune==n.tune;
    }
    bool operator!=(Note n)
    {
        return tune!=n.tune;
    }
};

#endif // NOTE_H_INCLUDED
