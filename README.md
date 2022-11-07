# Zadatak

Realizovati program koji konvertuje mala slova u velika slova. Formirati tri 
programske niti:

1. ulazna programska nit, 
2. programska nit obrade i 
3. izlazna programska nit.

Ulazna programska nit prihvata ulazni karakter i smešta ga u ulazni kružni niz 
maksimalne veličine RING_SIZE. Programska nit obrade, preuzima karaktere iz ulaznog niza 
i vrši njihovo konvertovanje u velika slova. Konvertovani karakter se zatim smešta u izlazni 
kružni niz. Izlazna programska nit preuzima karaktere iz izlaznog kružnog niza i ispisuje ih 
na standardni izlaz. 
Pretvaranje malih u velika slova se vrši oduzimanjem vrednosti karaktera sa 0x20.
