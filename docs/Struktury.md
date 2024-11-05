# Struktury używane w programie
*niekoniecznie w samej bazie danych*

## Statystyki
 - Maksymalne życie
 - Minimalne obrażenia
 - Maksymalne obrażenia
 - Szybkość ataku
 - Obrona
 - Regeneracja zdrowia

---

- Obrażenia będą losowane [min, max] inclusive.  
- Szybkość ataku to co ile rund kucyk będzie mógł zaatakować.  
 (Czyli im mniejsze tym szybsze? TODO Do zmienienia, żeby działało odwrotnie?)  
- Jeżeli atak będzie mniejszy od obrony, to zadaje 0 obrażeń, a gdy większy lub równy,
 to normalnie zadaje jego obrażenia.  
 Czyli:  
 Gdy obrona = 10, atak = 8, to kucyk nie traci życia  
 Gdy obrona = 10, atak = 12, to kucyk traci 12 życia  
- Regeneracja zdrowia to ile zdrowia zyskuje na koniec rundy (czyt. działa trochę
 jak typowa obrona w grze, bo po prostu redukuje obrażenia, więc dlatego obrona
 jest taka śmieszna)


## Kucyk
 - id
 - Nazwa
 - Aktualny poziom życia
 - Nauczone statystyki
 - Geny - jeszcze nie ma
 - Choroby - jeszcze nie ma

Prawdziwe, używane w walce statystyki wyliczane są sumując modyfikatory statystyk
wszystkich [fenotypów](https://pl.wikipedia.org/wiki/Fenotyp) i dodając do nich
wyuczone statystyki.

To znaczy, że kucyk może mieć genetyczne predyspozycje do bycia silnym i to jest
jego punkt startowy. Następnie z czasem jak coraz więcej walczy, może zwiększyć
swój poziom w danej statystyce.
Po przegranej walce redukowane są tylko statystyki nauczone; te naturalne pozostają
bez zmian.

Genetyczne modyfikatory statystyk mogą obniżyć daną statystykę poniżej typowego,
początkowego poziomu, a nauczone mogą tylko zwiększyć dany poziom.
