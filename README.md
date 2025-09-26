# 🎮 Tic-Tac-Toe with Minimax AI

![C++](https://img.shields.io/badge/Language-C++-blue.svg)  
![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)  
![AI](https://img.shields.io/badge/AI-Minimax_Algorithm-red.svg)  
![Board](https://img.shields.io/badge/Board-Scalable_(n_x_n)-blueviolet.svg)  

---

## 📌 Project Overview
This project is a **C++ implementation of Tic-Tac-Toe** with both **Human vs Human** and **Human vs AI** modes.  
The AI is powered by the **Minimax Algorithm**, making it unbeatable at hard difficulty.  

It is designed to be:
- **Object-Oriented** (with classes for `Board`, `Player`, `HumanPlayer`, `AIPlayer`, and `Game`).  
- **Scalable** (supports both the standard **3×3 board** and any custom **n×n board**).  
- **User-Friendly** (clear menus, board visualization, and input validation).  

---

## ✅️ Features
- 🧑‍🤝‍🧑 **Player vs Player** mode.  
- 🤖 **Player vs Computer** mode:  
  - Easy → Random moves.  
  - Hard → **Unbeatable AI using Minimax**.  
- 🔢 **Customizable board size** (3×3 or larger).  
- 🎯 **Win, draw, and invalid move detection**.  
- 🔄 **Replay option** after each game.  
- 🧹 **Clean, modular, and extensible code**.  

---

## 🧠 Minimax Algorithm (AI Logic)
The **Minimax Algorithm** is used to simulate all possible moves and outcomes:
1. **Check terminal state** → win, loss, or draw.  
2. **Maximizing (AI)** → choose the move with the **highest score**.  
3. **Minimizing (Human)** → choose the move with the **lowest score**.  
4. Recursively simulate until the game ends, then backtrack the scores.  
5. AI selects the **optimal move** at every turn.  

This guarantees that at **hard difficulty**, the AI **never loses**.  

---

## 🏗️ Project Structure
- **`Board`** → Manages the grid, moves, win checks, and display.  
- **`Player` (Abstract)** → Base class for both human and AI.  
- **`HumanPlayer`** → Handles user input with validation.  
- **`AIPlayer`** → Implements AI logic (random or minimax).  
- **`Game`** → Controls the flow, menu, and turns.  
- **`main`** → Entry point, board size selection, replay loop.  

---

## 📸 Example Gameplay
```
TIC-TAC-TOE GAME
 ==================
1. Player vs Player
2. Player vs Computer (Easy)
3. Player vs Computer (Hard)
4. Exit
Select game mode: 3

Hello Player 1, Enter your name: Alex
Player 1: Alex (X)
Player 2: Computer (O , Difficulty = Hard)

   1   2   3
 1   |   |  
   ---+---+---
 2   |   |  
   ---+---+---
 3   |   |  

Alex's turn (X):
Enter row: 1
Enter column: 1
```

---

## 🚀 How to Run
1. **Clone this repository** or copy the code file.  
2. Compile with any C++ compiler:
   ```bash
   g++ template.cpp -o tictactoe
   ./tictactoe
   ```
3. Choose game mode and enjoy 🎮.  

---

## 💫 Future Enhancements
- 🖥️ Add **GUI interface** (Qt / SFML).  
- 📊 Maintain **player statistics** (win/loss history).  
- 🌐 Enable **network multiplayer** mode.
  
---

## 🏅 Acknowledgments
- Developed as part of **FuzeTek Summer Internship 2025 - Project 6**.  
- **Team Members (Team 5):**  
  - Youssef Alaa *(Leader)*  
  - Ahmed Mahmoud  
  - Habeba Sherif  
  - Mohamed Mostafa  
  - Sondos Mohamed  

---
