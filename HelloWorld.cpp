#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;
// TODO : Remove global variables
vector<string> words;
vector<string> selectedWords;
vector<int> selectedIndex;
fstream file;

int RandomNumber(int minDeger, int maxDeger)
{
	int RandomNumber = rand() % (maxDeger - minDeger + 1) + minDeger;

	return RandomNumber;
}

template <typename T>
int IndexOf(vector<T> arananyer, T aranandeger)
{
	for (int i = 0; i < arananyer.size(); i++)
	{
		if (arananyer[i] == aranandeger)
		{
			return i;
		}
	}
	return -1;
}

int IndexOfSTR(string arananyer, char arananI)
{
	for (int i = 0; i < arananyer.size(); i++)
	{
		if (arananyer[i] == arananI)
		{
			return i;
		}
	}
	return -1;
}
bool IcindeVarMiSTR(string aranilankelime, char arananharf)
{
	return IndexOfSTR(aranilankelime, arananharf) != -1;
}

template <typename T>
bool IcindeVarMi(vector<T> arananyer, T aranandeger)
{
	return IndexOf(arananyer, aranandeger) != -1;
}

void RastKelime(vector<string> icindenSecilenV, int kelimeSayisi)
{
	// for (int i = 0; i < Kelime; i++)
	// {
	// 	int rndIdx = RandomNumber(0, icindenSecilenV.size() - 1);
	// 	if (IcindeVarMi(selectedIndex, rndIdx)) continue;
	// 	selectedIndex.push_back(rndIdx);
	// 	selectedWords.push_back(icindenSecilenV[rndIdx]);
	// }

	int i = 0;
	while (i < kelimeSayisi) // NEDEN WHILE ?!
	{
		int randomIndex = RandomNumber(0, icindenSecilenV.size() - 1);
		if (IcindeVarMi(selectedIndex, randomIndex))
		{
			continue;
		}
		selectedIndex.push_back(randomIndex);
		selectedWords.push_back(icindenSecilenV[randomIndex]);
		i++;
	}
}
string FindM(string buyukkelime, string kucukkelime)
{
	string bulunanharf;
	for (int i = 0; i < kucukkelime.size(); i++)
	{
		int IndexBK;
		IndexBK = IndexOfSTR(buyukkelime, kucukkelime[i]);
		if (IndexBK != -1)
		{
			buyukkelime.erase(buyukkelime.begin() + IndexBK);
			bulunanharf += kucukkelime[i];
		}
	}

	return bulunanharf;
}

int main()
{
	srand(time(0));
	file.open("TextFile.txt", ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			words.push_back(line);
		}
		file.close();
	}
	while (true)
	{
		RastKelime(words, 2);
		string birlesikKelime;
		string karistirilmisKelime;
		for (auto selected : selectedWords)
		{
			birlesikKelime += selected;
		}
		int kelimeuzunlugu = birlesikKelime.size();
		for (int i = 0; i < kelimeuzunlugu; i++)
		{
			char harf;
			int rastgelesayi = RandomNumber(0, birlesikKelime.size() - 1);
			harf = birlesikKelime[rastgelesayi];
			karistirilmisKelime += harf;
			birlesikKelime.erase(rastgelesayi, 1);
		}
		string sorulanKelime;
		sorulanKelime = selectedWords[RandomNumber(0, selectedWords.size() - 1)];
		while (true)
		{
			cout << "" << endl;
			cout << "-----------------------------------" << endl;
			cout << "        GUESS THE WORD            " << endl;
			cout << "-----------------------------------" << endl;
			cout << "" << endl;

			cout << karistirilmisKelime << endl;
			cout << "" << endl;
			cout << "Your Answer:";
			string cevap;
			cin >> cevap;
			if (sorulanKelime == cevap)
			{
				cout << "Tebrikler!" << endl;
				cout << "Baska bir oyun icin 'y' cikmak icin herhangi bir tusa basin.";
				string karar;
				cin >> karar;
				if (karar == "y")
				{
					selectedIndex.clear();
					selectedWords.clear();
					break;
				}
				return 31;
			}
			string bulunanharfler = FindM(sorulanKelime, cevap);
			double bolumsonuc = static_cast<double>(bulunanharfler.size()) / static_cast<double>(sorulanKelime.size());
			cout << "Bulunan harfler:" << bulunanharfler << endl;
			cout << "Bilinen Harf:" << bulunanharfler.size() << "/" << sorulanKelime.size() << endl;
			cout << "Bilinen Yüzde :" << bolumsonuc;
		}
	}
}