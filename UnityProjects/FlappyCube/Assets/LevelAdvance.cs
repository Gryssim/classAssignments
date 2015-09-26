using UnityEngine;
using System.Collections;

public class LevelAdvance : MonoBehaviour {

	void OnTriggerEnter2D(Collider2D Trigger){

        GameObject ground = (GameObject)Instantiate(Resources.Load("ground"));

    }
}
