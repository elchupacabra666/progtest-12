#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

/*
 *    Úkolem je realizovat třídu CPersonalAgenda, která bude implementovat databázi zaměstnanců.
 *
 *   Pro usnadnění práce HR oddělení máme realizovanou databázi zaměstnanců. Pro sledované zaměstnance si pamatujeme jméno,
 *    příjmení, email a plat. V průběhu evidence zaměstnance se tyto údaje mohou měnit, údaje chceme vyhledávat a chceme mít
 *    přehled o platech.
 *
 *   Zaměstnanec je identifikován svým jménem a příjmením nebo svým e-mailem. Firemní postupy zajišťují, že e-mail je
 *    unikátní přes celou databázi. Dále, jména a příjmení se mohou opakovat, ale dvojice (jméno, příjmení) je opět v
 *    databázi unikátní. Tedy v databázi může být mnoho lidí s příjmením Svoboda, mnoho lidí může mít jméno Petr, ale
 *    zaměstnanec Svoboda Petr může být v databázi v daném okamžiku pouze jeden. Při porovnávání jmen, příjmení i e-mailů
 *    rozlišujeme malá a velká písmena (case sensitive).
 *
 *   Veřejné rozhraní je uvedeno níže. Obsahuje následující:
 *
 *   Konstruktor bez parametrů. Tento konstruktor inicializuje instanci třídy tak, že vzniklá instance je zatím prázdná
 *    (neobsahuje žádné záznamy).
 *   Destruktor. Uvolňuje prostředky, které instance alokovala.
 *   Metoda add(name, surname, email, salary) přidá do existující databáze další záznam. Parametry name a surname
 *   reprezentují jméno a příjmení, parametr email udává mailovou adresu a salary plat. Metoda vrací hodnotu true,
 *    pokud byl záznam přidán, nebo hodnotu false, pokud přidán nebyl (protože již v databázi existoval záznam se
 *    stejným jménem a příjmením, nebo záznam se stejným e-mailem).
 *   Metody del (name, surname) / del (email) odstraní záznam z databáze. Parametrem je jednoznačná identifikace pomocí
 *    jména a příjmení (první varianta) nebo pomocí emailu (druhá varianta). Pokud byl záznam skutečně odstraněn, vrátí
 *    metoda hodnotu true. Pokud záznam odstraněn nebyl (protože neexistoval zaměstnanec s touto identifikací), vrátí
 *    metoda hodnotu false.
 *   Metoda changeName(email, newName, newSurname) změní zaměstnanci jeho jméno a příjmení. Zaměstnanec je identifikován
 *    pomocí e-mailu email, jméno zaměstnance je změněno na newName/newSurname. Metoda vrátí true pro úspěch, false pro
 *    chybu (neexistuje zaměstnanec s takovým e-mailem, nově přidělené jméno/příjmení není unikátní).
 *   Metoda changeEmail(name, surname, newEmail) změní zaměstnanci jeho email. Zaměstnanec je identifikován pomocí jména
 *    a příjmení name/surname, e-mail zaměstnance je změněn na newEmail. Metoda vrátí true pro úspěch, false pro
 *    chybu (neexistuje zaměstnanec s takovým jménem a příjmením, nově přidělený e-mail není unikátní).
 *   Metody setSalary (name, surname, salary) / setSalary (email, salary) změní výši výplaty zadanému zaměstnanci.
 *    Varianty jsou dvě - zaměstnanec je identifikován buď svým jménem a příjmením, nebo svojí e-mailovou adresou.
 *    Pokud metoda uspěje, vrací true, pro neúspěch vrací false (neexistující zaměstnanec).
 *   Metody getSalary (name, surname) / getSalary (email) zjistí výši výplaty zadaného zaměstnance. Varianty jsou
 *    dvě - zaměstnanec je identifikován buď svým jménem a příjmením, nebo svojí e-mailovou adresou. Pokud metoda uspěje,
 *    vrací výši výplaty zaměstnance, pro neúspěch (neexistující zaměstnanec) vrací hodnotu 0.
 *   Metody getRank (name, surname, rankMin, rankMax) / getRank (email, rankMin, rankMax) zjistí jak dobře je zaměstnanec
 *    placen ve vztahu k ostatním. Výsledkem je pozice výplaty zadaného zaměstnance na pomyslném žebříčku výplat od
 *    nejhorší (nejnižší) k nejlepší (nejvyšší). Parametrem je identifikace zaměstnance (podle varianty buď
 *    jménem a příjmením, nebo e-mailovou adresou), parametry rankMin/rankMax jsou výstupní, do nich funkce zapíše
 *    pozici výplaty hledaného zaměstnance v žebříčku. Protože stejnou výplatu může dostávat více zaměstnanců, je
 *    výstupem dvojice hodnot - interval min-max. Pokud například hledaný zaměstnanec dostává výplatu 20000,
 *    37 zaměstnanců dostává výplatu nižší a 21 dalších zaměstnanců dostává výplatu stejnou (tedy plat 20000 dostává
 *    celkem 22 zaměstnanců), pak výsledkem je rankMin=37 a rankMax=37+22-1=58. Návratovou hodnotou funkce je true pro
 *    úspěch (zadaný zaměstnanec nalezen, výstupní parametry vyplněny) nebo false (zadaný zaměstnanec nenalezen,
 *    výstupní parametry ponechány beze změn).
 *   Metoda getFirst ( outName, outSurname ) slouží pro procházení databází. Zaměstnance chceme procházet podle abecedy
 *    (seřazené vzestupně podle příjmení, v případě stejných příjmení podle jména). Metoda vrátí prvního zaměstnance v
 *    takto seřazeném seznamu, jeho jméno a příjmení zapíše do zadaných výstupních parametrů outName/outSurname.
 *    Návratovou hodnotou je true pro úspěch (databáze nebyla prázdná) nebo false (prázdná databáze, výstupní parametry
 *    ponechány beze změn).
 *   Metoda getNext ( name, surname, outName, outSurname ) slouží k procházení zaměstnanců podobně jako metoda getFirst.
 *    Tato metoda vrátí dalšího zaměstnance, který v seřazeném seznamu zaměstnanců (viz getFirst) následuje po
 *    zaměstnanci name/surname. Jméno následujícího zaměstnance zapíše do zadaných výstupních parametrů outName/outSurname.
 *    Návratovou hodnotou je true pro úspěch (zaměstnanec name/surname nalezen a není poslední v seřazeném seznamu) nebo
 *    false pro neúspěch (zaměstnanec name/surname nenalezen nebo je poslední v seznamu). V případě neúspěchu metoda nebude
 *    měnit výstupní parametry outName/outSurname.
 *
 *   Odevzdávejte soubor, který obsahuje implementovanou třídu CPersonalAgenda. Třída musí splňovat veřejné rozhraní podle
 *    ukázky - pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy si ale
 *    můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Dále si do odevzdávaného souboru můžete
 *    doplnit další podpůrné funkce nebo třídy. Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní),
 *    tak i definice metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline nebo odděleně.
 *    Odevzdávaný soubor nesmí obsahovat vkládání hlavičkových souborů a funkci main (funkce main a vkládání hlavičkových
 *    souborů může zůstat, ale pouze obalené direktivami podmíněného překladu). Za základ implementace použijte přiložený
 *    zdrojový soubor.
 *
 *   Rozhraní třídy obsahuje řadu metod ve dvou variantách, které se liší pouze způsobem identifikace zaměstnance. Je
 *    vhodné věnovat nenulový čas návrhu třídy tak, abyste všechen výkonný kód nekopírovali 2x (např. realizujte privátní
 *    metody, které budete volat z více veřejných metod).
 *
 *   Třída je testovaná v omezeném prostředí, kde je limitovaná dostupná paměť (dostačuje k uložení seznamu) a je omezena
 *    dobou běhu. Implementovaná třída se nemusí zabývat kopírujícím konstruktorem ani přetěžováním operátoru =. V této
 *    úloze ProgTest neprovádí testy této funkčnosti.
 *
 *   Implementace třídy musí být efektivní z hlediska nároků na čas i nároků na paměť. Jednoduché lineární řešení nestačí
 *    (pro testovací data vyžaduje čas přes 5 minut). Předpokládejte, že vkládání a mazání zaměstnance jsou řádově méně
 *    časté než ostatní operace, tedy zde je lineární složitost akceptovatelná. Častá jsou volání getSalary a setSalary,
 *    jejich časová složitost musí být lepší než lineární (např. logaritmická nebo amortizovaná konstantní). Dále, metody
 *    getFirst/getNext by též měly být efektivní, jejich složitost by též měla být lepší než lineární.
 *
 *   V povinných testech se metoda getRank volá málo často, tedy nemusí být příliš efektivní (pro úspěch v povinných
 *    testech stačí složitost lineární nebo n log n, pro bonusový test je potřeba složitost lepší než lineární. Pokud
 *    nechcete vymýšlet efektivní algoritmus pro bonusový test, zaměřte se spíše na to, aby volání setSalary byla efektivní
 *    i za cenu méně efektivní metody getRank.
 *
 *   Bonusový test lze vyřešit několika způsoby. Při návrhu řešení můžete využít znalosti, že zadávaná hodnota mzdy je
 *    nejvýše 1000000. Dále může pomoci znalost, že hodnoty mezd se často opakují.
 *
 *   Pro uložení hodnot alokujte pole dynamicky případně použijte STL. Pozor, pokud budete pole alokovat ve vlastní režii,
 *    zvolte počáteční velikost malou (např. tisíc prvků) a velikost zvětšujte/zmenšujte podle potřeby. Při zaplnění pole
 *    není vhodné alokovat nové pole větší pouze o jednu hodnotu, takový postup má obrovskou režii na kopírování obsahu.
 *    Je rozumné pole rozšiřovat s krokem řádově tisíců prvků, nebo geometrickou řadou s kvocientem ~1.5 až 2.
 *
 *   Pokud budete používat STL, nemusíte se starat o problémy s alokací. Pozor - k dispozici máte pouze část STL
 *    (viz hlavičkové soubory v přiložené ukázce). Tedy například kontejnery map / unordered_map / set / unordered_set / ...
 *    nejsou k dispozici.
 *
 *   V přiloženém zdrojovém kódu jsou obsažené základní testy. Tyto testy zdaleka nepokrývají všechny situace, pro
 *    odladění třídy je budete muset rozšířit. Upozorňujeme, že testy obsažené v odevzdaných zdrojových kódech považujeme
 *    za nedílnou součást Vašeho řešení. Pokud v odevzdaném řešení necháte cizí testy, může být práce vyhodnocena jako
 *    opsaná.
 *
 *   Správné řešení této úlohy, které splní závazné testy na 100%, může být odevzdáno k code review. (Tedy pro code
 *    review nemusíte zvládnout bonusové testy.)
 *
 *
 *
 */




