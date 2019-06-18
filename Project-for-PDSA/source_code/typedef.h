#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <map> 
#include <queue>
#include <stack>
#include <ctime>
#define Train_Num 4000     //���������� 
#define divided 10          //��divided������ 
#define label_max_num 10   //��ǩ��� 
#define word_max_num 200   //������� 
#define letter_num 26      //��ĸ���� 
#define result_labelnum 3  //�����ǩ��Ŀ 
using namespace std;
class Word {               //������ 
	private:
		string word;                                          //���� 
		short times[Train_Num + 1];                           //�����в��������зֱ���ֶ��ٴ� 
		int show, sum;                                        //���иõ��ʵľ������͵��ʳ��ֵ��ܴ��� 
		void Calculate_show();                                //���㺬�иõ��ʵľ����� 
	public:
		Word(ifstream &fin);                                                               //�ӵ��ʱ�����Ĺ��캮�� 
		Word(string word_);                                                                //��ѵ��������ȡ�Ĺ��캯��                                                                       //���� 
		void Export_Word(ofstream &fout);                                                  //�������ȫ����Ϣ                                                                         //��� 
		bool operator==(const Word &w) const;                                              //������� 
		bool operator<(const Word &w) const;                                               //����С�� 
		int Get_sum() const;                                                               //��ȡ�����ܴ��� 
		string Get_word() const;                                                           //��ȡ���� 
	friend class Sample;
	friend class Database;
};
class Sample {             //����� 
	private:
		string sentence;                                                    //���� 
		string *word, *label;                                               //���ʺͱ�ǩ 
		int id, wordnum, labelnum;                                          //���ӱ�š�������������ǩ���� 
	public:
		Sample();                                                           //���캯�� 
		~Sample();                                                          //�������� 
		void Input_Sample(ifstream &fin);                                   //���봦�����ѵ������ 
		void Import_Sample(ifstream &fin, int n);                           //����ѵ������
		void Export_Sample(ofstream &fout);                                 //����������ѵ������ 
		void mystrlwr(string &str);                                         //string����дתΪСд 
		void Set_word();                                                    //��ȡ���� 
		void Clear_tail();                                                  //���β��"#$#"��֮������ 
		void Clear_head();                                                  //���ͷ��"#$#"��֮ǰ���ݣ�
		void Set_label();                                                   //��ȡѵ�����ݱ�ǩ 
		int Get_Label_Count();												//���ر�ǩ������
		string* Get_Label_Array();											//���ش洢��ǩλ�õ�����
		void Push(vector<Word> *All_words);                                 //ͳ��ȫ������ 
		void Deal_with_Sample(vector<Word> *All_words);                     //����ѵ�������ܺ��� 
		void Deal_with_Test(string current, int n);                         //������������ܺ���
		void Output_Result(ofstream &fout);                                 //���������ܺ��� 
	friend class Database;
};
class Database {           //����
	private:
		int Count_num;                                                     //��� 
		Sample *sample;                                                    //�� 
		Sample current;                                                    //��ǰ�������� 
		vector<Word> All_words[letter_num];                                //���ʱ�������ĸ��Ͱ��������� 
		vector<Word> Vocabulary;                                           //�ܵ��ʱ����㰴��Ƶ���� 
		map <string, vector<double> > Map;								   //���ڴ洢��ǩ��Ӧ���������� 
		priority_queue<pair<double, string> > Q;                           // ���ȶ���Q���ڴ洢�뵱ǰ�������������н���С��ǰ������ǩ��
		                                                      //ÿ��pairԪ�ص�first�Ǽнǵ�����ֵ����������ֵ���ģ���second�Ǳ�ǩ����
	public:
		Database();                                                        //���캯�� 
		~Database();                                                       //�������� 
		void Import_Database(ifstream &fin);                               //���뵥�ʱ������ 
		int Find_Word_Index(const string&);                                //�ҵ���֪���ʵ��±�
		void Import_Samples(ifstream &fin);                                //����ѵ������ 
		void Export_Samples(ofstream &fout);                               //������� 
		void Deal_with_Samples();                                          //����ѵ������ 
		void Export_Words(ofstream &fout);                                 //������ʱ� 
		void Calc_Label_Feature();										   //�����ǩ��������
		void Extract_Labels(string current_, ofstream &fout);              //����������� 
};
