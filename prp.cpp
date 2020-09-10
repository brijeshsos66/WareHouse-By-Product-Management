#include<bits/stdc++.h>
using namespace std;

class manufacturer
{
public:
string id;
string name;
string amount;
string quantity;
string buffer,bufferi;
string id_list[100];
int address_list[100];
int count;
	void read_data();
	void pack();
	void munpack();
	void write_to_file();
	void create_index();
	int remove(string);
	void search(string);
        int search_index(string);
	string extract_id();
	void sort_index();
	void assign_values(string);
	void modify(string);
        void display();
};
void manufacturer::read_data()
	{
		
		cout<<"PARTS ID: ";
		cin>>id;
		cout<<"PARTS NAME: ";
		cin>>name;
		cout<<"AMOUNT: ";
		cin>>amount;
		cout<<"QUANTITY: ";
		cin>>quantity;
	}
			void manufacturer::pack()
	{
		
		buffer.erase();
		buffer+=id+"|"+name+"|"+amount+"|"+quantity+"$"+"\n";
	}
	void manufacturer::write_to_file()
	{
		int pos;

		fstream file,filei;
		file.open("manufacturer.txt",ios::out|ios::app);
		pos=file.tellp();
		file<<buffer;
		file.close();
		id_list[++count]=id;
		address_list[count]=pos;
filei.open("index.txt",ios::out|ios::app);
bufferi.erase();
string st;
ostringstream convert;
convert<<pos;
st=convert.str();
bufferi+=id+" "+st+"\n";
filei<<bufferi;


filei.close();
		sort_index();
		}
	string manufacturer::extract_id()
	{
		string id;
		int i=0;
		id.erase();
		while(buffer[i]!='|')
		id+=buffer[i++];
		return id;
	}
	void manufacturer::create_index()
	{
		fstream file;
		int pos;
		string id;
		count=-1;
		file.open("manufacturer.txt",ios::in);
		while(!file.eof())
		{
			pos=file.tellg();
			buffer.erase();
			getline(file,buffer);
			if(buffer[0]!='*')
			{
				if(buffer.empty())break;
				id=extract_id();
				
				
				id_list[++count]=id;
				
			address_list[count]=pos;
		
			
				
			}
		}
		file.close();
		sort_index();
		buffer.erase();
		
	}
	
	void manufacturer::sort_index()
	{
		int i,j,temp_address;
		string temp_id;
		for(int i=0;i<=count;i++)
		{
			for(int j=i+1;j<=count;j++)
			{
				if(id_list[i]>id_list[j])
				{
					temp_id=id_list[i];
					id_list[i]=id_list[j];
					id_list[j]=temp_id;
					temp_address=address_list[i];
					address_list[i]=address_list[j];
					address_list[j]=temp_address;
					}
			}
		}
	/*	for(i=0;i<=count;i++)
		{
			cout<<id_list[i]<<"\t"<<address_list[i]<<"\n";
		}*/
	}
	int manufacturer::search_index(string key)
	{
		int low=0,high=count,mid=0,flag=0,pos;
		while(low<=high)
		{
			mid=(low+high)/2;
			if(id_list[mid]==key){flag=1;break;}
			if(id_list[mid]>key)high=mid-1;
				if(id_list[mid]<key)low=mid+1;
			}
			if(flag)
			return mid;
			else
			return -1;
		}
		void manufacturer::munpack()
{
		int i=0;
		id.erase();
		while(buffer[i]!='|')
		id+=buffer[i++];
		name.erase();
		i++;
		while(buffer[i]!='|')
		name+=buffer[i++];
		amount.erase();
		i++;
		while(buffer[i]!='|')
		amount+=buffer[i++];
		quantity.erase();
		i++;
		while(buffer[i]!='$')
		quantity+=buffer[i++];
}

	
	void manufacturer::search(string key)
	{
		int pos=0,address;
		fstream file;
		buffer.erase();
		pos=search_index(key);
		if(pos==-1)
	    cout<<endl<<"Record not found"<<endl;
	    else if(pos>=0)
	    {
	    	file.open("manufacturer.txt");
	    	address=address_list[pos];
	    	file.seekp(address,ios::beg);
	    	getline(file,buffer);
               	munpack();
	    	cout<<"Record Record...........\n"<<endl;
	    	//cout<<"\n____________________________________________________________________\n";
	    	cout<<"PARTS ID""\t""PARTS NAME""\t\t""AMOUNT""\t\t""QUANTITY""\n";
	    	cout<<id<<"\t\t"<<name<<"\t\t\t"<<amount<<"\t\t"<<quantity;
	    	//cout<<"\n____________________________________________________________________\n";
                pack();
                
	    	file.close();
		}
	}
	void manufacturer::assign_values(string key)
{
	int pos=0,address;
		fstream file;
		buffer.erase();
		pos=search_index(key);
		if(pos==-1)
	    cout<<endl<<"Record not found"<<endl;
	    else if(pos>=0)
	    {
	    	file.open("manufacturer.txt");
	    	address=address_list[pos];
	    	file.seekp(address,ios::beg);
	    	getline(file,buffer);
	    	munpack();
	    }
}
void manufacturer::modify(string key)
	{
		int c;
		assign_values(key);
		if(remove(key))
			{
				cout<<"\nWHAT TO MODIFY\n1:NAME 2:AMOUNT 3:QUANTITY\n";
				cin>>c;
				switch(c)
					{
						
						case 1:cout<<"NAME:\n";
						cin>>name;
						break;
						case 2:cout<<"AMOUNT:\n";
						cin>>amount;
						break;
						case 3:cout<<"QUANTITY:\n";
						cin>>quantity;
					
						default:cout<<"wrong choice\n";
					}
				buffer.erase();
				pack();
				write_to_file();
			}
	}


		int manufacturer::remove(string key)
	{
		int pos=0, i,address,flag=0;
		fstream file;
		pos=search_index(key);
		if(pos>=0)
			{        
                                flag=1;
				file.open("manufacturer.txt",ios::out|ios::in);
				address=address_list[pos];
				file.seekp(address,ios::beg);
				file.put('*');
				file.close();
				/*cout<<"\nrecord deleted:";*/
				for(i=pos;i<count;i++)
				{
					id_list[i]=id_list[i+1];
					address_list[i]=address_list[i+1];
				}
				count--;
			}
                 if(flag==1) return 1;
                 else 
                     return -1;
 
	}
        void manufacturer::display()
	{
    		
    		ifstream file ;
			file.open("manufacturer.txt",ios::in);
		
    	 	cout<<"PART ID"<<"\t"<<"PARTS NAME"<<"\t\t\t"<<"AMOUNT"<<"\t\t\t"<<"QUANTITY"<<"\n";

    	 	cout<<"________________________________________________________________________________________________\n";
       				 while(1)
       				 {
       				 	buffer.erase();
            	      			 getline(file,buffer,'\n');
						
						if(file.fail())break;
						
       					 {		
       					 		
            			
            					munpack();
						if(id!="*")
{
            				cout<<setw(10)<<left<<id<<setw(30)<<left<<name<<setw(25)<<left<<amount<<setw(10)<<left<<quantity;
            					            					cout<<"\n";
								}
          				 }
}
          			
    					 file.close();
	}
	


	class dealer:public manufacturer
	{
		public:
			int i,nop;
			string cid;
			string CNAME;
			string cnam;
	string did;
	string dname;
	string state;
	string dparts;
	string dquantity;
	string buffer;
        void display();	
	int bread_data();
	void bpack();
	void xpack();
	void bwrite_to_file();
	void xwrite_to_file();
	void bunpack();
	int bsearch(string);
	int bdelete_from_file(string);
	void bmodify(string);
	void xunpack();
	string key;
		string compr(string);
		string state1;
		void xzunpack();
		string teststate;
	
	};
	void dealer::xzunpack()
	{
		int i=0;
		cid.erase();
		while(buffer[i]!='|')
		cid+=buffer[i++];
		CNAME.erase();
		i++;
		while(buffer[i]!='$')
		CNAME+=buffer[i++];
	
	
	}