struct Person{
	string name;
	string surname;
	string email;
	unsigned int salary;
};


class CPersonalAgenda {
	public:
	//CPersonalAgenda(void);

	//~CPersonalAgenda(void);

	bool add(const string &name,
		 const string &surname,
		 const string &email,
		 unsigned int salary);

	bool del(const string &name,
		 const string &surname);

	bool del(const string &email);

	bool changeName(const string &email,
			const string &newName,
			const string &newSurname);

	bool changeEmail(const string &name,
			 const string &surname,
			 const string &newEmail);

	bool setSalary(const string &name,
		       const string &surname,
		       unsigned int salary);

	bool setSalary(const string &email,
		       unsigned int salary);

	unsigned int getSalary(const string &name,
			       const string &surname) const;

	unsigned int getSalary(const string &email) const;

	bool getRank(const string &name,
		     const string &surname,
		     int &rankMin,
		     int &rankMax) const;

	bool getRank(const string &email,
		     int &rankMin,
		     int &rankMax) const;

	bool getFirst(string &outName,
		      string &outSurname) const;

	bool getNext(const string &name,
		     const string &surname,
		     string &outName,
		     string &outSurname) const;

	void print();

	private:
	friend bool operator==(const Person &x, const Person &y);
	long binarySearchName(const string &name, const string &surname) const;
	long binarySearchEmail(const string &email) const;
	unsigned int linearSearchName(const string &email);
	unsigned int linearSearchEmail(const string &name, const string &surname);

