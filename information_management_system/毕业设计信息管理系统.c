//毕业设计信息管理系统的设计与实现 
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<time.h> 
#include<math.h>
//储存一个学生的各项毕设信息储存在一起，不同学生间建立链表 
typedef struct student
{
	int ID;
	char CLASS[50];
	char MAJOR[50];
	char TOPIC[100];
	char GRADES[100];
	int INSTRUCTOR_NUM;
	char INSTRUCTOR_TITLE [50];
	char TOPIC_CLASSIFICATION [50];
	char WHE[5];
	struct student *next;
}STUDENT;
 
STUDENT *last = NULL;	//原始链表的尾 
STUDENT *head = NULL;	//原始链表的头 

STUDENT *h = NULL;	//暂用链表的头 

STUDENT *sc = NULL;	//抽查链表的头
 
int ll = 0;	//用于判断打开哪个文件
 
char buf[1024];	//储存毕设信息分类小标题 
char c[1024];	//在要求读入数字后用gets（），防止用户输入非数字引起程序故障 

enum InterFace {start, operate, view,  add, modify, strikeout, sort, inquire, count, sportcheck, end} interFace;
//     分别表示 开始    操作    查看  添加   修改     删除     排序   查询     统计   抽查       结束   的界面 
//很奇怪？？？  不能写interface??? 

int Start();
	void _Read(FILE *fp,STUDENT *p,int number);
void show(); 
	void save();
	STUDENT* traverse(int ID);
	STUDENT* Confirm_ID();
	void c_or_r();
	void Welcome();
	void Operate();
	void View(); 
		void _Print(STUDENT *p);
	void Add();
		void  fAppend();
	void Modify();
	void Strikeout();
	void Sort();
		void STUDENT_copy(STUDENT *p,STUDENT *q);
		void ID_Sort();
		void grades_Sort();
		void instructornum_Sort();
	void Inquire();
		void copy(); 
		void cut(STUDENT *tocut);
	void Count();
		void grades_Count(int a[4]);
		void classification_Count(int b[5]);
		void whe_Count(int c[2]);
	void Inquire();
	void Sportcheck();
		void create_x(STUDENT *p);
		void Sportcheck_1();
		void Sportcheck_print();
		void Sportcheck_save();
		void Sportcheck_init();
		STUDENT *h_traverse(int ID);
		int judge();
void End();


int main(int argc,char *argv[])
{
	Welcome();//欢迎界面 
	interFace = start;//初始化interFace 
	
	while(interFace != end)
	{
		show();
	}
	
	End();//结束 
	
	return 0;
} 

//读入文件中一行也是一个学生的毕设各项信息 
void _Read(FILE *fp,STUDENT *p,int number)
{
	char temp[1024];
		
	p->ID   = number;//将传入的number存入ID 
	fscanf(fp,"%s",&p->CLASS);
	fscanf(fp,"%s",&p->MAJOR);
	
	fscanf(fp,"%s",&p->TOPIC);
	fscanf(fp,"%s",&temp);
	// 因为毕设题目内可能有空格，文件中毕设题目与成绩的间隔也可能用空格表示，故读取标题直到读到成绩为止 
	while(strcmp(temp,"及格") &&  strcmp(temp,"中") && strcmp(temp,"良") && strcmp(temp,"优"))//全不相同 
	{
		p->TOPIC[strlen(p->TOPIC)] = ' ';
		strcat(p->TOPIC,temp); 
		fscanf(fp,"%s",&temp);
	}
	strcpy(p->GRADES,temp);
	
	fscanf(fp,"%d",&p->INSTRUCTOR_NUM);
	fscanf(fp,"%s",&p->INSTRUCTOR_TITLE);
	fscanf(fp,"%s",&p->TOPIC_CLASSIFICATION);
	fscanf(fp,"%s",&p->WHE);
	p->next = NULL;
}

//打印一个学生的毕设各项信息在一行 
void _Print(STUDENT *p)
{
	printf("%d ",p->ID);
	printf("%-20s ",p->CLASS);
	printf("%-16s ",p->MAJOR);
	printf("%-62s ",p->TOPIC);
	printf("%-4s ",p->GRADES);
	printf("%d ",p->INSTRUCTOR_NUM);
	printf("%-12s ",p->INSTRUCTOR_TITLE);
	printf("%-16s ",p->TOPIC_CLASSIFICATION);
	printf("%s\n",p->WHE);
//	printf("%s\n",p->TOPIC_CLASSIFICATION);
}

