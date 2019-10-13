#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
#define inum 15 //���̵ĵ���ָ����
struct pageInformation
{
	int ID;     //ҳ���
	int visit;  //�����ʱ��
};

pageInformation* block;    //�����
pageInformation* page;     //�ϲ����ҳ��Ŵ�
pageInformation* oriPage;  //ԭ����inum��ָ������Ӧ��inuimҳ
int instructions[inum];      //ԭ����inum��ָ��
int pageNum; //�ϲ����ҳ����

class Pager
{
private:
	int count; //ҳ���жϴ���
	int blockNum; //ϵͳ������ڴ��
public:
	//��ʼ������inum��ָ��
	void creatInstructions()
	{
		//����256 ��ָ���ַ Instruction address  ��ַ��ΧΪ0 ��32767
		int insAdress[256];
		insAdress[0] = 10000;
		srand((unsigned)time(NULL)); //���������
		for (int i = 1; i < 256; i++)
		{
			int random = rand() % 1024 + 1;
			if (random >= 1 && random <= 512)
			{
				insAdress[i] = insAdress[i - 1] + 1;
			}
			else if (random >= 513 && random <= 768)
			{
				random = rand() % insAdress[i - 1] + 1;
				insAdress[i] = random;
			}
			else if (random >= 769 && random <= 1024)
			{
				random = rand() % (32767 - insAdress[i - 1]) + insAdress[i - 1];
				insAdress[i] = random;
			}
		}
		//����inum��ָ��
		for (int j = 0; j < inum; j++)
		{
			int r = rand() % 256;
			instructions[j] = insAdress[r];
		}
	}
	//��ָ��ת����ҳ��
	void convertToPage(int pageSize)
	{
		oriPage = new pageInformation[inum]; //һ��ָ�����һҳ
		int num = pageSize * 1024; //ÿһҳ��ŵ�ָ������
		for (int i = 0; i < inum; i++)
		{
			oriPage[i].visit = 0;
			int a = instructions[i] / num;
			int b = instructions[i] % num;
			if (b)
				oriPage[i].ID = a;
			else
				oriPage[i].ID = a + 1;
		}
	}
	//����������ͬ��ҳ�ţ��ϲ�Ϊһ����
	void mergence()
	{
		pageNum = 0;
		page = new pageInformation[inum];
		//���˼·������ɨ��oriPage���飬��page�е����һ������Ƚϣ������ͬ��д��page����ͬ�Ͳ���д�롣
		page[0] = oriPage[0];
		for (int i = 1; i < inum; i++)
		{
			//�����ͬ��д��mergePage
			if (page[pageNum].ID != oriPage[i].ID)
			{
				pageNum++;
				page[pageNum].ID = oriPage[i].ID;
				page[pageNum].visit = oriPage[i].visit;
			}
		}
	}
	//��ʼ�������
	void creatBlock(int n)
	{
		blockNum = n;
		initalPhysicalBlock();
	}

	void initalPhysicalBlock()
	{
		block = new pageInformation[blockNum];
		BlockClear(blockNum);
	}

	//�÷���������ĳ�ֵ
	void BlockClear(int blockNum)
	{
		for (int i = 0; i < blockNum; i++)
		{
			block[i].ID = -1;
			block[i].visit = 0;
		}
	}

	//�����Ƿ��п����ڴ��
	int findSpace()
	{
		for (int i = 0; i < blockNum; i++)
			if (block[i].ID == -1)
				return i;//�ҵ������ڴ棬����BLOCK��λ��
		return -1;
	}
	//�����ڴ����Ƿ��и�ҳ��
	int findExist(int curpage)
	{
		for (int i = 0; i < blockNum; i++)
			if (block[i].ID == page[curpage].ID)
				return i;//�ҵ��ڴ����и�ҳ�棬����BLOCK��λ��
		return -1;
	}
	//����Ӧ���û���ҳ��
	int findReplace()
	{
		int pos = 0;
		for (int i = 0; i < blockNum; i++)
			if (block[i].visit > block[pos].visit)
				pos = i;//�ҵ�Ӧ���û�ҳ�棬����BLOCK��λ��
		return pos;
	}
	//��ʾ
	void display()
	{
		cout << "----------------------------" << endl;
		for (int i = 0; i < blockNum; i++)
			if (block[i].ID != -1)
				cout << block[i].ID << " ";
		cout << endl;
		cout << "----------------------------" << endl;
	}
	//FIFO�㷨
	void FIFO()
	{
		count = 0;
		int exist, space, position;
		for (int i = 0; i < pageNum; i++)
		{
			//�����ڴ����Ƿ���ڸ�ҳ
			exist = findExist(i);
			if (exist != -1)
			{
				cout << "----------------------------" << endl;
				cout << "�������ʵ���ҳ��" << page[i].ID << "----�ڴ����Ѵ��ڸ�ҳ" << endl;
				cout << "----------------------------" << endl;
			}
			//�ڴ���в����ڣ�����ȱҳ�жϵĵ���
			else
			{
				count++;//ȱҳ������һ
				space = findSpace();
				//���ڴ�����ҵ����е�λ�ã����ʱ��Ҳ��Ҫ�жϵ�
				if (space != -1)
				{
					block[space] = page[i];
					display();
				}
				else
				{
					position = 0;
					cout << "----------------------------" << endl;
					cout << "�������ʵ���ҳ��" << page[i].ID << "�����û�������ҳ��" << block[position].ID << endl;
					cout << "----------------------------" << endl;
					for(int i=position;i<blockNum;i++)
						block[i]=block[i+1];
					block[blockNum-1] = page[i];
					display();
				}
			}
			//����ҳ�����ڴ����פ����ʱ�䣬ÿһ�ζ�+1�����Խ��˵��פ��ʱ���������̭��
			for (int j = 0; j < blockNum; j++)
				block[j].visit++;//BLOCK������ҳ��visit++
		}
		cout << "ȱҳ������" << count << endl;
		cout << "FIFO�㷨��ȱҳ���ǣ�" << (float)count / pageNum << endl;
	}