void dealer::display()
{
string p;
		ifstream filex;
		ifstream file;
		int flag=0,pos=0;
		file.open("dealer.txt",ios::in);
cout<<" DEALERID"<<"\t"<<"DEALERNAME"<<"\t"<<"STATE"<<"\t\t"<<"PARTSID"<<"\t\t"<<"QUANTITY"<<endl;
									                                                     
                while(!file.eof())
                {
		buffer.erase();
		pos=file.tellg();
		getline(file,buffer);
		
                if(buffer[0]!='*')
{
                 if(buffer.empty()) break;
                 bunpack();
		 p=state1;
						
						filex.open("decomp.txt",ios::in);
						while(!filex.eof())
						{
								buffer.erase();
					
			getline(filex,buffer);
								xzunpack();
								if(cid==p)
								{
									teststate=CNAME;
                          cout<<did<<"\t\t"<<dname<<"\t\t"<<teststate<<"\t\t"<<dparts<<"\t\t"<<dquantity<<endl;
                           goto alan;
bpack();
}
}
}
alan:filex.close();
}
file.close();
}

int dealer::bsearch(string key)
	{//	string key;
	//	cout<<"enter the key\n";
	//	cin>>key;
	string p;
		ifstream filex;
		ifstream file;
		int flag=0,pos=0;
		file.open("dealer.txt",ios::in);
		while(!file.eof())
			{
				buffer.erase();
				pos=file.tellg();
				getline(file,buffer);
				bunpack();
				if(key==did)
					{    p=state1;
						
						filex.open("decomp.txt",ios::in);
						while(!filex.eof())
						{
								buffer.erase();
					
			getline(filex,buffer);
								xzunpack();
								if(cid==p)
								{
									teststate=CNAME;
cout<<"DEALERID""\t""DEALERNAME""\t""STATE""\t\t""PARTSID""\t\t""QUANTITY\n";									       cout<<did<<"\t\t"<<dname<<"\t\t"<<teststate<<"\t\t"<<dparts<<"\t\t"<<dquantity<<endl;
								goto alan;
								}
								
								
					}
					alan:filex.close();
						//	cout<<"\nfound the key. The record is...\n"<<buffer;
						return pos;
					}
			}
		file.close();
		if(flag==0)
			{
				cout<<"\nNot found..\n";
				return -1;
			}
	}
