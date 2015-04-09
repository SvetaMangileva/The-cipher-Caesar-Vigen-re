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
	int key; //Величина сдвига для Цезаря
	string result = "";
	n = atoi(argv[2]);
	cout << n;
	ifstream in(argv[3]);
	switch (q)
	{
	case 1: //шифр Цезаря
	{
		key = atoi(argv[4]);
		switch (n) 
		{
		case 1: //шифрование
		{
			
			if (key > 26)
				key = key % 26;//Вычисление сдвига
			string s; 
			getline(in, s);
			cout << "Source string: \n" << s << endl;
			in.close();

			cout << "The cipher string:\n";

			for (int i = 0; i < s.length(); i++)
			{
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))//Если не латиница
					result += s[i];
				if (((int)(s[i]) >= 97) && ((int)(s[i]) <= 122))//Если буква является строчной
				{
					if ((int)(s[i]) + key > 122)//Если буква, после сдвига выходит за пределы алфавита	
						result += (char)((int)(s[i]) + key - 26);
					else
						result += (char)((int)(s[i]) + key);
				}
				
				if (((int)(s[i]) >= 65) && ((int)(s[i]) <= 90))//Если буква является прописной
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
		case 2: //дешифрование
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
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))//Если не латиница
					result += s[i];
				if (((int)(s[i]) >= 97) && ((int)(s[i]) <= 122))//Если буква является строчной
				{
					if ((int)(s[i]) - key < 97)
						result += (char)((int)(s[i]) - key + 26);//Если буква, после сдвига выходит за пределы алфавита
					else
						result += (char)((int)(s[i]) - key);
				}
				//Если буква является прописной
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


	//шифр Виженера
	case 2:
	{
		string key1 = argv[4]; //Строка - ключ 		
		string key_on_s = "";
		bool flag;
		int x = 0, y = 0; //Координаты нового символа из таблицы Виженера
		int registr = 0;
		char dublicat; 
		int shift = 0;
		char **tabula_recta = new char *[26]; //Таблица Виженера
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
			//Формирование строки, длиной шифруемой, состоящей из повторений ключа
			for (int i = 0; i < s.length(); i++)
			{
				key_on_s += key1[i % key1.length()];
			}
			//Шифрование при помощи таблицы
			for (int i = 0; i < s.length(); i++)
			{
				//Если нешифруемый символ
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
					result += s[i];
				else
				{
					//Поиск в первом столбце строки, начинающейся с символа ключа
					int l = 0;
					flag = false;
					//Пока не найден символ
					while ((l < 26) && (flag == false))
					{
						if (key_on_s[i] == tabula_recta[l][0])//Если символ найден
						{
							x = l;//номер строки
							flag = true;
						}
						l++;
					}//Уменьшаем временно регистр прописной буквы
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
					//Пока не найден столбец в первой строке с символом строки
					while ((l < 26) && (flag == false))
					{
						if (dublicat == tabula_recta[0][l])
						{							
							y = l;//Запоминаем номер столбца
							flag = true;
						}
						l++;
					}
					//Увеличиваем регистр буквы до прописной
					if (registr == 1)
					{
						//Изменяем символ на первоначальный регистр
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
		case 2: //дешифрование
		{
			string s;
			getline(in, s);
			cout << "The cipher string:\n" << s << endl;
			in.close();
			cout << "Source string:\n";
			for (int i = 0; i < s.length(); i++)//Формирование строки, длиной дешифруемой, состоящей из повторений ключа
			{
				key_on_s += key1[i % key1.length()];
			}
			//Дешифрование при помощи таблицы
			for (int i = 0; i < s.length(); i++)
			{
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))//Если недешифруемый символ
					result += s[i];
				else
				{
					int l = 0;
					flag = false;
					//Пока не найден столбец в x строке с символом строки
					while ((l < 26) && (flag == false))
					{
						//Если символ найден
						if (key_on_s[i] == tabula_recta[l][0])
						{
							x = l;//номер строки
							flag = true;
						}
						l++;
					}
					if (((int)(s[i]) <= 90) && ((int)(s[i]) >= 65))
					{
						dublicat = (char)((int)(s[i]) + 32);//Изменяем символ на первоначальный регистр
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
							y = l;//Запоминаем номер столбца
							flag = true;
						}
						l++;
					}
					//Увеличиваем регистр буквы до прописной
					if (registr == 1)
					{
						//Изменяем символ на первоначальный регистр
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
