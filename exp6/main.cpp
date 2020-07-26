/*
�ı��˵�

1.�µ���Ϸ
	1.1 ħ��ʦ
		1.1.1 ��ʦ
		1.1.2 ����ʦ
		1.1.3 ����ʦ
		1.1.4 ���鷨ʦ
		1.1.5 ��ħ��ʦ
	1.2 ţսʿ
		1.2.1 ţħ
		1.2.2 ӡ����ţ
	1.3 ��ͷ��
		1.3.1 �ɸ���ʿ
		1.3.2 �޸�սʿ
		1.3.3 ������
	1.4 ������
		1.4.1 �����
		1.4.2 ���޹��
		1.4.3 ������
							1.n.n.1 �����ɫ
								1.n.n.1.1 �浵1
								1.n.n.1.2 �浵2
								1.n.n.1.3 �浵3
								1.n.n.1.4 �浵4
								1.n.n.1.5 �浵5
2.��ȡ�浵
	2.1 �浵1
	2.2 �浵2
	2.3 �浵3
	2.4 �浵4
	2.5 �浵5
3.��Ϸ����
	3.1 ��������
		3.1.1 ��������
			3.1.1.1 ����
			3.1.1.2 ��С
		3.1.2 ��Ч����
			3.1.2.1 ��ɫ��Ч
				3.1.2.1.1 ����
				3.1.2.1.2 ��С
			3.1.2.2 ������Ч
				3.1.2.1.1 ����
				3.1.2.1.2 ��С
	3.2 ��������
		3.2.1 ������
		3.2.2 ��Ч����
		3.2.3 ���⻭��
		3.2.4 ��Ӱ����
		3.2.5 ̽������
		3.2.6 ��������
	3.3 �Ѷ�����
		3.3.1 ��ƽ
		3.3.2 ��
		3.3.3 ����
4.�˳���Ϸ

*/
#include<cstdio>
#include<cstdlib>
#include<cstring>

int saveData[3][6];

typedef struct menuNode{
	int nodeIndex;
	char* str;
	struct menuNode* child;
	struct menuNode* next;
	int(*run)(int);
}MenuNode;

int setCurrentCharacter(int character){
	saveData[0][0] = character;
	return 0;
}

int setSaves(int save){
	int index = save%10;
	saveData[1][index] = save/10;
	return 0;
}

int getSaves(int index){
	return saveData[1][index];
}

int setAudio(int save){
	int index = save%10;
	saveData[2][index] = save/10;
	return 0;
}

int getAudio(int index){
	return saveData[2][index];
}

void loadData(){
	FILE* in = fopen("save.txt","r");
	if(in == NULL){
		for(int i = 0 ; i < 6 ; i++)
			saveData[1][i] = -1;
		saveData[2][0] = 50;
		saveData[2][1] = 50;
		saveData[2][2] = 50;
		saveData[2][3] = 3;
		saveData[2][4] = 2;
		return;
	}
	
	for(int i = 0 ; i < 6 ; i++)
		fscanf(in,"%d",&saveData[1][i]);
	for(int i = 0 ; i < 6 ; i++)
		fscanf(in,"%d",&saveData[2][i]);
}

int saveDatas(){
	FILE* out = fopen("save.txt","w");
	for(int i = 0 ; i < 6 ; i++)
		fprintf(out,"%d ",saveData[1][i]);
	for(int i = 0 ; i < 6 ; i++)
		fprintf(out,"%d ",saveData[2][i]);
} 


