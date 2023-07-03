#include<stdio.h>
#include<string.h>
#include<math.h>
#include<malloc.h>


typedef struct
{
	char naziv_igre[21];
	char naziv_izdavaca[21];
	int god_iz;
} Videoigra;

typedef struct Celija
{
	Videoigra element;
	struct Celija* psljedeca;
} CelijaVideoigra;

typedef struct
{
	CelijaVideoigra* pizlaz;
	CelijaVideoigra* pulaz;
} RedVideoigra;


void unosVideoigre(Videoigra* pvideoigra);

void ubaci(Videoigra noviElement, RedVideoigra* pred);
void ispisi(RedVideoigra* pred);
void obrisi(RedVideoigra* pred);
void izmijeni(Videoigra izmijenjeniElement, Videoigra originalniElement, RedVideoigra* pred);
void ispisi_v2(RedVideoigra* pred, int godina);

int main()
{
	RedVideoigra redVideoigara;
	redVideoigara.pulaz = (CelijaVideoigra*)malloc(sizeof(CelijaVideoigra));
	redVideoigara.pulaz->psljedeca = NULL;
	redVideoigara.pizlaz = redVideoigara.pulaz;

	Videoigra videoigra;
	Videoigra originalnaVideoigra, izmijenjenaVideoigra;

	char noviUnos;
	char izbornik;

	unosVideoigre(&videoigra);
	ubaci(videoigra, &redVideoigara);

	while (1) {
		printf("\n\n\t Pocetni izbornik");
		printf("\n\tUnesite koju operaciju zelite izvrsiti:\n");

		do {
			printf("Za sljedeci unos: 'U'\n Za ispis: 'I'\n Za brisanje: 'B'\n Za promjenu: 'P'\n Za pretrazivanje po godini: 'T'\n");
			scanf_s(" %c", &izbornik, 1);
		} while (izbornik != 'U' && izbornik != 'I' && izbornik != 'B' && izbornik != 'P' && izbornik != 'T');

		if (izbornik == 'U') {
			unosVideoigre(&videoigra);
			ubaci(videoigra, &redVideoigara);
		}
		else if (izbornik == 'B') {
			obrisi(&redVideoigara);
		}
		else if (izbornik == 'P') {
			printf("\n\n\n\n Unesite naziv videoigre za koju zelite izmijeniti podatke: ");
			scanf_s("%20s", originalnaVideoigra.naziv_igre, 21);
			printf("\n\n\t --- Unesite nove podatke --- ");
			unosVideoigre(&izmijenjenaVideoigra);

			izmijeni(izmijenjenaVideoigra, originalnaVideoigra, &redVideoigara);
			printf("\n\n\n\n ... Ispis nakon izmjene podataka ...");
			ispisi(&redVideoigara);
		}
		else if (izbornik == 'I') {
			printf("\n\tIspis nakon unosa videoigara\n");
			ispisi(&redVideoigara);
		}

		else if (izbornik == 'T') {
			int trazenaGodina;
			printf("\n Unesite godinu za pretragu: ");
			scanf_s("%d", &trazenaGodina);
			printf("\n\tIspis videoigara za godinu %d:\n", trazenaGodina);
			ispisi_v2(&redVideoigara, trazenaGodina);
		}

		printf("\n\nZelite li se vratiti u izbornik (DA - 'D', NE - 'N') \n");
		scanf_s(" %c", &noviUnos, 1);
		if (noviUnos == 'N') {
			printf("Program zavrsava");
			break;
		}

	}

	printf("\n\n");
	return 0;
}



void unosVideoigre(Videoigra* pvideoigra)
{
	printf("\n Unesite naziv videoigre: ");
	scanf_s("%20s", pvideoigra->naziv_igre, 21);

	printf(" Unesite naziv izdavaca videoigre: ");
	scanf_s("%20s", &pvideoigra->naziv_izdavaca, 21);

	printf(" Unesite godinu izdanja/izlaska videoigre: ");
	scanf_s("%d", &pvideoigra->god_iz);

}


