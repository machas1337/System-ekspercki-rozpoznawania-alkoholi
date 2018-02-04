# System-ekspercki-rozpoznawania-alkoholi

Projekt zrealizowany w ramach zaliczenia przedmiotu "Narzędzia i metody sztucznej inteligencji"
Poszczególne punkty są przekopiowane z dokumentacji stąd też numeracja może się nie zgadzać.


# 1 Wstęp 
Projekt został stworzony z wykorzystaniem następujących technik i technologi: 

  • język programowania C++11 
  
  • narzędzie programistyczne Qt w wersji 5.5.1 
  
  • środowisko programistyczne Qt Creator w wersji 4.5.0 
  
  • kompilator MSVC2010 w wersji 32bit
  
  
Zadaniem programu jest na podstawie odpowiedzi użytkownika wybranie najbardziej prawdopodobnej odpowiedzi na podstawie pliku tekstowego zawierającego dane bazodanowe na temat alkoholi. Schemat działania programu jest opisany w późniejszych rozdziałach dokumentacji. Rolę Eksperta w tym projekcie pełnił internet, konkretnie dwie strony internetowe: wikipedia.pl oraz swiatalkoholi.pl.



# 3 Instrukcja korzystania 

W niniejszym rozdziale przedstawię instrukcję korzystania z programu dla użytkownika jak i instrukcje wymagane do samodzielnej kompilacji programu przy pomocy środowiska programistycznego Qt w wersji 4.5.0.

3.1 Samodzielna kompilacja

Aby samodzielnie skompilować projekt należy wykonać następujące czynności: 

1. Pobrać kompilator  MSVC2010. 1.1. Można ten pominąć punkt jeżeli ktoś posiada zainstalowane obecnie oprogramowanie Microsoft Visual Studio 2010 bądź nowsze. 

2. Pobrać środowisko programistyczne Qt 4.5.0 (przykładowe źródło do pobrania: https://download.qt.io/archive/qt/4.5/ ) i zainstalować. 

3. Uruchomić program Qt Creator. 

4. Wybrać dostępną opcję „Otwórz Projekt” (Znajduje się w centralnej części ekranu powitalnego bądź w menu „Plik → Otwórz plik lub projekt”). 

5. Wybrać dostępny w folderze projektu plik: „SystemRozpoznawaniaAlkoholi → project → alkoo.pro”. 

6. W lewym dolnym rogu wybrać Zestaw narzędzi (ikona monitora) i następnie wybrać odpowiedni zestaw narzędzi – rekomendowany jest w celu kompilacji zestaw „Dekstop Qt 5.5.1 MSVC2010 32bit”. 

7. Wybrać opcję „Uruchom” bądź wcisnąć kombinację klawiszy CTRL + R. 

8. Program został skompilowany i uruchomiony.


# 4 Obliczania punktów odpowiedzi

4.1 Objaśnienie obliczania ilości punktów 

Każda odpowiedź będzie porównywana z odpowiednim alkoholem, oto następujące reguły wykorzystywane przy obliczeniach:

• za każda identyczną  pojedynczą odpowiedź (w przypadku stężenia mieszczenie się w danym zakresie liczbowym) otrzymuje dana odpowiedź +10 punktów. 

• za każdą „bliską” odpowiedź, tzn. przy alkoholach o wielu parametrach, to zostaje przyznane, za każdą prawidłową odpowiedź, +4 punkty. 

• Za każdą „złą” odpowiedź, tzn. przy alkoholach o wielu parametrach, to zostają odjęte, za każdą niewłaściwą odpowiedź -3 punkty. W przypadku stężenia za każdą różnicę 4% od stężenia alkoholu jest ujmowane -7 punkty. 

• Alkohol/-e z największą zebraną ilością punktów zostaje/-ą wyświetlone dla użytkownika.


Przykład: Użytkownik podał jako jako poszczególne odpowiedzi: 

1. kolor: brązowy, złoty 

2. stężenie: 37% 

3. zapach: słodki 

4. gazowany: nie 

5. pochodzenie: Europa 

6. smak: słodki

Dla alkoholu Amagnac będzie wyglądać następująco punktacja: 

1. kolor: brązowy, złoty +4 x 2 pkt (za każdą pasującą opcje) 

2. stężenie: 37% -7 pkt (bo różnica alkoholu wynosi: 40 – 37= 3) 

3. zapach: słodki +10 pkt (pasująca idealnie pojedyncza opcja) 

4. gazowany: nie +10 pkt ((pasująca idealnie pojedyncza opcja)

5. pochodzenie: Europa +10 pkt ((pasująca idealnie pojedyncza opcja) 

6. smak: słodki +10 pkt ((pasująca idealnie pojedyncza opcja) 

Suma punktów: 41 punktów. Następnie są porównywane wszystkie alkohole według powyższego szablonu i wybierany ten, co uzyskał największy wynik.


# 6 Zawartość i opis pliku „database.txt” 

Plik tekstowy database.txt jest plikiem zawierającym bazę przedstawioną w punkcie 4.2, dla uproszczenia określona odpowiednim schematem. Objaśnienie skrótów i znaków szczególnych: 

• symbol „:” oznacza granicę kategorii danego rekordu, 

• symbol „,” oznacza kolejny argument tej samej kategorii, 

• symbol końca linii oznacza przejście do kolejnego produktu 

• symbol „#” na początku linii oznacza komentarz i nie jest brany pod uwagę w trakcie przetwarzania pliku 

• objaśnienie skrótów: 
    ◦ n - nie 
    ◦ t - tak 
    ◦ eur - Europa
    ◦ azj - Azja
    ◦ amp - Ameryka Północna 
    ◦ ams - Ameryka Południowa 
    ◦ aus - Austalia 
    ◦ afr - Afryka 
    
• różnica w zastosowaniu „slodki” i „slodki2” wynika z powtórzenia tego samego elementu w receptorach smaku i zapachu – aby nie fałszować wyników stała „slodki” odnosi się do zapachu zaś „slodki2” do smaku. 

Przykładowy fragment

Absynt:zielony:45-80:ziolowy:n:eur:gorzki
