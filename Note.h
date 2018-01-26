#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED

class Note
{
public:
    int value /*ʱ��1~64,64����һ��ȫ����,1����һ��64������*/;
    int tune  /*����0~36,��λΪ����,��Χ�����˶�,0Ϊ��ֹ��*/;
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
