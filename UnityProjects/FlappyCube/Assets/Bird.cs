using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Bird : MonoBehaviour {

    public float speed = 2f;
    // flap force
    public float force = 300;
	// Use this for initialization

	void Start () {
	//fly towards the right
        GetComponent<Rigidbody2D>().velocity = Vector2.right * speed;
	}

	// Update is called once per frame
	void Update () {
	// flap
        if (Input.GetKeyDown(KeyCode.Space))
            GetComponent<Rigidbody2D>().AddForce(Vector2.up * force);
	}

    void OnCollisionEnter2D(Collision2D coll)
    {
        //Restart
        Application.LoadLevel(Application.loadedLevel);
    }


    void OnTriggerEnter2D(Collider2D trig)
    {
       ScoreTracker.IncreaseScore(1);
    }

}
