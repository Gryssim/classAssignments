using System;
using System.Linq;
using UnityEngine;
using System.Collections.Generic;


public class WorldController : MonoBehaviour {


    public static WorldController Instance { get; protected set; }

    public Sprite floorSprite; //FIXME
    public Sprite wallSprite; //FIXME


    Dictionary<Tile, GameObject> tileGameObjectMap;
    Dictionary<InstalledObject, GameObject> InstalledObjectGameObjectMap;

    public World World { get; protected set; }

	// Use this for initialization
	void Start () {
        if (Instance != null)
        {
            Debug.LogError("There should never be two world controllers.");
        }
        Instance = this;

        //Create World with Empty Tiles
        World = new World();

        World.RegisterInstalledObjectCreated(OnInstalledObjectCreated);

        //Instantiate our dictionary that tracks which GameObject is rednering which  Tile data.
        tileGameObjectMap = new Dictionary<Tile,GameObject>();
        InstalledObjectGameObjectMap = new Dictionary<InstalledObject, GameObject>();

        // Create a gameObject for each of our tiles, so they show visually.
        for (int x = 0; x < World.Width; x++)
        {
            for (int y = 0; y < World.Height; y++)
            {
                Tile tile_data = World.GetTileAt(x,y);

                GameObject tile_go = new GameObject();

                //Add our tile/GO pair to the dictionary.
                tileGameObjectMap.Add(tile_data, tile_go);

                tile_go.name = "Tile_" + x + "_" + y;
                tile_go.transform.position = new Vector3(tile_data.X, tile_data.Y, 0);
                tile_go.transform.SetParent(this.transform, true);


                //Add a sprite Renderer, but don't set sprite beacuse all tiles are empty.
                tile_go.AddComponent<SpriteRenderer>();

                //tile_data.RegisterTileTypeChangedCallback((tile) => { OnTileTypeChanged(tile, tile_go); });
                tile_data.RegisterTileTypeChangedCallback(OnTileTypeChanged);


            }
        }

        World.RandomizeTiles();

	}



	// Update is called once per frame
	void Update () {

	}


    //THIS IS AN EXAMPLE -- NOT CURRENTLY USED
    void DestroyAllTileGameObjects()
    {
        //this function might get called when we are changinging floors/levels.
        //We need to destroy all visual **GameObjects** -- but not the actual tile data!

        while (tileGameObjectMap.Count > 0)
        {
            Tile tile_data = tileGameObjectMap.Keys.First();
            GameObject tile_go = tileGameObjectMap[tile_data];

            //Remove pair from the map.
            tileGameObjectMap.Remove(tile_data);

            //Unregister the callback.
            tile_data.UnregisterTileTypeChangedCallback(OnTileTypeChanged);

            //destroy the visual GameObject
            Destroy(tile_go);
        }
        //Presumably, after this function gets called, we'd be calling another
        // function to build all the GameObjects for the tiles on the new floor/level.

    }

    void OnTileTypeChanged(Tile tile_data)
    {

        if (tileGameObjectMap.ContainsKey(tile_data) == false)
        {
            Debug.LogError("tileGameObjectMap doesn't contain the tile_data -- did you forget to add the tile to the dictionary? Or maybe forget to unregister a callback?");
            return;
        }
        
        GameObject tile_go = tileGameObjectMap[tile_data];

        if (tile_go == null)
        {
            Debug.LogError("tileGameObjectMap' returned GambObject is null -- did you forget to add the tile to the dictionary? Or maybe forget to unregister a callback?");
            return;
        }

        if (tile_data.Type == TileType.Floor)
        {
            tile_go.GetComponent<SpriteRenderer>().sprite = floorSprite;
        }
        else if (tile_data.Type == TileType.Empty)
        {
            tile_go.GetComponent<SpriteRenderer>().sprite = null;
        }
        else
        {
            Debug.LogError("OnTileTypeChanged - Unrecognized TileType");
        }

    }

    public Tile GetTileAtWorldCoord(Vector3 coord)
    {
        int x = Mathf.FloorToInt(coord.x);
        int y = Mathf.FloorToInt(coord.y);

        return WorldController.Instance.World.GetTileAt(x, y);
    }

    public void OnInstalledObjectCreated(InstalledObject obj)
    {
        //Create a visual GameObject linked to this data.

        //FIXME: Does not consider multi-tile objects nor rotated objects.

        GameObject obj_go = new GameObject();

        //Add our obj/GO pair to the dictionary.
        InstalledObjectGameObjectMap.Add(obj, obj_go);

        obj_go.name = obj.objectType + "_" + obj.tile.X + "_" + obj.tile.Y;
        obj_go.transform.position = new Vector3(obj.tile.X, obj.tile.Y, 0);
        obj_go.transform.SetParent(this.transform, true);


  
        obj_go.AddComponent<SpriteRenderer>().sprite = wallSprite;


        obj.RegisterOnChangedCallback(OnInstalledObjectChanged);

    }

    void OnInstalledObjectChanged(InstalledObject obj)
    {
        Debug.LogError("OnInstalledObjectChanged -- NOT IMPLEMENTED");
    }
}
