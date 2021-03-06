#include "Swiat.h"
#include "Organizm.h"
#include<cstdlib>
#include<algorithm>
using std::cout;
void Swiat::wykonajTure()
{
	srand(time(NULL));
	std::sort(organizmy.begin(), organizmy.end(),
		[](Organizm* const& stud1, Organizm* const& stud2) -> bool
	{
		return stud1->zwrocInicjatywa() > stud2->zwrocInicjatywa();
	});
	for (int k = 0; k < organizmy.size(); k++)
		if (organizmy[k]->zwrocOczekiwanie() > 0)
			organizmy[k]->zmniejszOczekiwanie();
	for (int i = 0; i < organizmy.size(); i++)
	{
		bool wartosc;
		if (organizmy[i]->zwrocKolizje() == false)
		{
			for (int j = 0; j < organizmy.size(); j++)
			{
				if (i < organizmy.size())
				{
					if (organizmy[i]->zwrocObraz().getGlobalBounds().intersects(organizmy[j]->zwrocObraz().getGlobalBounds()) && i != j)
					{
						wartosc = organizmy[i]->kolizja(*organizmy[j], *this);
						if (wartosc == true)
						{
							organizmy[i]->ustawKolizje(wartosc);
							organizmy[j]->ustawKolizje(true);
							organizmy[i]->zwiekszOczekiwanie();
							organizmy[j]->zwiekszOczekiwanie();
						}
						
					}
				}
			}
			if (i < organizmy.size())
			{
				if (organizmy[i]->zwrocKolizje() == false && organizmy[i]->zwrocOczekiwanie() == 0)
					organizmy[i]->akcja(*this);
			}
			
		}
		else
			if(organizmy[i]->zwrocOczekiwanie() == 0)
				organizmy[i]->akcja(*this);
		//this->rysujSwiat();
		//cout << i << endl;
		if (i < organizmy.size() && organizmy[i]->zwrocInicjatywa() > 0)
			organizmy[i]->zwiekszGlod();
		if (i < organizmy.size() && organizmy[i]->zwrocGlod() == 100)
			this->usunOrganizm(organizmy[i]);
	}


	//cout << counter;
}
void Swiat::rysujSwiat()
{
	Sleep(1000);
	system("cls");
	std::sort(organizmy.begin(), organizmy.end(),
		[](Organizm* const& stud1, Organizm* const& stud2) -> bool
	{
		return stud1->zwrocSila() < stud2->zwrocSila();
	});
	//for (int i = 0; i < organizmy.size(); i++)
	//	cout << organizmy[i]->zwrocSila();
	for (int i = 0; i < organizmy.size(); i++)
	{
		organizmy[i]->rysuj();
	}
}
void Swiat::dodajOrganizm(Organizm* _organizm)
{
	//cout << "dodaje organizm" << typeid(_organizm).name() << endl;
	//cout << _organizm->zwrocSila();
	counter++;
	organizmy.push_back(_organizm);
	Sleep(1000);
}
void Swiat::usunOrganizm(Organizm* _organizm)
{
	vector<Organizm*>::iterator it;
	it = find(organizmy.begin(), organizmy.end(), _organizm);
	organizmy.erase(it);
	delete _organizm;
}
void Swiat::pokazOrganizmy()
{
	for (int i = 0; i < organizmy.size(); i++)
	{
		cout << typeid(organizmy[i]).name() << organizmy[i]->zwrocPolozenie().x << organizmy[i]->zwrocPolozenie().y<<endl ;
	}
	Sleep(1000);
}
void Swiat::pokazSwiat()
{
	Sleep(100);
	//system("cls");
	std::sort(organizmy.begin(), organizmy.end(),
		[](Organizm* const& stud1, Organizm* const& stud2) -> bool
	{
		return stud1->zwrocSila() < stud2->zwrocSila();
	});
	//for (int i = 0; i < organizmy.size(); i++)
	//	cout << organizmy[i]->zwrocSila();
	okno->draw(sprite);
	for (int i = 0; i < organizmy.size(); i++)
	{
		organizmy[i]->pokazObraz(*okno);
	}
	okno->display();
}
void Swiat::dodajObraz()
{
	texture.loadFromFile("Images/back.jpg");
	sprite.setTexture(texture);
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

