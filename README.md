# <Texa$ hold'em>
A console-based poker simulator!

This game is intended to be played on a laptop which is passed around a group of 2 or more players. Since the role of the dealer is made redunant by the the program, it does not exist in this version of the game.

# How to play the game
* When the game is first launched, it will enter a setup screen for player count, starting money, and player names sequentially. Follow the instructions and enter the appropriate information when prompted with '>'
* During the small and big blinds, the current player must raise to at least the "minimum total", and a maximum of all your "free money". If the big blind player does not have enough money to match the small blind, they will call instead.
* From the pre-flop onwards, the laptop should be passed to the current player (displayed at the top) at the start of their turn, and other players may not view the screen.
* The game uses a command-line-style parser. For a list of these commands, enter "help" or see below.
* It is recommended to enter "info" at the start of every round after card(s) are dealt, to view your hand and community cards.
* At the start of the Showdown round, all players may view the screen to see the results of the current game.

# Game features
* Dynamic game progression. Each round ends when the required conditions are met. The game fast-forwards to the Showdown round if no players are required to move (e.g. during all-ins)
* All required info is available. For example, your bets and free money are displayed, as well as their sum (total money). no need for a calculator!
* Automatic hand detection! At the start of the Showdown, the best hand of each player is calculated, and the cards are displayed in order of their tie-breaker importance. 

# Game commands
The following is a list of the game commands. Additional parameters are not required, but may be helpful.
* help [command]
    * Displays this list in-game
    * [command] : gives more info about a particular command.
* info
    * Information about the current game, such as your hole cards, pot, etc.
* log [number]
    * A running log of the current game, such as who folded, raised (and how much), etc. Most recent on top.
    * [Number] : number of entries to display.
* check
    * Pass your turn if possible.
* call
    * Match the current minimum.
* raise [number]
    * Raise, then match the current minimum.
    * [number] : amount of money to raise the minimum total to.
* all in
    * Raise using all of your money.
* fold
    * Forfeit the current game.

# Abridged rules of Texas hold'em
This will be a very quick introduction to those who are not very familiary with poker.
In this example, there will be 4 players named A, B, C, D.

The order of gameplay for a single match is:
1. Players are dealt 2 cards. Cards cannot be viewed yet.
2. A - Small blind: half of the minimum bet.
3. B - Big blind : the starting minimum bet.
4. Players can now view their cards.
5. C - Pre-flop: check / call / raise / fold.
    Continue until all active players have matched the minimum bet.
6. Flop: 3 community cards are dealt.
7. Post-flop: same as pre-flop.
8. Turn: 1 community card is dealt.
9. Post-turn: same as pre-flop.
10. River: 1 community card is dealt.
11. Post-river: same as pre-flop.
12. Showdown: All active players reveal their hand to decide the winner.

# Hand rankings
1. Royal flush
2. Straight flush
3. Four-of-a-kind
4. Full house
5. Flush
6. Straight
7. Three-of-a-kind
8. Two-pair
9. Pair
10. High card
