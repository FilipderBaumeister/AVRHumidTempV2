# AVRHumidTempV2

Abschlussprüfung vorbereitung EIS 2023/2024 

## Einbinden der Libarys

Dieses Repository enthält einen AVR-Mikrocontroller-Code, der verschiedene Bibliotheken für Funktionen wie LCD-Anzeige, I2C-Kommunikation, ADC- und DAC-Konvertierung und Zeitverzögerungen nutzt.

## Einlesen Temp und Humid

"Die Funktion `einlesentempandhumid()` in diesem Repository liest die Spannungswerte von zwei analogen Eingängen eines AVR-Mikrocontrollers, die zur Messung von Temperatur und Feuchtigkeit verwendet werden."

## Temperatur und Feuchtigkeit Werte Bereiche

"Die Funktion `checkhumidandtemp(double x, double y)` in diesem Repository überprüft die Temperatur- und Feuchtigkeitswerte, die von einem AVR-Mikrocontroller gemessen werden. Sie ändert den Status einer LED basierend auf diesen Werten, um den optimalen, tolerierten und kritischen Bereich anzuzeigen."

Nach Vorgabe sollen bestimmte Abfrage, abgefragt werden.

## Erschuetterung Abfragen 

"Die Funktion `checkVibration()` in diesem Repository überwacht einen spezifischen Pin eines AVR-Mikrocontrollers auf Vibrationen. Bei Erkennung einer Vibration wird eine Warnmeldung auf einem LCD-Display angezeigt und der Status einer LED auf Rot gesetzt."

## Displaydata 

"Die Funktion `displayData()` in diesem Repository initialisiert ein LCD-Display und zeigt die gemessenen Temperatur- und Feuchtigkeitswerte an. Bei bestimmten Bedingungen wird zusätzlich ein Ausrufezeichen auf dem Display angezeigt."

## Buttoncheck (Buttonabfrage)

"Die Funktion `buttonCheck(uint32_t button)` in diesem Repository überprüft den Zustand eines bestimmten Buttons. Abhängig vom Zustand des Buttons führt sie verschiedene Aktionen aus, wie das Lesen von Temperatur- und Feuchtigkeitswerten, das Anzeigen von Daten auf einem LCD-Display, das Überprüfen auf Vibrationen und das Durchführen von Zeitoperationen."

## Main 

"Die `main` Funktion in diesem Repository initialisiert den Analog-Digital-Konverter und setzt einen bestimmten Pin des AVR-Mikrocontrollers auf High. In einer Endlosschleife liest sie den Zustand eines Buttons und führt die Funktion `buttonCheck(buttons)` aus, um verschiedene Aktionen basierend auf dem Zustand des Buttons durchzuführen."