//开始界面，选择读取全部或抽查毕设信息的文件并建立原始链表供其他函数进行操作 
int Start()
{
	//若更换操作文件，则将原来的链表空间释放 
	End();
	 
	int number;	//用于读入学生学号 
	STUDENT *p;	//用于指向链表新的一节 
	//要求用户选择打开哪个文件 
	printf("欢迎进入开始界面\n\
请输入1选择对所有毕设信息进行操作，输入2选择对抽查的毕设信息进行操作,输入其它数字无效\n");
	while(ll!= 1 && ll!= 2) 
	{
		scanf("%d",&ll);
		gets(c);
	}
	//打开文件 
	FILE *fp; 
	if(ll == 1)	fp = fopen("毕业设计信息.txt","r");
	else if(ll == 2) fp = fopen("毕业设计信息抽查.txt","r");
	if(fp == NULL)//若不能打开文件则提示错误，重新进入start界面 
	{
		printf("The file can not be opened.\n");
		system("pause");
		ll = 0; 
		return -1;
	}

	fscanf(fp,"%[^\n]",buf);
	
	last = (STUDENT*)malloc(sizeof(STUDENT));  
	if(fscanf(fp,"%d",&number) == EOF)//若文件为空 则提示错误，重新进入start界面 
	{
		printf("文件出错了！\n");
		system("pause");
		ll = 0;
		return -1;
	}
	//读入数据进原始链表的头 
	_Read(fp,last,number);
	head = last;
	
	//持续读入数据直到文件末尾 
	while(fscanf(fp,"%d",&number)!=EOF)
	{
		p = (STUDENT*)malloc(sizeof(STUDENT)); 
		_Read(fp,p,number);
		last->next = p;
		last = p;
	}
	
	fclose(fp);
	save();//将文件中内容规范排列 
	interFace = operate; 
	return 0;
}

//释放原始链表的全部空间 
void End()
{
	STUDENT *q;
	STUDENT *p;
	for(p = head;p;p = q)
	{
		q = p->next;
		free(p);
	}
}


//根据interFace的值判断进入各个界面 
void show()
{
//enum InterFace {welcome, operate, view, add, modify, strikeout, sort, inquire, count, sportcheck, end} interFace;
	system("cls");//清空屏幕 
	switch (interFace)
	{
		case start:
        	Start();
        break;
        
        case operate:
        	Operate();
        break;
        
        case view:
        	View();
        break;
        
        case add:
        	Add();
        break;
        
        case modify:
        	Modify();
        break;
        
        case strikeout:
        	Strikeout();
        break;
        
        case sort:
        	Sort();
        break;
        
        case inquire:
       	Inquire();
        break;
        
        case count:
        	Count();
        break;
        
        case sportcheck:
        	Sportcheck();
        break;
        
 /*     case end:
       		End();
        break;*/
        
        default:
        	;
        break;
	}
}

//在对原始链表进行操作后将操作保存至文件 
void save() 
{
	STUDENT *p;
	FILE *fp;
	if(ll == 1)	fp = fopen("毕业设计信息.txt","w");
	else if(ll == 2)	fp = fopen("毕业设计信息抽查.txt","w");
	if(fp == NULL)
	{
		printf("文件打开失败!\n");
		return ;
	}
	fprintf(fp,"%s\n",buf);
	for(p = head;p;p = p->next)
	{
		fprintf(fp,"%d ",p->ID);
		fprintf(fp,"%-20s ",p->CLASS);
		fprintf(fp,"%-16s ",p->MAJOR);
		fprintf(fp,"%-62s ",p->TOPIC);
		fprintf(fp,"%-4s ",p->GRADES);
		fprintf(fp,"%d ",p->INSTRUCTOR_NUM);
		fprintf(fp,"%-12s ",p->INSTRUCTOR_TITLE);
		fprintf(fp,"%-16s ",p->TOPIC_CLASSIFICATION);
		fprintf(fp,"%s",p->WHE);
		if(last != p) fprintf(fp,"%\n");//在文件的末尾不多余换行 
	} 
	fclose(fp);
}

//用于Add()函数在原始链表末尾添加一截后对文件进行同样操作，在Add函数中比save函数效率更高 
void fAppend()
{
	FILE *fp;
	if(ll == 1)	fp = fopen("毕业设计信息.txt","a+");
	else if(ll == 2)	fp = fopen("毕业设计信息抽查.txt","a+");
	if(fp == NULL)
	{
		printf("文件打开失败!\n");
		return ;
	}
	fprintf(fp,"%\n"); 
	fprintf(fp,"%d ",last->ID);
	fprintf(fp,"%-20s ",last->CLASS);
	fprintf(fp,"%-16s ",last->MAJOR);
	fprintf(fp,"%-62s ",last->TOPIC);
	fprintf(fp,"%-4s ",last->GRADES);
	fprintf(fp,"%d ",last->INSTRUCTOR_NUM);
	fprintf(fp,"%-12s ",last->INSTRUCTOR_TITLE);
	fprintf(fp,"%-16s ",last->TOPIC_CLASSIFICATION);
	fprintf(fp,"%s",last->WHE);
	fclose(fp);
}

//函数功能介绍：输入ID，返回对应原始链表结构体的指针 ,找不到的话返回NULL 
STUDENT *traverse(int ID)
{
	STUDENT *p = NULL;
	for(p = head;p;p = p->next)
	{
		if(p->ID == ID)
		{
			break;
		}
	}
	return p;
}


//用于各个界面完成操作后，要求用户输入1不改变interFace再次进入该界面，或者输入2回到操作界面 
void c_or_r()
{
	printf("继续对其他学生毕设信息进行该类操作请输入1，回到操作界面请输入2，输入其他数字无效\n");
	int a = 0;
	while(a != 1 && a != 2)
	{
		scanf("%d",&a);
		gets(c);
	}
	if(a == 1)
	{
		; 
	}
	else if(a == 2)
	{
		interFace = operate;
	}
	else 
	{
		printf("程序出错了！\n");
	}
}

