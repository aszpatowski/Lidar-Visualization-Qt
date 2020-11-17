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
- [x] - zaprojektowanie wstępnego prostego interfejsu graficznego (będzie dalej rozwijany).
- [x] - wczytywanie danych za pomocą interfejsu aplikacji (użytkownik podaje ręcznie ścieżkę pliku csv).
- [x] - sprawdzanie poprawności ścieżki i formatu danych oraz wyświetlanie użytkownikowi adekwatnego komunikatu.
- [x] - odczyt danych i wstępna obróbka przed wizualizacją danych w widgetcie OpenGL.
## Raport II (17.11.2020)
- [x] - stworzenie eksploatora plików w aplikacji w celu wybrania ścieżki do danych.
- [x] - utworzenie klasy MyOpenGlWidget z podstawowymi funkcjonalnościami. 
- [x] - skonfigurowanie widgetu openGL do tworzenia wizualizacji.
- [x] - tworzenie prymitywnej wizualizacji za pomocą danych pobranych od użytkownika.
### Funkcjonalność aplikacji w dzień raportu II
<img src="https://github.com/aszpatowski/Lidar-Visualization-Qt/raport2funkc.gif"/>