	vector<Person> vectorName;		//vector that stores names (first criteria to sort is surname, second one is name)
	vector<Person> vectorEmail;		//vector that stores emails
};

//two people are same if they have same name and surname or same email address
bool operator==(const Person &x, const Person &y){

	if ((x.name == y.name) && (x.surname == y.surname))
		return true;

	if (x.email == y.email)
		return true;

	return false;
}


void CPersonalAgenda::print() {
	unsigned int sizeName = vectorName.size();
	cout << "vectorName:" << endl;
	for (unsigned int i = 0; i < sizeName; i++) {
		cout << vectorName[i].name << "\t\t" << vectorName[i].surname << "\t\t" << vectorName[i].email << endl;
	}
	cout << "vectorEmail:" << endl;
	unsigned int sizeEmail = vectorEmail.size();
	for (unsigned int i = 0; i < sizeEmail; i++) {
		cout << vectorEmail[i].name << "\t\t" << vectorEmail[i].surname << "\t\t" << vectorEmail[i].email << endl;
	}
}


bool compName(const Person &x, const Person &y) {

	if (x.surname < y.surname)
		return true;
	if (x.surname > y.surname)
		return false;
	if (x.name < y.name)
		return true;
	return false;

}

bool compEmail(const Person &x, const Person &y) {

	if (x.email < y.email)
		return true;
	return false;
}


