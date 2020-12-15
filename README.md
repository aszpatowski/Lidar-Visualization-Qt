# Lidar-Visualization-Qt
Głównym założeniem programu jest wizualizacja danych z LiDAR (ang. Light Detection And Ranging, urządzenie skanujące otoczenie za pomocą światła lasera pozwalające określić odległość od obiektów).
Do tworzenia projektu będę posiłkował się darmowym zbiorem danych z lidarów zamontowanych na samochodach autonomicznych (źródło danych: https://pandaset.org/).
Użytkownik po wgraniu danych będzię mógł dostosować kolorystyke wizualizacji oraz zależnie od ilości wgranych danych wygenerować plik/pliki w formacie png lub plik wideo.
## Technologie
- C++ (prawdopodobnie pre obróbka danych będzie wykonywana w skryptach napisanych w pythonie)
- Qt
- OpenCV
- ... (prawdopodobnie zostaną użyte dodatkowe biblioteki do rozwiązania napotkanych problemów)
## Funkcjonalności
- Wczytywanie jednego lub wielu plików w formacie csv.
- Ustawianie kolorystyki za pomocą suwaków.
- Podgląd wygenerowanego obrazu w oknie aplikacji.
- Eksport wizualizacji jako:
  - plik graficzny (w formacie png)
  - plik wideo (w raz z możliwością ustawienia trwania pojedycznej klatki filmu)
## Wstępne przygotowanie projektu (20.10.2020)
- [x] - Instalacja QtCreatora i poprawne wyświetlenie podstawowego okienka.
- [x] - Pobranie danych i wstępna analiza ich struktury za pomocą pythona.

## Raport I (03.11.2020)
- [x] - Zaprojektowanie wstępnego prostego interfejsu graficznego (będzie dalej rozwijany).
- [x] - Wczytywanie danych za pomocą interfejsu aplikacji (użytkownik podaje ręcznie ścieżkę pliku csv).
- [x] - Sprawdzanie poprawności ścieżki i formatu danych oraz wyświetlanie użytkownikowi adekwatnego komunikatu.
- [x] - Odczyt danych i wstępna obróbka przed wizualizacją danych w widgetcie OpenGL.
## Raport II (17.11.2020)
- [x] - Stworzenie eksploatora plików w aplikacji w celu wybrania ścieżki do danych.
- [x] - Utworzenie klasy MyOpenGlWidget z podstawowymi funkcjonalnościami. 
- [x] - Skonfigurowanie widgetu openGL do tworzenia wizualizacji.
- [x] - Tworzenie prymitywnej wizualizacji za pomocą danych pobranych od użytkownika.
## Raport III (01.12.2020)
- [x] - Dodanie możliwości odczytu więcej niż jednego pliku.
- [x] - Stworzenie algorytmu do kolorowania wizualizacji zależnie od odległości obiektu. (wrażenie głębi wizualizacji) 
- [x] - Dodanie możliwość generowania więcej niż jednej wizualizacji.
- [x] - Dodanie nawigacji w interfejsie pomiędzy wizualizacjami.
- [x] - Zaimplementowanie algorytmów do normalizacji danych. (w poprzednim raporcie wizualizacja odbywała się na danych już znormalizowanych za pomocą pythona.)
## Raport IV (15.12.2020)
- [x] - Dodanie klas exportChoice, exportImage, exportVideo i implementacja ich podstawowych metod.
- [x] - Dodanie i skonfigurowanie suwaka odpowiedzialnego za kolorystyke zależnie od odległości punktów.
- [x] - Dodanie przycisku "Eksportuj", który otwiera okienka, za pomocą których użytkownik będzię mógł wygenerować pliki zdjęciowe lub wideo.
- [x] - Stworzenie designu okienek do eksportowania wizualizacji.
### Funkcjonalność aplikacji w dzień raportu II
<img width = "900" src="https://github.com/aszpatowski/Lidar-Visualization-Qt/blob/master/raport2funkc.gif"/>

### Funkcjonalność aplikacji w dzień raportu III
<img width ="900" src="https://github.com/aszpatowski/Lidar-Visualization-Qt/blob/master/raport3funkc.gif"/>

### Funkcjonalność aplikacji w dzień raportu IV
<video width="900" controls>
  <source src="https://github.com/aszpatowski/Lidar-Visualization-Qt/blob/master/stanRaport4.mp4" type="video/mp4">
</video>

Dane użyte do generowania wizualizacji: https://drive.google.com/file/d/1F6QjhFEiY_vIJTU7E7YA-PcnQQ1qHxe4/view
