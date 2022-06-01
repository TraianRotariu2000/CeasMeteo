# CeasMeteo
## Descriere generala
#### Proiectul presupune implementarea unui modul capabil sa monitorizeze parametri meteorologigici precum temperatura si umiditatea. Controlul acestor parametri este foarte important in cazul incintelor in care acestia pot varia doar cu valori mici (de exemplu: o sera sau o ciupercarie).
## Mod de functionare
#### Pentru initializare este necesara conectarea la un sistem de calcul care permite comunicarea seriala cu placuta Arduino. Prin intermediul comunicarii seriale, utilizatorul seteaza limitele de temperatura si presiune dorite in incinta prin simpla introducere de la tastatura a valorilor solicitate. Dupa configurare, modulul va functiona intr-un regim mixt. La fiecare 30 de secunde, senzorul de temperatura si umiditate va transmite rezultatele masuratorilor. 
#### In cazul in care un parametru masurat se regaseste in limitele setate, se va aprinde cate un LED verde corespunzator acestuia. Depasirea limitelor setate unui parametru va fi semnalata prin aprinderea unui LED rosu. Daca LED-urile ofera doar o imagine calitativa a rezultatelor masuratorilor, pe monitorul serial poate fi consultata o detaliere a rezultatelor masuraturilor. Vor fi afisate: temperatura (masurata in grade Celsius) si umiditatea relativa(masurata in procente) din incinta, momentul la care s-a realizat masuratoarea (data, ziua saptamanii, ora), respectiv limitele de temperatura si umiditate setate de utilizator. O scurta prezentare a modului de functionare poate fi consultata in urmatorul videoclip: https://www.youtube.com/watch?v=u2lJJYeJQEE
## Implementare
#### Proiectul a fost implementat dupa urmatoarea schema electrica, cu mentiunea ca au fost folosite componente provenite de la producatori diferiti dar cu functii similare in cazul modulului RTC, respectiv senzorului de temperatura si umiditate:

<img src="poze/Proiect_SMP_schem.png" width=800>


