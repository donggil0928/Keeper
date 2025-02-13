using System.Collections;
using System.Collections.Generic;
using CardGame;
using UnityEngine;


public class GameState
{
    public List<Player> Players { get; private set; }
    public List<Card> CommunityCards { get; private set; }
    public int Pot { get; private set; }
    public int CurrentBet { get; private set; }
    public int RoundNumber { get; private set; }
    public int CurrentPlayerIndex { get; set; }
    public bool SpecialCardSelectionUsed { get; set; }
    
    public GameState() {
        Players = new List<Player>();
        CommunityCards = new List<Card>();
        RoundNumber = 1;
        ResetRound();
    }

    public void ResetRound() {
        Pot = 0;
        CurrentBet = 0;
        CommunityCards.Clear();
        SpecialCardSelectionUsed = false;
    }

    public void AddToPot(int amount) {
        Pot += amount;
    }

    public void IncrementRound()
    {
        RoundNumber++;
    }
    
    public void SetCurrentBet(int amount) {
        CurrentBet = amount;
    }
    

    public void AddCommunityCard(Card card) {
        CommunityCards.Add(card);
    }
}

