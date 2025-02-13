using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum GameActionType { Fold, Call, Raise }

public class GameAction
{
    public GameActionType Type { get; private set; }
    public int Amount { get; private set; }

    public GameAction(GameActionType type, int amount)
    {
        Type = type;
        Amount = amount;
    }
}