//returns -1 if person with email is not stored
//or returns position of person with email
long CPersonalAgenda::binarySearchEmail(const string &email) const {

	Person newPerson = {"", "", email, 0};

	auto it = lower_bound(vectorEmail.begin(), vectorEmail.end(), newPerson, compEmail);
	long i = distance(vectorEmail.begin(), it);
	if (it != vectorEmail.end() && vectorEmail[i].email == email)
		return i;
	return -1;

}

//returns -1 if person with name and surname is not stored
//or returns position of person with name and surname
long CPersonalAgenda::binarySearchName(const string &name, const string &surname) const {

	Person newPerson = {name, surname, "", 0};

	auto it = lower_bound(vectorName.begin(), vectorName.end(), newPerson, compName);
	long i = distance(vectorName.begin(), it);
	if (it != vectorName.end() && vectorName[i].name == name && vectorName[i].surname == surname)
		return i;
	return -1;


}
//adds person to vectorName and vectorEmail
bool CPersonalAgenda::add(const string &name, const string &surname, const string &email, unsigned int salary) {

	Person newPerson = {name, surname, email, salary};

	//returns false if person does not exist
	if (binarySearchName(name, surname) != -1) {
		return false;
	}
	if (binarySearchEmail(email) != -1) {
		return false;
	}
	unsigned int size = vectorName.size();
	unsigned int i;

	//insert into position found with the loop, maybe I could use the binarySearchName function (too lazy)
	for (i = 0; i < size; i++) {
		if (vectorName[i].surname > surname)
			break;
		if (vectorName[i].surname == surname && vectorName[i].name > name)
			break;
	}

	vectorName.insert(vectorName.begin() + i, newPerson);

	for (i = 0; i < size; i++) {
		if (vectorEmail[i].email > email)
			break;
	}
	vectorEmail.insert(vectorEmail.begin() + i, newPerson);


	return true;
}

