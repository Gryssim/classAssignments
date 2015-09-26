using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ScoreTracker : MonoBehaviour {

    public static int Score = 0;
    private string scoreText;
    

    void Start()
    {
        Score = 0;
        scoreText = "Score: " + Score.ToString();
    }

    void Update()
    {
        scoreText = "Score: " + Score.ToString();
    }

    void OnGUI()
    {
        GUI.contentColor = Color.black;
        GUI.Label(new Rect(20, 20, 100, 100), scoreText);
        
    }

    public static void IncreaseScore(int Amount)
    {
        Score += Amount;
    }
    
}