	//LRU�㷨
	void LRU()
	{
		int exist, space, position;
		count = 0;
		for (int i = 0; i < pageNum; i++)
		{
			exist = findExist(i);
			if (exist != -1)
			{
				cout << "----------------------------" << endl;
				cout << "�������ʵ���ҳ��" << page[i].ID << "----�ڴ����Ѵ��ڸ�ҳ" << endl;;
				cout << "----------------------------" << endl;
				//ÿһ��ҳ�汻���ʺ����¼�ʱ
				block[exist].visit = 0;//�ָ����ڵĲ��շ��ʹ���BLOCK��ҳ��visitΪ0
			}
			else
			{
				count++;
				space = findSpace();
				if (space != -1)
				{
					block[space] = page[i];
					display();
				}
				else
				{
					position = findReplace();
					cout << "----------------------------" << endl;
					cout << "�������ʵ���ҳ��" << page[i].ID << "�����û�������ҳ��" << block[position].ID << endl;
					cout << "----------------------------" << endl;
					block[position] = page[i];
					display();
				}
			}
			//��ʱ
			for (int j = 0; j < blockNum; j++)
			{
				block[j].visit++;
			}
		}
		cout << "ȱҳ������" << count << endl;
		cout << "FIFO�㷨��ȱҳ���ǣ�" << (float)count / pageNum << endl;

	}
	//OPT�㷨
	void OPT()
	{
		int exist, space, position;
		count = 0;
		cout<<endl;
		for (int i = 0; i < pageNum; i++)
		{
			exist = findExist(i);
			//ҳ�Ѿ����ڴ����
			if (exist != -1)
			{
				cout << "----------------------------" << endl;
				cout << "�������ʵ���ҳ��" << page[i].ID << "----�ڴ����Ѵ��ڸ�ҳ" << endl;
				cout << "----------------------------" << endl;
			}
			else
			{
				count++;
				space = findSpace();
				if (space != -1)
				{
					block[space] = page[i];
					display();
				}
				else
				{
					for (int k = 0; k < blockNum; k++)
						for (int j = i; j < pageNum; j++) //�޸������j<pageNum �Ϳ��Ըı�Ԥ������ҳ���ҳ��
						{
							if (block[k].ID != page[j].ID)
							{
								block[k].visit = 2000;
							}
							else
							{
								block[k].visit = j;
								break;
							}
						}
					position = findReplace();
					cout << "----------------------------" << endl;
					cout << "�������ʵ���ҳ��" << page[i].ID << "�����û�������ҳ��" << block[position].ID << endl;
					cout << "----------------------------" << endl;
					block[position] = page[i];
					display();
				}
			}
		}
		cout << "ȱҳ������" << count << endl;
		cout << "FIFO�㷨��ȱҳ���ǣ�" << (float)count / pageNum << endl;
	}

};
int main()
{

	while (1)
	{
		int selection;
		cout << "----����������㷨��1:OPT 2:FIFO 3:LRU---->>";
		cin >> selection;
		int pSize, num;
		cout << "----������ҳ���С��(1��2��4��8��16K)��";
		cin >> pSize;
		cout << "----������ϵͳ������ڴ������";
		cin >> num;
		Pager test;
		test.creatInstructions();
		test.convertToPage(pSize);
		test.mergence();
		test.creatBlock(num);
		for(int i=0;i<pageNum;++i)
			cout<<page[i].ID<<" ";
		cout<<endl;
		if (selection == 1)
		{
			test.OPT();
		}
		else if (selection == 2)
		{
			test.FIFO();
		}
		else if (selection == 3)
		{
			test.LRU();
		}
		delete page;
		delete oriPage;
		delete block;
		cout << endl;
	}
	return 0;
}