//deletes person using name and surname
bool CPersonalAgenda::del(const string &name, const string &surname) {

	long i;

	//person does not exist, return false
	if ((i = binarySearchName(name, surname)) == -1)
		return false;

	string email = vectorName[i].email;

	vectorName.erase(vectorName.begin() + i);

	i = binarySearchEmail(email);

	vectorEmail.erase(vectorEmail.begin() + i);

	return true;
}

//deletes person using email
bool CPersonalAgenda::del(const string &email) {
	long i;
	if ((i = binarySearchEmail(email)) == -1)
		return false;

	string name = vectorEmail[i].name;
	string surname = vectorEmail[i].surname;

	vectorEmail.erase(vectorEmail.begin() + i);

	i = binarySearchName(name, surname);

	vectorName.erase(vectorName.begin() + i);
	return true;
}

unsigned int CPersonalAgenda::linearSearchName(const string &email) {

	unsigned int size = vectorName.size();

	for (unsigned int i = 0; i < size; i++) {
		if (vectorName[i].email == email)
			return i;
	}

	return -1;

}

unsigned int CPersonalAgenda::linearSearchEmail(const string &name, const string &surname) {

	unsigned int size = vectorEmail.size();

	for (unsigned int i = 0; i < size; i++) {
		if (vectorEmail[i].name == name && vectorEmail[i].surname == surname)
			return i;
	}

	return -1;

}


//changes name and resorts vectorName
bool CPersonalAgenda::changeName(const string &email, const string &newName, const string &newSurname) {

	long i, j;
	if ((i = binarySearchEmail(email)) == -1)
		return false;


	if (binarySearchName(newName, newSurname) != -1)
		return false;

	vectorEmail[i].name = newName;
	vectorEmail[i].surname = newSurname;

	j = linearSearchName(email);
	vectorName[j].name = newName;
	vectorName[j].surname = newSurname;

	sort(vectorName.begin(), vectorName.end(), compName);
	return true;
}

//changes Email and resorts vectorEmail
bool CPersonalAgenda::changeEmail(const string &name, const string &surname, const string &newMail) {

	long i, j;
	if ((i = binarySearchName(name, surname)) == -1)
		return false;

	if (binarySearchEmail(newMail) != -1)
		return false;

	vectorName[i].email = newMail;

	j = linearSearchEmail(name, surname);
	vectorEmail[j].email = newMail;

	sort(vectorEmail.begin(), vectorEmail.end(), compEmail);
	return true;

}

//sets salary of person with the name and the surname
bool CPersonalAgenda::setSalary(const string &name, const string &surname, unsigned int salary) {

	long i;
	if ((i = binarySearchName(name, surname)) == -1)
		return false;

	vectorName[i].salary = salary;

	i = linearSearchEmail(name, surname);

	vectorEmail[i].salary = salary;

	return true;

}

//sets salary of person with the email
bool CPersonalAgenda::setSalary(const string &email, unsigned int salary) {

	long i;
	if ((i = binarySearchEmail(email)) == -1)
		return false;

	vectorEmail[i].salary = salary;

	i = linearSearchName(email);

	vectorName[i].salary = salary;

	return true;
}

//gets salary of person with the name and the surname
unsigned int CPersonalAgenda::getSalary(const string &name, const string &surname) const {

	long i;

	if ((i = binarySearchName(name, surname)) == -1)
		return 0;

	return vectorName[i].salary;
}

//gets salary of person with the email
unsigned int CPersonalAgenda::getSalary(const string &email) const {

	long i;

	if ((i = binarySearchEmail(email)) == -1)
		return 0;

	return vectorEmail[i].salary;
}