int dealer::bdelete_from_file(string key)
	{
		fstream file;
		int pos, flag=0;
		pos=bsearch(key);
		if(pos>=0)
			{
				file.open("dealer.txt");
				file.seekp(pos,ios::beg);
				file.put('*');
				flag=1;
				file.close();
			}
		if(flag==1) 
		return 1;
		else
		return 0;
	}
	
		int dealer::bread_data()
	{
		cout<<"     ***********Enter parts details**********\n";
		//cout<"______________________________________________________\n";
		cout<<"DEALER ID: ";
		cin>>did;
		cout<<"DEALER NAME: ";
		cin>>dname;
		cout<<"STATE: ";
		cin>>state;
		state1=compr(state);
		cout<<"PARTS ID: ";
		cin>>dparts;
		cout<<"QUANTITY: ";
		cin>>dquantity;
	
	}
		void dealer::bpack()
	{
		buffer.erase();
		buffer+=did+"|"+dname+"|"+state1+"|"+dparts+"|"+dquantity+"$"+"\n";
	}
		void dealer::bwrite_to_file()
	{
		fstream file;
		file.open("dealer.txt",ios::out|ios::app);
		file<<buffer;
		file.close();
	}
		string dealer::compr(string state)
	{
		if(state=="ANDHRAPRADESH" || state=="andhrapradesh")
		return "AP";
	else if(state=="ARUNACHALPRADESH" || state=="arunachalpradesh")
	return "AR";
	else if(state=="ASSAM" || state=="assam")
	return "AS";
	else if(state=="BIHAR" || state=="bihar")
	return "BR";
	else if(state=="CHHATTISGARH" || state=="chhattisgarh")
	return "CG";
		else if(state=="GOA" || state=="goa")
	return "GA";
		else if(state=="GUJARAT" || state=="gujarat")
	return "GJ";
		else if(state=="HARYANA" || state=="haryana")
	return "HR";
		else if(state=="HIMACHALPRADESH" || state=="himachalpradesh")
	return "HP";
		else if(state=="JAMMU&KASHMIR" || state=="jammu&kashmir")
	return "JK";
		else if(state=="JHARKHAND" || state=="jharkhand")
	return "JH";
		else if(state=="KARNATAKA" || state=="karnataka")
	return "KA";
		else if(state=="KERALA" || state=="kerala")
	return "KL";
		else if(state=="MADHYAPRADESH" || state=="madhyapradesh")
	return "MP";
		else if(state=="MAHARASHTRA" || state=="maharashtra")
	return "MH";
		else if(state=="MANIPUR" || state=="manipur")
	return "MN";
		else if(state=="MEGHALAYA" || state=="meghalaya")
	return "ML";
		else if(state=="MIZORAM" || state=="mizoram")
	return "MZ";
		else if(state=="NAGALAND" || state=="nagaland")
	return "NL";
		else if(state=="ORRISA" || state=="orrisa")
	return "OD";
		else if(state=="PUNJAB" || state=="punjab")
	return "PB";
		else if(state=="RAJASTHAN" || state=="rajasthan")
	return "RJ";
		else if(state=="SIKKIM" || state=="sikkim")
	return "SK";
		else if(state=="TAMILNADU" || state=="tamilnadu")
	return "TN";
		else if(state=="TELAGANA" || state=="telagana")
	return "TG";
		else if(state=="TRIPURA" || state=="tripura")
	return "TR";
		else if(state=="UTTARPRADESH" || state=="uttarpradesh")
	return "UP";
		else if(state=="UTTARAKHAND" || state=="uttarakhand")
	return "UK";
	
	else
	return "WB"; 

	}
			
		void dealer::bunpack()
	{
		int ch=1, i=0;
		did.erase();
		while(buffer[i]!='|')
		did+=buffer[i++];
		dname.erase();
		i++;
		while(buffer[i]!='|')
		dname+=buffer[i++];
		state1.erase();
		i++;
		while(buffer[i]!='|')
		state1+=buffer[i++];
		dparts.erase();
		i++;
		while(buffer[i]!='|')
		dparts+=buffer[i++];
		dquantity.erase();
		i++;
		while(buffer[i]!='$')
		dquantity+=buffer[i++];
	}
			
		
		void dealer::bmodify(string key)
	{
		int c;
		if(bdelete_from_file(key))
			{
				cout<<"\nWHAT TO MODIFY\n 1:DEALER NAME 2:STATE 3:PARTS ID 4:QUANTITY 5:EXIT\n";
				cin>>c;
				switch(c)
					{
						case 1:cout<<"DEALER NAME:\n";
						cin>>dname;
						break;
						case 2:cout<<"STATE:\n";
						cin>>state;
                                                state1=compr(state);
						break;
						case 3:cout<<"PARTS ID:\n";
						cin>>dparts;
						break;
						case 4:cout<<"QUANTITY:\n";
						cin>>dquantity;
						break;
                                                
						default:cout<<"wrong choice\n";
					}
				buffer.erase();
				bpack();
				bwrite_to_file();
			}
	}
