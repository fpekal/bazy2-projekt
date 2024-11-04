# Połączenie z bazą

Utworzona jest specjalna klasa do łączenia się z bazą danych.
Aby utworzyć połączenie z bazą należy wywołać funkcję `open_db`, która przyjmuje
URI pliku z bazą danych.

Przykład:
```cpp
{
    DbConnection db = open_db("file:test.db"); // Utworzenie połączenia
}
// Tutaj połączenie już jest zamknięte
```

Aby uzyskać z tego z powrotem wskaźnik używany przy poleceniach sqlite3, wystarczy
go zdereferencjować (użyć gwiazdki \*):
```cpp
DbConnection db = open_db("file:test.db");
sqlite3* db_ptr = *db;
```

---

Głównym powodem istnienia tej klasy jest to, że używa ona reference counting.
Znaczy to tyle, że obiekt tej klasy można skopiować w inne miejsce i nie
przejmować się, czy nie zostanie zniszczony.

Przykład o co chodzi:
```cpp
{
    DbConnection db; // Pusty obiekt, nie jest tworzone połączenie

    {
        DbConnection tmp = open_db("file:test.db"); // Utworzenie połączenia z bazą
        db = tmp; // Kopiowanie połączenia; NIE JEST TWORZONE NOWE POŁĄCZENIE
    }
    // Połączenie NADAL ISTNIEJE, bo jest przechowywane w db
}
// Tutaj połączenie już zostało zamknięte
```

Ogólnie kopiowanie tego połączenia jest raczej tanią operacją, więc można je
przekazywać do funkcji używając zwykłego kopiowania:
```cpp
void foo(DbConnection db) {
    
}
```
