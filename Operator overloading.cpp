#include<iostream>
#include<cstring>
using namespace std;
class String
{
	char *Character;
	int len;
public:
	String()
	{
		len = 0;
	}
	~String()
	{
		delete[]Character;
		len = 0;
	}
	String(String &t)
	{
		len=t.len;
		Character=new char [len+1];
		strcpy(Character,t.Character);
	}
	int getLenth()
	{
		return len;
	}
	String & operator=(const String &str);
	String & operator+=(const String &str);
	char operator[](int i)const;
	friend String operator+(const String &str_1,const String &str_2);
	friend ostream & operator<< (ostream &output, const String &);
	friend istream & operator>> (istream &input, String &);
};
ostream & operator<< (ostream &output, const String &str)
{
	for (int i = 0; i < str.len; i++)
	{
		output << str.Character[i];
	}
	return output;
}
istream & operator>> (istream &input, String &str)
{
	char temp=0;
	if (temp == '\n') return input;
	while (temp != '\n')
	{
		input.get(temp);
		if (temp == '\n') break;
		if (str.len != 0)
		{
			char *Temp = new char[str.len + 1];
			for (int i = 0; i < str.len; i++)
			{
				Temp[i] = str.Character[i];
			}
			Temp[str.len] = '\0';
			delete[]str.Character;
			str.len++;
			str.Character = new char[str.len + 1];
			for (int i = 0; i < str.len - 1; i++)
			{
				str.Character[i] = Temp[i];
			}
			str.Character[str.len - 1] = temp;
			str.Character[str.len] = '\0';
			delete[]Temp;
		}
		else
		{
			str.len++;
			str.Character = new char[str.len + 1];
			str.Character[str.len - 1] = temp;
			str.Character[str.len] = '\0';
		}
	}
	return input;
}
String operator+(const String &str_1,const String &str_2)
{
	String Temp_str;
	Temp_str.len = str_1.len + str_2.len;
	Temp_str.Character = new char[str_1.len + str_2.len+1];
	for (int i = 0; i < str_1.len; i++)
	{
		Temp_str.Character[i] = str_1.Character[i];
	}
	for (int j = str_1.len ; j < str_1.len + str_2.len; j++)
	{
		Temp_str.Character[j] = str_2.Character[j-str_1.len];
	}
	Temp_str.Character[str_1.len + str_2.len ] = '\0';
	return String(Temp_str);
}
String &String::operator=(const String &str)
{
	if (len != 0)
	{
		delete[]Character;
		len = str.len;
		Character = new char[str.len+1];
		for (int i = 0; i < str.len ; i++)
		{
			Character[i] = str.Character[i];
		}
		Character[str.len ] = '\0';
		return *this;
	}
	else
	{
		len = str.len;
		Character = new char[str.len+1];
		for (int i = 0; i < str.len ; i++)
		{
			Character[i] = str.Character[i];
		}
		Character[str.len] = '\0';
		return *this;
	}
}
String &String::operator+=(const String &str)
{
	char *temp=new char[len+1];
	strcpy(temp,Character);
	len+=str.len;
	delete []Character;
	Character =new char[len+1];
	for(int i=0;i<len-str.len;i++)
	{
		Character[i]=temp[i];
	}
	delete []temp;
	for(int j=len-str.len;j<len;j++)
	{
		Character[j]=str.Character[j-len+str.len];
	}
	Character[len]='\0';
	return *this;
}
char String::operator[](int i)const
{
	if(i>=len) cout<<"Error!"<<endl;
	else
	{
		return Character[i];
	}
	return 0;
}
int main()
{
	String str_1,str_2;
	cin >> str_1;
	cin >> str_2;
	cout << "string1：";
	cout << str_1 <<"\t长度："<<str_1.getLenth()<< endl;
	cout << "string2：";
	cout << str_2 <<"\t长度："<<str_2.getLenth()<< endl;
	cout << "string3=string1+string2：";
	String str_3;
	str_3 = str_1 + str_2;
	cout << str_3 << "=" << str_1 << "+" << str_2 << endl;
	return 0;
}