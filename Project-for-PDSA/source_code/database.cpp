#include "typedef.h"
/*class Database {           //����
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
};*/
Database::Database() {sample = NULL;Count_num = 1;}                          //���캯�� 
Database::~Database() {if (sample) delete [] sample;}                        //�������� 
void Database::Import_Database(ifstream &fin) {                              //���뵥�ʱ������ 
	sample = new Sample[Train_Num];
	fin.open("sentence list.data");
	for (int i = 0 ; i < Train_Num ; i ++) {
		sample[i].Input_Sample(fin);
	}
	fin.close();
	fin.open("word list.data");
	for (int i = 0 ; i < letter_num ; i ++) {
		int t;
		fin >> t;
		for (int j = 0 ; j < t ; j ++)
			Vocabulary.push_back(Word(fin));
	}
	fin.close();
	return;
}
void Database::Import_Samples(ifstream &fin) {                               //����ѵ������ 
	sample = new Sample[Train_Num / divided];
	for (int i = 0 ; i < Train_Num / divided ; i ++)
		sample[i].Import_Sample(fin, Count_num ++);
	return;
}
void Database::Export_Samples(ofstream &fout) {                              //������� 
	for (int i = 0 ; i < Train_Num / divided ; i ++)
		sample[i].Export_Sample(fout);
	delete [] sample;
	sample = NULL;
	return;
}
void Database::Deal_with_Samples() {                                         //����ѵ������ 
	for (int i = 0 ; i < Train_Num / divided ; i ++)
		sample[i].Deal_with_Sample(All_words);
	return;
}
void Database::Export_Words(ofstream &fout) {                                //������ʱ� 
	for (int i = 0 ; i < letter_num ; i ++) {
		sort(All_words[i].begin(), All_words[i].end());
		fout << All_words[i].size() << endl;
		for (vector<Word>::iterator p = All_words[i].begin() ; p < All_words[i].end() ; p ++)
			p->Export_Word(fout); 
	}
	return;
}
double Module(const vector<double>& V) 
// ���������ģ��
{
	size_t sz = V.size();
	double Sum = 0;
	for (int i = 0; i < sz; i++)
		Sum += V[i] * V[i];
	return sqrt(Sum);
}
double CosAngle(const vector<double>& V1, const vector<double>& V2)
// ��������ļн� 
{
	size_t sz = V1.size();
	double Sum = 0;
	for (int i = 0; i < sz; i++)
		Sum += V1[i] * V2[i];
	return Sum;
}
int Database::Find_Word_Index(const string& w)
// ���ö��ַ��ҵ���֪���ʵ��±�
{
	int l = 0, r = Vocabulary.size(), mid;
	while (r - l >= 2)
	{
		mid = (r + l)>> 1;
		if (Vocabulary[mid].Get_word() < w)
			l = mid;
		else
			r = mid;
	}
	if (Vocabulary[l].Get_word() == w) 
		return l;
	else if (Vocabulary[r].Get_word() == w)
		return r;
	else return -1;
}
void Database::Calc_Label_Feature()
// �����ǩ�����������������ӳ�ڳ�ԱMap�С� 
{
	int i, j, jj, sz = Vocabulary.size();
	map <string, vector <double> >::iterator it;
	for (i = 0; i < Train_Num; i++)
	{
		Sample& Sam = sample[i];
		for (j = 0; j < Sam.labelnum; j++)
		{
			if ((it = Map.find(Sam.label[j]))== Map.end())
				Map[Sam.label[j]] = vector<double>(sz);
			for (jj = 0; jj < Sam.wordnum; jj++) {
				int tar = Find_Word_Index(Sam.word[jj]);
				Map[Sam.label[j]][tar] -= log((double)Vocabulary[tar].show / (double)Train_Num);
				//���ö�����TF-IDF 
			}
		}
	}
	for(it = Map.begin(); it != Map.end(); it++)
	{
		double len = Module(it->second);
		for (int i = 0; i < sz; i++)
			it->second[i] /= len;
	}
}
void Database::Extract_Labels(string current_, ofstream &fout) {             //����������� 
	current.Deal_with_Test(current_, Count_num ++);

	vector <double> SampVec(Vocabulary.size()); //���ڴ洢��ǰ����ľ��ӵ��������� 
	map<string, vector<double> >::iterator it;
	int i, j, sz = Vocabulary.size();
	for (i = 0; i < current.wordnum; i++)
	{
		int at = Find_Word_Index(current.word[i]); // Ѱ�ҵ�ǰ�����ʵ��±� 
		if (at < 0) continue; // ����δ֪���ʣ����账�� 
		Word& W = Vocabulary[at];
		SampVec[at] -= log((double)W.show / (double)Train_Num); // ����ÿ����֪������Ȩ�� 
	}
	double lenth = Module(SampVec);
	for (int i = 0; i < sz; i++)
		SampVec[i] /= lenth;
	for (it = Map.begin(); it != Map.end(); it++)
	{
		double angle = CosAngle(it->second, SampVec);
		Q.push(make_pair(angle, it->first));
	}
	for (int ii = 0; ii < result_labelnum; ii++)
	{
		current.label[ii] = Q.top().second;
		Q.pop();
		// �Ѽн�����ֵ����������ǩ������current�� 
	}
	while (!Q.empty()) Q.pop();
	current.Output_Result(fout);
	return;
}