//欢迎用户进入系统 
void Welcome()
{
	printf("欢迎来到毕业设计信息管理系统！\n\
请在键盘输入'a'进入管理系统\n");
	char c = '\0';
	while(c != 'a')scanf("%c",&c);
	{
		scanf("%c",&c);
	}
	interFace = operate;
}

//操作界面 
void Operate()
{
	printf("欢迎进入操作系统!\n\
请选择以下操作\n\
查看所有毕设信息：输入1\n\
增加毕设信息：输入2\n\
修改毕设信息: 输入3 (请记住你要修改毕设信息的学生学号)\n\
删除毕设信息: 输入4 (请记住你要修改毕设信息的学生学号)\n\
排序毕设信息：输入5\n\
查询毕设信息：输入6\n\
统计毕设信息: 输入7\n\
进入开始界面: 输入8\n\
退出毕设信息管理系统: 输入9\n");
if(ll == 1) printf("抽查毕设信息: 输入10\n");//当ll==2亦即打开文件为”毕业设计信息抽查.txt“时不能再进行抽查操作 
	int a=0;
	while(a<1 || a>9)
	{
		scanf("%d",&a);
		gets(c);
		if(a == 10 && ll == 1) break;
	} 
	switch (a)
	{
		case 1:
			interFace = view;
		break;
		
		case 2:
			interFace = add;
		break;
		
		case 3:
			interFace = modify;
		break;
		
		case 4:
			interFace = strikeout;
		break;
		
		case 5:
			interFace = sort;
		break;
		
		case 6:
			interFace = inquire;
		break;
		
		case 7:
			interFace = count;
		break;
		
		case 8:
			interFace = start; 
			ll = 0;//将ll重置为0 
			
		break;
			
		case 9:
			interFace = end;
		break;
		
		case 10:
			interFace = sportcheck;
		default:
			;
		break;
	}
}

//查看原始链表全部毕设信息 
void View()
{
	STUDENT *p;
	printf("%s\n",buf);
	for(p = head; p;p =p->next)	_Print(p);
	printf("请在键盘输入b返回操作界面\n");
	char c;
	while(c != 'b')
	{
		scanf("%c",&c);
	}
	interFace = operate;
}

