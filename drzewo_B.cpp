//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 8.1
//  Drzewo B
//
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <stdio.h>

using namespace std;

//DEKLARACJA STRUKTURY
struct BDrzewo
{
    int t;
    int n;
    int *klucz;
    bool lisc;  
	struct BDrzewo **nastepny; 
};

//DEKLARACJA FUNKCJI KTORE BEDA UZYWANE W DALSZEJ CZESCI PROGRAMU
struct BDrzewo *Inicjalizuj(int dana, bool listek);
struct BDrzewo* Wstaw (struct BDrzewo * wezel, int dana, int t);
bool Szukaj (struct BDrzewo * wezel, int dana);
void WstawNiepelne (struct BDrzewo * wezel, int dana);
void Rodziel (struct BDrzewo * wezel, int i, BDrzewo *pomocnicza);
void LVR (struct BDrzewo * wezel);
void UsunCaleDrzewo(struct BDrzewo*& wezel);
void Usun(struct BDrzewo * wezel, int dana,  int t);
void WypiszSciezke(struct BDrzewo *wezel, int dana, int droga[], int dlugosc);
string ** Przejdz(struct BDrzewo * wezel, string **wypisanie, int n);

//MAIN PROGRAMU
int main() 
{
    struct BDrzewo *korzen = NULL;
    int t = 2;
    int data;
    int pobrana;
    
    ifstream plik;
    char nazwapliku[50];
    
    int opcja;
    int petla = 1;
    int droga[100];
    int dlugosc = 0;
    string **wypisanie = (string**)malloc(sizeof(string*)*10);
    
    while(petla)
	{
		system("cls");
        cout << "BDrzewo B" << endl;
		cout << "Wybierz operacje:" << endl;
		cout << "1. Wstaw dane z pliku. " << endl;
    	cout << "2. Dodaj wezel z klawiatury." << endl;
    	cout << "3. Usun wezel." << endl;
    	cout << "4. Szukaj wezla." << endl;
    	cout << "5. Usun cale Drzewo." << endl;
    	cout << "6. Rysuj Drzewo." << endl;
   		cout << "7. Wypisanie wezlow drzewa w kolejnosci przechodzenia 'LVR - in order'." << endl;
        cout << "0. Zakoncz prace programu" << endl;
        cout << "Operacja: " << endl;
        
        cin >> opcja;
		system("cls");
        switch (opcja) 
		{	
			case 0: //ZAKONCZENIE PRACY PROGRAMU
					cout << "Koniec pracy programu." << endl;
            		exit(0);
                	break;
            case 1: //DODANIE NOWEGO WEZLA Z PLIKU
            		cout << "Podaj nazwe pliku do otwarcia (koniecznie z rozszerzeniem): " << endl;
            		cin >> nazwapliku;
            		plik.open(nazwapliku);
            		if(!plik)
            		{
            			cout << "Nie otworzono pliku." << endl;
					}
					else
					{
						while(!plik.eof())
						{
							plik >> pobrana;
							korzen = Wstaw(korzen, pobrana, t);
						}
						cout << "Dane pomyslnie pobrano z pliku." << endl;
					}
					cout << endl;
            		break;
            case 2: //DODANIE NOWEGO WEZLA Z KLAWIATURY
                	cout << "Podaj wartosc dodawanego wezla: ";
                	cin >> data;
                	korzen = Wstaw(korzen, data, t);
                	
                	cout << endl;
               		break;

            case 3: //USUWANIE WEZLA
            		if(korzen == NULL)
            		{
            			cout << "Drzewo jest puste, najpierw dodaj liczby do niego." << endl;
					}
					else
					{
                		cout << "Podaj wartosc wezla: ";
                		cin >> data;
                		
                		if(Szukaj(korzen, data) == true)
                		{
                			Usun(korzen, data, t);
                			cout << "Pomyslnie usunieto wpisana wartosc." << endl;
                		}
                		else
                		{
                			cout << "Podanej wartosci nie ma w drzewie." << endl;
						}
                	}
                	cout << endl;
                	break;

            case 4: //SZUKANIE WEZLA
            		if(korzen == NULL)
            		{
            			cout << "Drzewo jest puste, najpierw dodaj liczby do niego." << endl;
					}
					else
					{
            		cout << "Podaj wartosc wezla do wyszukania: " << endl;
                	cin >> data;
                	int droga[100];
    				int dlugosc = 0;
    				WypiszSciezke(korzen, data, droga, dlugosc);
					}
		
					cout << endl;
                	break;

            case 5: //USUWANIE CALEGO DRZEWA
            		if(korzen == NULL)
            		{
            			cout << "Drzewo jest puste, najpierw dodaj liczby do niego." << endl;
					}
					else
					{
                		UsunCaleDrzewo(korzen);
                		cout << "Pomyslnie usunieto cale drzewo." << endl;
                	}
                	cout << endl;
                	break;

            case 6: //RYSOWANIE DRZEWA
            		for(int i = 0; i < 10; i++)
					{
        				wypisanie[i] = new string;
    				}
            		if(korzen == NULL)
            		{
            			cout << "Drzewo jest puste, najpierw dodaj liczby do niego." << endl;
					}
					else
					{
						cout << "Narysowane drzewo: " << endl;
						if(korzen != NULL) 
						{
                    	for(int i = 0; i < 10; i++)
						{
                        	*wypisanie[i] = "";
                    	}
                    	wypisanie = Przejdz(korzen, wypisanie, 0);
                    	for(int i = 0; i < 10; i++)
						{
                        	if(*wypisanie[i] != "")
							{
                            	cout << *wypisanie[i] << endl;
                        	}
                    	}
                    	cout<<endl;
                		}
                	}
                	cout << endl;
               	 	break;

            case 7: //WYPISZ LVR
            		if(korzen == NULL)
            		{
            			cout << "Drzewo jest puste, najpierw dodaj liczby do niego." << endl;
					}
					else
					{
            			cout << "LVR - in-order, przejscie poprzeczne, infiksowe:" << endl;;
                		LVR(korzen);
                		cout << endl;
                	}
                	cout << endl;
                	break;
                	
            default: //PRZYPADEK GDY WPISZEMY INTA NIE ZE WSKAZANYCH OPERACJI
                	cout << "Wpisano bledny numer operacji. Sprobuj ponownie." << endl;
                	break;
        }
        system("pause");
    };
return 0;
}

