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
## Wykonane zadania
- [x] - Instalacja QtCreatora i poprawne wyświetlenie podstawowego okienka.
- [x] - Pobranie danych i wstępna analiza za pomocą pythona.
- [ ] - Stworzenie wstępnego interfejsu graficznego.
- [ ] - ... (zadania będą dodawane wraz z rozwojem projektu w kolejnych raportach)
