/*
文本菜单

1.新的游戏
	1.1 魔法师
		1.1.1 火法师
		1.1.2 冰法师
		1.1.3 毒法师
		1.1.4 死灵法师
		1.1.5 恶魔法师
	1.2 牛战士
		1.2.1 牛魔
		1.2.2 印度神牛
	1.3 斧头人
		1.3.1 飞斧勇士
		1.3.2 巨斧战士
		1.3.3 刽子手
	1.4 弓箭手
		1.4.1 惊羽诀
		1.4.2 天罗诡道
		1.4.3 朝弦门
							1.n.n.1 保存角色
								1.n.n.1.1 存档1
								1.n.n.1.2 存档2
								1.n.n.1.3 存档3
								1.n.n.1.4 存档4
								1.n.n.1.5 存档5
2.读取存档
	2.1 存档1
	2.2 存档2
	2.3 存档3
	2.4 存档4
	2.5 存档5
3.游戏设置
	3.1 音量设置
		3.1.1 音乐设置
			3.1.1.1 增大
			3.1.1.2 减小
		3.1.2 音效设置
			3.1.2.1 角色音效
				3.1.2.1.1 增大
				3.1.2.1.2 减小
			3.1.2.2 环境音效
				3.1.2.1.1 增大
				3.1.2.1.2 减小
	3.2 画面设置
		3.2.1 极简画质
		3.2.2 高效画质
		3.2.3 均衡画质
		3.2.4 电影画质
		3.2.5 探索画质
		3.2.6 绝世画质
	3.3 难度设置
		3.3.1 和平
		3.3.2 简单
		3.3.3 困难
4.退出游戏

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
	_1->str = "新的游戏";
	MenuNode* _11 = (MenuNode*)malloc(sizeof(MenuNode));
	_11->str = "魔法师";
	MenuNode* _111 = (MenuNode*)malloc(sizeof(MenuNode));
	_111->str = "火法师";
	MenuNode* _112 = (MenuNode*)malloc(sizeof(MenuNode));
	_112->str = "冰法师";
	MenuNode* _113 = (MenuNode*)malloc(sizeof(MenuNode));
	_113->str = "毒法师";
	MenuNode* _114 = (MenuNode*)malloc(sizeof(MenuNode));
	_114->str = "死灵法师";
	MenuNode* _115 = (MenuNode*)malloc(sizeof(MenuNode));
	_115->str = "恶魔法师";
	
	MenuNode* _12 = (MenuNode*)malloc(sizeof(MenuNode));
	_12->str = "牛战士";
	MenuNode* _121 = (MenuNode*)malloc(sizeof(MenuNode));
	_121->str = "牛魔";
	MenuNode* _122 = (MenuNode*)malloc(sizeof(MenuNode));
	_122->str = "印度神牛";
	MenuNode* _13 = (MenuNode*)malloc(sizeof(MenuNode));
	_13->str = "斧头人";
	MenuNode* _131 = (MenuNode*)malloc(sizeof(MenuNode));
	_131->str = "飞斧勇士";
	MenuNode* _132 = (MenuNode*)malloc(sizeof(MenuNode));
	_132->str = "巨斧战士";
	MenuNode* _133 = (MenuNode*)malloc(sizeof(MenuNode));
	_133->str = "刽子手";
	MenuNode* _14 = (MenuNode*)malloc(sizeof(MenuNode));
	_14->str = "弓箭手";
	MenuNode* _141 = (MenuNode*)malloc(sizeof(MenuNode));
	_141->str = "惊羽诀";
	MenuNode* _142 = (MenuNode*)malloc(sizeof(MenuNode));
	_142->str = "天罗诡道";
	MenuNode* _143 = (MenuNode*)malloc(sizeof(MenuNode));
	_143->str = "朝弦门";
	MenuNode* _1nn1 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn1->str = "保存角色";
	MenuNode* _1nn11 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn11->str = "存档1";
	MenuNode* _1nn12 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn12->str = "存档2";
	MenuNode* _1nn13 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn13->str = "存档3";
	MenuNode* _1nn14 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn14->str = "存档4";
	MenuNode* _1nn15 = (MenuNode*)malloc(sizeof(MenuNode));
	_1nn15->str = "存档5";
	
	MenuNode* _2 = (MenuNode*)malloc(sizeof(MenuNode));
	_2->str = "读取存档";
	MenuNode* _21 = (MenuNode*)malloc(sizeof(MenuNode));
	_21->str = "存档1";
	MenuNode* _22 = (MenuNode*)malloc(sizeof(MenuNode));
	_22->str = "存档2";
	MenuNode* _23 = (MenuNode*)malloc(sizeof(MenuNode));
	_23->str = "存档3";
	MenuNode* _24 = (MenuNode*)malloc(sizeof(MenuNode));
	_24->str = "存档4";
	MenuNode* _25 = (MenuNode*)malloc(sizeof(MenuNode));
	_25->str = "存档5";
	
	MenuNode* _3 = (MenuNode*)malloc(sizeof(MenuNode));
	_3->str = "游戏设置";
	MenuNode* _31 = (MenuNode*)malloc(sizeof(MenuNode));
	_31->str = "音量设置";
	MenuNode* _311 = (MenuNode*)malloc(sizeof(MenuNode));
	_311->str = "音乐设置";
	MenuNode* _3111 = (MenuNode*)malloc(sizeof(MenuNode));
	_3111->str = "增大";
	MenuNode* _3112 = (MenuNode*)malloc(sizeof(MenuNode));
	_3112->str = "减小";
	MenuNode* _312 = (MenuNode*)malloc(sizeof(MenuNode));
	_312->str = "音效设置";
	MenuNode* _3121 = (MenuNode*)malloc(sizeof(MenuNode));
	_3121->str = "角色音效";
	MenuNode* _31211 = (MenuNode*)malloc(sizeof(MenuNode));
	_31211->str = "增大";
	MenuNode* _31212 = (MenuNode*)malloc(sizeof(MenuNode));
	_31212->str = "减小";
	MenuNode* _3122 = (MenuNode*)malloc(sizeof(MenuNode));
	_3122->str = "环境音效";
	MenuNode* _31221 = (MenuNode*)malloc(sizeof(MenuNode));
	_31221->str = "增大";
	MenuNode* _31222 = (MenuNode*)malloc(sizeof(MenuNode));
	_31222->str = "减小";
	MenuNode* _32 = (MenuNode*)malloc(sizeof(MenuNode));
	_32->str = "画面设置";
	MenuNode* _321 = (MenuNode*)malloc(sizeof(MenuNode));
	_321->str = "极简画质";
	MenuNode* _322 = (MenuNode*)malloc(sizeof(MenuNode));
	_322->str = "高效画质";
	MenuNode* _323 = (MenuNode*)malloc(sizeof(MenuNode));
	_323->str = "均衡画质";
	MenuNode* _324 = (MenuNode*)malloc(sizeof(MenuNode));
	_324->str = "电影画质";
	MenuNode* _325 = (MenuNode*)malloc(sizeof(MenuNode));
	_325->str = "探索画质";
	MenuNode* _326 = (MenuNode*)malloc(sizeof(MenuNode));
	_326->str = "世画质";
	MenuNode* _33 = (MenuNode*)malloc(sizeof(MenuNode));
	_33->str = "难度设置";
	MenuNode* _331 = (MenuNode*)malloc(sizeof(MenuNode));
	_331->str = "和平";
	MenuNode* _332 = (MenuNode*)malloc(sizeof(MenuNode));
	_332->str = "简单";
	MenuNode* _333 = (MenuNode*)malloc(sizeof(MenuNode));
	_333->str = "困难";
	
	MenuNode* _4 = (MenuNode*)malloc(sizeof(MenuNode));
	_4->str = "退出游戏";

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