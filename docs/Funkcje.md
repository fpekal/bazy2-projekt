# Funkcje

## Ładowanie danych z bazy

### Załaduj kucyka
- `Pony load_pony(DbConnection db, int id)`
- `Pony load_pony(DbConnection db, const std::string& name)`

Ładuje kucyka po id albo po nazwie.  
Gdy nie ma takiego kucyka, wyrzucany jest `std::runtime_error`.

### Załaduj wszystkie kucyki
- `std::vector<Pony> load_all_ponies(DbConnection db)`
