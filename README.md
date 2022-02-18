# SO-postpone-process
*Specyfikacja drugiego projektu realizowanego w ramach ćwiczeń do przedmiotu Systemy Operacyjne.*

Celem projektu jest implementacja mechanizmu pozwalającego na czasowe zastopowanie procesu wskazanego za pomocą `pid`. Należy zaimplementować następujące funkcje:

- `int postpone_proc(pid_t ppid, int interval)` - po wywołaniu funkcji system powinien zawiesić szeregowanie procesu o numerze `ppid` na czas `interval`. Czas jest wyrażony w milisekundach. Można przyjąć że `interval`<= 10000.
- `int stop_proc(pid_t ppid)` - po wywołaniu funkcji system powinien zawiesić szeregowanie procesu o numerze `ppid` aż do odwołania.
- `int resume_proc(pid_t ppid)` - wywołanie funkcji powinno poskutkować wznowieniem procesu o numerze `ppid`.

Wartość zwracana przez funkcje powinna wynosić `0` w przypadku gdy funkcja zakończyła się sukcesem. W pozostałych przypadkach funkcje powinny zwrócić `-1` i ustawić `errno` na odpowiednią wartość.
Deklaracje powyższych funkcji powinny się znaleźć w pliku `include/minix/postpone.h`. Ich implementacja powinna zostać dołączona do biblioteki `libc`.

Zawieszony proces nie powinien być przerwany sygnałami dla których zarejestrował obsługę. Sygnały które go zabijają powinny to robić natychmiastowo.

Dodatkowo system powinien udostępnić informacje o tym jak długo jeszcze proces będzie wstrzymany poprzez `procfs`. Dla każdego procesu o identyfikatorze `pid` w pliku `/proc/[pid]/delay` powinna się znaleźć liczba w zapisie dziesiętnym, która oznacza liczbę milisekund która pozostała do odwieszenia procesu.

## Organizacja repozytorium

 - `postpone_src/`  - katalog zawiera zmieniane źródła systemu Minix. Zawartość katalogu zostanie skopiowana do `/usr/src` poleceniem `cp -r postpone_src/* /usr/src`. Potem nastąpi kompilacja i instalacja nagłówków, bibliotek i obrazu systemu. Początkowa przykładowa zawartość tego katalogu powstała na podstawie wzorcowego rozwiązania.
 - `postpone_tests/` - katalog zawiera źródła programów używanych do testowania. Większość z nich opakowuje odpowiednie wywołania wymienionych powyżej funkcji. Program `ticker.c` to przykładowy program do stopowania, opóźniania i wznawiania. Program `postpone_tests.c` uruchamia prosty test opóźnień wielu procesów na raz.