//INICJALIZACJA FUNKCJI
struct BDrzewo *Inicjalizuj(int dana, bool listek)
{
    struct BDrzewo* drzewko = (struct BDrzewo*)malloc(sizeof(struct BDrzewo));
    drzewko->t = dana;
    drzewko->lisc = listek;
    drzewko->klucz = (int*)malloc(sizeof(int) * (2*dana-1));
    drzewko->nastepny = (struct BDrzewo**)malloc(sizeof(struct BDrzewo*) * (2*dana));
    drzewko->n = 0;
    return drzewko;
}

//WSTAWIANIE DO DRZEWA
struct BDrzewo* Wstaw(struct BDrzewo *wezel, int dana, int t)
{
    if (wezel == NULL)
	{
        wezel = Inicjalizuj(t,true);
        wezel->klucz[0] = dana;
        wezel->n = 1;
    }
	else
	{
        if(wezel->n == 2*t-1)
		{
            BDrzewo *wypisanie = Inicjalizuj(t, false);

            wypisanie->nastepny[0] = wezel;
            Rodziel(wypisanie,0,wezel);

            int i = 0;
            if(wypisanie->klucz[0]<dana) i++;

            WstawNiepelne(wypisanie->nastepny[i],dana);

            wezel = wypisanie;
        }
		else
		{
            WstawNiepelne(wezel,dana);
        }
    }
    return wezel;
}

//FUNCKJA NA WSTAWIANIE NIEPELNE
void WstawNiepelne(struct BDrzewo * wezel, int dana)
{
    int i = wezel->n-1;

    if(wezel->lisc == true)
	{
        while(i>=0 && wezel->klucz[i]>dana)
		{
            wezel->klucz[i+1]=wezel->klucz[i];
            i--;
        }

        wezel->klucz[i+1]=dana;
        wezel->n=wezel->n+1;
    }
	else
	{
        while(i>=0 && wezel->klucz[i]>dana) i--;

        if(wezel->nastepny[i+1]->n==2*wezel->t-1)
		{
            Rodziel(wezel,i+1,wezel->nastepny[i+1]);
            if(wezel->klucz[i+1]<dana) i++;
        }
        WstawNiepelne(wezel->nastepny[i+1],dana);
    }
}

//ROZDZIELENIE
void Rodziel(struct BDrzewo * wezel, int i, struct BDrzewo *pomocnicza)
{
    struct BDrzewo *temp = Inicjalizuj(pomocnicza->t, pomocnicza->lisc);
    temp->n = wezel->t-1;

    for(int j = 0; j < wezel->t-1; j++)
	{
		temp->klucz[j] = pomocnicza->klucz[j+wezel->t];
	}

    if(pomocnicza->lisc == false)
	{
        for(int j=0;j<wezel->t;j++)
        {
        	temp->nastepny[j] = pomocnicza->nastepny[j+wezel->t];
		}
    }
    pomocnicza->n = wezel->t-1;
    for(int j = wezel->n; j>=1 ;j--)
	{
		wezel->nastepny[j+1] = wezel->nastepny[j];	
	} 

    wezel->nastepny[i+1] = temp;

    for(int j = wezel->n-1; j>=1; j--)
	{
		wezel->klucz[j+1] = wezel->klucz[j];
	}
    wezel->klucz[i] = pomocnicza->klucz[wezel->t-1];
    wezel->n = wezel->n+1;
}

