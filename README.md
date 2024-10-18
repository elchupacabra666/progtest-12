# Evidence zaměstnanců

- **Hodnocení**: 5.0 bodů (maximálně 6.25 bodů)
- **Termín odevzdání**: 03.04.2023 11:59:59

## Zadání

Úkolem je realizovat třídu `CPersonalAgenda`, která bude implementovat databázi zaměstnanců.

Pro usnadnění práce HR oddělení máme realizovanou databázi zaměstnanců. Pro sledované zaměstnance si pamatujeme jméno, příjmení, email a plat. V průběhu evidence zaměstnance se tyto údaje mohou měnit, údaje chceme vyhledávat a chceme mít přehled o platech.

Zaměstnanec je identifikován svým jménem a příjmením nebo svým e-mailem. Firemní postupy zajišťují, že e-mail je unikátní přes celou databázi. Dvojice (jméno, příjmení) je v databázi unikátní. Při porovnávání jmen, příjmení i e-mailů rozlišujeme malá a velká písmena (_case sensitive_).

### Rozhraní třídy obsahuje následující:

- **Konstruktor bez parametrů** - Inicializuje prázdnou instanci třídy.
- **Destruktor** - Uvolňuje alokované prostředky.
- **`add(name, surname, email, salary)`** - Přidá záznam o zaměstnanci. Vrací `true`, pokud byl přidán, nebo `false`, pokud již existuje záznam se stejným jménem a příjmením nebo e-mailem.
- **`del(name, surname)`** / **`del(email)`** - Odstraní záznam o zaměstnanci podle jména a příjmení, nebo podle e-mailu. Vrací `true`, pokud byl záznam odstraněn, nebo `false`, pokud neexistoval.
- **`changeName(email, newName, newSurname)`** - Změní jméno a příjmení zaměstnance. Vrací `true` pro úspěch, nebo `false` pro chybu (zaměstnanec neexistuje, nové jméno není unikátní).
- **`changeEmail(name, surname, newEmail)`** - Změní e-mail zaměstnance. Vrací `true` pro úspěch, nebo `false` pro chybu (zaměstnanec neexistuje, e-mail není unikátní).
- **`setSalary(name, surname, salary)`** / **`setSalary(email, salary)`** - Změní plat zaměstnanci podle jména a příjmení, nebo e-mailu. Vrací `true` pro úspěch, nebo `false` pro chybu (zaměstnanec neexistuje).
- **`getSalary(name, surname)`** / **`getSalary(email)`** - Zjistí plat zaměstnance podle jména a příjmení, nebo e-mailu. Vrací plat zaměstnance, nebo `0`, pokud zaměstnanec neexistuje.
- **`getRank(name, surname, rankMin, rankMax)`** / **`getRank(email, rankMin, rankMax)`** - Zjistí pozici platu zaměstnance v žebříčku platů. Vrací `true` pro úspěch, nebo `false` pro chybu.
- **`getFirst(outName, outSurname)`** - Vrátí prvního zaměstnance podle abecedy. Vrací `true`, pokud není databáze prázdná, nebo `false` pro prázdnou databázi.
- **`getNext(name, surname, outName, outSurname)`** - Vrátí dalšího zaměstnance v abecedním pořadí. Vrací `true` pro úspěch, nebo `false` pro chybu.

### Poznámky

- Implementujte třídu efektivně z hlediska času i paměti.
- Časté operace jako `getSalary` a `setSalary` musí být rychlejší než lineární (_logaritmická nebo amortizovaná konstantní složitost_).
- Pro bonusový test zvažte efektivnější algoritmy pro metodu `getRank`.

Odevzdávejte soubor s kompletní implementací třídy `CPersonalAgenda`, včetně konstruktoru, destruktoru, metod a potřebných testů.
