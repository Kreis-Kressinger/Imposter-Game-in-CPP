# Los geht's! – Getting started!

 - Klone das Projekt. / Clone the repository.
 - Kompiliere den Code in ```main.cpp``` in die ausführbare Datei ```imposter.exe``` (Windows und Linux)
 ```
    make
    ./imposter.exe
 ```


# Spielregeln – Imposter

In *Imposter* werden Spieler zufällig in zwei Rollen eingeteilt: **Imposter** und **normale Spieler**.

---

## 🎯 Ziel des Spiels

### Normale Spieler
- Finden die Imposter und eliminieren sie.

### Imposter
- Erraten das geheime Wort oder überleben bis zum Ende.

---

## 🎮 Spielablauf

1. Zu Beginn wird ein zufälliges Wort aus dem Wortset gewählt.
2. Alle normalen Spieler kennen dieses Wort – die Imposter jedoch nicht.
3. Die Imposter erhalten stattdessen einen Hinweis, der ihnen hilft, das Wort zu erraten.

### Rundenprinzip

- In jeder Runde kommen Spieler nacheinander an die Reihe.
- Nur der aktive Spieler darf auf den Bildschirm schauen.
- Alle anderen müssen wegschauen.
- Der aktive Spieler gibt ein Wort ein, das dem gesuchten Wort nahekommt, um zu zeigen, dass er das Wort kennt.
- Imposter müssen ebenfalls Wörter eingeben, um das geheime Wort zu erraten, dürfen dabei aber nicht auffallen.

---

## 🕵️ Verdacht & Ausschluss

- Am Ende jeder Runde diskutieren die Spieler.
- Gemeinsam kann entschieden werden, einen Spieler zu eliminieren, wenn dieser als Imposter verdächtigt wird.
- Imposter können strategisch andere Spieler verdächtig erscheinen lassen, um ihre eigenen Chancen zu erhöhen.

---

## 🏆 Siegesbedingungen

### Normale Spieler gewinnen, wenn:
- alle Imposter eliminiert wurden.

### Ein einzelner Imposter gewinnt, wenn:
- er das geheime Wort richtig errät.

### Imposter-Team gewinnt, wenn:
- die Anzahl der Imposter gleich oder größer ist als die Anzahl der verbleibenden Spieler.

---

## 📁 Benutzerdefinierte wordSet-Datei

- Es kann immer nur **eine** Datei namens `wordSet.txt` existieren.
- Diese Datei muss sich im **gleichen Verzeichnis wie das Spiel** befinden.

### 📌 Format der Datei

- Immer abwechselnd:
  - 1. Wort
  - 1. Hinweis
- Kein zusätzlicher Text erlaubt.
- Keine leeren Zeilen erlaubt.
- Nach jedem Wort/Hinweis eine neue Zeile anfangen
- Es ist ein Beispiel-Wortset bereits vorhanden
