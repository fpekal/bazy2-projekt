# Hodowla i Walki Kucyków

## Kompilacja
Potrzebne pakiety:
 - sqlite
 - pkg-config
 - g++ w wersji 14
 - make
 - ponysay
 - boost (do testów)

Aby skompilować program wystarczy użyć polecenia
```sh
make
```

Aby przeprowadzić testy programu należy użyć polecenia
```sh
make test
```


Jeżeli masz menedżera pakietów `nix`, to cały proces instalacji pakietów,
kompilacji i uruchomienia można wykonać używając
```sh
nix run github:fpekal/bazy2-projekt
```

Albo bardziej manualnie, pobierając projekt i wchodząc do folderu z nim
```sh
nix develop
make
```
Ale dzięki temu nie trzeba dodawać nowych plików w kodzie do repozytorium.
(idk nix po prostu taki jest)

Aby przeprowadzić testy programu używając nixa należy wykonać
```sh
nix develop --check
```

## Dokumentacja
[Dokumentacja](docs/Dokumentacja.md)
