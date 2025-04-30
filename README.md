# GU Keep'Em — C Project

Welcome to *GU Keep'Em*, a poker-style card game built in C as part of the 2322ENG Engineering Programming major project.

## 🗂️ Project Structure

```
gu_keepem/
├── main.c             # Entry point and main game loop
├── player.h           # Player struct and related function declarations
├── player.c           # Player-related functions (create, quit, etc.)
├── game.h             # Game flow and logic declarations
├── game.c             # Game flow functions (play_hand, check_winner, etc.)
└── utils.h/.c         # Utility functions like input handling
```

## 📆 Development Roadmap

| Week | Features |
|------|----------|
| Week 1 | Interface & fake gameplay scaffold |
| Week 2 | Betting logic and player status |
| Week 3 | Card struct, deck logic, shuffle & deal |
| Week 4 | Hand scoring (basic) |
| Week 5 | Full scoring (tie-breakers, kickers, Ace high/low) |
| Week 6 | Custom feature development |
| Week 7 | Final presentation |

## 🧪 How to Compile and Run

### 🛠️ Compile the program (Linux/macOS)
```bash
gcc -o gu_keepem main.c game.c player.c utils.c
```

### ▶️ Run the program
```bash
./gu_keepem
```

### 🪟 On Windows (CMD or PowerShell)
```bash
Week1:
gcc -o gu_keepem main.c game.c player.c utils.c
gu_keepem.exe

Week2:
gcc -o gu_keepem main.c game.c player.c utils.c card.c

``````

```

Make sure you're in the same directory as the `.c` and `.h` files when compiling and running.

## 👨‍💻 Author

- Student ID: `s2921450`
- Course: 2322ENG – Engineering Programming
- Institution: Griffith University
