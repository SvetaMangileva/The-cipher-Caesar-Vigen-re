#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>

using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	int n;
	int q = atoi(argv[1]);
	int key; 
	string result = "";
	n = atoi(argv[2]);
	cout << n;
	ifstream in(argv[3]);
	switch (q)
	{
	case 1: 
	{
		key = atoi(argv[4]);
		switch (n) 
		{
		case 1:
		{
			if (key > 26)
			key = key % 26;
			string s; 
			getline(in, s);
			cout << "Source string: \n" << s << endl;
			in.close();

			cout << "The cipher string:\n";

			for (int i = 0; i < s.length(); i++)
			{
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
					result += s[i];
				if (((int)(s[i]) >= 97) && ((int)(s[i]) <= 122))
				{
					if ((int)(s[i]) + key > 122)	
						result += (char)((int)(s[i]) + key - 26);
					else
						result += (char)((int)(s[i]) + key);
				}
				
				if (((int)(s[i]) >= 65) && ((int)(s[i]) <= 90))
				{
					if ((int)(s[i]) + key > 90)
						result += (char)((int)(s[i]) + key - 26);
					else
						result += (char)((int)(s[i]) + key);
				}
			}
			cout << "Encryption complete\n";
			cout << "Result:\n";
			cout << result; 
			break;
		}
		case 2: 
		{
			if (key > 26)
				key = key % 26;
			cout << "The cipher string:\n";

			string s;
			getline(in, s);
			cout << "Source string: \n" << s << endl;
			in.close();
			cout << "Decryption:\n";
			for (int i = 0; i < s.length(); i++)
			{
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
					result += s[i];
				if (((int)(s[i]) >= 97) && ((int)(s[i]) <= 122))
				{
					if ((int)(s[i]) - key < 97)
						result += (char)((int)(s[i]) - key + 26);
					else
						result += (char)((int)(s[i]) - key);
				}
				if (((int)(s[i]) >= 65) && ((int)(s[i]) <= 90))
				{
					if ((int)(s[i]) - key < 65)
					result += (char)((int)(s[i]) - key + 26);
					else
						result += (char)((int)(s[i]) - key);
				}
			}
			cout << "Decryption complete!\n";
			cout << "Result:\n";
			cout << result; 
			break;
		}
		default: 
		{
			cout << "Error value\n";
			break;
		}
		}

		break;
	}

	case 2:
	{
		string key1 = argv[4]; 		
		string key_on_s = "";
		bool flag;
		int x = 0, y = 0; 
		int registr = 0;
		char dublicat; 
		int shift = 0;
		char **tabula_recta = new char *[26]; 
		for (int i = 0; i < 26; i++)
			tabula_recta[i] = new char[26];
		string alfabet = "abcdefghijklmnopqrstuvwxyz"; 
		for (int i = 0; i < 26; i++)
			for (int j = 0; j < 26; j++)
			{
				shift = j + i;
				if (shift >= 26) shift = shift % 26;
				tabula_recta[i][j] = alfabet[shift];
			}
		switch (n)
		{
		case 1:
		{
			string s; 
			getline(in, s);
			cout << "Source string:: \n" << s << endl;
			in.close();
			cout << "The cipher string:\n";
	
			for (int i = 0; i < s.length(); i++)
			{
				key_on_s += key1[i % key1.length()];
			}
		
			for (int i = 0; i < s.length(); i++)
			{
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
					result += s[i];
				else
				{
					int l = 0;
					flag = false;
	
					while ((l < 26) && (flag == false))
					{
						if (key_on_s[i] == tabula_recta[l][0])
						{
							x = l;
							flag = true;
						}
						l++;
					}
					if (((int)(s[i]) <= 90) && ((int)(s[i]) >= 65))
					{
						dublicat = (char)((int)(s[i]) + 32);
						registr = 1;
					}
					else
					{
						registr = 0;
						dublicat = s[i];
					}
					l = 0;
					flag = false;
					while ((l < 26) && (flag == false))
					{
						if (dublicat == tabula_recta[0][l])
						{							
							y = l;
							flag = true;
						}
						l++;
					}
				
					if (registr == 1)
					{
						dublicat = char((int)(tabula_recta[x][y]) - 32);
						result += dublicat;
					}
					else
						result += tabula_recta[x][y];
				}
			}
			cout << "Encryption complete\n";
			cout << "Result:\n";
			cout << result; 
			break;
		}
		case 2: 
		{
			string s;
			getline(in, s);
			cout << "The cipher string:\n" << s << endl;
			in.close();
			cout << "Source string:\n";
			for (int i = 0; i < s.length(); i++)
			{
				key_on_s += key1[i % key1.length()];
			}
			for (int i = 0; i < s.length(); i++)
			{
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
					result += s[i];
				else
				{
					int l = 0;
					flag = false;
					while ((l < 26) && (flag == false))
					{
						if (key_on_s[i] == tabula_recta[l][0])
						{
							x = l;
							flag = true;
						}
						l++;
					}
					if (((int)(s[i]) <= 90) && ((int)(s[i]) >= 65))
					{
						dublicat = (char)((int)(s[i]) + 32);
						registr = 1;
					}
					else
					{
						registr = 0;
						dublicat = s[i];
					}
					l = 0;
					flag = false;
					while ((l < 26) && (flag == false))
					{
						if (dublicat == tabula_recta[x][l])
						{						
							y = l;
							flag = true;
						}
						l++;
					}
					if (registr == 1)
					{
						dublicat = char((int)(tabula_recta[0][y]) - 32);
						result += dublicat;
					}
					else
						result += tabula_recta[0][y];
				}
			}
			cout << "Decryption complete\n";
			cout << "Result:\n";
			cout << result; 
			break;
		}
		}
		break;
	}

	}
	return 0;
}
