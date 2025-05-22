# GU Keep'Em — C Project

Welcome to *GU Keep'Em*, a poker-style card game built in C as part of the 2322ENG Engineering Programming major project.

## 🗂️ Project Structure

```
gu_keepem/
├── main.c              # Entry point and main game loop
├── game.h / game.c     # Game flow functions (setup, play_hand, deal, etc.)
├── player.h / player.c # Player struct and player management logic
├── card.h / card.c     # Card, suit, rank enums and deck operations
├── utils.h / utils.c   # Input/output helpers and intro
├── status.h            # Player status enumeration (ACTIVE, FOLDED, OUT)
├── inGame.h            # In-game state enumeration (PLAYING, QUIT)
├── playerStatus.h      # Optional: centralized player status aliases
└── config.h            # Project-wide config macros (DEBUG, USE_UNICODE)
```

## 📆 Development Roadmap

| Week    | Features                                         |
|---------|--------------------------------------------------|
| Week 1  | Interface & fake gameplay scaffold               |
| Week 2  | Betting logic and player status                  |
| Week 3  | Card struct, deck logic, shuffle & deal          |
| Week 4  | Hand scoring (basic)                             |
| Week 5  | Full scoring (tie-breakers, kickers, Ace high/low) |
| Week 6  | Custom feature development                       |
| Week 7  | Final presentation                               |

## 🧪 How to Compile and Run

### 🛠️ Compile the program (Linux/macOS)
```bash
gcc -o gu_keepem main.c game.c player.c utils.c card.c
```

### 🛠️ Compile with optional debug flags
```bash
gcc -o gu_keepem main.c game.c player.c utils.c card.c -DDEBUG=0 -DUSE_UNICODE=0
```

### ▶️ Run the program
```bash
./gu_keepem
```

### 🪟 On Windows (CMD or PowerShell)

#### Week 1:
```bash
gcc -o gu_keepem main.c game.c player.c utils.c
gu_keepem.exe
```

#### Week 2+:
```bash
gcc -o gu_keepem main.c game.c player.c utils.c card.c handscore.c
gu_keepem.exe
```

If Unicode characters (♥, ♦, etc.) don’t render correctly:
```bash
gcc -o gu_keepem main.c game.c player.c utils.c card.c handscore.c -DUSE_UNICODE=0
```

> 💡 Make sure you're in the same directory as the `.c` and `.h` files when compiling and running.

## 🔧 Configuration Options (`config.h`)

| Macro         | Effect                                               | Default |
|---------------|------------------------------------------------------|---------|
| `DEBUG`       | Enable or disable debug print blocks                 | 1       |
| `USE_UNICODE` | Use fancy suit symbols (♥♦♣♠) or fallback to H/D/C/S | 1       |

You can change these either:
- Directly in `config.h`
- Or via `-DDEBUG=0` and `-DUSE_UNICODE=0` at compile time

## 👨‍💻 Author

- Student ID: `s2921450`
- Course: 2322ENG – Engineering Programming
- Institution: Griffith University
