# Funkcje

## Ładowanie danych z bazy

### Załaduj kucyka
- `Pony load_pony(DbConnection db, int id)`
- `Pony load_pony(DbConnection db, const std::string& name)`

Ładuje kucyka po id albo po nazwie.  
Gdy nie ma takiego kucyka, wyrzucany jest `std::runtime_error`.

### Załaduj wszystkie kucyki
- `std::vector<Pony> load_all_ponies(DbConnection db)`


## Zapisywanie kucyków

### Tworzenie kucyka
- `Pony create_pony(DbConnection db, const std::string& name)`

Tworzy nowego kucyka o podanej nazwie i zwraca jego obiekt.  
Może wyrzucić `std::runtime_error`, gdy kucyk o podanej nazwie juz istnieje.

### Aktualizacja kucyka
- `void update_pony(DbConnection db, const Pony& pony)`

Aktualizuje informacje o kucyku w bazie.

### Usuwanie kucyka
- `void delete_pony(DbConnection db, int id)`

Usuwa kucyka o podanym id.  
Po usunięciu, użycie `update_pony(db, pony)` lub `delete_pony(db, id)` na
usuniętym kucyku wyrzuci `std::runtime_error`.  
Próba usunięcia nieistniejącego kucyka wyrzuci `std::runtime_error`.


## Ładowanie genów

### Załaduj wszystkie kategorie genów
- `std::map<int, GeneCategory> load_all_gene_categories(DbConnection db)`

Ładuje wszystkie kategorie genów, aby przechować je w globalnym kontenerze.

### Załaduj gen
- `Gene load_gene(DbConnection db, int id)`

Ładuje gen o podanym id.  
Gdy nie ma takiego genu, wyrzucany jest `std::runtime_error`.

### Załaduj wszystkie geny kucyka
- `std::vector<Gene> load_genes_by_pony(DbConnection db, const Pony& pony)`

Ładuje wszystkie geny kucyka.
Używane podczas `load_pony`.

## Zapisywanie genów

### Tworzenie kategorii genów
- `GeneCategory& create_gene_category(DbConnection db)`

Tworzy pustą kategorie genów.
Następnie należy poustawiać jej efekty dla genów recesywnych i dominujących.

### Aktualizacja kategorii genów
- `void update_gene_category(DbConnection db, const GeneCategory& gc)`

Aktualizuje informacje o kategorii genów w bazie.

### Usuwanie kategorii genów
- `void delete_gene_category(DbConnection db, int id)`

Usuwa kategorie genów o podanym id.

### Tworzenie genu
- `Gene create_gene(DbConnection db, const GeneCategory& gc, Pony& pony)`

Tworzy nowy genu w kategorii `gc` dla kucyka `pony`.
Nowy gen jest wpisywany od razu do kucyka.

### Aktualizacja genu
- `void update_gene(DbConnection db, const Gene& gene)`

Aktualizuje informacje o genie w bazie.

### Usuwanie genu
- `void delete_gene(DbConnection db, int id)`

Usuwa gen o podanym id.

## Wyświetlanie kucyków

- `void draw_pony(const Pony& pony)`

Wyświetla obrazek kucyka na podstawie jego nazwy i jego statystyki.
![Wyświetlanie kucyka](draw-pony.png)

