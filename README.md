# 🧠 Mind Guessing Game Plus

An interactive console-based C++ game that uses a mathematical trick to guess the number a user is thinking of. Built using Object-Oriented Programming (OOP) concepts, this project demonstrates user interaction, logic building, and console UI enhancements.

## 🚀 Features
- Interactive step-by-step gameplay
- Uses mathematical logic to predict final number
- Colored console UI (Windows API)
- Slow typing effect for better user experience
- Prize system based on result
- Score tracking system

## 🧠 Concepts Used
- Inheritance (Base class `Game`, Derived class `MindGame`)
- Polymorphism (Virtual function `run()`)
- Encapsulation (Protected & private members)
- Random number generation
- User input handling

## 🎮 How It Works
1. User thinks of a number (1–9)
2. Performs simple operations guided by the program
3. Program predicts the final number using logic
4. User gets a prize based on result

## 🛠️ Technologies
- C++
- Windows.h (for colors & effects)
- conio.h (for key input)

## ▶️ How to Run
```bash
g++ main.cpp -o game
./game
*********************************************************
📌 Note
This project runs on Windows due to use of windows.h and conio.h
👤 Author

Muhammad Mustafa
