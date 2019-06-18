#include "typedef.h"
int main() {               //������ 
	Database database;                            //����һ������ 
	ifstream fin("train.data");                   //��ѵ�������ļ�
	if (!fin) {
		cerr << "Fail to open \"train.data\", please make sure that it is under the same directory with this programme then try again!" << endl; 
		return 0;		
	} 
	ofstream fout("sentence list.data");          //�������� 
	cout << "Making sentence list ......" << endl;
	for (int i = 0 ; i < divided ; i ++) {        //ִ��divided�� 
		database.Import_Samples(fin);             //����ѵ������ 
		database.Deal_with_Samples();             //����ѵ������
		database.Export_Samples(fout);            //������� 
	}
	cout << "Sentence list is finished." << endl;
	fin.close();                                  //�ر�ѵ������ 
	fout.close();                                 //�ر����� 
	fout.open("word list.data");                  //�������ʱ� 
	cout << "Making word list ......" << endl;
	database.Export_Words(fout);                  //������ʱ� 
	cout << "Word list is finished." << endl;
	fout.close();                                 //�رյ��ʱ�
	string current;                               //��ʱ�洢��������
	database.Import_Database(fin);                //��������͵��ʱ�
	database.Calc_Label_Feature();				  //�����ǩ����ֵ
	
	fin.open("test.data");                        //�򿪲������� 
	if (!fin) {
		cerr << "Fail to open \"test.data\", please make sure that it is under the same directory with this programme then try again!" << endl; 
		return 0;
	}
	fout.open("result.data");                     //��������ļ�
	cout << "Extracting the labels ......" << endl;
	while (getline(fin, current)) {                //����������� 
		database.Extract_Labels(current, fout);  //��ȡ�������ǩ
	}
	cout << "All the work is finished." << endl << "You can check the result now." << endl;;
	fin.close();                                  //�رղ������� 
	fout.close();                                 //�رս���ļ� 
	return 0; 
}
