#include "typedef.h"
/*class Word {               //������ 
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
};*/
void Word::Calculate_show() {                                                            //���㺬�иõ��ʵľ����� 
	for (int i = 1 ; i <= Train_Num ; i ++)
		if (times[i]) show ++;
}
Word::Word(ifstream &fin) {                                                              //�ӵ��ʱ�����Ĺ��캮�� 
	fin >> word >> show >> sum;
	memset(times, 0, sizeof(times)); 
	int t;
	for (int i = 0 ; i < show ; i ++) {
		fin >> t;
		fin >> times[t];
	}
	return;
}
Word::Word(string word_):word(word_) {                                                   //��ѵ��������ȡ�Ĺ��캯�� 
	memset(times, 0, sizeof(times));
	show = sum = 0;
	return;
}                                                                                        //���� 
void Word::Export_Word(ofstream &fout) {                                                 //�������ȫ����Ϣ 
	Calculate_show();
	fout << word << " " << show << " " << sum;
	for (int i = 1 ; i <= Train_Num ; i ++)
		if (times[i])
			fout << " " << i << " " << times[i];
	fout << endl;
	return;
}                                                                                        //��� 
bool Word::operator==(const Word &w) const {return word == w.word;}                      //������� 
bool Word::operator<(const Word &w) const {return word < w.word;}                        //����С�� 
int Word::Get_sum() const {return sum;}                                                  //��ȡ�����ܴ��� 
string Word::Get_word() const {return word;}   
