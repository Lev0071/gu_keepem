gcc -o run_tests test_hands.c ../src/card.c ../src/player.c ../src/utils.c ../src/game.c ../src/handscore.c -I../src -Wl,--subsystem,console
