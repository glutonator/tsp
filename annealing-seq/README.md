# Problem komiwojażera
Wersja przeszukiwania sekwencyjnego wykorzystująca algorytm symulowanego wyżarzania

Uruchomienie:  
(1) > cmake .\
(2) > make\
(3) > ./salesman_seq [N] [T] [L] [alfa]

N - Wielkość grafu\
T - Temperatura\
L - Liczba kroków w wenętrznej pętli\
alfa - Szybkość zbiegania temeraturu z zakresu (0,1)

Przykładowa komenda:\
./salesman_seq 100 1000 100 0.1
