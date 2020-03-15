using UnityEngine;
using System.Collections;

    public class Player_controller : MonoBehaviour
    {
        public float moveSpeed = 10f;
        public float turnSpeed = 10f;
        public string input;

        // Start is called before the first frame update
        void Start()
        {
        
        }

        // Update is called once per frame
        void Update()
        {
            
            if (input == "u")
            {
                transform.Translate(Vector3.forward * moveSpeed * Time.deltaTime);
                
            }
            if (input == "d")
            {
                transform.Translate(Vector3.back * moveSpeed * Time.deltaTime);
            }
            if (input == "l")
            {
                transform.Rotate(Vector3.up * Time.deltaTime * -turnSpeed);
            }
            if (input == "r")
            {
                transform.Rotate(Vector3.up * Time.deltaTime * turnSpeed);
            }
        }
        // Invoked when a line of data is received from the serial device.
        void OnMessageArrived(string msg)
        {
            Debug.Log("Message arrived: " + msg);
            input = msg;
        }
        // Invoked when a connect/disconnect event occurs. The parameter 'success'
        // will be 'true' upon connection, and 'false' upon disconnection or
        // failure to connect.
        void OnConnectionEvent(bool success)
        {
            if (success)
                Debug.Log("Connection established");
            else
                Debug.Log("Connection attempt failed or disconnection detected");
        }
    }
    