class menu
{ public:
	string id;
string name;
string amount;
string quantity;
	string did;
	string dname;
	string state;
	string dparts;
	string dquantity;
	string key;
	int manufactureroperation();
	int dealeroperation();
	int bill();
	string buffer;
	manufacturer s1;
	dealer b1;
	void bxunpack();
	void lunpack();
};
void menu::lunpack()
	{
		int ch=1, i=0;
		id.erase();
		while(buffer[i]!='|')
		id+=buffer[i++];
		name.erase();
		i++;
		while(buffer[i]!='|')
		name+=buffer[i++];
		amount.erase();
		i++;
		while(buffer[i]!='|')
		amount+=buffer[i++];
		quantity.erase();
		i++;
		while(buffer[i]!='$')
		quantity+=buffer[i++];
	}

void menu::bxunpack()
	{
		int ch=1, i=0;
		did.erase();
		while(buffer[i]!='|')
		did+=buffer[i++];
		dname.erase();
		i++;
		while(buffer[i]!='|')
		dname+=buffer[i++];
		state.erase();
		i++;
		while(buffer[i]!='|')
		state+=buffer[i++];
		dparts.erase();
		i++;
		while(buffer[i]!='|')
		dparts+=buffer[i++];
		dquantity.erase();
		i++;
		while(buffer[i]!='$')
		dquantity+=buffer[i++];
	}
