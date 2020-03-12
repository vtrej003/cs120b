using UnityEngine;

namespace User_Scripts
{
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

            if (input == "up")
            {
                transform.Translate(Vector3.forward * Time.deltaTime * moveSpeed);
            }
            if (input == "down")
            {
                transform.Translate(Vector3.back * moveSpeed * Time.deltaTime);
            }
            if (input == "left")
            {
                transform.Rotate(Vector3.up * Time.deltaTime * turnSpeed);
            }
            if (input == "right")
            {
                transform.Rotate(Vector3.up * Time.deltaTime * -turnSpeed);
            }
        }
    }
}
