# Architettura di MonsterChase

## Descrizione dell'architettura ad alto livello

MonsterChase è organizzato in livelli logici che separano il **flusso applicativo**, la **simulazione di gioco**, la **presentazione UI** e i **servizi trasversali**.

A livello alto:

1. **Application/UI Flow**: `MonsterChase` e i controller/pagine UI gestiscono menu, navigazione e transizioni tra schermate (main menu, opzioni, editor, classifica, partita).
2. **Game Orchestration**: `GameController` governa il ciclo della partita, i timer, la macchina a stati (`MatchState`) e coordina l'aggiornamento del mondo.
3. **Game Domain**: `Match` incapsula regole/modalità (strategy), mentre `GameWorld` mantiene le entità runtime (arena, player, monsters) e avanza la simulazione frame-by-frame.
4. **Entities & AI**: Player e Monster usano componenti di comportamento/animazione (in `src/lib`, `src/player`, `src/monsters`) per movimento, collisioni e decisioni.
5. **Infrastructure**: persistenza/profili, audio, risorse e level editor supportano il dominio senza accoppiarsi alla logica core.

L'architettura combina pattern pratici:

- **Controller/View separation** nel mini framework UI (`UiPageController`, `UiPageViewQt`, `UiPageMenu`).
- **State pattern** per gli stati di match (`match_sm`).
- **Strategy-like behavior** per varianti di `Match` create via factory.
- **Singleton/Facade** in `GameWorld` per accedere allo stato globale della simulazione.

---

## Component diagram (PlantUML)

```plantuml
@startuml
skinparam componentStyle rectangle

title MonsterChase - Component Diagram

component "Main App\n(MonsterChase)" as App
component "UI Framework\n(UiPageController/View/Menu)" as UI
component "Game Controller\n(GameController)" as GC
component "Match Engine\n(Match + MatchState)" as ME
component "Game World\n(GameWorld)" as GW
component "Entities & AI\n(Player, Monsters, Behaviors, Animations)" as EAI
component "Level Editor\n(editor, level_editor)" as LE
component "Options & HighScore\n(options, highscores)" as OHS
component "Profiles & Persistence\n(player_profile, lib/persistence)" as PP
component "Audio Service\n(AudioServer)" as AS
component "Resources\n(maps, sprites, audio)" as RES

App --> UI : navigazione pagine/menu
App --> GC : avvia partita
App --> LE : apre editor
App --> OHS : apre opzioni/classifica

GC --> ME : stato match e regole
GC --> GW : loop/step di gioco
GC --> UI : popup pausa/fine

ME --> PP : profilo giocatore
GW --> EAI : update entità
GW --> RES : caricamento mappa/asset

LE --> RES : modifica/salvataggio mappe
OHS --> PP : lettura/scrittura dati
AS --> RES : playback audio
App --> AS : theme music/menu

@enduml
```

---

## Class diagram (PlantUML)

```plantuml
@startuml

title MonsterChase - Class Diagram (core)

class UiPageController
class UiPageViewQt
class UiPageMenu

class MonsterChase {
  -game_controller: GameController*
  -current_menu: UiPageMenu*
  +handleKey(key, released): bool
  +editor_closed()
}

class GameController {
  -timer: QTimer*
  -m_match: Match*
  -current_state: MatchStateE
  +gameStep()
  +start()
  +change_match_state(next_state)
}

class Match {
  -match_type: MatchType
  -map_name: QString
  -player_profile: QString
  +check_rules(): MatchResult
  +compute_match_score(): int
  +update_play_time()
}

class MatchState

class GameWorld {
  -arena: Arena*
  -player: Player*
  -monsters: vector<Monster*>
  +instance(): GameWorld&
  +initLevel(map)
  +nextFrame()
}

class Arena
class Player
class Monster
class AudioServer
class LevelEditor
class OptionPageController
class HighScorePageController

UiPageController <|-- MonsterChase
UiPageController <|-- GameController

MonsterChase --> UiPageMenu
MonsterChase --> GameController
MonsterChase --> LevelEditor
MonsterChase --> OptionPageController
MonsterChase --> HighScorePageController
MonsterChase --> AudioServer

GameController --> Match
GameController --> MatchState
GameController --> GameWorld

GameWorld --> Arena
GameWorld --> Player
GameWorld --> Monster

UiPageViewQt --> UiPageMenu

@enduml
```

---

## Descrizione sintetica dei componenti

- **Main App (`MonsterChase`)**  
  Entry point logico dell'esperienza utente: costruisce i menu, intercetta input globali, apre pannelli secondari (editor/opzioni/classifica) e delega la partita a `GameController`.

- **UI Framework (`src/lib/ui_framework`)**  
  Astrazione di pagine, widget e menu basata su Qt Graphics View. Riduce il coupling tra logica di navigazione e rendering dei componenti.

- **Game Controller (`GameController`)**  
  Coordina il game loop tramite timer, innesca `GameWorld::nextFrame()`, gestisce pause/fine partita e transizioni degli stati match.

- **Match Engine (`Match` + `match_sm`)**  
  Modella modalità e regole di vittoria/sconfitta, punteggio e progressione temporale. La factory di match abilita varianti senza cambiare il controller.

- **Game World (`GameWorld`)**  
  Contiene lo stato runtime del livello (arena, player, mostri), inizializza/deinizializza le mappe e applica l'avanzamento della simulazione.

- **Entities & AI (`player`, `monsters`, `lib/behaviors`, `lib/animations`)**  
  Implementa movimento, collisioni, comportamento e animazioni delle entità di gioco. È il nucleo della dinamica hunter/hunted.

- **Level Editor (`editor`, `level_editor`)**  
  Tool interno per creare/modificare mappe e contenuti del livello, riusando parte dell'ecosistema Qt del progetto.

- **Options & HighScore (`options`, `highscores`)**  
  Gestione impostazioni utente e visualizzazione/aggiornamento classifiche.

- **Profiles & Persistence (`player_profile`, `lib/persistence`)**  
  Persistenza di profili, score e dati di supporto tra sessioni.

- **Audio Service (`AudioServer`)**  
  Servizio dedicato alla riproduzione audio/music score e integrazione sonora delle schermate.

- **Resources (`resources`, `models`)**  
  Asset statici (mappe, sprite, audio, immagini) caricati da gameplay, UI ed editor.
