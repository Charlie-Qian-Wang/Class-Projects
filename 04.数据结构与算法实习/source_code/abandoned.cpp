void Sample::Do_Choose_Work(vector<Word> *All_words) {
	double label_choose[500] = { 0 }; //����ǩ�ķ�ֵ
	int choo[3] = { 0 };              //Ŀǰǰ���ı�ǩ���
	vector<Word>::iterator p;
	for (int i = 0; i < wordnum; i++) {//�������ǩ�ķ�ֵ
		p = find(All_words[word[i][0] - 'a'].begin(), All_words[word[i][0] - 'a'].end(), word[i]);
		if (p == All_words[word[i][0] - 'a'].end()) continue;
		int *temp = p->label_showed;
		for (int t = 0; t < str_and_int.str_num; t++) {
			if (temp[t] && p->show <= 60)  //���ƴʵĳ��ִ���
				label_choose[t]+= (1 / p->show);
		}
	}
	//ѡ����ֵǰ���ı�ǩ
	double max0 = 0;
	double max1 = 0;
	double max2 = 0;
	for (int i = 0; i < str_and_int.str_num; i++) {
		if (label_choose[i] >= max0) {
			max2 = max1;
			choo[2] = choo[1];
			max1 = max0;
			choo[1] = choo[0];
			max0 = label_choose[i];
			choo[0] = i;
		}
		else if (label_choose[i] >= max1) {
			max2 = max1;
			choo[2] = choo[1];
			max1 = label_choose[i];
			choo[1] = i;
		}
		else if (label_choose[i] >= max2) {
			max2 = label_choose[i];
			choo[2] = i;
		}
	}
	for (int i = 0; i < 3; i++) {
		label[i] = str_and_int.int2str[choo[i]];
	}
}
