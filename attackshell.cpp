
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>
#include <algorithm>

using namespace std;

struct digram
{
	string test;
	int count;
};

struct has_string
{
        string id;
        has_string(string id):id(id){}
        bool operator()(digram const& digram) const
        {
                return digram.test == id;
        }
};

bool sortsv( const digram& e1, const digram& e2)
{
	return e1.count > e2.count;
}

string preprocess(char* file)
{
	ifstream myfile (file);	
	char c;
	string ptext;
	if(myfile.is_open())
	{
		while(!myfile.eof())
		{
			c = myfile.get();
			if(isalpha(c))	
			{
				if(isupper(c))
				{
					c = tolower(c);
				}
				ptext += c;
			}
		}
	}
	myfile.close();
	return ptext;
}

void encrypt(string ptext, string efile, char key[])
{
	int cvalue;
	char newval;
	string perm;
	ofstream estream;
	estream.open(efile.c_str());
		for(int i = 0; i < ptext.size(); i++)
		{
			if(isalpha(ptext[i]))
			{
				cvalue = (int)ptext[i];
				newval = (char)key[cvalue - 97];
				perm += newval;
			}
			else
			{
				perm += ptext[i];
			}
		}
	estream << perm << endl;
	estream.close();
//	cout << perm;
}

int getposition(const char *array, int size, char c)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == c)
		{
			return (int)i;
		}
	}
	return -1;
}

string gettext(string file)
{
	ifstream efile;
	string val;
	char c;
	efile.open(file.c_str());
	if(efile.is_open())
	{
		while(!efile.eof())
		{
			c = efile.get();		
			val += c;
		}
	}
	efile.close();
	return val;
}

void decrypt(string ftext, char key[])
{
	ofstream newfile;
	char c;
	int size = 26;
	int cvalue;
	char newval;
	string ptext = gettext(ftext);
	string dperm;
		for(int i = 0; i < ptext.size(); i++)
		{	
			if(isalpha(ptext[i]))
			{
				cvalue = getposition(key, size, ptext[i]);
				cvalue += 97;
				newval = (char)cvalue;
				dperm += newval;
			}
			else
			{
				dperm += ptext[i];
			}
		}
	newfile.open(ftext.c_str());
	if(newfile.is_open())
	{
		newfile << dperm << endl;	
	}	
	newfile.close();
}

void getcount(string ptext)
{
        ifstream efile;
        efile.open(ptext.c_str());
        int cryptarray[26];
        int asciival;
        fill(cryptarray, cryptarray+26, 0);
        char c;
        if(efile.is_open())
        {
                while(!efile.eof())
                {
                        c = efile.get();
                        asciival = ((int)c - 65);
                        cryptarray[asciival]++;
                }
        }
        efile.close();
        for(int i = 65; i < 91; i++)
        {
                cout << (char)i << ": " << cryptarray[i-65] << endl;
        }
}

void help()
{
	cout << "\nList of all commands in attack mode:\n" << endl;
	cout << "count		Lists the frequency of each letter" << endl;	
	cout << "count all	Lists the frequency of each letter" << endl;
	cout << "count digrams 	Lists the top 30 occurrences of digrams" << endl;
	cout << "count trigrams  Lists the top 12 occurrences of trigrams" << endl; 
	cout << "exit		Exit attack mode (same as quit)" << endl;
	cout << "help		Display this help" << endl;
	cout << "key		Shows the current state of the key" << endl;
	cout << "quit		Leave attack mode" << endl;
	cout << "reset 		Resets the key to empty" << endl;
	cout << "show all	Output the current state of the attack" << endl;
}

void getdoubles(string ptext)
{
	string ctext = gettext(ptext);
        string a,b;
        bool found,room,spot;
        vector<digram> vec;
        vector<digram>::iterator result;
        digram di;
        for(int i = 0; i < ctext.length()-2; i++)
        {
                a = ctext[i];
                b = ctext[i+1];
                found = false;
                room = false;
		if(a==b)
		{
                	a += b;
                	result = find_if(vec.begin(), vec.end(), has_string(a));
                	if(result == vec.end())
               		{
                        	di.test = a;
                        	di.count = 1;
                        	vec.push_back(di);
              		}
                	else
                	{
                       		vec[result - vec.begin()].count++;
                	}
		i += 2;
        	}
	}
       	sort(vec.begin(), vec.end(), sortsv);
       	for(int n = 0; n < 10; n++)
        {
                cout << vec[n].test << " " << vec[n].count << endl;
        }
}

void getdigrams(string ptext)
{
	string ctext = gettext(ptext);	
	string a,b;
	bool found,room,spot;
	vector<digram> vec;
	vector<digram>::iterator result;
	digram di;
	for(int i = 0; i < ctext.length()-2; i++)
	{
		a = ctext[i];
		b = ctext[i+1];
		found = false;
		room = false;
		a += b;
		result = find_if(vec.begin(), vec.end(), has_string(a));	
		if(result == vec.end())
		{
			di.test = a;
			di.count = 1;
			vec.push_back(di);
		}	
		else
		{
			vec[result - vec.begin()].count++;
		}
	}
	sort(vec.begin(), vec.end(), sortsv);
	for(int n = 0; n < 30; n++)
	{
		cout << vec[n].test << " " << vec[n].count << endl;
	}
}

