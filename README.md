# Hodowla i Walki Kucyków

## Kompilacja
Potrzebne pakiety:
 - sqlite
 - pkg-config
 - g++
 - make

Aby skompilować program wystarczy użyć polecenia
```sh
make
```


Jeżeli masz menedżera pakietów `nix`, to cały proces instalacji pakietów,
kompilacji i uruchomienia można wykonać używając
```sh
nix run
```

Albo bardziej manualnie
```sh
nix develop
make
```
Ale dzięki temu nie trzeba dodawać nowych plików w kodzie do repozytorium.
(idk nix po prostu taki jest)

## Dokumentacja
[Dokumentacja](docs/Dokumentacja.md)
