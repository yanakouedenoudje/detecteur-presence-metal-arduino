# Détecteur de présence et de métal (Arduino)

Système qui détecte la présence d'un objet puis détermine s'il est métallique.

## Fonctionnement
1. Le capteur à ultrasons HC-SR04 mesure la distance de l'objet.
2. Si l'objet est à moins de 5 cm, le capteur inductif SN04-N est lu.
3. Signalisation :
   - LED D3 allumée : métal détecté
   - LED D4 allumée : objet non métallique
   - Aucune LED : pas d'objet dans la zone

## Matériel
- Arduino Uno
- Capteur à ultrasons HC-SR04
- Capteur inductif de proximité SN04-N (NPN, 10-30 V DC, portée nominale 4 mm)
- 2 LED + résistances
- Alimentation 12 V pour le SN04-N

## Branchements
| Composant | Broche / Raccordement |
|---|---|
| HC-SR04 VCC / GND | 5V / GND |
| HC-SR04 Trig | D7 |
| HC-SR04 Echo | D8 |
| SN04-N fil marron (+) | +12 V (alimentation externe) |
| SN04-N fil bleu (-) | GND commun avec l'Arduino |
| SN04-N fil noir (signal) | D2 (INPUT_PULLUP) |
| LED métal détecté | D3 |
| LED non métallique | D4 |

## Fonctionnement du SN04-N
Le SN04-N est un capteur inductif à sortie NPN : au repos la sortie est
flottante, et elle passe à GND quand un métal est détecté. Avec
`INPUT_PULLUP`, l'entrée D2 lit donc LOW (0) en présence de métal et
HIGH (1) sinon. La masse de l'alimentation 12 V doit être reliée à la
masse de l'Arduino.

## Utilisation
Ouvrir le fichier `.ino` dans l'IDE Arduino, le téléverser sur la carte,
puis ouvrir le moniteur série à 9600 bauds.

## Limites
La portée du SN04-N est d'environ 4 mm : le métal doit être presque au
contact du capteur pour être détecté.
