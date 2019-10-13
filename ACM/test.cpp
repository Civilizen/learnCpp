#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
#define inum 15 //进程的调用指令数
struct pageInformation
{
	int ID;     //页面号
	int visit;  //被访问标记
};

pageInformation* block;    //物理块
pageInformation* page;     //合并后的页面号串
pageInformation* oriPage;  //原生的inum条指令所对应的inuim页
int instructions[inum];      //原生的inum条指令
int pageNum; //合并后的页面数

class Pager
{
private:
	int count; //页面中断次数
	int blockNum; //系统分配的内存块
public:
	//初始化生成inum条指令
	void creatInstructions()
	{
		//生成256 个指令地址 Instruction address  地址范围为0 到32767
		int insAdress[256];
		insAdress[0] = 10000;
		srand((unsigned)time(NULL)); //随机数种子
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
		//生成inum条指令
		for (int j = 0; j < inum; j++)
		{
			int r = rand() % 256;
			instructions[j] = insAdress[r];
		}
	}
	//将指令转换成页号
	void convertToPage(int pageSize)
	{
		oriPage = new pageInformation[inum]; //一条指令对于一页
		int num = pageSize * 1024; //每一页存放的指令条数
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
	//对于相邻相同的页号，合并为一个。
	void mergence()
	{
		pageNum = 0;
		page = new pageInformation[inum];
		//解决思路：依次扫描oriPage数组，和page中的最后一个数组比较，如果不同就写入page，相同就不用写入。
		page[0] = oriPage[0];
		for (int i = 1; i < inum; i++)
		{
			//如果不同就写入mergePage
			if (page[pageNum].ID != oriPage[i].ID)
			{
				pageNum++;
				page[pageNum].ID = oriPage[i].ID;
				page[pageNum].visit = oriPage[i].visit;
			}
		}
	}
	//初始化物理块
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

	//置分配的物理块的初值
	void BlockClear(int blockNum)
	{
		for (int i = 0; i < blockNum; i++)
		{
			block[i].ID = -1;
			block[i].visit = 0;
		}
	}

	//查找是否有空闲内存块
	int findSpace()
	{
		for (int i = 0; i < blockNum; i++)
			if (block[i].ID == -1)
				return i;//找到空闲内存，返回BLOCK中位置
		return -1;
	}
	//查找内存中是否有该页面
	int findExist(int curpage)
	{
		for (int i = 0; i < blockNum; i++)
			if (block[i].ID == page[curpage].ID)
				return i;//找到内存中有该页面，返回BLOCK中位置
		return -1;
	}
	//查找应予置换的页面
	int findReplace()
	{
		int pos = 0;
		for (int i = 0; i < blockNum; i++)
			if (block[i].visit > block[pos].visit)
				pos = i;//找到应予置换页面，返回BLOCK中位置
		return pos;
	}
	//显示
	void display()
	{
		cout << "----------------------------" << endl;
		for (int i = 0; i < blockNum; i++)
			if (block[i].ID != -1)
				cout << block[i].ID << " ";
		cout << endl;
		cout << "----------------------------" << endl;
	}
	//FIFO算法
	void FIFO()
	{
		count = 0;
		int exist, space, position;
		for (int i = 0; i < pageNum; i++)
		{
			//查找内存中是否存在该页
			exist = findExist(i);
			if (exist != -1)
			{
				cout << "----------------------------" << endl;
				cout << "即将访问的是页面" << page[i].ID << "----内存中已存在该页" << endl;
				cout << "----------------------------" << endl;
			}
			//内存块中不存在，进行缺页中断的调度
			else
			{
				count++;//缺页次数加一
				space = findSpace();
				//在内存块中找到空闲的位置，这个时候也是要中断的
				if (space != -1)
				{
					block[space] = page[i];
					display();
				}
				else
				{
					position = 0;
					cout << "----------------------------" << endl;
					cout << "即将访问的是页面" << page[i].ID << "将被置换出的是页面" << block[position].ID << endl;
					cout << "----------------------------" << endl;
					for(int i=position;i<blockNum;i++)
						block[i]=block[i+1];
					block[blockNum-1] = page[i];
					display();
				}
			}
			//计算页面在内存块中驻留的时间，每一次都+1，如果越大，说明驻留时间最长，就淘汰他
			for (int j = 0; j < blockNum; j++)
				block[j].visit++;//BLOCK中所有页面visit++
		}
		cout << "缺页次数：" << count << endl;
		cout << "FIFO算法的缺页率是：" << (float)count / pageNum << endl;
	}

	//LRU算法
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
				cout << "即将访问的是页面" << page[i].ID << "----内存中已存在该页" << endl;;
				cout << "----------------------------" << endl;
				//每一次页面被访问后，重新计时
				block[exist].visit = 0;//恢复存在的并刚访问过的BLOCK中页面visit为0
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
					cout << "即将访问的是页面" << page[i].ID << "将被置换出的是页面" << block[position].ID << endl;
					cout << "----------------------------" << endl;
					block[position] = page[i];
					display();
				}
			}
			//计时
			for (int j = 0; j < blockNum; j++)
			{
				block[j].visit++;
			}
		}
		cout << "缺页次数：" << count << endl;
		cout << "FIFO算法的缺页率是：" << (float)count / pageNum << endl;

	}
	//OPT算法
	void OPT()
	{
		int exist, space, position;
		count = 0;
		cout<<endl;
		for (int i = 0; i < pageNum; i++)
		{
			exist = findExist(i);
			//页已经在内存块中
			if (exist != -1)
			{
				cout << "----------------------------" << endl;
				cout << "即将访问的是页面" << page[i].ID << "----内存中已存在该页" << endl;
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
						for (int j = i; j < pageNum; j++) //修改这里的j<pageNum 就可以改变预读后续页面的页数
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
					cout << "即将访问的是页面" << page[i].ID << "将被置换出的是页面" << block[position].ID << endl;
					cout << "----------------------------" << endl;
					block[position] = page[i];
					display();
				}
			}
		}
		cout << "缺页次数：" << count << endl;
		cout << "FIFO算法的缺页率是：" << (float)count / pageNum << endl;
	}

};
int main()
{

	while (1)
	{
		int selection;
		cout << "----请输入调度算法：1:OPT 2:FIFO 3:LRU---->>";
		cin >> selection;
		int pSize, num;
		cout << "----请输入页面大小：(1、2、4、8、16K)：";
		cin >> pSize;
		cout << "----请输入系统分配的内存块数：";
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