int menu::bill()
{       int pos,flag=0;
	int total=0,xp,xq;
	fstream file;
	cout<<"ENTER DEALER ID:\n";
	cin>>key;
	file.open("dealer.txt",ios::in);
	while(!file.eof())
	{
		buffer.erase();
		getline(file,buffer);
		bxunpack();
		stringstream ab(dquantity);
		ab>>xq;
		if(key==did)
		{
			fstream filex;
			filex.open("manufacturer.txt",ios::in);
			while(!filex.eof())
			{
				buffer.erase();
				getline(filex,buffer);
				lunpack();
				if(dparts==id)
				{
					stringstream ab1(amount);
					ab1>>xp;
					total=xp*xq;
					//cout<<"\n________________________________________________________\n";
					cout<<"\n********************RECIPT********************\n";
					//cout<<"\n________________________________________________________\n";
					cout<<"PARTS ID\t"<<id<<"\tNAME IS:\t"<<name<<endl;
					cout<<"\nTHE TOTAL COST FOR PURCHASE OF \t"<<dquantity<<"\tQUANTITY IS:\n";
					cout<<total<<endl;
					//cout<<"\n________________________________________________________\n";
ostringstream str1;
str1<<total;
string d1=str1.str(); 
buffer.erase();
		buffer+=id+"|"+name+"|"+dquantity+"|"+d1+"$"+"\n";

		
		
		fstream file;
		file.open("bill.txt",ios::out|ios::app);
		file<<buffer;
		
		file.close();
	return pos;


				}
			}
			filex.close();

		}
	}
	file.close();
if(flag==0)
			{
				cout<<"\n Person with this id is not found..\n";
				return -1;
			}
	}
int menu:: manufactureroperation()
{ int ch,i,count;
string key;
manufacturer s1;
s1.create_index();
	while(1)
	{
		cout<<"\n********MANUFACTURER DETAILS*********\n"<<endl;
		cout<<" 1.ADD MANUFACTURER INFORMATION\n 2.SEARCH PARTICULAR INFORMATION \n 3.DELETE MANUFACTURER DETAILS\n 4.MODIFY DETAILS\n 5.DISPLAY MANUFACTURER DETAILS\n 6.EXIT\n";
		cout<<"\nEnter  your choice: \n";
		cin>>ch;
			switch(ch)
			{
				case 1: cout<<"\n How many record to insert\n";
				cin>>count;
				for(i=0;i<count;i++)
				{
				cout<<"DATA\n";
				        s1.read_data();
						s1.pack();
						s1.write_to_file();
					}
						break;
					
				case 2:cout<<"ENTER MANUFACTURER ID.....\n";
				        cin>>key;
			            s1.search(key);
						break;
				case 3: cout<<"ENTER MANUFACTURER ID....\n";
				        cin>>key;
				       i=s1.remove(key);
                                       if(i==1)
                                       cout<<"RECORD DELETED\n";
                                       else
                                       cout<<"RECORD NOT FOUND\n";
						break;
		        case 4:cout<<"ENTER MANUFACTURER ID....\n";
				        cin>>key;
				        s1.modify(key);
						break;
                        case 5:s1.display();
                                 break;
				case 6:return 0;
				default: cout<<"wrong choice\n";
				break;
			}
	}
}

int menu::dealeroperation()
{ int ch,i;
dealer b1;
	while(1)
	{
		
		
		cout<<"\n********DEALER MENU*********\n"<<endl;
		cout<<" 1.ADD DEALER DETAILS\n 2.DELETE DETAILS \n 3.SEARCH PATICULAR DETAILS\n 4.MODIFY PARTICULAT INFO.\n 5.DISPLAY DETAILS\n 6.MAIN MENU";
		cout<<"\nENTER CHOICE: \n";
		cin>>ch;
			switch(ch)
			{
				case 1: b1.bread_data();
						b1.bpack();
						b1.bwrite_to_file();
						break;
				case 2: cout<<"ENTER DEALER ID.....\n";
				    	cin>>key;
			            i=b1.bdelete_from_file(key);
						if(i==1)
						cout<<"RECORD DELETED\n";
						else
						cout<<"RECORD NOT FOUND";
						break;
				case 3: cout<<"ENTER DEALER ID.....\n";
				        cin>>key;
				        b1.bsearch(key);
						break;
				case 4:cout<<"ENTER DEALER ID.....\n";
				       cin>>key;
				       b1.bmodify(key);
						break;
                                case 5:b1.display();
                                       break;
				case 6: return 0;
				default: cout<<"wrong choice\n";
			}
	}
	return 0;
	
}
int main()
{
	int i,choice;
	menu m1;
	while(1)
	{
	cout<<"\n********WAREHOUSE BY-PRODUCT MANAGEMENT*********\n"<<endl;
	cout<<" 1.MANUFACTURER DETAILS\n 2.DEALER DETAILS \n 3.BILL\n 4.EXIT\n";
	cout <<"Enter your choice\n";
	cin>>choice;
	switch(choice)
	{
			case 1:m1.manufactureroperation();
					break;
			case 2:m1.dealeroperation();
					break;
			case 4:return 0;
			case 3:m1.bill();
				break;
			default:cout<<"wrong choice\n";
	}
	}return 0;
}


	

	
	

