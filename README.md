Grafika Komputerowa
=====================

#Projekt 1 - Algorytmy rastrowe

Pierwsze zadanie polega na zaprojektowaniu aplikacji do rysowania prostych prymitywów. Widoczny ekran na mieć wymiary 800x600 z czarnym tłem.
Użytkownik ma możliwość dodawania i usuwania odcinków i okregów. Każdy z prymitywów można też wybrać
za pomocą kliknięcia, przesuwać i ustawiać koloru.
Dodatkowo aplikacja powinna umożliwiać opcjonalne wyświetlenie szarej siatki z wybraną szerokością kratki.
W zależności od tego czy liczba liter w nazwisku jest parzysta czy nieparzysta, aplikacja ma posiadać możliwość rysowania odpowiednio antyaliasowanych odcinków lub okręgów.
Efektywność będzie mierzona jako czas narysowania ustalonej liczby prymitywów.
Rysowanie na rastrze powinno być zrealizowane z użyciem podwójnego bufora ramki.
Aplikacja będzie wykorzystywana jako baza do następnych projektów.

Część laboratoryjna: dodać ustawianie grubości rysowanych odcinków i okręgów, dodać rysowanie wielokątów

#Projekt 2 - Algorytmy wypełniania i obcinania

Do aplikacji z pierwszego zadania dodajemy nowe funkcjonalności:
możliwość tekstowego wprowadzenia współrzędnych początku i końca nowo tworzonego odcinka
przycinanie rysowanych odcinków i wielokątów do obrysu ekranu: algorytm do wyboru: Cohen-Sutherland, Cyrus-Beck, Liang-Barsky, Sutherland-Hodgman
możliwość dodania do sceny wypukłego wielokąta który będzie przycinał zawartość sceny i wyświetlał tylko część sceny znajdującą się w jego wnętrzu; wielokąt można przesuwać na scenie; sprawdzić wypukłość wielokąta (jak?)
możliwość dodania do sceny wypełnionego kolorem lub teksturą (z pliku) dowolnego wielokąta; brzeg ma niezależny kolor; tekstura jest przytwierdzona; algorytm scanline
Efektywność będzie mierzona jako czas narysowania ustalonej liczby wypełnionych/teksturowanych wielokątów.

Część laboratoryjna: dodać możliwość utworzenia wielokąta w kształcie grzebienia, dodać przycinanie wypełnionych wielokątów

#Projekt 3 - Kolory

Do aplikacji z poprzedniego zadania dodajemy okienko wyboru koloru. Wybrany w tym okienku kolor można ustawić dla wypełnionego kolorem wielokąta w scenie.
Okienko ma posiadać trzy zakładki z paletami kolorów: RBG, HSV i CIE XYZ. Każda z palet wizualizowana jest jako dwuwymiarowy przekrój. Trzecią
współrzędną regulujemy za pomocą dodatkowego suwaka (należy wybrać najodpowiedniejszą do tego współrzędną). Należy oznaczyć osie przekroju za pomocą
odpowiednich współrzędnych i skrajnych wartości. Wybrany kolor należy oznaczyć np. za pomocą małego kwadracika lub krzyżykiem. Kolor wybieramy
kliknięciem na przekroju lub wpisując wartość z klawiatury. W każdej z zakładek ma być wyświetlona aktualna wartość koloru w wybranej przestrzeni kolorów.

Przy przechodzeniu między zakładkami, zawsze następuje automatyczna konwersja kolorów z jednej przestrzeni barw na drugą. Należy obsłużyć każdą sytuację
wyjścia poza zakres reprezentowanych kolorów przez dany model. Gdy zajdzie sytuacja wyjścia poza zakres reprezentowanych kolorów, należy kolor
sprowadzić do zakresu i zaznaczyć w interfejsie, że doszło do takiej sytuacji.

Dodać opcję redukcji kolorów w oteksturowanych wielokątach. Skorzystać z algorytmu drzewa ósemkowego (octree) dla RGB. Dodać suwak regulujący docelową liczbę
liści drzewa ósemkowego. Redukcje kolorów zachodzą od razu podczas regulacji suwakiem.

Część laboratoryjna: dodać okienko z histogramem kolorów widocznej tekstury; dodać możliwość konwersji tekstury do szarości (składowa Y z modelu YUV)

