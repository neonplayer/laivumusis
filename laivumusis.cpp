#include <iostream>
#include <iomanip> //nes setw naudoju
#include <string> //žaidimo pradžia palūžta be šito
#include <ctime> //atsitiktinumui
using namespace std;

#define x_length 10 //lentos ilgis
#define y_length 10 //lentos plotis

void isvalyti(); //išvalo ekraną
void linija(int x); //parašo '-' x kartų

class lenta
{
	private:
		int plytele[x_length][y_length] = { 0 }; //pačios plytelės
		bool sleptilaivus; //jei taip, laivus vartotojui rodo kaip vandenį
	public:
		lenta(bool sleptilaivus) 
		{
			this->sleptilaivus = sleptilaivus;
		}

		bool aryralaivu() //patikra ar yra dar gyvų laivų
		{
			for(int i = 0; i < y_length; i++)
			{
				for(int o = 0; o < x_length; o++)
				{
					//jei bent viena plytelė turi gyvą laivo dalį išmetama true
					if(plytele[o][i] == 2)
					{
						return true;
						break;
					}
				}
			}
			return false;
		}

		int statusas(int x, int y) //išmeta plytelės statusą (vanduo ar laivas, šauta ar ne)
		{
			return plytele[x][y];
		}

		void suvis(int x, int y) //šūvis į nurodytą lentos vietą
		{
			if(statusas(x, y) == 2) //tikrinama ar ten laivas yra
			{
				plytele[x][y] = 3;
			}
			else
			{
				plytele[x][y] = 1;
			}
		}

		void sukurtilaiva(int ilgis)
		{
			int orientacija = rand() % 2;
			//0 - horizontaliai
			//1 - vertikaliai
			int x, y;
			bool tinkama = false;
			while(!tinkama)
			{
				//atsitiktinai parenkamos koordinatės
				x = rand() % 10;
				y = rand() % 10;

				if(orientacija == 0) //jei horizontaliai
				{
					if(x + ilgis < 10) //jei laivo pabaiga nebus už lentos ribų
					{
						//dar tikrinama ar ten jau yra laivas,
						//jei visos plytelės tuščios, vieta tampa tinkama
						int tinkama2 = 0;
						for(int i = 0; i < ilgis; i++)
						{
							if(plytele[x+i][y] == 0)
							{
								tinkama2++;
							}
						}
						if(tinkama2 == ilgis)
						{
							tinkama = true;
						}
					}
				}
				else //tas pats, bet vertikaliai
				{
					if(y + ilgis < 10)
					{
						int tinkama2 = 0;
						for(int i = 0; i < ilgis; i++)
						{
							if(plytele[x][y+i] == 0)
							{
								tinkama2++;
							}
						}
						if(tinkama2 == ilgis)
						{
							tinkama = true;
						}
					}
				}
			}
			//sukūriamas laivas (plytelės pakeičiamos į dvejetus)
			if(orientacija == 0)
			{
				for(int i = 0; i < ilgis; i++)
				{
					plytele[x+i][y] = 2;
				}
			}
			else
			{
				for(int i = 0; i < ilgis; i++)
				{
					plytele[x][y+i] = 2;
				}
			}
		}

		void plytelesvaizdas(int x, int y) 
		/*
		Pačios plytelės yra saugomos kaip skaičiai, ši funkcija
		vietoje tų skaičių išmeta simbolius
		*/
		{
			switch(plytele[x][y])
			{
				case 0: //vanduo
					cout << " ";
					break;
				case 1: //vanduo, šautas
					cout << ".";
					break;
				case 2: //laivas
					if(sleptilaivus)
					{
						cout << " ";
					}
					else
					{
						cout << "O";
					}
					break;
				case 3: //laivas, šautas
					if(sleptilaivus)
					{
						cout << ".";
					}
					else
					{
						cout << "X";
					}
					break;
			}
			cout << " ";
		}

