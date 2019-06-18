#include "typedef.h"
/*class Sample {             //����� 
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
};*/
Sample::Sample() {                                                          //���캯�� 
	word = label = NULL;
}
Sample::~Sample() {                                                         //�������� 
	if (word) delete [] word;
	if (label) delete [] label;
}
void Sample::Input_Sample(ifstream &fin) {                                  //���봦�����ѵ������ 
	fin >> id >> wordnum;
	word = new string[wordnum];
	for (int i = 0 ; i < wordnum ; i ++)
		fin >> word[i];
	fin >> labelnum;
	char o = fin.get();
	label = new string[labelnum];
	for (int i = 0 ; i < labelnum ; i ++)
		getline(fin, label[i]);
	return;
}
void Sample::Import_Sample(ifstream &fin, int n) {                          //����ѵ������
	getline(fin, sentence);
	id = n;
	if (id % (Train_Num / divided) == 0) cout << "It's sample sentence " << id << " now." << endl;
	wordnum = labelnum = 0;
	word = new string[word_max_num];
	label = new string[label_max_num];
	return;
}
void Sample::Export_Sample(ofstream &fout) {                                //����������ѵ������ 
	fout << id << endl;
	fout << wordnum << endl;
	for (int i = 0 ; i < wordnum ; i ++)
		fout << word[i] << " ";
	fout << endl;
	fout << labelnum << endl;			
	for (int i = 0 ; i < labelnum ; i ++)
		fout << label[i] << endl;
	return;
}
void Sample::mystrlwr(string &str) {                                        //string����дתΪСд 
	for (int i = 0 ; i < str.length() ; i ++)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 'a' - 'A';
	return;
}
void Sample::Set_word() {                                                   //��ȡ���� 
	for (int i = 0 ; i < sentence.length() ; i ++) {
		if (!isalpha(sentence[i])) {
			if (!word[wordnum].empty())
					wordnum ++;
		}
		else word[wordnum].append(1, sentence[i]);
	}
	if (!word[wordnum].empty()) wordnum ++;
	for (int i = 0 ; i < wordnum ; i ++) {
		mystrlwr(word[i]);
	}
	return;
}
void Sample::Clear_tail() {                                                 //���β��"#$#"��֮������ 
	int length = sentence.length();
	int p = length;
	while (true)
		if (sentence[-- p] == '#') {
			sentence.erase(p - 2, length - p + 2);
				break;
		}
	return;
}
void Sample::Clear_head() {                                                 //���ͷ��"#$#"��֮ǰ���ݣ�
	int p = 0;
	while (true)
		if (sentence[p ++] == '#') {
				sentence.erase(0, p + 2);
				break;
		}
	return;	
}
void Sample::Set_label() {                                                  //��ȡѵ�����ݱ�ǩ 
	int begin = sentence.length() - 1;
	while (sentence[begin] != '#') begin --;
	while (begin != sentence.length() - 1) {
		begin ++;
		if (sentence[begin] == ',') labelnum ++;
		else label[labelnum].append(1, sentence[begin]);
	}
	for (int i = 0 ; i < labelnum ; i ++) mystrlwr(label[i]); 
	return;
}
void Sample::Push(vector<Word> *All_words) {                                //ͳ��ȫ������ 
	for (int i = 0 ; i < wordnum ; i ++) {
		vector<Word>::iterator p = find(All_words[word[i][0] - 'a'].begin(), All_words[word[i][0] - 'a'].end(), word[i]);
		if (p == All_words[word[i][0] - 'a'].end())
			All_words[word[i][0] - 'a'].push_back(Word(word[i]));
		p = find(All_words[word[i][0] - 'a'].begin(), All_words[word[i][0] - 'a'].end(), word[i]);
		p->times[id] ++;
		p->sum ++;
	}
	return;
}
void Sample::Deal_with_Sample(vector<Word> *All_words) {                    //����ѵ�������ܺ��� 
	Set_label();
	Clear_tail();
	Clear_head();
	Set_word();
	Push(All_words);
	return;
}
void Sample::Deal_with_Test(string current, int n) {                        //������������ܺ��� 
	sentence = current;
	id = n;
	if (id % (Train_Num / divided / divided) == 0) cout << "It's test sentence " << id << " now." << endl;			
	wordnum = labelnum = 0;
	word = new string[word_max_num];
	label = new string[result_labelnum];
	Clear_head();
	Set_word();
	return;
}
void Sample::Output_Result(ofstream &fout) {                                //���������ܺ��� 
	fout << id << "#$#";
	for (int i = 0 ; i < result_labelnum ; i ++)
		fout << label[i] << ",";
	fout << endl;
	return;
}
