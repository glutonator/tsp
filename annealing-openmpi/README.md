# Problem komiwojażera
Wersja przeszukiwania sekwencyjnego wykorzystująca algorytm symulowanego wyżarzania

Uruchomienie:  
(1) > cmake .
(2) > make
(3) > mpiexec -n [P] annealing_openmpi [N] [T] [L] [alfa]

P - liczba procesów
N - Wielkość grafu
T - Temperatura
L - Liczba kroków w wenętrznej pętli
alfa - Szybkość zbiegania temeraturu z zakresu (0,1)

Przykładowa komenda:
mpiexec -n 4 annealing_openmpi 100 1000 100 0.1
