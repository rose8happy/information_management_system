//��ҵ�����Ϣ����ϵͳ�������ʵ�� 
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<time.h> 
#include<math.h>
//����һ��ѧ���ĸ��������Ϣ������һ�𣬲�ͬѧ���佨������ 
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
 
STUDENT *last = NULL;	//ԭʼ�����β 
STUDENT *head = NULL;	//ԭʼ�����ͷ 

STUDENT *h = NULL;	//���������ͷ 

STUDENT *sc = NULL;	//��������ͷ
 
int ll = 0;	//�����жϴ��ĸ��ļ�
 
char buf[1024];	//���������Ϣ����С���� 
char c[1024];	//��Ҫ��������ֺ���gets��������ֹ�û�������������������� 

enum InterFace {start, operate, view,  add, modify, strikeout, sort, inquire, count, sportcheck, end} interFace;
//     �ֱ��ʾ ��ʼ    ����    �鿴  ���   �޸�     ɾ��     ����   ��ѯ     ͳ��   ���       ����   �Ľ��� 
//����֣�����  ����дinterface??? 

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
	Welcome();//��ӭ���� 
	interFace = start;//��ʼ��interFace 
	
	while(interFace != end)
	{
		show();
	}
	
	End();//���� 
	
	return 0;
} 

//�����ļ���һ��Ҳ��һ��ѧ���ı��������Ϣ 
void _Read(FILE *fp,STUDENT *p,int number)
{
	char temp[1024];
		
	p->ID   = number;//�������number����ID 
	fscanf(fp,"%s",&p->CLASS);
	fscanf(fp,"%s",&p->MAJOR);
	
	fscanf(fp,"%s",&p->TOPIC);
	fscanf(fp,"%s",&temp);
	// ��Ϊ������Ŀ�ڿ����пո��ļ��б�����Ŀ��ɼ��ļ��Ҳ�����ÿո��ʾ���ʶ�ȡ����ֱ�������ɼ�Ϊֹ 
	while(strcmp(temp,"����") &&  strcmp(temp,"��") && strcmp(temp,"��") && strcmp(temp,"��"))//ȫ����ͬ 
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

//��ӡһ��ѧ���ı��������Ϣ��һ�� 
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

//��ʼ���棬ѡ���ȡȫ�����������Ϣ���ļ�������ԭʼ���������������в��� 
int Start()
{
	//�����������ļ�����ԭ��������ռ��ͷ� 
	End();
	 
	int number;	//���ڶ���ѧ��ѧ�� 
	STUDENT *p;	//����ָ�������µ�һ�� 
	//Ҫ���û�ѡ����ĸ��ļ� 
	printf("��ӭ���뿪ʼ����\n\
������1ѡ������б�����Ϣ���в���������2ѡ��Գ��ı�����Ϣ���в���,��������������Ч\n");
	while(ll!= 1 && ll!= 2) 
	{
		scanf("%d",&ll);
		gets(c);
	}
	//���ļ� 
	FILE *fp; 
	if(ll == 1)	fp = fopen("��ҵ�����Ϣ.txt","r");
	else if(ll == 2) fp = fopen("��ҵ�����Ϣ���.txt","r");
	if(fp == NULL)//�����ܴ��ļ�����ʾ�������½���start���� 
	{
		printf("The file can not be opened.\n");
		system("pause");
		ll = 0; 
		return -1;
	}

	fscanf(fp,"%[^\n]",buf);
	
	last = (STUDENT*)malloc(sizeof(STUDENT));  
	if(fscanf(fp,"%d",&number) == EOF)//���ļ�Ϊ�� ����ʾ�������½���start���� 
	{
		printf("�ļ������ˣ�\n");
		system("pause");
		ll = 0;
		return -1;
	}
	//�������ݽ�ԭʼ�����ͷ 
	_Read(fp,last,number);
	head = last;
	
	//������������ֱ���ļ�ĩβ 
	while(fscanf(fp,"%d",&number)!=EOF)
	{
		p = (STUDENT*)malloc(sizeof(STUDENT)); 
		_Read(fp,p,number);
		last->next = p;
		last = p;
	}
	
	fclose(fp);
	save();//���ļ������ݹ淶���� 
	interFace = operate; 
	return 0;
}

//�ͷ�ԭʼ�����ȫ���ռ� 
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


//����interFace��ֵ�жϽ���������� 
void show()
{
//enum InterFace {welcome, operate, view, add, modify, strikeout, sort, inquire, count, sportcheck, end} interFace;
	system("cls");//�����Ļ 
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

//�ڶ�ԭʼ������в����󽫲����������ļ� 
void save() 
{
	STUDENT *p;
	FILE *fp;
	if(ll == 1)	fp = fopen("��ҵ�����Ϣ.txt","w");
	else if(ll == 2)	fp = fopen("��ҵ�����Ϣ���.txt","w");
	if(fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
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
		if(last != p) fprintf(fp,"%\n");//���ļ���ĩβ�����໻�� 
	} 
	fclose(fp);
}

//����Add()������ԭʼ����ĩβ���һ�غ���ļ�����ͬ����������Add�����б�save����Ч�ʸ��� 
void fAppend()
{
	FILE *fp;
	if(ll == 1)	fp = fopen("��ҵ�����Ϣ.txt","a+");
	else if(ll == 2)	fp = fopen("��ҵ�����Ϣ���.txt","a+");
	if(fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
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

//�������ܽ��ܣ�����ID�����ض�Ӧԭʼ����ṹ���ָ�� ,�Ҳ����Ļ�����NULL 
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


//���ڸ���������ɲ�����Ҫ���û�����1���ı�interFace�ٴν���ý��棬��������2�ص��������� 
void c_or_r()
{
	printf("����������ѧ��������Ϣ���и������������1���ص���������������2����������������Ч\n");
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
		printf("��������ˣ�\n");
	}
}

//��ӭ�û�����ϵͳ 
void Welcome()
{
	printf("��ӭ������ҵ�����Ϣ����ϵͳ��\n\
���ڼ�������'a'�������ϵͳ\n");
	char c = '\0';
	while(c != 'a')scanf("%c",&c);
	{
		scanf("%c",&c);
	}
	interFace = operate;
}

//�������� 
void Operate()
{
	printf("��ӭ�������ϵͳ!\n\
��ѡ�����²���\n\
�鿴���б�����Ϣ������1\n\
���ӱ�����Ϣ������2\n\
�޸ı�����Ϣ: ����3 (���ס��Ҫ�޸ı�����Ϣ��ѧ��ѧ��)\n\
ɾ��������Ϣ: ����4 (���ס��Ҫ�޸ı�����Ϣ��ѧ��ѧ��)\n\
���������Ϣ������5\n\
��ѯ������Ϣ������6\n\
ͳ�Ʊ�����Ϣ: ����7\n\
���뿪ʼ����: ����8\n\
�˳�������Ϣ����ϵͳ: ����9\n");
if(ll == 1) printf("��������Ϣ: ����10\n");//��ll==2�༴���ļ�Ϊ����ҵ�����Ϣ���.txt��ʱ�����ٽ��г����� 
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
			ll = 0;//��ll����Ϊ0 
			
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

//�鿴ԭʼ����ȫ��������Ϣ 
void View()
{
	STUDENT *p;
	printf("%s\n",buf);
	for(p = head; p;p =p->next)	_Print(p);
	printf("���ڼ�������b���ز�������\n");
	char c;
	while(c != 'b')
	{
		scanf("%c",&c);
	}
	interFace = operate;
}

//��ӱ�����Ϣ 
void Add()
{
	STUDENT *p;
	STUDENT *q;
	STUDENT *temp = (STUDENT *)malloc(sizeof(STUDENT));
	int w = 0;
	printf("Ϊ��ӱ�����Ϣ������������������Ϣ\n");
	printf("������ѧ��ѧ��\n");
	while(w != -1)
	{
		char c[1024];
		temp->ID = 0;
		scanf("%d",&temp->ID);
		gets(c); 
		if(temp->ID == 0) printf("��δ�������֣�����������ѧ��ѧ��\n");
		else if(traverse(temp->ID) != NULL) //�ж�Ҫ��ӵı�����ϢID�Ƿ���� 
		{									//��������Ҫ��������������ѧ�� 
			int t=0;
			printf("�������ѧ��ѧ���Ѵ���\
������1�ص���������ѡ���޸��������Ϣ,���������������ֺ������������ѧ��\n");
			scanf("%d",&t);
			if (t == 1) //ֱ�ӻص��������� 
			{
				interFace = operate;
				return ;
			} 
		}
		else
		{
			printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ��ѧ��\n");
			scanf("%d",&w);
		} 
	}
	w = 0;
	printf("�밴��16�������1�ĸ�ʽ������ѧ���༶\n");
	while(w != -1)
	{
		scanf("%s",&temp->CLASS);
		printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ���༶\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("������ѧ��רҵ\n");
	while(w != -1)
	{
		scanf("%s",&temp->MAJOR);
		printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ��רҵ\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("������ѧ����ҵ�����Ŀ\n");
	while(w != -1)
	{
		scanf("%s",&temp->TOPIC);
		printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ��������Ŀ\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("������ѧ����ҵ��Ƴɼ����ţ������л򼰸�\n");
	while(w != -1)
	{
		scanf("%s",&temp->GRADES);
		printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ������ɼ�\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("������ѧ����ҵ���ָ����ʦ����\n");
	while(w != -1)
	{
		scanf("%d",&temp->INSTRUCTOR_NUM);
		printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ������ָ����ʦ����\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("������ѧ����ҵ���ָ����ʦְ��\n");
	while(w != -1)
	{
		scanf("%s",&temp->INSTRUCTOR_TITLE);
		printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ������ָ����ʦְ��\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("������ѧ����ҵ�����Ŀ����\n");
	while(w != -1)
	{
		scanf("%s",&temp->TOPIC_CLASSIFICATION);
		printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ��������Ŀ����\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ������� �������ǻ��\n");
	while(w != -1)
	{
		scanf("%s",&temp->WHE);
		printf("ȷ��������ȷ��������-1,���������������ּ��������ǻ��\n");
		scanf("%d",&w);
	}
	w = 0;
	printf("�����ȷ���Ƿ�ȫ��������ȷ\n\
��ȫ��������ȷ������-1�Ա�������ı�����Ϣ\n\
���������������ֲ���������ı�����Ϣ\n");
	while(w == 0)
	{
		scanf("%d",&w);
		gets(c);
	}
	if(w == -1)
	{
		//����ӵı�����Ϣ������ԭʼ����ĩβ����Ҫ�Ļ����Խ���sort�������� 
		last->next = temp;
		temp->next = NULL;
		last       = temp;	
		//����ӵı�����Ϣ�������ļ�ĩβ 
		fAppend();
	}
	else free(temp);
	c_or_r();//���ز�����������½�����ӽ��棬������ӱ�����Ϣ 
} 

//�޸Ľ��� 
void Modify()
{
	int a=0;
	int w=0;
	STUDENT *select;
	printf("��ӭ�����޸Ľ���\n\
��������Ҫ�޸ı�����Ϣ��ѧ��ѧ��\n");
	if(select = Confirm_ID())
	{
		while(w != -1)
		{
			printf("������1�޸�ѧ��ѧ��\n\
������2�޸�ѧ���༶\n\
������3�޸�ѧ��רҵ\n\
������4�޸�ѧ��������Ŀ\n\
������5�޸�ѧ���ɼ�\n\
������6�޸�ѧ��ָ����ʦ�̹���\n\
������7�޸�ѧ��ָ����ʦְ��\n\
������8�޸�ѧ��������Ŀ����\n\
������9�޸�ѧ�������Ƿ���ʵ�������\n");
			a=0;
			scanf("%d",&a);
			gets(c);
			switch (a)
			{
				case 1:
					printf("������ѧ��ѧ��\n");
					scanf("%d",&select->ID);
					gets(c);
					break;
					
				case 2:
					printf("�밴'16�������2'��ʽ����ѧ���༶\n");
					scanf("%s",&select->CLASS);				
					break;
					
				case 3:
					printf("������ѧ��רҵ\n");
					scanf("%s",&select->MAJOR);					
					break;
					
				case 4:
					printf("������ѧ��������Ŀ\n");
					scanf("%s",&select->TOPIC);			
					break;
					
				case 5:
					printf("������ѧ���ɼ�\n");
					scanf("%s",&select->GRADES);					
					break;
					
				case 6:
					printf("������ѧ��ָ����ʦ�̹���\n");
					scanf("%d",&select->INSTRUCTOR_NUM);	
					gets(c);				
					break;
					
				case 7:
					printf("������ѧ��ָ����ʦְ��\n");
					scanf("%s",&select->INSTRUCTOR_TITLE);					
					break;
					
				case 8:
					printf("������ѧ��������Ŀ����\n");
					scanf("%s",&select->TOPIC_CLASSIFICATION);					
					break;
					
				case 9:
					printf("������ѧ�������Ƿ���ʵ�������,���롯�ǡ��򡯷�\n");
					scanf("%s",&select->WHE);					
					break;
					
				default :
					;
					break;
			}	
			printf("�����޸�������Ϣ�������������֣���������-1\n");
			scanf("%d",&w);
			gets(c);	 
		}
		save();//���޸Ľ���������ļ� 
		c_or_r();
	} 
}

//ɾ������ 
void Strikeout() 
{
	STUDENT *select;
	printf("��ӭ����ɾ������\n\
��������Ҫɾ��������Ϣ��ѧ��ѧ��\n");
	if(select = Confirm_ID())
	{
		STUDENT *p;
		//���Ҫɾ�����������ͷ 
		if(select == head)
		{
			p=head->next;
			free(head);
			head = p;
		}
		//���Ҫɾ���Ĳ��������ͷ 
		else if(select != head)
		{
			for(p=head;p->next = select;p=p->next) ; 
			p->next = select->next;
			free(select);
		} 
		save();//��ɾ������������ļ� 
		c_or_r();
	}
}

// ����������ʾѧ����Ϣ������ԭʼ��������ָ�룬���в��������򷵻�0�������в���
//ͬtraverse������ȶ��˴�ӡ������ʾ�û� 
STUDENT* Confirm_ID()
{
	int w = 0;
	int ID; 
	STUDENT *p;
	while(w != -1)
	{
		scanf("%d",&ID);;
		gets(c);
		printf("ȷ��������ȷ��������-1,���������������ּ�������ѧ��ѧ��\n");
		scanf("%d",&w);
		gets(c);
	}
	p = traverse(ID);
	if(p == NULL)
	{
		printf("��Ҫ���в�����ѧ��������Ϣ������\n");
		c_or_r();
		return NULL;
	}
	else if(p != NULL)
	{
		printf("%s\n",buf);
		_Print(p);
		return p;
	}
	else printf("��������ˣ�\n");
}

//������棬��ѡ��ѧ�š��ɼ���ָ����ʦ�������� 
void Sort()
{
	printf("��ӭ�����������\n\
�������ṩ��������ʽ����ѧ������������1�����ɼ�����������2����ָ����ʦ��������������3����������������Ч\n");
	int branch;
	STUDENT *p; 
	while(branch != 1 && branch != 2 && branch != 3)
	{
		scanf("%d",&branch);
		gets(c);
	}
	if(branch == 1)
	{
		ID_Sort();//���� 
		save();//���������������ļ� 
		//����������ӡ����ʾ�� 
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
		printf("���������...\n");
	}
	c_or_r();//�������������ص��������� 
}

//��ѧ������ 
void ID_Sort()
{
	int min;
	STUDENT *p;
	STUDENT *q;
	STUDENT *temp;
	STUDENT *t = (STUDENT *)malloc(sizeof(STUDENT));//ʹ��ָ�����ʹ��STUDENT_copy���� 
	for(p=head;p;p = p->next)//����С�ķ��ڵ�һ�����ڶ�С�ķ��ڵڶ��� 
	{
		min = p->ID;
		temp = p;
		for(q = p->next;q;q = q->next)//�ҵ��ӱ�λ������ ��С�� 
		{
			if(q->ID < min)
			{
				min = q->ID;
				temp =q;
			}
		}
		if( p!=temp )	//����λ�ô���ı�����ϢID�պ��Ǳ�λ������������С��ʱ����Ҫ���� 
		{	
			STUDENT_copy(t,p);
			STUDENT_copy(p,temp);
			STUDENT_copy(temp,t);
		}
	}
	free(t);//������Ŀռ��ͷ� 
}

//��ָ��qָ��Ľṹ�����ݿ�����ָ��pָ��Ľṹ�� 
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

//�ɼ�����  �ţ������У�����
void grades_Sort()
{
	STUDENT *p,*q;
	int a[4]={0};  
	grades_Count(a);//���ú���ͳ�Ƹ��ɼ����� 
	STUDENT *t = (STUDENT *)malloc(sizeof(STUDENT));
//	printf("%d %d %d %d\n",a[0],a[1],a[2],a[3]);
	int x=1;
	p = head;
	for(x=1;x<=a[0];p=p->next,x++) 
	{
		if(strcmp(p->GRADES,"��"))//������0 
		{
			for(q=p->next;q;q=q->next)
			{
				if(!strcmp(q->GRADES,"��"))//����0 
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
		if(strcmp(p->GRADES,"��"))//������0 
		{
			for(q=p->next;q;q=q->next)
			{
				if(!strcmp(q->GRADES,"��"))//����0 
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
		if(strcmp(p->GRADES,"��"))//������0 
		{
			for(q=p->next;q;q=q->next)
			{
				if(!strcmp(q->GRADES,"��"))//����0 
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
		if(strcmp(p->GRADES,"����"))//������0 
		{
			for(q=p->next;q;q=q->next)
			{
				if(!strcmp(q->GRADES,"����"))//����0 
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

//��ָ����ʦ�̹������� 
void instructornum_Sort()
{
	int min;
	STUDENT *temp;
	STUDENT *p,*q;
	STUDENT *t = (STUDENT *)malloc(sizeof(STUDENT));
	for(p = head;p;p=p->next)//�̹�����С�ķ��ڵ�һ�� 
	{
		min  = p->INSTRUCTOR_NUM;
		temp = p;
		for(q=p->next;q;q=q->next)
		{
			if(q->INSTRUCTOR_NUM < min)//���̹�����ͬ�򲻱ؽ��� 
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

//��ָ����ʦ���ţ���ѧ�ţ����ɼ���Ҳ��������ϵķ�ʽ��ѯ
void Inquire()
{
	int w=0,a=0;
	STUDENT compare; 
	STUDENT *p,*q;
	copy();
	printf("��ӭ������ѯ����\n\
�������Ϣ�Բ�ѯ\n");
//	for(p=h;p;p=p->next) _Print(p);
	while(w != -1)
	{
		printf("������1���ѧ��ѧ��\n\
������2���ѧ���༶\n\
������3���ѧ��רҵ\n\
������4���ѧ��������Ŀ\n\
������5���ѧ���ɼ�\n\
������6���ѧ��ָ����ʦ�̹���\n\
������7���ѧ��ָ����ʦְ��\n\
������8���ѧ��������Ŀ����\n\
������9���ѧ�������Ƿ���ʵ�������\n");
		a=0;
		scanf("%d",&a);
		gets(c);
		switch (a)//�ж��û�Ҫ��ӵĲ�ѯҪ����ʲô 
		{
			case 1:
				printf("������ѧ��ѧ��\n");
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
				printf("�밴'16�������2'��ʽ����ѧ���༶\n");
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
				printf("������ѧ��רҵ\n");
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
				printf("������ѧ��������Ŀ\n");
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
				printf("������ѧ���ɼ�\n");
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
				printf("������ѧ��ָ����ʦ�̹���\n");
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
				printf("������ѧ��ָ����ʦְ��\n");
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
				printf("������ѧ��������Ŀ����\n");
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
				printf("������ѧ�������Ƿ���ʵ�������,���롯�ǡ��򡯷�\n");
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
		printf("�������������Ϣ�������������֣���������-1\n");
		scanf("%d",&w);
		gets(c);	 
	}
	if(h!=NULL)//������ڷ���Ҫ��ı�����Ϣ��ȫ����ӡ 
	{
		printf("%s\n",buf);
		for(p=h;p;p=p->next) _Print(p);
	}
	else if(h == NULL)//�������������ʾδ�ҵ� 
	{
		printf("δ�ҵ���Ӧ��Ϣ��\n");
	}
	//��h�����ڴ�ռ��ͷ� 
	for(p = h;p;p = q)
	{
		q = p->next;
		free(p);
	}
	
	c_or_r();//������ѯ��ص��������� 
}

//������STUDENT *hΪͷ������������ԭʼ��������ݸ��Ƶ��������� 
void copy()
{
	STUDENT *p,*q;
	STUDENT *last;
	if(head != NULL)//�ж�ԭʼ�����ͷ��Ϊ�� 
	{
		//������������ĵ�һ�� 
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
		
		//��ԭʼ�����ͷ�����ÿһ�ڶ��� 
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
	else printf("ԭʼ����Ϊ�գ�\n"); 
}

//������������Ҫɾȥ����һ�ڵ�ָ�룬Ŀ�ģ�ɾȥ�����������һ�� 
void cut(STUDENT *tocut)
{
	STUDENT *p;
	//���Ҫɾȥ��ʱ���������ͷ 
	if( tocut == h)
	{	
		p=h->next;
		free(h);
		h =p;
	}
	//���Ҫɾȥ�Ĳ������������ͷ 
	else if(tocut != h)
	{
		for(p=h; p->next != tocut; p=p->next) ;
		p->next = tocut->next;
		free(tocut);
	}	
} 

//���ڳɼ���ͳ�� ��������Ŀ�����ͳ�� �������Ƿ���ʵ������ɵ�ͳ�� 
void Count()
{
	printf("��ӭ����ͳ�ƽ���\n\
�������ṩ����ͳ�Ʒ�ʽ��ͳ�Ƴɼ�������1��ͳ����Ŀ����������2��ͳ���Ƿ���ʵ�������������3\n");
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
		printf("��	��	��	����\n\
%d	%d	%d	%d\n",a[0],a[1],a[2],a[3]);
	}
	else if(branch == 2)
	{
		int b[5]={0};
		classification_Count(b);
		printf("���������	Ӧ���о���	���������	�����о�/������	����\n\
%d		%d		%d		%d		%d\n",b[0],b[1],b[2],b[3],b[4]);
	}
	else if(branch == 3)
	{
		int c[2]={0};
		whe_Count(c);
		printf("��	��\n%d	%d\n",c[0],c[1]);
	}
	else
	{
		printf("���������...\n");
	}
	c_or_r();
}

//�������飬ͳ�Ƹ��ɼ�������д�봫������� 
void grades_Count(int a[4])
{
	STUDENT *p;
	for(p = head;p;p=p->next)
	{
		if(!strcmp(p->GRADES,"��")) a[0]++;
		if(!strcmp(p->GRADES,"��")) a[1]++;
		if(!strcmp(p->GRADES,"��")) a[2]++;
		if(!strcmp(p->GRADES,"����")) a[3]++;
	}
}


//�������飬ͳ�Ƹ��������������д�봫������� 
void classification_Count(int b[5])
{
	STUDENT *p;
	for(p = head;p;p=p->next)
	{
		if(!strcmp(p->TOPIC_CLASSIFICATION,"���������")) b[0]++;
		if(!strcmp(p->TOPIC_CLASSIFICATION,"Ӧ���о���")) b[1]++;
		if(!strcmp(p->TOPIC_CLASSIFICATION,"���������")) b[2]++;
		if(!strcmp(p->TOPIC_CLASSIFICATION,"�����о�/������")) b[3]++;
		if(!strcmp(p->TOPIC_CLASSIFICATION,"����")) b[4]++;
	}
}

//�������飬ͳ�Ʊ����ǻ����ʵ������ɵ�������д�봫������� 
void whe_Count(int c[2])
{
	STUDENT *p;
	for(p = head;p;p=p->next)
	{
		if(!strcmp(p->WHE,"��")) c[0]++;
		if(!strcmp(p->WHE,"��")) c[1]++;
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
	printf("��ӭ��������棡\n");
	int radom_x = 0;
	Sportcheck_init();
	STUDENT *p;
	x *q,*a;
	for(p=h;p;p=p->next)
	{
		if(!strcmp(p->GRADES,"��")) create_x(p);
	}
	Sportcheck_1();
	
	
	for(p=h;p;p=p->next)
	{
		if(!strcmp("����",p->GRADES)) create_x(p);
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
	//�����ļ� 
	Sportcheck_save();
	//��ӡ���� 
	printf("���������\n");
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
		j = (x *)malloc(sizeof(x));	//�����������һ��;
		j->instructor_num = p->INSTRUCTOR_NUM;
		j->ID[0] = p->ID;
		j->ID_num = 1;
		j->next = NULL;
		k=j;
	}
	else if(j != NULL)
	{
		for(q=j;q;q=q->next)//����x���� 
		{
			if(q->instructor_num == p->INSTRUCTOR_NUM)//���ָ����ʦ��ͬ 
			{
				q->ID[q->ID_num] = p->ID;//����ID�����ָ����ʦ������ṹ���� 
				q->ID_num++;
				break;
			}
		}
		if(q == NULL)//���������û�д������ID��ָ����ʦ 
		{
			tlast = (x *)malloc(sizeof(x));	//�����������һ��
			// ��ʼ���������� 
			tlast->instructor_num = p->INSTRUCTOR_NUM;
			tlast->ID[0] = p->ID;
			tlast->ID_num = 1;
			tlast->next = NULL;
			//�������� 
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
		//����h�ҵ�����h��ID��Ӧָ��
		p = h_traverse(q->ID[radom_x]);
		cut(p); //������ܳ������ˣ� 
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
		if(!strcmp(t->GRADES,"��")) b[0]++;
		else if(!strcmp(t->GRADES,"��")) b[1]++;
	}
	if(b[0]-b[1]>2 || b[0]-b[1]<-2) return 0;
	
	// 
	int c[6];
	for(a=0;a<pc;a++)
	{
		t = traverse(luck[a]);
		if(!strcmp(t->GRADES,"16�������ѧ�뼼��1")) c[0]++;
		else if(!strcmp(t->GRADES,"16�������ѧ�뼼��2")) c[1]++;
		else if(!strcmp(t->GRADES,"16�������1")) c[2]++;
		else if(!strcmp(t->GRADES,"16�������2")) c[3]++;
		else if(!strcmp(t->GRADES,"16���繤��1")) c[4]++;
		else if(!strcmp(t->GRADES,"16���繤��2")) c[5]++;
	}
	//�ҵ�������С
	min=c[0];
	max=c[0];
	for(a=1;a<5;a++)
	{
		if(c[a]<min) min=c[a];
		if(c[a]>max) max=c[a]; 
	} 
	//�Ƚ�
	if(max-min>2) return 0; 
	
	//Ӧ��x ��jk���� 
	copy();
	for(a=0;a<pc;a++)
	{
		t = traverse(luck[a]);
		//���tָ��Ľṹ��Ľ�ʦ�Ѵ������ҵ�����
		create_x(t); 
	}
	//�ҵ�������С
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
	//�Ƚ�
	if(max-min>2) return 0; 
	
	return 1;
} 

void Sportcheck_save()
{
	FILE *fp;
	STUDENT *t;
	int a;
	fp = fopen("��ҵ�����Ϣ���.txt","w");
	if(fp == NULL)
	{
		printf("�ļ���ʧ��!\n");
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
		if(a != luck_num-1) fprintf(fp,"%\n");//���ļ���ĩβ�����໻��
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