		void piestlenta()
		{
			linija(23);
			cout << setw(5);
			for(int i = 0; i < y_length; i++)
			{
				cout << i << " ";
			}
			cout << endl;
			linija(23);
			for(int i = 0; i < y_length; i++)
			{
				cout << i << " | ";
				for(int o = 0; o < x_length; o++)
				{
					plytelesvaizdas(o, i);
				}
				cout << endl;
			}
		}
};

int main() {

	//pagrindinės funkcijos pradžia

	/*
	Titulinis ekranas, žaidimas šiaip puikiai be jo veikia, bet čia
	šiaip dėl stiliaus idėjau
	*/

	cout << endl;
	cout << "	L     AAAAA III V   V U   U" << endl;
	cout << "	L     A   A III V   V U   U" << endl;
	cout << "	L     AAAAA III  V V  U   U" << endl;
	cout << "	L     A   A III  V V  U   U" << endl;
	cout << "	LLLLL A   A III   V   UUUUU" << endl;
	cout << "					          '" << endl;
	cout << "		   ---    v" << endl;
	cout << "	M   M U   U SSSSS III SSSSS" << endl;
	cout << "	MM MM U   U S     III S" << endl;
	cout << "	MM MM U   U SSSSS III SSSSS" << endl;
	cout << "	M M M U   U     S III     S" << endl;
	cout << "	M M M UUUUU SSSSS III SSSSS" << endl;
	cout << endl;
	string asdf;
	cout << "Žaidimo pradžiai įveskite betką: ";
	cin >> asdf;
	isvalyti();

	//sukūriamos lentos ir laivai
	
	lenta zmogaus(0), kompo(0);

	srand(time(NULL)); //čia tam, kad laivai visi būtų atsitiktiniai

	zmogaus.sukurtilaiva(2);
	zmogaus.sukurtilaiva(2);
	zmogaus.sukurtilaiva(3);
	zmogaus.sukurtilaiva(3);
	zmogaus.sukurtilaiva(4);
	zmogaus.sukurtilaiva(5);

	kompo.sukurtilaiva(2);
	kompo.sukurtilaiva(2);
	kompo.sukurtilaiva(3);
	kompo.sukurtilaiva(3);
	kompo.sukurtilaiva(4);
	kompo.sukurtilaiva(5);

	//Pačio žaidimo pradžia

	cout << "Čia bus rašomi erorai, jei yra" << endl << endl;

	while( zmogaus.aryralaivu() && kompo.aryralaivu() )
	{
		//Nupiešiamos lentos

		cout << "Tavo lenta" << endl;
		zmogaus.piestlenta();
		cout << endl;
		cout << "Kompiuterio lenta" << endl;
		kompo.piestlenta();

		//Žaidimo informacija

		cout << endl;
		cout << "Legenda:" << endl;
		cout << "<tuščia> - vanduo, . - šautas vanduo" << endl;
		cout << "O - laivas, X - šautas laivas" << endl;
		cout << "Sintaksė: <y koordinatė>; <x koordinatė>" << endl;
		cout << endl;
		cout << "Kur Šausite?" << endl;

		//Vartotojo eilė

		int suvisx, suvisy; //Vartotojo šūvio koordinatės

		int praetasx, praetasy; //Kompiuterio praeto ėjimo šūvio koordindatės
		int cpuorientacija = rand() % 2; //Kompiuterio orientacija (0 - horz, 1 - vert),
		//naudojama taikymui
		int cpuorientacija2 = 1; //jeigu praetame šūvyje pataikė, bus šauname į tą vietą + šis skaičius
		bool cputaiko = false; //Ar kompiuteris taiko kokį nors laivą

		//tikrinama įvestis, jeigu ji nėra tarp 0 ir 9, prašoma pakartoti

		while( (cout << "y = ") && (!(cin >> suvisy) || suvisy > 9 || suvisy < 0) )
		{
			cout << "Netinkama koordinatė!" << endl;
			cin.clear();
			cin.ignore(INT32_MAX,'\n');
		}
		while( (cout << "x = ") && (!(cin >> suvisx) || suvisx > 9 || suvisx < 0) )
		{
			cout << "Netinkama koordinatė!" << endl;
			cin.clear();
			cin.ignore(INT32_MAX,'\n');
		}
		
		//metamas eroras jeigu vieta jau šauta
		if(kompo.statusas(suvisx, suvisy) == 1 || kompo.statusas(suvisx, suvisy) == 3)
		{
			isvalyti();
			cout << "Šią vietą jau šovei!" << endl << endl;
		}
		else
		{
			//Jei viskas gerai, šaunama į nurodytą vietą

			kompo.suvis(suvisx, suvisy);

			//Kompiuterio eilė

			bool sauta = false;
			while(!sauta)
			{
				if(!cputaiko) //jei nepataike
				{
					//atsitiktinai ieškoma vieta kur dar nėra šauta
					int ksuvisx = rand() % 10;
					int ksuvisy = rand() % 10;
					if(zmogaus.statusas(ksuvisx, ksuvisy) == 0 || zmogaus.statusas(ksuvisx, ksuvisy) == 2)
					{
						zmogaus.suvis(ksuvisx, ksuvisy);
						//Įsimenamos šūvio koordinatės ir ar buvo į laivą pataikyta
						praetasx = ksuvisx;
						praetasy = ksuvisy;
						if(zmogaus.statusas(ksuvisx, ksuvisy) == 3)
						{
							//cputaiko = true;
						}
						else
						{
							cputaiko = false;
						}
						sauta = true;
					}
				}
				/*
				else
				{
					//jeigu pataikė, kompiuteris bando rasti daugiau laivo daliu

					//0 - horizontaliai
					//1 - vertikaliai
					if(cpuorientacija == 0)
					{
						//if(ksuvisx+cpuorientacija2, ksuvisy) == 3)

						zmogaus.suvis(praetasx+cpuorientacija2, praetasy);
						//jei nepataikė, bandoma kita pusė
						if(zmogaus.statusas(praetasx+cpuorientacija2, praetasy) == 1)
						{
							if(cpuorientacija2 == -1)
							{
								//jei vis dar nepataike, tai bandoma vertikaliai
								cpuorientacija = 1;
							}
							cpuorientacija2 = -1;
						}
						//jei pataikė, tai toliau einama į tą pusę
						else
						{
							cpuorientacija2++;
						}
						sauta = true;
					}
					else
					{
						zmogaus.suvis(praetasx, praetasy+cpuorientacija2);
						//jei nepataikė, bandoma kita pusė
						if(zmogaus.statusas(praetasx, praetasy+cpuorientacija2) == 1)
						{
							if(cpuorientacija2 == -1)
							{
								//jei vis dar nepataike, tai matyt nebeliko i ka sauti
								cputaiko = false;
							}
							cpuorientacija2 = 1;
						}
						//jei pataikė, tai toliau einama į tą pusę
						else
						{
							cpuorientacija2++;
						}
						sauta = true;
					}
				}
				*/
			}
			isvalyti();
			//cout << praetasx << endl;
			//cout << praetasy << endl;
			//cout << endl;
		}
	}

	//Žaidimo pabaiga

	isvalyti();
	cout << "Žaidimas baigtas - ";
	if( zmogaus.aryralaivu() && !kompo.aryralaivu() ) { cout << "Pergalė!" << endl; }
	else if ( !zmogaus.aryralaivu() && !kompo.aryralaivu() ) { cout << "Lygiosios!" << endl; }
	else { cout << "Pražūtis!" << endl; }

	cout << "---Paskutinis ekranas---" << endl;
	cout << endl;
	cout << "Tavo lenta" << endl;
	zmogaus.piestlenta();
	cout << endl;
	cout << "Kompiuterio lenta" << endl;
	kompo.piestlenta();
	
	return 0;
}

void isvalyti()
{
	/*
	šiaip galima būtų tiesiog system("cls"); padaryti, bet
	kažkodėl repl-ui tai nepatinka tai googlas sakė šitą naudoti
	*/
	cout << "\033[2J\033[1;1H";
}

void linija(int x)
{
	for(int i = 0; i < x; i++)
	{
		cout << "-";
	}
	cout << endl;
}