//FUNCKJA NA SZUKANIE LICZBY W DRZEWIE
bool Szukaj(struct BDrzewo *wezel, int dana) 
{
  int i = 0;
  while (i < wezel->n && dana > wezel->klucz[i]) 
  {
    i++;
  }
  if (i < wezel->n && dana == wezel->klucz[i]) 
  {
    return true;
  }
  if (wezel->lisc) 
  {
    return false;
  }
  return Szukaj(wezel->nastepny[i], dana);
}

//FUNKCJA NA WYPIS LVR
void LVR(struct BDrzewo * wezel)
{
    int i;
    for(i = 0;i < wezel->n; i++)
	{
        if(wezel->lisc == false)
		{
            LVR(wezel->nastepny[i]);
        }
        cout << " " << wezel->klucz[i];
    }
    if(wezel->lisc == false)
	{
        LVR(wezel->nastepny[i]);
    }
}

//FUNKCJA NA USUWANIE CALEGO DRZEWA
void UsunCaleDrzewo(struct BDrzewo*& wezel)
{
	wezel = NULL;
}

//FUNCKJA NA SZUKANIE LICZBY W DRZEWIE
void Usun(struct BDrzewo *wezel, int dana, int t)
{
    if (!wezel)
    {
        return;
    }

    int i = 0;
    while (i < wezel->n && dana > wezel->klucz[i])
    {
        i++;
    }

    if (i < wezel->n && dana == wezel->klucz[i])
    {
        if (wezel->lisc)
        {
            for (int j = i; j < wezel->n - 1; j++)
            {
                wezel->klucz[j] = wezel->klucz[j + 1];
            }
            wezel->n--;
        }
        else
        {
            struct BDrzewo *poprzednik = wezel->nastepny[i];
            while (!poprzednik->lisc)
            {
                poprzednik = poprzednik->nastepny[poprzednik->n];
            }
            wezel->klucz[i] = poprzednik->klucz[poprzednik->n - 1];
            poprzednik->n--;
        }
    }
    else
    {
        if (wezel->lisc)
        {
            return;
        }
        struct BDrzewo *nastepnik = wezel->nastepny[i];
        if (nastepnik->n == t - 1)
        {
            if (i > 0 && wezel->nastepny[i - 1]->n > t - 1)
            {
                nastepnik->klucz[nastepnik->n] = wezel->klucz[i - 1];
                nastepnik->nastepny[nastepnik->n + 1] = nastepnik->nastepny[nastepnik->n];
                for (int j = nastepnik->n - 1; j >= 0; j--)
                {
                    nastepnik->klucz[j] = nastepnik->klucz[j - 1];
                    nastepnik->nastepny[j + 1] = nastepnik->nastepny[j];
                }
                nastepnik->klucz[0] = wezel->klucz[i - 1];
                nastepnik->nastepny[0] = wezel->nastepny[i - 1];
                wezel->klucz[i - 1] = wezel->nastepny[i - 1]->klucz[wezel->nastepny[i - 1]->n - 1];
                wezel->nastepny[i - 1]->n--;
            }
            else if (i < wezel->n && wezel->nastepny[i + 1]->n > t - 1)
            {
                nastepnik->klucz[nastepnik->n] = wezel->klucz[i];
                nastepnik->nastepny[nastepnik->n + 1] = wezel->nastepny[i + 1];
                nastepnik->n++;
                wezel->klucz[i] = wezel->nastepny[i + 1]->klucz[0];
                wezel->nastepny[i + 1] = wezel->nastepny[i + 1]->nastepny[0];
                for (int j = 0; j < wezel->nastepny[i + 1]->n - 1; j++)
                {
                    wezel->nastepny[i + 1]->klucz[j] = wezel->nastepny[i + 1]->klucz[j + 1];
                    wezel->nastepny[i + 1]->nastepny[j] = wezel->nastepny[i + 1]->nastepny[j + 1];
                }
                wezel->nastepny[i + 1]->n--;
            }
            else
            {
                if (i > 0)
                {
                    struct BDrzewo *Lewo = wezel->nastepny[i - 1];
                    Lewo->klucz[Lewo->n] = wezel->klucz[i - 1];
                    Lewo->nastepny[Lewo->n + 1] = nastepnik;
                    for (int j = 0; j < nastepnik->n; j++)
                    {
                        Lewo->klucz[Lewo->n + 1 + j] = nastepnik->klucz[j];
                        Lewo->nastepny[Lewo->n + 2 + j] = nastepnik->nastepny[j];
                    }
                    Lewo->n = Lewo->n + 1 + nastepnik->n;
                    for (int j = i - 1; j < wezel->n - 1; j++)
                    {
                        wezel->klucz[j] = wezel->klucz[j + 1];
                        wezel->nastepny[j] = wezel->nastepny[j + 1];
                    }
                    wezel->n--;
                    Usun(wezel, dana, t);
                }
                else
                {
                    struct BDrzewo *Prawo = wezel->nastepny[i + 1];
                    nastepnik->klucz[nastepnik->n] = wezel->klucz[i];
                    nastepnik->nastepny[nastepnik->n + 1] = Prawo->nastepny[0];
                    for (int j = 0; j < Prawo->n; j++)
                    {
                        nastepnik->klucz[nastepnik->n + 1 + j] = Prawo->klucz[j];
                        nastepnik->nastepny[nastepnik->n + 2 + j] = Prawo->nastepny[j + 1];
                    }
                    nastepnik->n = nastepnik->n + 1 + Prawo->n;
                    for (int j = i; j < wezel->n - 1; j++)
                    {
                        wezel->klucz[j] = wezel->klucz[j + 1];
                        wezel->nastepny[j + 1] = wezel->nastepny[j + 2];
                    }
                    wezel->n--;
                    Usun(wezel, dana, t);
                }
            }
        }
        else
        {
            Usun(nastepnik, dana, t);
        }
    }
    if (wezel->n == 0 && !wezel->lisc)
    {
        struct BDrzewo *noweDrzewo = wezel->nastepny[0];
        free(wezel);
        wezel = noweDrzewo;
    }
}