#Projekt 4 - Obróbka obrazów rastrowych

Dodanie możliwości wstawienia specjalnego prostokąta który powoduje modyfikacje pikseli aktualnie znajdujących się w jego wnętrzu. Można ustawić szerokość
i wysokość prostokąta a także przesuwać go. W trakcie przesuwania natychmiast uaktualniany jest obraz pod prostokątem oraz histogram kolorów bez potrzeby
klikania czegokolwiek.
Wystarczy możliwość dodania jednego takiego prostokąta. Gdy do sceny dodany jest specjalny prostokąt dostępne mają być następujące
operacje na pikselach w prostokącie:
okienko z filtrem funkcyjnym (dodawanie i usuwanie punktów łamanej, dla wybranego kanału) (3pkt)
okienko z filtrem macierzowym (wybór macierzy: 3, 5, 7, wpisywanie) przyciski automatycznie wpisujące rozmycie Gaussa 3, 5, 7 (2pkt)
obrót obrazu o ustalony kąt (obrócony obraz nie wychodzi poza prostokąt a brakujące piksele są czarne) środek obrotu znajduje się w środku prostokąta (1pkt)
skalowanie obrazu o wybrany współczynnik (przeskalowany obraz nie wychodzi poza prostokąt a brakujące piksele są czarne) skalowanie w górę i w dół, punkt
stały przekształcenia znajduje się w środku prostokąta, bez filtrów (2pkt)
rozciągnięcie histogramu (N) lub wyrównanie histogramu (P) (2pkt)
gdzie: P - parzysta liczba liter w nazwisku, N - nieparzysta liczba liter w nazwisku
Rozbudować histogram poprzez pokazywanie jednocześnie trzech oddzielnych wykresów dla R, G i B. Wartości na histogramie mają kierunek większych
wartości do góry.

Efektywność będzie mierzona dla jednego z filtrów macierzowych.

#Projekt 5 - Wprowadzenie do grafiki 3D

Należy zaprojektować prosty silnik do wyświetlania trójwymiarowych obiektów. Jako bazę należy wykorzystać wcześniejszą aplikację w zakresie rysowania odcinków, 
wypełnionych trójkątów oraz obcinania do obrysu ekranu. Do wyboru są dwa modele do wyświetlenia, dostępne na stronie http://www.mpi-inf.mpg.de/~kettner/proj/obj3d/
pod nazwami mushroom_triang.off.tz (prostszy) i teapot.off.tz (trudniejszy). Modele zapisane są w bardzo prostym formacie OFF którego opis jest np. tutaj.

Zadania do zrealizowania:
- obracanie, przybliżanie i oddalanie obiektu za pomocą myszki lub klawiatury (wymaganie: obrócenie do wskazanego fragmentu obiektu i jego przybliżenie lub oddalanie) (1 pkt)
- możliwość wyświetlenia obiektu jako siatka (1pkt)
- bufor Z (1pkt)
- backface culling (ukrywanie ścian zorientowanych tyłem) (1pkt)
- możliwość wyświetlenia obiektu jako wypełniony płaski model bez tekstur o losowo ustalonych kolorach ścianek (1pkt)
- możliwość wyświetlenia obiektu jak powyżej z oświetleniem typu Phong (możliwa edycja pozycji światła i kolorów ambient, diffuse, specular oraz wykładnika specular) (2pkt)
- możliwość wyświetlenia obiektu jak powyżej z teksturą (współrzędne tekstury dowolne: wygenerowane lub wylosowane po wczytaniu modelu; nie wymagana jest korekcja tekstury) (3pkt)

Wymagane jest aby aplikacja działała płynnie: minimum 10 fps na prostszym modelu. Jeśli wydajność aplikacji nie pozwala na wyświetlenie płynnie żadnego z opisanych modeli,
należy zastąpić je szcześcianem. Niska wydajność będzie karana ujemnymi punktami.

Nie jest wymagane aby aplikacja obsługiwała nadal wcześniejsze efekty takie jak np. rozmywanie i redukcja kolorów.

Efektywność będzie mierzona jako szybkość wyświetlania oświetlonego i oteksturowanego obiektu.
