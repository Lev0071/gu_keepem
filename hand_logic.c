START of play_hand()
│
├── 1. Reset pot to 0
│
├── 2. deal_hole_cards()
│     └── Each player gets 2 private cards
│
├── 3. deal_community_cards()
│     └── Deal 5 community cards into table[5] secretly
│
├── 4. Show Players' Hands
│     └── print each player's 2 cards
│
├── 5. Reveal FLOP
│     └── print_table_cards(3)
│     └── (Later: run_prediction_round() here)
│
├── 6. Reveal TURN
│     └── print_table_cards(4)
│     └── (Later: run_prediction_round() here)
│
├── 7. Reveal RIVER
│     └── print_table_cards(5)
│     └── (Later: run_prediction_round() here)
│
├── 8. Pick Winner
│     └── (For now: randomly pick a player still in game)
│
├── 9. Calculate Pot
│     └── Randomly deduct fake bets from other players
│
├── 10. Award Pot to Winner
│
└── 11. Show Updated Credits
END of play_hand()
