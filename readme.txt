Readme do projektu Arkanoid wersja Pre Alpha V0.6 NT, copyleft TeMPOraL Software, 2004.
=================================


=================================
	Zawarto�� Pakietu

W pakiecie znajduje si� gra Arkanoid w wersji Pre Alpha V0.6 NT (�r�d�a i exe), oraz plik wykonywalny Wersji
V0.08 Playable.


Wersja v0.08 Playable jest wersj� grywaln�, ale zawiera kilka paskudnych bl�d�w, kt�re powoduj� w niekt�rych
sytuacjach jej wy��czenie si� z komunikatem Access Violation.

Wersja v0.6 Pre Alpha NT jest wersj� niegrywaln�; posiada du�o zmian wewn�trznych wobec swojego poprzednika;
zawiera wci�� testowan� obs�ug� etap�w �adowanych z plik�w, i nie wyst�puje w niej b��d z wersji V0.8 Alpha.

Pakiet zawiera gr� w dw�ch wersjach j�zykowych - Angielskiej i Polskiej. Do prze��czania si� mi�dzy wersjami
s�u�� pliki stat_txt.tbl i system_txt.tbl, oraz ich odpowiedniki - stat_txt_pl.tbl i system_txt_pl.tbl.
Zamieniaj�c je nazwami (pl z tym bez pl) zmieniamy j�zyk gry.

Pakiet zawiera tak�e program ArkGRP s�u��cy do konwersji dowolnego formatu graficznego na niegdy� u�ywany
wewn�trzny format Arkanoida [wi�cej w dokumencie tech.txt], oraz program TblPad autorstwa ShadowFlare
(wi�cej w pliku TblPad.txt) s�u��cy do edycji plik�w tablic tekstowych (*.tbl)
=================================

=================================
	U�ytkowanie

�r�d�a gry powinny si� skompilowa� pod kompilatorem Visual C++ 6.0, z zainstalowanym Directy X 8.0 SDK i FMOD Api.

Do dzia�ania gry wymagane jest posiadanie biblioteki Direct X w wersji 8.0 lub nowszej, bibliotek� FMOD dostarczon�
w pakiecie, oraz akcelerator graficzny kompatybilny z OpenGL. Oczywi�cie karta d�wi�kowa tak�e jest wymagana.

Gra zawiera cztery tryby. Tryb normalny, to typowe odbijanie pi�ki i rozwalanie murk�w. W trybie Time Attack
liczy si�, jak szybko ca�a plansza zostanie oczyszczona. W trybie Survival gra si� tyle, ile si� prze�yje - 
niekt�re murki zregeneruj� si�, gdy ich ilo�� znacz�co spadnie. Tryb Gravity Mode to taka weso�a odmiana
trybu Normal - na pi�k� dzia�a tu skierowana w d� si�a grawitacji.

Oczywi�cie na dzie� dzisiejszy [07.06.2004] �aden z tych tryb�w nie dzia�a do ko�ca tak, jak mia� - nie ma High Score`�w,
powerup`�w, czy cho�by regeneracji murk�w.

Ma�a uwaga dot. kompilacji �r�de� wersji V0.08 Playable - kompilacja pliku ObjectManager.cpp w trybie Release
mo�e wywo�a� wewn�trzny b��d kompilatora - jest to wina u�ywania funkcji Vector2::Normalize() - czemu si� to dzieje,
nie wiem, ale jakby wyst�pi�, to jest tylko jedno rozwi�zanie: skompilowa� gr� w trybie Debug, skopiowa� plik
ObjectManager.obj z katalogu Debug do Release, i zlinkowa� Release (znaczy - najpierw F7, powinien zosta� jeden b��d, 
potem kopiujemy Obj`ta, a potem zn�w F7, �eby si� tylko linkowa�).
=================================

=================================
	Klawiszologia:

[Menu]
Strza�ki w g�r� i w d� - wyb�r danej opcji
Enter - zatwierdzenie opcji

[Gra]
Strza�ki w lewo i prawo - poruszanie paletk�
Spacja - potwierdzenie gotowo�ci do gry przy stosownym komunikacie
P - zapauzowanie gry
Q - odpauzowanie gry
ESC - powr�t do menu
=================================

=================================
	Pos�owie

Prosi�bym, szczeg�lnie w przypadku wyst�pienia jakich� problem�w, o dostarczenie do mnie pliku log.Arkanoid.txt
By�bym wdzi�czny, w przypadku sta�ego b��du, za przes�anie loga z gry uruchomionej z parametrem -d.
=================================

=================================
	Kontakt

Mailto: temporal at poczta dot fm.
www.temporal-software.prv.pl
=================================