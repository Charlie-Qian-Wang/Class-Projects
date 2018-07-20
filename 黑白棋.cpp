#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <limits> 
using namespace std;
void xuanze();
void chushi();
void qipan(bool);
void youxi();
int mychess, v, m; 
int white = 0, black = 0, blank = 0;
bool xin;
int a[10][10] = {0};
int c[10][10] = {0,0,0,0,0,0,0,0,0,0,
                 0,10,1,9,5,5,9,1,10,0,
				 0,1,1,3,7,7,3,1,1,0,
				 0,9,3,8,4,4,8,3,9,0,
				 0,5,7,4,0,0,4,7,5,0,
				 0,5,7,4,0,0,4,7,5,0,
				 0,9,3,8,4,4,8,3,9,0,
				 0,1,1,3,7,7,3,1,1,0,
				 0,10,1,9,5,5,9,1,10,0,
				 0,0,0,0,0,0,0,0,0,0};
struct dian
{
	int xx;
	int yy;
	int zz;
	int num;
	int score;
};
dian fenzhi[64];
dian t = {0,0,0,0,0}, temp;
bool f1(int h, int x, int y)
{
	int p = 1;
	for (p = 1;;p++)
		if (x - p == 0)
		    return false;
		else
		   if (a[x - p][y] == h)
		       break;
	if (p == 1)
	    return false;
	else
	    for (int i = 1;i < p;i++)
	        if (a[x - i][y] != -h)
	            return false;
	return true;
}
bool f2(int h, int x, int y)
{
	int p = 1;
	for (p = 1;;p++)
		if (x + p == 9)
		    return false;
		else
		   if (a[x + p][y] == h)
		       break;
	if (p == 1)
	    return false;
	else
	    for (int i = 1;i < p;i++)
	        if (a[x + i][y] != -h)
	            return false;
	return true;
}
bool f3(int h, int x, int y)
{
	int p = 1;
	for (p = 1;;p++)
		if (y - p == 0)
		    return false;
		else
		   if (a[x][y - p] == h)
		       break;
	if (p == 1)
	    return false;
	else
	    for (int i = 1;i < p;i++)
	        if (a[x][y - i] != -h)
	            return false;
	return true;
}
bool f4(int h, int x, int y)
{
	int p = 1;
	for (p = 1;;p++)
		if (y + p == 9)
		    return false;
		else
		   if (a[x][y + p] == h)
		       break;
	if (p == 1)
	    return false;
	else
	    for (int i = 1;i < p;i++)
	        if (a[x][y + i] != -h)
	            return false;
	return true;
}
bool f5(int h, int x, int y)
{
	int p = 1;
	for (p = 1;;p++)
		if (x - p == 0||y - p == 0)
		    return false;
		else
		   if (a[x - p][y - p] == h)
		       break;
	if (p == 1)
	    return false;
	else
	    for (int i = 1;i < p;i++)
	        if (a[x - i][y - i] != -h)
	            return false;
	return true;
}
bool f6(int h, int x, int y)
{
	int p = 1;
	for (p = 1;;p++)
		if (x + p == 9||y - p ==0)
		    return false;
		else
		   if (a[x + p][y - p] == h)
		       break;
	if (p == 1)
	    return false;
	else
	    for (int i = 1;i < p;i++)
	        if (a[x + i][y - i] != -h)
	            return false;
	return true;
}
bool f7(int h, int x, int y)
{
	int p = 1;
	for (p = 1;;p++)
		if (x + p == 9||y + p == 9)
		    return false;
		else
		   if (a[x + p][y + p] == h)
		       break;
	if (p == 1)
	    return false;
	else
	    for (int i = 1;i < p;i++)
	        if (a[x + i][y + i] != -h)
	            return false;
	return true;
}
bool f8(int h, int x, int y)
{
	int p = 1;
	for (p = 1;;p++)
		if (x - p == 0||y + p == 9)
		    return false;
		else
		   if (a[x - p][y + p] == h)
		       break;
	if (p == 1)
	    return false;
	else
	    for (int i = 1;i < p;i++)
	        if (a[x - i][y + i] != -h)
	            return false;
	return true;
}
bool check(int h, int x, int y)
{
	if (a[x][y])
	    return false;
	else
        return f1(h,x,y)+f2(h,x,y)+f3(h,x,y)+f4(h,x,y)+f5(h,x,y)+f6(h,x,y)+f7(h,x,y)+f8(h,x,y);
}
void dafen()
{
	for (int j = 0;j < m;j++)
	{
		int s = 0;
		if (f1(-mychess, fenzhi[j].xx, fenzhi[j].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[j].xx - p][fenzhi[j].yy] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            s++;
	    }
	    if (f2(-mychess, fenzhi[j].xx, fenzhi[j].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[j].xx + p][fenzhi[j].yy] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            s++;
	    }
	    if (f3(-mychess, fenzhi[j].xx, fenzhi[j].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[j].xx][fenzhi[j].yy - p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            s++;
        }
	    if (f4(-mychess, fenzhi[j].xx, fenzhi[j].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[j].xx][fenzhi[j].yy + p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            s++;
	    }
	    if (f5(-mychess, fenzhi[j].xx, fenzhi[j].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[j].xx - p][fenzhi[j].yy - p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            s++;
	    }
	    if (f6(-mychess, fenzhi[j].xx, fenzhi[j].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[j].xx + p][fenzhi[j].yy - p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            s++;
	    }
	    if (f7(-mychess, fenzhi[j].xx, fenzhi[j].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[j].xx + p][fenzhi[j].yy + p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            s++;
	    }
	    if (f8(-mychess, fenzhi[j].xx, fenzhi[j].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[j].xx - p][fenzhi[j].yy + p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	        	s++;
	    }
	    fenzhi[j].num = s;
	    fenzhi[j].score = fenzhi[j].zz * fenzhi[j].num;
	}
	return;
}
void paixu()
{
	for (int i = 0;i < m;i++)
	    for (int j = i + 1;j < m;j++)
	        if (fenzhi[i].score < fenzhi[j].score)
	        {
	        	temp = fenzhi[i];
	        	fenzhi[i] = fenzhi[j];
	        	fenzhi[j] = temp;
			}
			for (int i = 0;i < m;i++)
		cout <<fenzhi[i].score<<endl;
	return;
}
bool allcheck(int h)
{
	if (h == mychess)
	{
	    for (int i = 1;i < 9;i++)
	        for (int j = 1;j < 9;j++)
	        {
			    if (check(h, i, j))
	                return true;
	        }
	    return false;
	}
	else
	{
	    for (int i = 0;i < 64;i++)
	        fenzhi[i] = t;
	    m = 0;
        for (int i = 1;i < 9;i++)
	        for (int j = 1;j < 9;j++)
	        {
				if (check(h, i, j))
				{
					fenzhi[m].xx = i;
					fenzhi[m].yy = j;
					fenzhi[m].zz = c[i][j];
					m++;
				}
			}
		return m;
    }
}
void yourturn()
{
	if (allcheck(-mychess))
	{
		dafen();
		paixu();
		a[fenzhi[0].xx][fenzhi[0].yy] = -mychess;
		if (f1(-mychess, fenzhi[0].xx, fenzhi[0].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[0].xx - p][fenzhi[0].yy] == -mychess)
		            break;
			for (int i = 1;i < p;i++)
	            a[fenzhi[0].xx - i][fenzhi[0].yy] = -mychess;
	    }
		if (f2(-mychess, fenzhi[0].xx, fenzhi[0].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[0].xx + p][fenzhi[0].yy] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[fenzhi[0].xx + i][fenzhi[0].yy] = -mychess;   
	    }
	    if (f3(-mychess, fenzhi[0].xx, fenzhi[0].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[0].xx][fenzhi[0].yy - p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[fenzhi[0].xx][fenzhi[0].yy - i] = -mychess;
	    }
	    if (f4(-mychess, fenzhi[0].xx, fenzhi[0].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[0].xx][fenzhi[0].yy + p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[fenzhi[0].xx][fenzhi[0].yy + i] = -mychess;
	    }
	    if (f5(-mychess, fenzhi[0].xx, fenzhi[0].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[0].xx - p][fenzhi[0].yy - p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[fenzhi[0].xx - i][fenzhi[0].yy - i] = -mychess;
	    }
	    if (f6(-mychess, fenzhi[0].xx, fenzhi[0].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[0].xx + p][fenzhi[0].yy - p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[fenzhi[0].xx + i][fenzhi[0].yy - i] = -mychess;
	    }
	    if (f7(-mychess, fenzhi[0].xx, fenzhi[0].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[0].xx + p][fenzhi[0].yy + p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[fenzhi[0].xx + i][fenzhi[0].yy + i] = -mychess;
	    }
	    if (f8(-mychess, fenzhi[0].xx, fenzhi[0].yy))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[fenzhi[0].xx - p][fenzhi[0].yy + p] == -mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[fenzhi[0].xx - i][fenzhi[0].yy + i] = -mychess;
	    }
	}
	else
    {
    	cout << v << "�Ż�������·���ߣ����������" << endl;
		Sleep(500);
	}
}
bool myturn(int x, int y)
{
	if (check(mychess, x, y))
	{
		a[x][y] = mychess;
		if (f1(mychess, x, y))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[x - p][y] == mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[x - i][y] = mychess;
	    }
	    if (f2(mychess, x, y))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[x + p][y] == mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[x + i][y] = mychess;
	    }
	    if (f3(mychess, x, y))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[x][y - p] == mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[x][y - i] = mychess;
	    }
	    if (f4(mychess, x, y))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[x][y + p] == mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[x][y + i] = mychess;
	    }
	    if (f5(mychess, x, y))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[x - p][y - p] == mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[x - i][y - i] = mychess;
	    }
	    if (f6(mychess, x, y))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[x + p][y - p] == mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[x + i][y - i] = mychess;
	    }
	    if (f7(mychess, x, y))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[x + p][y + p] == mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[x + i][y + i] = mychess;
	    }
	    if (f8(mychess, x, y))
		{
			int p = 1;
	        for (p = 1;;p++)
	            if (a[x - p][y + p] == mychess)
		            break;
	        for (int i = 1;i < p;i++)
	            a[x - i][y + i] = mychess;
	    }
		return true;
	}
	else
	{
	    cout << "���������Ӳ��ܳԵ��κζԷ��ӣ���������������" << endl; 
	    return false;
	}
}
void cundang()
{
	char name[40];
	cout << "��������ϣ���浵���ļ���" << endl <<"�粻��������Զ�����" << endl
	     << "�����س����򷵻���Ϸ" << endl ;
    int g = 0;
    do
    {
    	cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		cin.getline(name, sizeof(name));
    	if (name[0] == '\0')
    	{
    		qipan(true);
			youxi();
    		g = 1;
		}
		else
		{
			g = 1;
			ofstream fout(name);
			if (!fout)
			{
				cout << "�浵ʧ�ܣ�" << endl;
				cout << "�������������·���Ƿ���ȷ" << endl;
				cout << "������ѡ����ļ��Ƿ����������������" << endl;
				cout << "���ڼ��������Ի򰴻س���������Ϸ" << endl; 
				g = 0;
				continue; 
			}
	        fout << v << "  " << mychess << "  ";
	        fout << black << "  " << white << "  " << blank << endl;
	        for (int i = 0;i < 10;i++)
	            for (int j = 0;j < 10;j++)
		            fout << a[i][j] << endl;
			fout.close();
		}
	}
	while (g == 0);	
}
void tishi()
{
	cout << "�Ƿ񱣴浱ǰ��֣�" << endl << endl;
	cout << "����Ҫ����  ������1" << endl;
	cout << "�粻�豣��  ������0" << endl << endl;
	char o;
	int g = 0;
	do
	{
		cin >> o;
		switch (o)
		{
			case '0':xuanze();g = 1;return;break;
			case '1':cundang();g = 1;return;break;
			default:
				{
					cout << endl;
		            cout << "����Ĳ���0��1�е�һ��" << endl;
		            cout << "����������" << endl << endl; 	
				}
		};
	}
	while (g == 0);
}
void tuichu()
{
	cout << "��ȷ��Ҫ�˳���" << endl;
	cout << "ȷ���˳� ������1" << endl;
	cout << "������Ϸ ������0" << endl << endl;
	char o;
	int g = 0;
	do
	{
		cin >> o;
		switch (o)
		{
			case '0':qipan(true);youxi();g = 1;return;break;
			case '1':tishi();g = 1;return;break;
			default:
				{
					cout << endl;
		            cout << "����Ĳ���0��1�е�һ��" << endl;
		            cout << "����������" << endl << endl; 	
				}
		};
	}
	while (g == 0);
 } 
void youxi()
{
	if (mychess == -1&&xin)
	{
	    Sleep(500);
		yourturn();
	    qipan(true);
	}
	xin = false;
	while (blank&&(allcheck(mychess)||allcheck(-mychess)))
	{
		char p, q;
		int x, y;
		int g = 0;
		do
		{
		    bool l = allcheck(mychess);
			if (l)
		    {
			    cin >> p;
			    switch (p)
		        {
			        case '0':cundang();g = 1;return;break;
			        case '9':tuichu();g = 1;return;break;
			        case '1':
			        case '2':
			        case '3':
			        case '4':
			        case '5':
			        case '6':
			        case '7':
			        case '8':cin >> q;
			                 g = 1;
				             switch (q)
				             {
				                 case '1':
				         	     case '2':
				         	     case '3':
				         	     case '4':
				         	     case '5':
				         	     case '6':
				         	     case '7':
				         	     case '8':x = p - '0';
				         	              y = q - '0';
									      g = myturn(x, y);
									      if (g == 1)
									      {
									 	      qipan(true);
									 	      Sleep(1000);
									 	      yourturn();
									 	      qipan(true);
									      }
										  break;
				         	     default:
				         		      {
				         			   cout << endl; 
						               cout << "������Ĳ�����ȷ������" << endl;
						               cout << "����������" << endl; 
						               g = 0; 
								       }
						     };break;
				    default:
					    {
						    cout << endl; 
					    	cout << "������Ĳ���0��9����ȷ������" << endl;
						    cout << "����������" << endl; 
				        }
		        };
		    }
		    else
		    {
		    	cout << "����·���ߣ�" << v << "�Ż����˽���������" <<endl; 
				Sleep(1000);
				yourturn();
		    	qipan(true);
		    	g = 1;
			}
		}
		while (g == 0);
	};
}
void qizi(int b)
{
	if (b == 1)
	    cout << "��";
	if (b == -1)
	    cout << "��";
    if (b == 0)
	    cout << "  ";
	return;
}
void qipan(bool k) 
{
    system("cls");
	white = 0;
	black = 0;
	blank = 0;
	for (int i = 1;i < 9;i++)
	    for (int j = 1;j < 9;j++)
	    {
	    	if (a[i][j] == -1) white++;
	    	if (a[i][j] == 1) black++;
	    	if (a[i][j] == 0) blank++;
		}
    cout << "    1   2   3   4   5   6   7   8    " << endl;
	cout << "  �����ש��ש��ש��ש��ש��ש��ש���" << endl;
	for (int i = 1;i < 8;i++)
	{
	    cout << i << " ��";
		qizi(a[i][1]);
		cout << "��";
		qizi(a[i][2]);
		cout << "��";
		qizi(a[i][3]);
		cout << "��";
		qizi(a[i][4]);
		cout << "��";
		qizi(a[i][5]);
		cout << "��";
		qizi(a[i][6]);
		cout << "��";
		qizi(a[i][7]);
		cout << "��";
		qizi(a[i][8]);
		cout << "��" << endl;										
        cout << "  �ǩ��贈�贈�贈�贈�贈�贈�贈��" << endl;
    }
	cout << "8 ��";
	qizi(a[8][1]);
	cout << "��";
	qizi(a[8][2]);
	cout << "��";
	qizi(a[8][3]);
	cout << "��";
	qizi(a[8][4]);
	cout << "��";
	qizi(a[8][5]);
	cout << "��";
	qizi(a[8][6]);
	cout << "��";
	qizi(a[8][7]);
	cout << "��";
	qizi(a[8][8]);
	cout << "��" << endl;	 
    cout << "  �����ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ���" << endl;	
	if (blank == 0||(!allcheck(mychess)&&!allcheck(-mychess)))
	{
		if (black == white)
		    cout << "������ƽ�֣�����" << black << "ö������" << white << "ö" << endl << endl;
		else
		{
		    if (black > white&&mychess == 1)
			    cout << "���ֺڷ����㣩ʤ��" << "����" << black << "ö������" << white << "ö" <<endl << endl;
			if (black > white&&mychess == -1)
			    cout << "���ֺڷ���" << v <<"�Ż����ˣ�ʤ��" << "����" << black << "ö������" << white << "ö" <<endl << endl;
		    if (black < white&&mychess == -1)
			    cout << "���ְ׷����㣩ʤ��" << "����" << black << "ö������" << white << "ö" <<endl << endl;
			if (black < white&&mychess == 1)
			    cout << "���ְ׷���" << v <<"�Ż����ˣ�ʤ��" << "����" << black << "ö������" << white << "ö" <<endl << endl;
		}
	    cout << "����һ��    ������1" << endl << endl;
	    cout << "�������˵�  ������2" << endl << endl;  
	    int g = 0;
	    do
	    {
		    char o;
		    cin >> o;
		    switch (o)
		    {
		    	case '1':chushi();g = 1;return;break;
		    	case '2':xuanze();g = 1;return;break;
			    default:
			    	{
		    	        cout << endl;
			            cout << "����Ĳ���1��2�е�һ��" << endl;
			            cout << "����������" << endl << endl; 	
			    	}
	    	};
    	}
    	while (g == 0);
	}
	else
	{
		cout << "        ���ӡ� " << black << "  ���ӡ� " << white << endl << endl;
		cout << "��������ϣ�����ӵ�λ�� ���������ڵ����е��������� �����롰3  5��" << endl; 
		cout << "��Ҫ�浵       ������0" << endl << "��Ҫ�������˵� ������9" << endl << endl; 
		if (k)
		    return;
		else
		    youxi();
    }
}
void chushi()
{
	system("cls");
	cout << "��ѡ����ϣ��ִ����(���壩���Ǻ��֣����壩" << endl << endl;
	cout << "ѡ������ ������1" << endl << endl;
	cout << "ѡ����� ������2" << endl << endl;
	cout << "�������˵� ������3" << endl << endl; 
	mychess = 0;
	xin = true;
	int g = 0;
	do
	{
	    char o;
	    cin >> o;
	    switch (o)
	    {
		    case '1':mychess = 1;g = 1;break;
		    case '2':mychess = -1;g = 1;break;
		    case '3':xuanze();return;break;
		    default:
			{
			    cout << endl;
			    cout << "����Ĳ���1��2��3�е�һ��" << endl;
			    cout << "����������" << endl << endl; 	
			}
		};
	}
	while (g == 0);
	for (int i = 0;i < 10;i++)
	    for (int j = 0;j < 10;j++)
	        a[i][j] = 0;
	a[4][4] = -1;
	a[4][5] = 1;
	a[5][4] = 1;
	a[5][5] = -1;
	qipan(!xin);
}
void duqu()
{
	system("cls");
	xin = false;
	char name[50];
	cout << "��������ϣ����ȡ���ļ�����" << endl 
	     << "�����س����򷵻����˵�" <<endl;
	int g = 0;     
	do
	{
    	cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		cin.getline(name,sizeof(name));
	    if (name[0] == '\0')
	    {
	        xuanze();
	        g = 1;
	    }
	    else
	    {
		    g = 1;
	        ifstream fin(name);
	        if (!fin)
	        {
		        cout << "�浵��ʧ�ܣ�" << endl;
		        cout << "��������������ļ�����·���Ƿ���ڲ���ȷ" << endl << name << endl ;
		        cout << "������ļ��Ƿ����������������" << endl;
		        cout << "���ڼ��������Ի򰴻س��������˵�" << endl << endl;
		        g = 0;
				continue; 
	        }
	        fin >> v >> mychess;
	        fin >> black >> white >> blank;
	        for (int i = 0;i < 10;i++)
	            for (int j = 0;j < 10;j++)
		            fin >> a[i][j];
		    fin.close();
	        qipan(false);
	    }
	}
	while (g == 0);
}
void guize()
{
    system("cls");
	cout << "����һ���ĺڰ�����Ϸ" << endl << endl; 
	cout << "��Ϸ�����̹���8��8�У���64��" << endl << endl;
	cout << "����ʱ�����������4�����÷źڰ������4ö����" << endl << endl;	
	cout << "����˫���������ӣ�ֻҪ���Ӻ���������һö������������һ�����Ϻ�ֱб�߽Կɼ��ŶԷ�����" << endl << endl; 
	cout << "���ܽ��Է�����Щ����ת��Ϊ��������" << endl << endl;
	cout << "�������һλ�����Ӷ����ܼ�ס���ֵ���һ������" << endl << endl;
	cout << "��Ҫ�ö������ӣ���˫���Բ���������Ϸ�ͽ���" << endl << endl;
	cout << "�Ӷ��һ��ʤ" << endl << endl;
	cout << "�õģ������Ѿ������Ϸ�����ˣ�����������������ĸ����" << endl << endl;
	char o;
	cin >> o; 
	xuanze();
}
void xuanze()
{
	system("cls");
	cout << "������Ӧ��ţ�������Ϸ����" << endl << endl;
	cout << "��ʼ����Ϸ" << "   " << "������1" << endl << endl;
	cout << "��ȡ�浵" << "     " << "������2" << endl << endl;
	cout << "�˽���Ϸ����" << " " << "������3"  << endl << endl;
	cout << "�˳���Ϸ" << "     " << "������4" << endl << endl;
	char o;
	int g = 0;
	do
	{
    cin >> o;
	switch (o)
	{
		case '1':chushi(); g = 1; break;
		case '2':duqu(); g = 1; break;
		case '3':guize(); g = 1; break;
		case '4':return;
		default:
		{
		    cout << endl;
			cout << "����Ĳ���1��2��3��4�е�һ��" << endl;
			cout << "����������" << endl << endl; 
		}
	 } ;
    }
	 while (g == 0);
}
int main()
{
	cout << "��ӭ��������ڰ��� " << endl << endl;
	srand(time(0));
	v = rand();
	cout << "������" << v << "�Ż�������������" << endl << endl;
	cout << "������Ӧ��ţ�������Ϸ����" << endl << endl;
	cout << "��ʼ����Ϸ" << "   " << "������1" << endl << endl;
	cout << "��ȡ�浵" << "     " << "������2" << endl << endl;
	cout << "�˽���Ϸ����" << " " << "������3"  << endl << endl;
	cout << "�˳���Ϸ" << "     " << "������4" << endl << endl;
	char o;
	int g = 0;
	do
	{
        cin >> o;
	    switch (o)
	    {
	    	case '1':chushi(); g = 1; break;
	    	case '2':duqu(); g = 1; break;
	    	case '3':guize(); g = 1; break;
	    	case '4':return 0;
	    	default:
	    	{
	    	    cout << endl;
	    		cout << "����Ĳ���1��2��3��4�е�һ��" << endl;
	    		cout << "����������" << endl << endl; 
	    	}
    	};
    }
	while (g == 0);
	return 0;
 } 
