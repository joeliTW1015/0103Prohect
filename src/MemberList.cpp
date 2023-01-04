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
            cout<<"�m�W: "<<name<<"\n�~��: "<<age<<"\n¾�~: "<<job<<"\n";
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
	cout << "�w��ϥέӤH��Ƭ����t��\n���O����: �s�W���(N) �j�M�浧���(F) �R���浧���(R) \n�i�ܷ�e�Ҧ����(D) ��ܥثe��Ƽƶq(C) �x�s��e�Ҧ����(S) �h�X�t��(Q)";
	bool quit = false;
	while(!quit)
	{
		char order = '0';
		cout << "\n�п�J���O�r��: ";
		cin >> order;
		if(order == 'n')
		{
			string n, j;
			int a;
			cout << "\n�s�W���\n�п�J�s�W�ӤH������\n�m�W: ";
			cin >> n;
			cout << "\n�~��: ";
			cin >> a;
			cout << "\n¾�~: ";
			cin >> j;
			list.insert(n, a, j);
			cout <<"\n��Ʒs�W����\n";
			continue;
		}
		else if(order == 'f')
		{
			string searchName;
			cout << "\n�j�M���\n�п�J�n�d�䪺�m�W: ";
			cin >> searchName;
			if(list.find(searchName) == nullptr)
			{
				cout << "\n�z�Ҫ��m�W���s�b���Ʈw��\n";
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
			cout << "\n�������\n�п�J�n������ƪ��m�W: ";
			cin >> removeName;
			if(list.remove(removeName))
			{
				cout << "\n�R������\n";	
			}
			else
			{
				cout << "\n�z�ҿ�J���m�W���s�b���Ʈw��\n";
			}
			continue;
		}
		else if(order == 'd')
		{
			cout << "\n��ܥثe���\n";
			list.displayL();
			continue;
		}
        else if(order == 'c')
		{
			cout << "\n�ثe��" << list.len <<"�����\n";
			continue;
		}
		else if(order == 's')
		{
			list.save();
			cout << "\n����x�s����\n";
			continue;
		}
		else if(order == 'q')
		{
			char quitOrNot = 'n';
			cout << "\n�z�T�w�n���}�t�ζ�?(Y/N) ";
			cin >> quitOrNot;
			if(quitOrNot == 'y' || quitOrNot == 'Y')
				quit = true;
			else
				continue;
		}
		else
		{
			cout << "\n�z�����T��J���O�A�Э���\n";
			continue;
		}
	}
}


int main()
{
	interface();
	return 0;
}