MenuNode* InitMenu(){
	MenuNode* root = (MenuNode*)malloc(sizeof(MenuNode));
	root->str = "root";
	MenuNode* _1 = (MenuNode*)malloc(sizeof(MenuNode));
	_1->str = "�µ���Ϸ";
	MenuNode* _11 = (MenuNode*)malloc(sizeof(MenuNode));
	_11->str = "ħ��ʦ";
	MenuNode* _111 = (MenuNode*)malloc(sizeof(MenuNode));
	_111->str = "��ʦ";
	MenuNode* _112 = (MenuNode*)malloc(sizeof(MenuNode));
	_112->str = "����ʦ";
	MenuNode* _113 = (MenuNode*)malloc(sizeof(MenuNode));
	_113->str = "����ʦ";
	MenuNode* _114 = (MenuNode*)malloc(sizeof(MenuNode));
	_114->str = "���鷨ʦ";
	MenuNode* _115 = (MenuNode*)malloc(sizeof(MenuNode));
	_115->str = "��ħ��ʦ";
	
	MenuNode* _12 = (MenuNode*)malloc(sizeof(MenuNode));
	_12->str = "ţսʿ";
	MenuNode* _121 = (MenuNode*)malloc(sizeof(MenuNode));
	_121->str = "ţħ";
	MenuNode* _122 = (MenuNode*)malloc(sizeof(MenuNode));
	_122->str = "ӡ����ţ";
	MenuNode* _13 = (MenuNode*)malloc(sizeof(MenuNode));
	_13->str = "��ͷ��";
	MenuNode* _131 = (MenuNode*)malloc(sizeof(MenuNode));
	_131->str = "�ɸ���ʿ";
	MenuNode* _132 = (MenuNode*)malloc(sizeof(MenuNode));
	_132->str = "�޸�սʿ";
	MenuNode* _133 = (MenuNode*)malloc(sizeof(MenuNode));
	_133->str = "������";
	MenuNode* _14 = (MenuNode*)malloc(sizeof(MenuNode));
	_14->str = "������";
	MenuNode* _141 = (MenuNode*)malloc(sizeof(MenuNode));
	_141->str = "�����";
	MenuNode* _142 = (MenuNode*)malloc(sizeof(MenuNode));
	_142->str = "���޹��";
	MenuNode* _143 = (MenuNode*)malloc(sizeof(MenuNode));
	_143->str = "������";
	MenuNode* _1nn1 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn1->str = "�����ɫ";
	MenuNode* _1nn11 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn11->str = "�浵1";
	MenuNode* _1nn12 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn12->str = "�浵2";
	MenuNode* _1nn13 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn13->str = "�浵3";
	MenuNode* _1nn14 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn14->str = "�浵4";
	MenuNode* _1nn15 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn15->str = "�浵5";
	
	MenuNode* _2 = (MenuNode*)malloc(sizeof(MenuNode));
	_2->str = "��ȡ�浵";
	MenuNode* _21 = (MenuNode*)malloc(sizeof(MenuNode));
	_21->str = "�浵1";
	MenuNode* _22 = (MenuNode*)malloc(sizeof(MenuNode));
	_22->str = "�浵2";
	MenuNode* _23 = (MenuNode*)malloc(sizeof(MenuNode));
	_23->str = "�浵3";
	MenuNode* _24 = (MenuNode*)malloc(sizeof(MenuNode));
	_24->str = "�浵4";
	MenuNode* _25 = (MenuNode*)malloc(sizeof(MenuNode));
	_25->str = "�浵5";
	
	MenuNode* _3 = (MenuNode*)malloc(sizeof(MenuNode));
	_3->str = "��Ϸ����";
	MenuNode* _31 = (MenuNode*)malloc(sizeof(MenuNode));
	_31->str = "��������";
	MenuNode* _311 = (MenuNode*)malloc(sizeof(MenuNode));
	_311->str = "��������";
	MenuNode* _3111 = (MenuNode*)malloc(sizeof(MenuNode));
	_3111->str = "����";
	MenuNode* _3112 = (MenuNode*)malloc(sizeof(MenuNode));
	_3112->str = "��С";
	MenuNode* _312 = (MenuNode*)malloc(sizeof(MenuNode));
	_312->str = "��Ч����";
	MenuNode* _3121 = (MenuNode*)malloc(sizeof(MenuNode));
	_3121->str = "��ɫ��Ч";
	MenuNode* _31211 = (MenuNode*)malloc(sizeof(MenuNode));
	_31211->str = "����";
	MenuNode* _31212 = (MenuNode*)malloc(sizeof(MenuNode));
	_31212->str = "��С";
	MenuNode* _3122 = (MenuNode*)malloc(sizeof(MenuNode));
	_3122->str = "������Ч";
	MenuNode* _31221 = (MenuNode*)malloc(sizeof(MenuNode));
	_31221->str = "����";
	MenuNode* _31222 = (MenuNode*)malloc(sizeof(MenuNode));
	_31222->str = "��С";
	MenuNode* _32 = (MenuNode*)malloc(sizeof(MenuNode));
	_32->str = "��������";
	MenuNode* _321 = (MenuNode*)malloc(sizeof(MenuNode));
	_321->str = "������";
	MenuNode* _322 = (MenuNode*)malloc(sizeof(MenuNode));
	_322->str = "��Ч����";
	MenuNode* _323 = (MenuNode*)malloc(sizeof(MenuNode));
	_323->str = "���⻭��";
	MenuNode* _324 = (MenuNode*)malloc(sizeof(MenuNode));
	_324->str = "��Ӱ����";
	MenuNode* _325 = (MenuNode*)malloc(sizeof(MenuNode));
	_325->str = "̽������";
	MenuNode* _326 = (MenuNode*)malloc(sizeof(MenuNode));
	_326->str = "������";
	MenuNode* _33 = (MenuNode*)malloc(sizeof(MenuNode));
	_33->str = "�Ѷ�����";
	MenuNode* _331 = (MenuNode*)malloc(sizeof(MenuNode));
	_331->str = "��ƽ";
	MenuNode* _332 = (MenuNode*)malloc(sizeof(MenuNode));
	_332->str = "��";
	MenuNode* _333 = (MenuNode*)malloc(sizeof(MenuNode));
	_333->str = "����";
	
	MenuNode* _4 = (MenuNode*)malloc(sizeof(MenuNode));
	_4->str = "�˳���Ϸ";

	root->next = NULL;
	root->child = _1;
	_1->next = _2;_2->next = _3;_3->next = _4;_4->next = NULL;
	
	_1->child = _11;
	_11->next = _12;_12->next = _13;_13->next = _14;_14->next = NULL;
	
	_11->child=_111;
	_111->next = _112;_112->next = _113;_113->next = _114;_114->next = _115;_115->next=NULL;
	
	_12->child=_121;
	_121->next = _122;_122->next=NULL;
	
	_13->child=_131;
	_131->next=_132;_132->next=_133;_133->next=NULL;
	
	_14->child=_141;
	_141->next=_142;_142->next=_143;_143->next=NULL;
/*
	_111->child = _1nn1;
	_112->child = _1nn1;
	_113->child = _1nn1;
	_114->child = _1nn1;
	_115->child = _1nn1;
	_121->child = _1nn1;
	_122->child = _1nn1;
	_131->child = _1nn1;
	_132->child = _1nn1;
	_133->child = _1nn1;
	_141->child = _1nn1;
	_142->child = _1nn1;
	_143->child = _1nn1;

	_1nn1->child = _1nn11;
	_1nn11->next=_1nn12;_1nn12->next=_1nn13;_1nn13->next=_1nn14;_1nn14->next=_1nn15;_1nn15->next=NULL;
*/
	_2->child = _21;
	_21->next = _22;_22->next = _23;_23->next = _24;_24->next = _25;_25->next =  NULL;
	
	_3->child = _31;
	_31->next = _32;_32->next = _33;_33->next =NULL;
	
	_31->child = _311;
	_311->next = _312;_312->next = NULL;
	
	_311->child = _3111;
	_3111->next = _3112;_3112->next = NULL;
	
	_312->child = _3121;
	_3121->next = _3122;_3122->next = NULL;
	
	_3121->child = _31211;
	_31211->next = _31212;_31212->next = NULL;
	
	_3122->child = _31221;
	_31221->next = _31222;_31222->next = NULL;
	
	_32->child = _321;
	_321->next = _322;_322->next = _323;_323->next = _324;_324->next = _325;_325->next = _326;_326->next = NULL;
	
	_33->child = _331;
	_331->next = _332;_332->next = _333;_333->next = NULL;
	printf("over\n");
	return root;
}

void printWholeMenu(MenuNode* root,int deep){
	for(int i = 0 ; i < deep ;i++){
		printf("\t");
	}
	if(root == NULL){
		printf("NULL\n");
		return;
	}
	printf("%s\n",root->str);
	MenuNode* next = root->child;
	while(next != NULL){
		printWholeMenu(next,deep+1);
		next = next->next;
	}
}

int main(){
	MenuNode*root = InitMenu();
	printWholeMenu(root,0);
	
	return 0;
}