//WYPISANIE SCIEZKI
void WypiszSciezke(struct BDrzewo *wezel, int dana, int droga[], int dlugosc)
{
    if (wezel == NULL)
    {
        cout << "dana nie zostal znaleziony w drzewie" << endl;
        return;
    }
    if (wezel->lisc == true)
    {
        for (int i = 0; i < wezel->n; i++)
        {
            if (wezel->klucz[i] == dana)
            {
                droga[dlugosc] = dana;
                cout << "Sciezka elementu w drzewie: ";
                for (int j = 0; j <= dlugosc; j++)
                    cout << droga[j] << " ";
                cout << endl;
                return;
            }
        }
        cout << "dana nie zostal znaleziony w drzewie" << endl;
        return;
    }
    for (int i = 0; i < wezel->n; i++)
    {
        if (wezel->klucz[i] == dana)
        {
            droga[dlugosc] = dana;
            cout << "Sciezka elementu w drzewie: " << endl;
            for (int j = 0; j <= dlugosc; j++)
            {
                cout << droga[j] << " ";
            }
            cout << endl;
            return;
        }
        if (i < wezel->n - 1 && dana > wezel->klucz[i] && dana < wezel->klucz[i + 1])
        {
            droga[dlugosc] = wezel->klucz[i];
            WypiszSciezke(wezel->nastepny[i + 1], dana, droga, dlugosc + 1);
            return;
        }
        if (i == wezel->n - 1 && dana > wezel->klucz[i])
        {
            droga[dlugosc] = wezel->klucz[i];
            WypiszSciezke(wezel->nastepny[i + 1], dana, droga, dlugosc + 1);
            return;
        }
        if (i == 0 && dana < wezel->klucz[i])
        {
            WypiszSciezke(wezel->nastepny[i], dana, droga, dlugosc);
            return;
        }
    }
}
//RYSOWANIE DRZEWA
string ** Przejdz(struct BDrzewo * wezel, string **wypisanie,int n)
{
    int i;
        *wypisanie[n]=*wypisanie[n]+"[ ";
    for(i=0;i<wezel->n;i++)
	{
        if(wezel->lisc== false)
		{
            wypisanie=Przejdz(wezel->nastepny[i],wypisanie,n+1);
        }
        stringstream sss;
		sss<<wezel->klucz[i];
        string ss=sss.str();

        *wypisanie[n]=*wypisanie[n]+ss+" ";
    }
    *wypisanie[n]=*wypisanie[n]+']';
    if(wezel->lisc == false)
	{
        wypisanie=Przejdz(wezel->nastepny[i],wypisanie,n+1);
    }
    return wypisanie;
}
