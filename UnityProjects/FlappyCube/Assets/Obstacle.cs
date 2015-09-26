using UnityEngine;
using System.Collections;

public class Obstacle : MonoBehaviour {

    //movement speed (0 means no movement)
    public float speed = 0;

    // Switch Movement direction every x seconds
    public float switchTime = 2;

	// Use this for initialization
	void Start () {
        GetComponent<Rigidbody2D>().velocity = Vector2.up * speed;

        InvokeRepeating("Switch", 0, switchTime);
	}

    void Switch()
    {
        GetComponent<Rigidbody2D>().velocity *= -1;
    }
	
	// Update is called once per frame
	void Update () {
	
	}
}
