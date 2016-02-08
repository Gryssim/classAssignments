using UnityEngine;
using System.Collections;
using System;

//TileType is the base type of the tile. In some tile-based games, that might be
//the terrain type. For us, we only need to differentiate between empty space
//and floor (a.k.a. the station structure/scaffold). Walls/Doors/etc... will be
//InstalledObjects sitting on top of the floor.
public enum TileType { Empty, Floor };

public class Tile {

    TileType type = TileType.Empty;

    public TileType Type
    {
        get { return type; }
        set
        {
            TileType oldType = type;
            type = value;
            //Call the callback and let things know we've changed type.
            if (cbTileTypeChanged != null && oldType != type)
            {
                cbTileTypeChanged(this);
            }
        }
    }

    Action<Tile> cbTileTypeChanged;
   //LooseObject is something like a stack of metal on the floor.
    LooseObject looseObject;
    //InstalledObject is something like an installed door or sofa.
    InstalledObject installedObject;

    World world;
    int x;

    public int X
    {
        get { return x; }
    }
    int y;

    public int Y
    {
        get { return y; }
    }

    public void RegisterTileTypeChangedCallback(Action<Tile> callback)
    {
        cbTileTypeChanged += callback;
    }

    public void UnregisterTileTypeChangedCallback(Action<Tile> callback)
    {
        cbTileTypeChanged -= callback;
    }

    public Tile( World world, int x, int y ) {
        this.world = world;
        this.x = x;
        this.y = y;
    }

    public bool PlaceObject(InstalledObject objInstance)
    {
        if (objInstance == null)
        {
            //We are uninstalling whatever was here beofre.
            installedObject = null;
            return true;
        }
        
        //objInstance isn't null
        if (installedObject != null)
        {
            Debug.LogError("Trying to assign an installed object to a tile that already has one!");
            return false;
        }

        // At this point, everything fine!

        installedObject = objInstance;
        return true;
    }

}