//添加毕设信息 
void Add()
{
	STUDENT *p;
	STUDENT *q;
	STUDENT *temp = (STUDENT *)malloc(sizeof(STUDENT));
	int w = 0;
	printf("为添加毕设信息，请依次输入以下信息\n");
	printf("请输入学生学号\n");
	while(w != -1)
	{
		char c[1024];
		temp->ID = 0;
		scanf("%d",&temp->ID);
		gets(c); 
		if(temp->ID == 0) printf("你未输入数字，请重新输入学生学号\n");
		else if(traverse(temp->ID) != NULL) //判断要添加的毕设信息ID是否存在 
		{									//若存在则要求重新输入其它学号 
			int t=0;
			printf("你输入的学生学号已存在\
请输入1回到操作界面选择修改其毕设信息,或者输入任意数字后继续输入其他学号\n");
			scanf("%d",&t);
			if (t == 1) //直接回到操作界面 
			{
				interFace = operate;
				return ;
			} 
		}
		else
		{
			printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生学号\n");
			scanf("%d",&w);
		} 
	}
	w = 0;
	printf("请按“16软件工程1的格式”输入学生班级\n");
	while(w != -1)
	{
		scanf("%s",&temp->CLASS);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生班级\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("请输入学生专业\n");
	while(w != -1)
	{
		scanf("%s",&temp->MAJOR);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生专业\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("请输入学生毕业设计题目\n");
	while(w != -1)
	{
		scanf("%s",&temp->TOPIC);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生毕设题目\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("请输入学生毕业设计成绩：优，良，中或及格\n");
	while(w != -1)
	{
		scanf("%s",&temp->GRADES);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生毕设成绩\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("请输入学生毕业设计指导教师工号\n");
	while(w != -1)
	{
		scanf("%d",&temp->INSTRUCTOR_NUM);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生毕设指导教师工号\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("请输入学生毕业设计指导教师职称\n");
	while(w != -1)
	{
		scanf("%s",&temp->INSTRUCTOR_TITLE);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生毕设指导教师职称\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("请输入学生毕业设计题目分类\n");
	while(w != -1)
	{
		scanf("%s",&temp->TOPIC_CLASSIFICATION);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生毕设题目分类\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("是否在实验、实习、工程实践和社会调查等实践中完成 请输入是或否\n");
	while(w != -1)
	{
		scanf("%s",&temp->WHE);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入是或否\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("最后请确定是否全部输入正确\n\
若全部输入正确请输入-1以保存输入的毕设信息\n\
否则输入任意数字不保存输入的毕设信息\n");
	while(w == 0)
	{
		scanf("%d",&w);
		gets(c);
	}
	if(w == -1)
	{
		//将添加的毕设信息保存在原始链表末尾，需要的话可以进入sort界面排序 
		last->next = temp;
		temp->next = NULL;
		last       = temp;	
		//将添加的毕设信息保存在文件末尾 
		fAppend();
	}
	else free(temp);
	c_or_r();//返回操作界面或重新进入添加界面，继续添加毕设信息 
} 

//修改界面 
void Modify()
{
	int a=0;
	int w=0;
	STUDENT *select;
	printf("欢迎进入修改界面\n\
请输入你要修改毕设信息的学生学号\n");
	if(select = Confirm_ID())
	{
		while(w != -1)
		{
			printf("请输入1修改学生学号\n\
请输入2修改学生班级\n\
请输入3修改学生专业\n\
请输入4修改学生毕设题目\n\
请输入5修改学生成绩\n\
请输入6修改学生指导教师教工号\n\
请输入7修改学生指导教师职称\n\
请输入8修改学生毕设题目分类\n\
请输入9修改学生毕设是否在实践中完成\n");
			a=0;
			scanf("%d",&a);
			gets(c);
			switch (a)
			{
				case 1:
					printf("请输入学生学号\n");
					scanf("%d",&select->ID);
					gets(c);
					break;
					
				case 2:
					printf("请按'16软件工程2'格式输入学生班级\n");
					scanf("%s",&select->CLASS);				
					break;
					
				case 3:
					printf("请输入学生专业\n");
					scanf("%s",&select->MAJOR);					
					break;
					
				case 4:
					printf("请输入学生毕设题目\n");
					scanf("%s",&select->TOPIC);			
					break;
					
				case 5:
					printf("请输入学生成绩\n");
					scanf("%s",&select->GRADES);					
					break;
					
				case 6:
					printf("请输入学生指导教师教工号\n");
					scanf("%d",&select->INSTRUCTOR_NUM);	
					gets(c);				
					break;
					
				case 7:
					printf("请输入学生指导教师职称\n");
					scanf("%s",&select->INSTRUCTOR_TITLE);					
					break;
					
				case 8:
					printf("请输入学生毕设题目分类\n");
					scanf("%s",&select->TOPIC_CLASSIFICATION);					
					break;
					
				case 9:
					printf("请输入学生毕设是否在实践中完成,输入’是‘或’否‘\n");
					scanf("%s",&select->WHE);					
					break;
					
				default :
					;
					break;
			}	
			printf("继续修改其他信息请输入任意数字，否则输入-1\n");
			scanf("%d",&w);
			gets(c);	 
		}
		save();//将修改结果保存至文件 
		c_or_r();
	} 
}

//删除界面 
void Strikeout() 
{
	STUDENT *select;
	printf("欢迎进入删除界面\n\
请输入你要删除毕设信息的学生学号\n");
	if(select = Confirm_ID())
	{
		STUDENT *p;
		//如果要删除的是链表的头 
		if(select == head)
		{
			p=head->next;
			free(head);
			head = p;
		}
		//如果要删除的不是链表的头 
		else if(select != head)
		{
			for(p=head;p->next = select;p=p->next) ; 
			p->next = select->next;
			free(select);
		} 
		save();//将删除结果保存至文件 
		c_or_r();
	}
}

// 若存在则显示学生信息，返回原始链表中其指针，进行操作；否则返回0，不进行操作
//同traverse函数相比多了打印文字提示用户 
STUDENT* Confirm_ID()
{
	int w = 0;
	int ID; 
	STUDENT *p;
	while(w != -1)
	{
		scanf("%d",&ID);;
		gets(c);
		printf("确定输入正确请再输入-1,否则输入任意数字继续输入学生学号\n");
		scanf("%d",&w);
		gets(c);
	}
	p = traverse(ID);
	if(p == NULL)
	{
		printf("你要进行操作的学生毕设信息不存在\n");
		c_or_r();
		return NULL;
	}
	else if(p != NULL)
	{
		printf("%s\n",buf);
		_Print(p);
		return p;
	}
	else printf("程序出错了！\n");
}

//排序界面，可选择按学号、成绩、指导教师工号排序 
void Sort()
{
	printf("欢迎进入排序界面\n\
本界面提供三种排序方式。按学号排序请输入1，按成绩排序请输入2，按指导教师工号排序请输入3，输入其他数字无效\n");
	int branch;
	STUDENT *p; 
	while(branch != 1 && branch != 2 && branch != 3)
	{
		scanf("%d",&branch);
		gets(c);
	}
	if(branch == 1)
	{
		ID_Sort();//排序 
		save();//将排序结果保存至文件 
		//将排序结果打印在显示器 
		printf("%s\n",buf);
		for(p=head;p;p=p->next) _Print(p);
	}
	else if(branch == 2)
	{
		grades_Sort();
		save();
		printf("%s\n",buf);
		for(p=head;p;p=p->next) _Print(p);
	}
	else if(branch == 3)
	{
		instructornum_Sort();
		save();
		printf("%s\n",buf);
		for(p=head;p;p=p->next) _Print(p);
	}
	else
	{
		printf("程序出错了...\n");
	}
	c_or_r();//继续排序操作或回到操作界面 
}

//用学号排序 
void ID_Sort()
{
	int min;
	STUDENT *p;
	STUDENT *q;
	STUDENT *temp;
	STUDENT *t = (STUDENT *)malloc(sizeof(STUDENT));//使用指针才能使用STUDENT_copy函数 
	for(p=head;p;p = p->next)//将最小的放在第一个，第二小的放在第二个 
	{
		min = p->ID;
		temp = p;
		for(q = p->next;q;q = q->next)//找到从本位置往后 最小的 
		{
			if(q->ID < min)
			{
				min = q->ID;
				temp =q;
			}
		}
		if( p!=temp )	//当本位置储存的毕设信息ID刚好是本位置往后里面最小的时不需要交换 
		{	
			STUDENT_copy(t,p);
			STUDENT_copy(p,temp);
			STUDENT_copy(temp,t);
		}
	}
	free(t);//将申请的空间释放 
}

//把指针q指向的结构体内容拷贝到指针p指向的结构体 
void STUDENT_copy(STUDENT *p,STUDENT *q)
{
	p->ID = q->ID;
	p->INSTRUCTOR_NUM = q->INSTRUCTOR_NUM;
	strcpy(p->CLASS,q->CLASS);
	strcpy(p->GRADES,q->GRADES);
	strcpy(p->INSTRUCTOR_TITLE,q->INSTRUCTOR_TITLE);
	strcpy(p->MAJOR,q->MAJOR);
	strcpy(p->TOPIC,q->TOPIC);
	strcpy(p->TOPIC_CLASSIFICATION,q->TOPIC_CLASSIFICATION);
	strcpy(p->WHE,q->WHE);
}

//成绩排序  优，良，中，及格
void grades_Sort()
{
	STUDENT *p,*q;
	int a[4]={0};  
	grades_Count(a);//利用函数统计各成绩人数 
	STUDENT *t = (STUDENT *)malloc(sizeof(STUDENT));
//	printf("%d %d %d %d\n",a[0],a[1],a[2],a[3]);
	int x=1;
	p = head;
	for(x=1;x<=a[0];p=p->next,x++) 
	{
		if(strcmp(p->GRADES,"优"))//不等于0 
		{
			for(q=p->next;q;q=q->next)
			{
				if(!strcmp(q->GRADES,"优"))//等于0 
				{
					STUDENT_copy(t,p);
					STUDENT_copy(p,q);
					STUDENT_copy(q,t);
					break;
				} 
			}
		}
	}
	
	for(x=1;x<=a[1];p=p->next,x++)
	{
		if(strcmp(p->GRADES,"良"))//不等于0 
		{
			for(q=p->next;q;q=q->next)
			{
				if(!strcmp(q->GRADES,"良"))//等于0 
				{
					STUDENT_copy(t,p);
					STUDENT_copy(p,q);
					STUDENT_copy(q,t);
					break;
				} 
			}
		}
	}
	
	for(x=1;x<=a[2];p=p->next,x++)
	{
		if(strcmp(p->GRADES,"中"))//不等于0 
		{
			for(q=p->next;q;q=q->next)
			{
				if(!strcmp(q->GRADES,"中"))//等于0 
				{
					STUDENT_copy(t,p);
					STUDENT_copy(p,q);
					STUDENT_copy(q,t);
					break;
				} 
			}
		}
	}
	
	for(x=1;x<=a[3];p=p->next,x++)
	{
		if(strcmp(p->GRADES,"及格"))//不等于0 
		{
			for(q=p->next;q;q=q->next)
			{
				if(!strcmp(q->GRADES,"及格"))//等于0 
				{
					STUDENT_copy(t,p);
					STUDENT_copy(p,q);
					STUDENT_copy(q,t);
					break;
				} 
			}
		}
	}
	free(t);
}

//按指导教师教工号排序 
void instructornum_Sort()
{
	int min;
	STUDENT *temp;
	STUDENT *p,*q;
	STUDENT *t = (STUDENT *)malloc(sizeof(STUDENT));
	for(p = head;p;p=p->next)//教工号最小的放在第一个 
	{
		min  = p->INSTRUCTOR_NUM;
		temp = p;
		for(q=p->next;q;q=q->next)
		{
			if(q->INSTRUCTOR_NUM < min)//若教工号相同则不必交换 
			{
				min  = q->INSTRUCTOR_NUM;
				temp = q;
			}
		}
		if(p != temp)
		{
			STUDENT_copy(t,p);
			STUDENT_copy(p,temp);
			STUDENT_copy(temp,t);
		}
	}
	free(t);
}

//按指导教师工号，按学号，按成绩，也可以是组合的方式查询
void Inquire()
{
	int w=0,a=0;
	STUDENT compare; 
	STUDENT *p,*q;
	copy();
	printf("欢迎来到查询界面\n\
请添加信息以查询\n");
//	for(p=h;p;p=p->next) _Print(p);
	while(w != -1)
	{
		printf("请输入1添加学生学号\n\
请输入2添加学生班级\n\
请输入3添加学生专业\n\
请输入4添加学生毕设题目\n\
请输入5添加学生成绩\n\
请输入6添加学生指导教师教工号\n\
请输入7添加学生指导教师职称\n\
请输入8添加学生毕设题目分类\n\
请输入9添加学生毕设是否在实践中完成\n");
		a=0;
		scanf("%d",&a);
		gets(c);
		switch (a)//判断用户要添加的查询要求是什么 
		{
			case 1:
				printf("请输入学生学号\n");
				scanf("%d",&compare.ID);
				gets(c);
				for(p=h;p != NULL;)
				{
					if(p->ID != compare.ID)
					{
						q=p;
						p=p->next;
						cut(q);
					}	
					else
					{
						p=p->next;
					}
				}
				break;
				
			case 2:
				printf("请按'16软件工程2'格式输入学生班级\n");
				scanf("%s",&compare.CLASS);
				for(p=h;p != NULL;)
				{
					if(strcmp(compare.CLASS,p->CLASS))
					{
						q=p;
						p=p->next;
						cut(q);
					}			
					else
					{
						p=p->next;
					}		
				}
				break;
				
			case 3:
				printf("请输入学生专业\n");
				scanf("%s",&compare.MAJOR);
				for(p=h;p != NULL;)
				{
					if(strcmp(compare.MAJOR,p->MAJOR))
					{
						q=p;
						p=p->next;
						cut(q);
					}		
					else
					{
						p=p->next;
					}			
				}
			
				break;
				
			case 4:
				printf("请输入学生毕设题目\n");
				scanf("%s",&compare.TOPIC);
				for(p=h;p != NULL;)
				{
					if(strcmp(compare.TOPIC,p->TOPIC))
					{
						q=p;
						p=p->next;
						cut(q);
					}		
					else
					{
						p=p->next;
					}		
				}
				break;
				
			case 5:
				printf("请输入学生成绩\n");
				scanf("%s",&compare.GRADES);
				for(p=h;p != NULL;)
				{
					if(strcmp(compare.GRADES,p->GRADES))
					{
						q=p;
						p=p->next;
						cut(q);
					}				
					else
					{
						p=p->next;
					}
				}
			
				break;
				
			case 6:
				printf("请输入学生指导教师教工号\n");
				scanf("%d",&compare.INSTRUCTOR_NUM);
				gets(c);
				for(p=h;p != NULL;)
				{
					if(compare.INSTRUCTOR_NUM != p->INSTRUCTOR_NUM)
					{
						q=p;
						p=p->next;
						cut(q);
					}	
					else
					{
						p=p->next;
					}			
				}
				break;
				
			case 7:
				printf("请输入学生指导教师职称\n");
				scanf("%s",&compare.INSTRUCTOR_TITLE);
				for(p=h;p != NULL;)
				{
					if(strcmp(compare.INSTRUCTOR_TITLE,p->INSTRUCTOR_TITLE))
					{
						q=p;
						p=p->next;
						cut(q);
					}		
					else
					{
						p=p->next;
					}			
				}
				break;
				
			case 8:
				printf("请输入学生毕设题目分类\n");
				scanf("%s",&compare.TOPIC_CLASSIFICATION);
				for(p=h;p != NULL;)
				{
					if(strcmp(compare.TOPIC_CLASSIFICATION,p->TOPIC_CLASSIFICATION))
					{
						q=p;
						p=p->next;
						cut(q);
					}		
					else
					{
						p=p->next;
					}			
				}
				break;
				
			case 9:
				printf("请输入学生毕设是否在实践中完成,输入’是‘或’否‘\n");
				scanf("%s",&compare.WHE);
				for(p=h;p != NULL;)
				{
					if(strcmp(compare.WHE,p->WHE))
					{
						q=p;
						p=p->next;
						cut(q);
					}	
					else
					{
						p=p->next;
					}				
				}
				break;
			
			default: 
				break ; 
		}	
		printf("继续添加其他信息请输入任意数字，否则输入-1\n");
		scanf("%d",&w);
		gets(c);	 
	}
	if(h!=NULL)//如果存在符合要求的毕设信息则全部打印 
	{
		printf("%s\n",buf);
		for(p=h;p;p=p->next) _Print(p);
	}
	else if(h == NULL)//如果不存在则提示未找到 
	{
		printf("未找到对应信息！\n");
	}
	//把h链表内存空间释放 
	for(p = h;p;p = q)
	{
		q = p->next;
		free(p);
	}
	
	c_or_r();//继续查询或回到操作界面 
}

//创建以STUDENT *h为头的暂用链表，将原始链表的内容复制到暂用链表 
void copy()
{
	STUDENT *p,*q;
	STUDENT *last;
	if(head != NULL)//判断原始链表的头不为空 
	{
		//创建暂用链表的第一节 
		h = (STUDENT *)malloc(sizeof(STUDENT));
		
		h->ID = head->ID;
		strcpy(h->CLASS,head->CLASS);
		strcpy(h->MAJOR,head->MAJOR);
		strcpy(h->TOPIC,head->TOPIC);
		strcpy(h->GRADES,head->GRADES);
		h->INSTRUCTOR_NUM = head->INSTRUCTOR_NUM;
		strcpy(h->INSTRUCTOR_TITLE,head->INSTRUCTOR_TITLE);
		strcpy(h->TOPIC_CLASSIFICATION,head->TOPIC_CLASSIFICATION);
		strcpy(h->WHE,head->WHE);
		
		h->next = NULL;
		last = h;
		
		//将原始链表的头后面的每一节读入 
		for(p = head->next; p; p=p->next)
		{
			q=(STUDENT *)malloc(sizeof(STUDENT));
			last->next = q;
			
			q->ID = p->ID;
			strcpy(q->CLASS,p->CLASS);
			strcpy(q->MAJOR,p->MAJOR);
			strcpy(q->TOPIC,p->TOPIC);
			strcpy(q->GRADES,p->GRADES);
			q->INSTRUCTOR_NUM = p->INSTRUCTOR_NUM;
			strcpy(q->INSTRUCTOR_TITLE,p->INSTRUCTOR_TITLE);
			strcpy(q->TOPIC_CLASSIFICATION,p->TOPIC_CLASSIFICATION);
			strcpy(q->WHE,p->WHE);
			
			q->next = NULL;
			last = q;
		}
	}
	else printf("原始链表为空！\n"); 
}

//传入暂用链表要删去的那一节的指针，目的：删去暂用链表的那一节 
void cut(STUDENT *tocut)
{
	STUDENT *p;
	//如果要删去的时暂用链表的头 
	if( tocut == h)
	{	
		p=h->next;
		free(h);
		h =p;
	}
	//如果要删去的不是暂用链表的头 
	else if(tocut != h)
	{
		for(p=h; p->next != tocut; p=p->next) ;
		p->next = tocut->next;
		free(tocut);
	}	
} 

//对于成绩的统计 ，对于题目分类的统计 ，对于是否在实践中完成的统计 
void Count()
{
	printf("欢迎来到统计界面\n\
本界面提供三种统计方式：统计成绩请输入1，统计题目分类请输入2，统计是否在实践中完成请输入3\n");
	int branch;
	STUDENT *p; 
	while(branch != 1 && branch != 2 && branch != 3)
	{
		scanf("%d",&branch);
	}
	if(branch == 1)
	{
		int a[4]={0,0,0,0};
		grades_Count(a);
		printf("优	良	中	及格\n\
%d	%d	%d	%d\n",a[0],a[1],a[2],a[3]);
	}
	else if(branch == 2)
	{
		int b[5]={0};
		classification_Count(b);
		printf("工程设计类	应用研究类	软件开发类	理论研究/论文类	其它\n\
%d		%d		%d		%d		%d\n",b[0],b[1],b[2],b[3],b[4]);
	}
	else if(branch == 3)
	{
		int c[2]={0};
		whe_Count(c);
		printf("是	否\n%d	%d\n",c[0],c[1]);
	}
	else
	{
		printf("程序出错了...\n");
	}
	c_or_r();
}

//传入数组，统计各成绩人数并写入传入的数组 
void grades_Count(int a[4])
{
	STUDENT *p;
	for(p = head;p;p=p->next)
	{
		if(!strcmp(p->GRADES,"优")) a[0]++;
		if(!strcmp(p->GRADES,"良")) a[1]++;
		if(!strcmp(p->GRADES,"中")) a[2]++;
		if(!strcmp(p->GRADES,"及格")) a[3]++;
	}
}


//传入数组，统计各毕设分类人数并写入传入的数组 
void classification_Count(int b[5])
{
	STUDENT *p;
	for(p = head;p;p=p->next)
	{
		if(!strcmp(p->TOPIC_CLASSIFICATION,"工程设计类")) b[0]++;
		if(!strcmp(p->TOPIC_CLASSIFICATION,"应用研究类")) b[1]++;
		if(!strcmp(p->TOPIC_CLASSIFICATION,"软件开发类")) b[2]++;
		if(!strcmp(p->TOPIC_CLASSIFICATION,"理论研究/论文类")) b[3]++;
		if(!strcmp(p->TOPIC_CLASSIFICATION,"其它")) b[4]++;
	}
}

//传入数组，统计毕设是或否在实践中完成的人数并写入传入的数组 
void whe_Count(int c[2])
{
	STUDENT *p;
	for(p = head;p;p=p->next)
	{
		if(!strcmp(p->WHE,"是")) c[0]++;
		if(!strcmp(p->WHE,"否")) c[1]++;
	}	
}




typedef struct X
{
	int instructor_num;
	int ID[300];
	int ID_num;
	struct X *next;
}x;
x *j = NULL;
x *k = NULL;
int luck[1000] = {0};
int luck_num =0;
int pc;


//
void Sportcheck()
{
	printf("欢迎进入抽查界面！\n");
	int radom_x = 0;
	Sportcheck_init();
	STUDENT *p;
	x *q,*a;
	for(p=h;p;p=p->next)
	{
		if(!strcmp(p->GRADES,"优")) create_x(p);
	}
	Sportcheck_1();
	
	
	for(p=h;p;p=p->next)
	{
		if(!strcmp("及格",p->GRADES)) create_x(p);
	}
	Sportcheck_1();
	
	int y;
	STUDENT *o =NULL;
	do{
		y=luck_num;
		while(y < pc)
		{
			for(p=h;p;p=o)
			{
				radom_x=rand()%pc;
				luck[y] = p->ID;
				y++;
				o = p->next;
				cut(p);
			}
		}
	}while(judge());
	//存入文件 
	Sportcheck_save();
	//打印出来 
	printf("抽查结果如下\n");
	Sportcheck_print();
	
	c_or_r();
}

//
void Sportcheck_init()
{
	srand((unsigned int) time(0));
	copy();
	int total=0;
	STUDENT *p;
	for(p=head;p;p=p->next) total++;
	pc = (int)round(((double)total)/5.0);
}

void create_x(STUDENT *p)
{	
	int a;
	x *q;
	x* tlast;
	if(j == NULL)
	{
		j = (x *)malloc(sizeof(x));	//申请链表的新一节;
		j->instructor_num = p->INSTRUCTOR_NUM;
		j->ID[0] = p->ID;
		j->ID_num = 1;
		j->next = NULL;
		k=j;
	}
	else if(j != NULL)
	{
		for(q=j;q;q=q->next)//遍历x链表 
		{
			if(q->instructor_num == p->INSTRUCTOR_NUM)//如果指导教师相同 
			{
				q->ID[q->ID_num] = p->ID;//将该ID存入该指导教师的这个结构体中 
				q->ID_num++;
				break;
			}
		}
		if(q == NULL)//如果链表中没有存有这个ID的指导教师 
		{
			tlast = (x *)malloc(sizeof(x));	//申请链表的新一节
			// 初始化申请的这节 
			tlast->instructor_num = p->INSTRUCTOR_NUM;
			tlast->ID[0] = p->ID;
			tlast->ID_num = 1;
			tlast->next = NULL;
			//链入链表 
			k->next = tlast;
			k = tlast;
		}
	}
}


//
STUDENT *h_traverse(int ID)
{
	STUDENT *p;
	for(p=h;p;p=p->next)
	{
		if(p->ID == ID)
		{
			break;
		}
	}
	return p;
}

void Sportcheck_1()
{
	STUDENT *p;
	x *q,*a;
	int radom_x;
	for(q=j;q;q=q->next)
	{
		radom_x =rand()%((q->ID_num));
		if(q->ID_num>1) radom_x =rand()%((q->ID_num)-1);
//		printf("%d\n",radom_x);
		luck[luck_num] = q->ID[radom_x];
		luck_num++;
		//遍历h找到链表h中ID对应指针
		p = h_traverse(q->ID[radom_x]);
		cut(p); //这里可能出问题了？ 
	}
	for(q = j;q;q = a)
	{
		a = q->next;
		free(q);
	}
}

int judge()
{
	int a=0;
	STUDENT *t;
	int max,min;
	
	int b[2];
	for(;a<pc;a++)
	{
		t = traverse(luck[a]);
		if(!strcmp(t->GRADES,"良")) b[0]++;
		else if(!strcmp(t->GRADES,"中")) b[1]++;
	}
	if(b[0]-b[1]>2 || b[0]-b[1]<-2) return 0;
	
	// 
	int c[6];
	for(a=0;a<pc;a++)
	{
		t = traverse(luck[a]);
		if(!strcmp(t->GRADES,"16计算机科学与技术1")) c[0]++;
		else if(!strcmp(t->GRADES,"16计算机科学与技术2")) c[1]++;
		else if(!strcmp(t->GRADES,"16软件工程1")) c[2]++;
		else if(!strcmp(t->GRADES,"16软件工程2")) c[3]++;
		else if(!strcmp(t->GRADES,"16网络工程1")) c[4]++;
		else if(!strcmp(t->GRADES,"16网络工程2")) c[5]++;
	}
	//找到最大和最小
	min=c[0];
	max=c[0];
	for(a=1;a<5;a++)
	{
		if(c[a]<min) min=c[a];
		if(c[a]>max) max=c[a]; 
	} 
	//比较
	if(max-min>2) return 0; 
	
	//应用x 的jk链表 
	copy();
	for(a=0;a<pc;a++)
	{
		t = traverse(luck[a]);
		//如果t指向的结构体的教师已存在则找到存入
		create_x(t); 
	}
	//找到最大和最小
	min=j->ID_num;
	max=j->ID_num;
	x *p,*q;
	for(p=j;j;j=j->next)
	{
		if(p->ID_num<min) min = p->ID_num;
		if(p->ID_num>max) max = p->ID_num;
	} 
	for(p = j;p;p = q)
	{
		q = p->next;
		free(p);
	}
	//比较
	if(max-min>2) return 0; 
	
	return 1;
} 

void Sportcheck_save()
{
	FILE *fp;
	STUDENT *t;
	int a;
	fp = fopen("毕业设计信息抽查.txt","w");
	if(fp == NULL)
	{
		printf("文件打开失败!\n");
		return ;
	}
	fprintf(fp,"%s\n",buf);
	for(;a<luck_num;a++)
	{
		t=traverse(luck[a]);
		fprintf(fp,"%d ",t->ID);
		fprintf(fp,"%-20s ",t->CLASS);
		fprintf(fp,"%-16s ",t->MAJOR);
		fprintf(fp,"%-62s ",t->TOPIC);
		fprintf(fp,"%-4s ",t->GRADES);
		fprintf(fp,"%d ",t->INSTRUCTOR_NUM);
		fprintf(fp,"%-12s ",t->INSTRUCTOR_TITLE);
		fprintf(fp,"%-16s ",t->TOPIC_CLASSIFICATION);
		fprintf(fp,"%s",t->WHE);
		if(a != luck_num-1) fprintf(fp,"%\n");//在文件的末尾不多余换行
	}
	fclose(fp);
}

void Sportcheck_print()
{
	int a; 
	STUDENT *t;
	printf("%s\n",buf);
	for(a=0;a<pc;a++)
	{
		t=traverse(luck[a]);
		if(t != NULL)
		{
			printf("%d ",t->ID);
			printf("%-20s ",t->CLASS);
			printf("%-16s ",t->MAJOR);
			printf("%-62s ",t->TOPIC);
			printf("%-4s ",t->GRADES);
			printf("%d ",t->INSTRUCTOR_NUM);
			printf("%-12s ",t->INSTRUCTOR_TITLE);
			printf("%-16s ",t->TOPIC_CLASSIFICATION);
			printf("%s\n",t->WHE);
		}
	}
}