void ubaci(Videoigra noviElement, RedVideoigra* pred)
{
	pred->pulaz->psljedeca = (CelijaVideoigra*)malloc(sizeof(CelijaVideoigra));
	pred->pulaz = pred->pulaz->psljedeca;

	pred->pulaz->element = noviElement;
	pred->pulaz->psljedeca = NULL;
}


void ispisi(RedVideoigra* pred)
{
	CelijaVideoigra* ptrenutnaCelija = pred->pizlaz;
	int brig = 0;

	if (pred->pizlaz != pred->pulaz)
	{
		while (ptrenutnaCelija->psljedeca != NULL)
		{
			ptrenutnaCelija = ptrenutnaCelija->psljedeca;

			printf("\n");
			printf("\n Naziv videoigre: %s ", ptrenutnaCelija->element.naziv_igre);
			printf("\n Naziv izdavaca igre: %s ", ptrenutnaCelija->element.naziv_izdavaca);
			printf("\n Godina izdanja/izlaska videoigre: %d ", ptrenutnaCelija->element.god_iz);

			brig++;
		}

		printf("\n\n UKUPNO VIDEOIGARA %d", brig);
	}
}


void obrisi(RedVideoigra* pred)
{
	CelijaVideoigra* ptrenutnaCelija = pred->pizlaz;
	CelijaVideoigra* pprethodnaCelija = NULL;
	char nazivVideoigre[21];
	int pronadena = 0;

	if (pred->pizlaz == pred->pulaz)
	{
		printf("\n Red je prazan. ");
		return;
	}

	printf("\n Unesite naziv videoigre koju zelite izbrisati: ");
	scanf_s("%20s", nazivVideoigre, 21);

	while (ptrenutnaCelija->psljedeca != NULL)
	{
		pprethodnaCelija = ptrenutnaCelija;
		ptrenutnaCelija = ptrenutnaCelija->psljedeca;

		if (strcmp(ptrenutnaCelija->element.naziv_igre, nazivVideoigre) == 0)
		{
			pronadena = 1;
			break;
		}
	}

	if (pronadena)
	{
		pprethodnaCelija->psljedeca = ptrenutnaCelija->psljedeca;
		free(ptrenutnaCelija);
		printf("\n Videoigra '%s' je izbrisana.", nazivVideoigre);
	}
	else
	{
		printf("\n Videoigra '%s' nije pronadena u redu.", nazivVideoigre);
	}
}


void izmijeni(Videoigra izmijenjeniElement, Videoigra originalniElement, RedVideoigra* pred)
{
	CelijaVideoigra* ptrenutnaCelija = pred->pizlaz;

	while (ptrenutnaCelija->psljedeca != NULL)
	{
		ptrenutnaCelija = ptrenutnaCelija->psljedeca;

		if (strcmp(ptrenutnaCelija->element.naziv_igre, originalniElement.naziv_igre) == 0)
		{
			ptrenutnaCelija->element = izmijenjeniElement;
		}
	}
}

void ispisi_v2(RedVideoigra* pred, int godina)
{
	CelijaVideoigra* ptrenutnaCelija = pred->pizlaz;
	int brojac = 0;
	int pronadeno = 0;

	while (ptrenutnaCelija->psljedeca != NULL)
	{
		ptrenutnaCelija = ptrenutnaCelija->psljedeca;

		if (ptrenutnaCelija->element.god_iz == godina)
		{
			printf("\n");
			printf("\n Naziv videoigre: %s ", ptrenutnaCelija->element.naziv_igre);
			printf("\n Naziv izdavaca igre: %s ", ptrenutnaCelija->element.naziv_izdavaca);
			printf("\n Godina izdanja/izlaska videoigre: %d ", ptrenutnaCelija->element.god_iz);

			brojac++;
			pronadeno = 1;
		}
		else if (ptrenutnaCelija->element.god_iz > godina)
		{
			break;
		}
	}

	if (pronadeno)
	{
		printf("\n\n Ukupan broj videoigara u godini %d je  %d", godina, brojac);
	}
	else
	{
		printf("\n Nema videoigara za %d godinu", godina);
	}
}



