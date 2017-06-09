Readme do projektu Arkanoid wersja Pre Alpha V0.6 NT, copyleft TeMPOraL Software, 2004.
=================================


=================================
	Zawartoœæ Pakietu

W pakiecie znajduje siê gra Arkanoid w wersji Pre Alpha V0.6 NT (Ÿród³a i exe), oraz plik wykonywalny Wersji
V0.08 Playable.


Wersja v0.08 Playable jest wersj¹ grywaln¹, ale zawiera kilka paskudnych blêdów, które powoduj¹ w niektórych
sytuacjach jej wy³¹czenie siê z komunikatem Access Violation.

Wersja v0.6 Pre Alpha NT jest wersj¹ niegrywaln¹; posiada du¿o zmian wewnêtrznych wobec swojego poprzednika;
zawiera wci¹¿ testowan¹ obs³ugê etapów ³adowanych z plików, i nie wystêpuje w niej b³¹d z wersji V0.8 Alpha.

Pakiet zawiera grê w dwóch wersjach jêzykowych - Angielskiej i Polskiej. Do prze³¹czania siê miêdzy wersjami
s³u¿¹ pliki stat_txt.tbl i system_txt.tbl, oraz ich odpowiedniki - stat_txt_pl.tbl i system_txt_pl.tbl.
Zamieniaj¹c je nazwami (pl z tym bez pl) zmieniamy jêzyk gry.

Pakiet zawiera tak¿e program ArkGRP s³u¿¹cy do konwersji dowolnego formatu graficznego na niegdyœ u¿ywany
wewnêtrzny format Arkanoida [wiêcej w dokumencie tech.txt], oraz program TblPad autorstwa ShadowFlare
(wiêcej w pliku TblPad.txt) s³u¿¹cy do edycji plików tablic tekstowych (*.tbl)
=================================

=================================
	U¿ytkowanie

ród³a gry powinny siê skompilowaæ pod kompilatorem Visual C++ 6.0, z zainstalowanym Directy X 8.0 SDK i FMOD Api.

Do dzia³ania gry wymagane jest posiadanie biblioteki Direct X w wersji 8.0 lub nowszej, bibliotekê FMOD dostarczon¹
w pakiecie, oraz akcelerator graficzny kompatybilny z OpenGL. Oczywiœcie karta dŸwiêkowa tak¿e jest wymagana.

Gra zawiera cztery tryby. Tryb normalny, to typowe odbijanie pi³ki i rozwalanie murków. W trybie Time Attack
liczy siê, jak szybko ca³a plansza zostanie oczyszczona. W trybie Survival gra siê tyle, ile siê prze¿yje - 
niektóre murki zregeneruj¹ siê, gdy ich iloœæ znacz¹co spadnie. Tryb Gravity Mode to taka weso³a odmiana
trybu Normal - na pi³kê dzia³a tu skierowana w dó³ si³a grawitacji.

Oczywiœcie na dzieñ dzisiejszy [07.06.2004] ¿aden z tych trybów nie dzia³a do koñca tak, jak mia³ - nie ma High Score`ów,
powerup`ów, czy choæby regeneracji murków.

Ma³a uwaga dot. kompilacji Ÿróde³ wersji V0.08 Playable - kompilacja pliku ObjectManager.cpp w trybie Release
mo¿e wywo³aæ wewnêtrzny b³¹d kompilatora - jest to wina u¿ywania funkcji Vector2::Normalize() - czemu siê to dzieje,
nie wiem, ale jakby wyst¹pi³, to jest tylko jedno rozwi¹zanie: skompilowaæ grê w trybie Debug, skopiowaæ plik
ObjectManager.obj z katalogu Debug do Release, i zlinkowaæ Release (znaczy - najpierw F7, powinien zostaæ jeden b³¹d, 
potem kopiujemy Obj`ta, a potem znów F7, ¿eby siê tylko linkowa³).
=================================

=================================
	Klawiszologia:

[Menu]
Strza³ki w górê i w dó³ - wybór danej opcji
Enter - zatwierdzenie opcji

[Gra]
Strza³ki w lewo i prawo - poruszanie paletk¹
Spacja - potwierdzenie gotowoœci do gry przy stosownym komunikacie
P - zapauzowanie gry
Q - odpauzowanie gry
ESC - powrót do menu
=================================

=================================
	Pos³owie

Prosi³bym, szczególnie w przypadku wyst¹pienia jakichœ problemów, o dostarczenie do mnie pliku log.Arkanoid.txt
By³bym wdziêczny, w przypadku sta³ego b³êdu, za przes³anie loga z gry uruchomionej z parametrem -d.
=================================

=================================
	Kontakt

Mailto: temporal at poczta dot fm.
www.temporal-software.prv.pl
=================================