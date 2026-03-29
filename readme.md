Backendowy projekt - hipotetyczna trasa w górach, implementacja algorytmu Dijkstry.

Postać musi przejść z punktu startowego do docelowego, a pola mają pewną wysokość.
Postać chodzi po sąsiednich polach, ale nie może chodzić po skosie.
Przejście z pola a na pole b zajmuje:
b - a + 1 minut, jeśli b > a
1 minutę, jeśli b <= a
W dodatku na planszy znajdują się wyciągi. Wyciąg jest jednokierunkowy, podróż nim zajmuje określony czas i kursuje co jakiś czas (postać może czekać na przyjazd wyciągu).

Celem programu jest wyświetlenie najmniejszej liczby minut potrzebnych do przebycia trasy (bez szczegółów, jak do tego doszedł).
Program działa w konsoli. Tworzony w Visual Studio Community 2022.

Wejście do programu wygląda następująco:
szerokość, wysokość planszy
pozycja startowa (x i y, numerowane od 0)
pozycja docelowa (x i y, numerowane od 0)
liczba wyciągów
Dla każdego wyciągu:
	pozycja startowa (x i y, numerowane od 0)
	pozycja docelowa (x i y, numerowane od 0)
	czas trwania podróży (w minutach)
	co ile minut odjeżdża - z wyciągu można korzystać w minutach będących wielokrotnością tej wartości
Na koniec wysokości kolejnych pól mapy (najpierw x, potem y).

Przykładowe dane:
Bez wyciągów:
10 10 0 0 9 9 0
0 1 2 3 4 5 6 7 8 9
0 9 9 9 9 9 9 9 9 9
0 1 0 1 0 1 0 1 0 9
0 9 0 9 0 9 0 9 0 9
0 1 0 1 0 1 0 1 0 9
0 9 0 9 0 9 0 9 0 9
0 1 0 1 0 1 0 1 0 9
0 2 3 1 4 9 9 9 0 9
0 0 0 8 0 0 0 0 0 0
8 1 4 9 1 0 2 0 1 0
Wynik: 22

Z wyciągami:
10 10 0 0 9 9 3
2 2 8 8 7 5
5 0 5 9 7 4
1 8 9 1 12 6
0 1 2 3 4 5 6 7 8 9
0 9 9 9 9 9 9 9 9 9
0 3 2 1 0 1 0 1 0 9
0 9 0 9 0 9 0 9 0 9
0 1 0 1 0 1 0 1 0 9
0 9 1 0 0 9 0 9 0 9
0 1 5 1 0 1 0 1 0 9
0 9 9 9 9 9 9 9 0 9
0 2 2 3 4 5 3 1 0 0
2 2 2 3 4 5 4 3 2 1
Wynik: 20