void gettrigrams(string ptext)
{
	string ctext = gettext(ptext);
        string a,b,c;
        bool found,room,spot;
        vector<digram> vec;
        vector<digram>::iterator result;
        digram di;
        for(int i = 0; i < ctext.length()-3; i++)
        {
                a = ctext[i];
                b = ctext[i+1];
		c = ctext[i+2];
                found = false;
                room = false;
                a += b;
		a += c;
                result = find_if(vec.begin(), vec.end(), has_string(a));
                if(result == vec.end())
                {
                        di.test = a;
                        di.count = 1;
                        vec.push_back(di);
                }
                else
                {
                        vec[result - vec.begin()].count++;
                }
        }
        sort(vec.begin(), vec.end(), sortsv);
        for(int n = 0; n < 12; n++)
        {
                cout << vec[n].test << " " << vec[n].count << endl;
        }

}

void display(string ptext, char key[])
{
	int cols,lines;
	int spot = 0;
	int length = 0;
	string etext,dtext;
	string s = "";
	etext = gettext(ptext);
	ifstream infile;
	#ifdef TIOCGSIZE
   	struct ttysize ts;
    	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    	cols = ts.ts_cols;
    	lines = ts.ts_lines;
	#elif defined(TIOCGWINSZ)
    	struct winsize ts;
    	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    	cols = ts.ws_col;
    	lines = ts.ws_row;
	#endif /* TIOCGSIZE */

	for(int i = 0; i <= etext.size()/cols; i++)
	{
		for(int k = 0; k < cols; k++)
		{
			if(!isalpha(key[(int)etext[spot+k] - 65]))
			{
				cout << "-";
			}
			else
			{
				cout << key[(int)etext[spot+k] - 65];
			}

		}
		cout << endl;
		for(int j = 0; j < cols; j++)
		{
			if(etext[spot+j] == '\n')
			{
				cout << '\n' << endl; 
			}
			else
			{
				cout << etext[spot+j];
			}
		}
		cout << endl;
		spot += cols;
	}
}

void attack(string ptext)
{
	string input;
	string dtext, etext;
	etext = gettext(ptext);
	dtext.reserve(etext.length());
	char c,d;
	int loc;
	char key[26] = {0};
	cout << "\nSubstitution Cipher Attack Window. Type 'help' for a list of commands." << endl;
	for(;;)
	{
		cout << "attack>> ";
		getline(cin,input);
		if(input == "count all" || input == "count")
		{
			getcount(ptext);
		}
		else if(input == "quit" || input == "exit")
		{
			exit(0);
		}
		else if(input == "count doubles")
		{
			getdoubles(ptext);
		}
		else if(input == "count digrams")
		{
			getdigrams(ptext);
		}
		else if(input == "count trigrams")
		{
			gettrigrams(ptext);
		}
		else if(input == "show all")
		{
			display(ptext,key);
		}
		else if(input == "help")
		{
			help();
		}
		else if(input.rfind("=") == 1)
		{
			int j;
			bool used = false;
			if(isalpha(input[input.rfind("=") - 1]) && islower(input[input.rfind("=") - 1]))
			{
				c = input[input.rfind("=") - 1];
				if(isalpha(input[input.rfind("=") + 1]) && isupper(input[input.rfind("=") + 1]))
				{
					d = input[input.rfind("=") + 1];
					for(int i = 0; i < 26; i++)
					{
						if((key[i] == c) && (used==false))
						{
							used = true;
							key[i] = 0;
							key[(int)d-65] = c;
						}
					}
					if(!(used==true))
					{
						key[(int)d-65] = c;	
					}	
				}
			}
		}
		else if(input == "key")
		{
			for(int i = 65; i < 91; i++)
			{
				cout << (char)i << ": " << key[i-65] << endl;
			}
		}
		else if(input == "reset")
		{
			for(int i = 0; i < 26; i++)
			{
				key[i] = 0;
			}
		}
	}
}

void mainhelp()
{
	cout << "\nValid arguments (format: prog [flag] [filename])\n" << endl;
	cout << "Flags:\n" << endl;
	cout << "-e	Encrypt the file" << endl; 
	cout << "-d	Decrypt the file" << endl;
	cout << "-a	Enter attack mode on encrypted file\n" << endl;
}

int main(int argc, char* argv[])
{
	string str;
	string ename = "e";
	ofstream efile;
	char key[26] = {'B','M','O','E','P','C','Q','N','F','X','R','G','S','H','A','T','Y','D','U','I','Z','J','W','K','V','L'};
	if(!argv[1]==0)
	{
		if(string(argv[1]) == "-help")
		{
			mainhelp();
		}
		else if(!argv[2]==0)
		{
			if(string(argv[1]) == "-e")
			{
				str = preprocess(argv[2]);
				ename.append(argv[2]);
				encrypt(str,ename,key);
			}
			else if(string(argv[1]) == "-d")
			{
				decrypt(argv[2],key);
			}
			else if(string(argv[1]) == "-a")
			{
				attack(argv[2]);
			}
			else
			{
				cout << "Unrecognized arguments. Enter: 'program -help' for argument list " << endl;
			}
		}
	}
	else
	{
		cout << "\nEnter valid arguments (format: prog [flag] [filename]). Enter: 'program -help' for argument list\n" << endl;
	}
	return 0;
}