//calculates how many people have same or worse salary (detailed information at beginning of file
bool CPersonalAgenda::getRank(const string &name, const string &surname, int &rankMin, int &rankMax) const {

	long i;
	unsigned int size = vectorName.size();
	if ((i = binarySearchName(name, surname)) == -1)
		return false;

	unsigned int salary = vectorName[i].salary;
	int min = 0;
	int max = 0;
	for (unsigned int j = 0; j < size; j++) {
		if (vectorName[j].salary < salary)
			min++;
		if (vectorName[j].salary == salary)
			max++;
	}

	rankMax = min + max - 1;
	rankMin = min;
	return true;

}

//calculates how many people have same or worse salary (detailed information at beginning of file
bool CPersonalAgenda::getRank(const string &email, int &rankMin, int &rankMax) const {

	long i;
	unsigned int size = vectorEmail.size();

	if ((i = binarySearchEmail(email)) == -1)
		return false;

	unsigned int salary = vectorEmail[i].salary;
	int min = 0;
	int max = 0;
	for (unsigned int j = 0; j < size; j++) {
		if (vectorEmail[j].salary < salary)
			min++;
		if (vectorEmail[j].salary == salary)
			max++;
	}

	rankMax = min + max - 1;
	rankMin = min;
	return true;


}

//returns name and surname of first person
bool CPersonalAgenda::getFirst(string &outName, string &outSurname) const {

	if (vectorName.empty())
		return false;
	outName = vectorName[0].name;
	outSurname = vectorName[0].surname;
	return true;
}


bool CPersonalAgenda::getNext(const string &name, const string &surname, string &outName, string &outSurname) const {

	long i;
	if ((i = binarySearchName(name, surname)) == -1)
		return false;
	if (i == long(vectorName.size() - 1))
		return false;
	outName = vectorName[i + 1].name;
	outSurname = vectorName[i + 1].surname;
	return true;
}

#ifndef __PROGTEST__

