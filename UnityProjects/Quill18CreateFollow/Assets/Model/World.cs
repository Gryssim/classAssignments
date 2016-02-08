using UnityEngine;
using System;
using System.Collections.Generic;


public class World {

    Tile[,] tiles;

    Dictionary<string, InstalledObject> installedObjectPrototypes;


    int width;

    public int Width
    {
        get { return width; }
        set { width = value; }
    }

    int height;

    public int Height
    {
        get { return height; }
        set { height = value; }
    }

    Action<InstalledObject> cbInstalledObjectCreated;

    public World(int width = 100, int height = 100) 
    {
        this.width = width;
        this.height = height;

        tiles = new Tile[width, height];

        for (int x = 0; x < width; x++){
            for (int y = 0; y < height; y++){
                tiles[x, y] = new Tile(this, x, y);
            }
        }

        Debug.Log ("World created with " + (width * height) + " tiles");

        CreateInstalledObjectPrototypes();
    
    }

    void CreateInstalledObjectPrototypes()
    {
        installedObjectPrototypes = new Dictionary<string, InstalledObject>();



        installedObjectPrototypes.Add("Wall", InstalledObject.CreatePrototype(
            "Wall",
            0,  // Impassable 
            1,  // width 
            1)); // height);

    }



    public void RandomizeTiles()
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                if (UnityEngine.Random.Range(0, 2) == 0)
                {
                    tiles[x, y].Type = TileType.Empty;
                }
                else
                {
                    tiles[x, y].Type = TileType.Floor;
                }
            }
        }
    }

    public Tile GetTileAt(int x, int y)
    {
        if (x > width || x < 0 || y > height || y < 0){
            return null;
        }
   
        return tiles[x, y];
    }

    public void PlaceInstalledObject(string objectType, Tile t)
    {
       // Debug.Log("PlaceInstalledObject");
        // TODO this function assumes 1x1 tiles == change this later.

        if (installedObjectPrototypes.ContainsKey(objectType) == false)
        {
            Debug.LogError("installedObjectPrototypes doesn't contain a proto for key " + objectType);
        }

        InstalledObject obj = InstalledObject.placeInstance(installedObjectPrototypes[objectType], t);

        if (obj == null)
        {
            //Faled to place object -- most liklely there was already something there.
            return;
        }

        if (cbInstalledObjectCreated != null)
        {
            cbInstalledObjectCreated(obj);
        }

    }


    public void RegisterInstalledObjectCreated(Action<InstalledObject> callbackfunc)
    {
        cbInstalledObjectCreated += callbackfunc;
    }

    public void UnregisterInstalledObjectCreated(Action<InstalledObject> callbackfunc)
    {
        cbInstalledObjectCreated -= callbackfunc;
    }
}
