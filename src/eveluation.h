#ifndef EVELUATION_H
#define EVELUATION_H
#include "define.h"
#define BASEVALUE_WOLF 0
#define BASEVALUE_SHEEP 100
#define FLEXIBILITY_WOLF 20
#define FLEXIBILITY_SHEEP 0
#include <cstring>

class CEveluation
{
public:
    CEveluation();
    virtual ~CEveluation();
    int wolfscore;
    int sheepscore;

    virtual int Eveluate(byte position[gridNum][gridNum],bool iswolf);
protected:

   //�о���ָ��λ����ص�����
   int GetRelatePiece(byte position[gridNum][gridNum],int i,int j);
   //�ж�λ��from�������ܷ��ߵ�λ��to
   bool CanTouch(byte position[gridNum][gridNum],QPoint start,QPoint end);
   //��һ��λ�ü������λ�ö���
   void AddPoint(int x,int y);
   int m_BaseValue[3];//������ӻ�����ֵ
   int m_FlexValue[3];//�����������Է���������
   short m_AttackPos[gridNum][gridNum];//�������λ�ñ���в����Ϣ
   byte m_FlexibilityPos[gridNum][gridNum];//�������λ����������Է���
   int m_chessValue[gridNum][gridNum];//���ÿһ�����ӵ��ܼ�ֵ
   int nPosCount;//��¼һ�������λ�õ�����
   QPoint RelatePos[20];//��¼һ���������λ�õ�����



};

#endif // EVELUATION_H