int main(void) {
	string outName, outSurname;
	int lo, hi;


	CPersonalAgenda b1;

	b1.add("c", "c", "a", 30000);
	b1.add("c", "d", "d", 30000);
	b1.add("d", "a", "c", 30000);


	b1.print();

assert (b1.add("John", "Smith", "john", 30000));

assert (b1.add("John", "Miller", "johnm", 35000));
assert (b1.add("Peter", "Smith", "peter", 23000));
assert (!b1.add("Peter", "Smith", "peter", 23000));

assert (b1.getFirst(outName, outSurname)
	&& outName == "John"
	&& outSurname == "Miller");
assert (b1.getNext("John", "Miller", outName, outSurname)
	&& outName == "John"
	&& outSurname == "Smith");
assert (b1.getNext("John", "Smith", outName, outSurname)
	&& outName == "Peter"
	&& outSurname == "Smith");
assert (!b1.getNext("Peter", "Smith", outName, outSurname));
assert (b1.setSalary("john", 32000));
assert (b1.getSalary("john") == 32000);
assert (b1.getSalary("John", "Smith") == 32000);
assert (b1.getRank("John", "Smith", lo, hi)
	&& lo == 1
	&& hi == 1);
assert (b1.getRank("john", lo, hi)
	&& lo == 1
	&& hi == 1);
assert (b1.getRank("peter", lo, hi)
	&& lo == 0
	&& hi == 0);
assert (b1.getRank("johnm", lo, hi)
	&& lo == 2
	&& hi == 2);
assert (b1.setSalary("John", "Smith", 35000));
assert (b1.getSalary("John", "Smith") == 35000);
assert (b1.getSalary("john") == 35000);
assert (b1.getRank("John", "Smith", lo, hi)
	&& lo == 1
	&& hi == 2);
assert (b1.getRank("john", lo, hi)
	&& lo == 1
	&& hi == 2);
assert (b1.getRank("peter", lo, hi)
	&& lo == 0
	&& hi == 0);
assert (b1.getRank("johnm", lo, hi)
	&& lo == 1
	&& hi == 2);
assert (b1.changeName("peter", "James", "Bond"));
assert (b1.getSalary("peter") == 23000);
assert (b1.getSalary("James", "Bond") == 23000);
assert (b1.getSalary("Peter", "Smith") == 0);
assert (b1.getFirst(outName, outSurname)
	&& outName == "James"
	&& outSurname == "Bond");
assert (b1.getNext("James", "Bond", outName, outSurname)
	&& outName == "John"
	&& outSurname == "Miller");
assert (b1.getNext("John", "Miller", outName, outSurname)
	&& outName == "John"
	&& outSurname == "Smith");
assert (!b1.getNext("John", "Smith", outName, outSurname));
assert (b1.changeEmail("James", "Bond", "james"));
assert (b1.getSalary("James", "Bond") == 23000);
assert (b1.getSalary("james") == 23000);
assert (b1.getSalary("peter") == 0);
assert (b1.del("james"));
assert (b1.getRank("john", lo, hi)
	&& lo == 0
	&& hi == 1);
assert (b1.del("John", "Miller"));
assert (b1.getRank("john", lo, hi)
	&& lo == 0
	&& hi == 0);
assert (b1.getFirst(outName, outSurname)
	&& outName == "John"
	&& outSurname == "Smith");
assert (!b1.getNext("John", "Smith", outName, outSurname));
assert (b1.del("john"));
assert (!b1.getFirst(outName, outSurname));
assert (b1.add("John", "Smith", "john", 31000));
assert (b1.add("john", "Smith", "joHn", 31000));
assert (b1.add("John", "smith", "jOhn", 31000));

CPersonalAgenda b2;
assert (!b2.getFirst(outName, outSurname));
assert (b2.add("James", "Bond", "james", 70000));
assert (b2.add("James", "Smith", "james2", 30000));
assert (b2.add("Peter", "Smith", "peter", 40000));
assert (!b2.add("James", "Bond", "james3", 60000));
assert (!b2.add("Peter", "Bond", "peter", 50000));
assert (!b2.changeName("joe", "Joe", "Black"));
assert (!b2.changeEmail("Joe", "Black", "joe"));
assert (!b2.setSalary("Joe", "Black", 90000));
assert (!b2.setSalary("joe", 90000));
assert (b2.getSalary("Joe", "Black") == 0);
assert (b2.getSalary("joe") == 0);
assert (!b2.getRank("Joe", "Black", lo, hi));
assert (!b2.getRank("joe", lo, hi));
assert (!b2.changeName("joe", "Joe", "Black"));
assert (!b2.changeEmail("Joe", "Black", "joe"));
assert (!b2.del("Joe", "Black"));
assert (!b2.del("joe"));
assert (!b2.changeName("james2", "James", "Bond"));
assert (!b2.changeEmail("Peter", "Smith", "james"));
assert (!b2.changeName("peter", "Peter", "Smith"));
assert (!b2.changeEmail("Peter", "Smith", "peter"));
assert (b2.del("Peter", "Smith"));
assert (!b2.changeEmail("Peter", "Smith", "peter2"));
assert (!b2.setSalary("Peter", "Smith", 35000));
assert (b2.getSalary("Peter", "Smith") == 0);
assert (!b2.getRank("Peter", "Smith", lo, hi));
assert (!b2.changeName("peter", "Peter", "Falcon"));
assert (!b2.setSalary("peter", 37000));
assert (b2.getSalary("peter") == 0);
assert (!b2.getRank("peter", lo, hi));
assert (!b2.del("Peter", "Smith"));
assert (!b2.del("peter"));
assert (b2.add("Peter", "Smith", "peter", 40000));
assert (b2.getSalary("peter") == 40000);

return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
