#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class PersonData
{
    private:
        string name;
        int age;
        string job;
        PersonData* prev;
        PersonData* next;
    public:
        PersonData(string n, int a, string j): name(n), age(a), job(j){}
        string getName()
        {
            return name;
        }
        void display()
        {
            cout<<"姓名: "<<name<<"\n年齡: "<<age<<"\n職業: "<<job<<"\n";
        }
        friend class DataList;
};

class DataList
{
    private:
        PersonData* startData;
        PersonData* endData;
    public:
        int len;
        DataList();
        ~DataList();
        PersonData* find(string searchName);
        void insert(string n, int a, string j);
        bool remove(string removeName);
        void displayL();
        void load();
        void save();
};


DataList::DataList(): len(0)
{
    startData = new PersonData("None", -1, "None");
    endData = new PersonData("None", -1, "None");

    startData->next = endData;
    endData->prev = startData;
}

DataList::~DataList()
{
    PersonData* cur = startData;
    while (cur != endData)
    {
        PersonData* toDelete = cur;
        cur = cur->next;
        delete toDelete;
    }

    delete endData;
    return;
}

PersonData* DataList :: find(string searchName)
{
    PersonData* cur = startData->next;
    while(cur!= endData)
    {
        if(cur->name == searchName)
        {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

void DataList :: insert(string n, int a, string j)
{   
    PersonData* insertPtr = new PersonData(n, a, j);
    insertPtr->next = endData;
    insertPtr->prev = endData->prev;
    endData->prev->next = insertPtr;
    endData->prev = insertPtr;
    len++;
}
bool DataList :: remove(string removeName)
{
    PersonData* cur = startData->next;
    while(cur!= endData)
    {
        if(cur->name == removeName)
        {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
            len--;
            return true;
        }
        cur = cur->next;
    }
    return false;
}
void DataList :: displayL()
{
    PersonData* cur = startData->next;
    while(cur != endData)
    {
        cur->display();
        cout <<"\n";
        cur = cur->next;
    }
    return;
}
void DataList :: load()
{
    len = 0;
	ifstream nameList;
	nameList.open("NameList.txt");
	if(nameList)
	{
		string n;
		int a;
		string j;
		while(nameList.get() == '\n')
		{
			if(nameList >> n >> a >> j)
				this ->insert(n, a, j);
		}
	}
	nameList.close();
}
void DataList :: save()
{
    ofstream nameList;
	nameList.open("NameList.txt");
	if(nameList)
	{
		nameList<< "\n";
        PersonData* cur = startData->next;
		while(cur != endData)
		{
			nameList<< cur-> name <<" "<< cur-> age <<" "<< cur-> job<<"\n";
            cur = cur->next;
		}
        
	}
	nameList.close();
}



void interface ()
{
	DataList list;
	list.load();
	cout << "歡迎使用個人資料紀錄系統\n指令說明: 新增資料(N) 搜尋單筆資料(F) 刪除單筆資料(R) \n展示當前所有資料(D) 顯示目前資料數量(C) 儲存當前所有資料(S) 退出系統(Q)";
	bool quit = false;
	while(!quit)
	{
		char order = '0';
		cout << "\n請輸入指令字元: ";
		cin >> order;
		if(order == 'n')
		{
			string n, j;
			int a;
			cout << "\n新增資料\n請輸入新增個人資料欄位\n姓名: ";
			cin >> n;
			cout << "\n年齡: ";
			cin >> a;
			cout << "\n職業: ";
			cin >> j;
			list.insert(n, a, j);
			cout <<"\n資料新增完成\n";
			continue;
		}
		else if(order == 'f')
		{
			string searchName;
			cout << "\n搜尋資料\n請輸入要查找的姓名: ";
			cin >> searchName;
			if(list.find(searchName) == nullptr)
			{
				cout << "\n您所的姓名不存在於資料庫中\n";
			}
			else
			{
				list.find(searchName) -> display();
			}
			continue;
		}
		else if(order == 'r')
		{
			string removeName;
			cout << "\n移除資料\n請輸入要移除資料的姓名: ";
			cin >> removeName;
			if(list.remove(removeName))
			{
				cout << "\n刪除完成\n";	
			}
			else
			{
				cout << "\n您所輸入的姓名不存在於資料庫中\n";
			}
			continue;
		}
		else if(order == 'd')
		{
			cout << "\n顯示目前資料\n";
			list.displayL();
			continue;
		}
        else if(order == 'c')
		{
			cout << "\n目前有" << list.len <<"筆資料\n";
			continue;
		}
		else if(order == 's')
		{
			list.save();
			cout << "\n資料儲存完成\n";
			continue;
		}
		else if(order == 'q')
		{
			char quitOrNot = 'n';
			cout << "\n您確定要離開系統嗎?(Y/N) ";
			cin >> quitOrNot;
			if(quitOrNot == 'y' || quitOrNot == 'Y')
				quit = true;
			else
				continue;
		}
		else
		{
			cout << "\n您未正確輸入指令，請重試\n";
			continue;
		}
	}
}


int main()
{
	interface();
	return 0;
}

