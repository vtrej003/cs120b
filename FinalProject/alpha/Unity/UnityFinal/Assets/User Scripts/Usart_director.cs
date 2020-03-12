using UnityEngine;

namespace User_Scripts
{
    public class UsartDirector : MonoBehaviour
    {
        public SerialController serialController;
        public Player_controller playerInput;
        // Start is called before the first frame update
        void Start()
        {
            serialController = GameObject.Find("SerialController").GetComponent<SerialController>();
            playerInput = GameObject.Find("Player").GetComponent<Player_controller>();
        }
        // Update is called once per frame
        void Update()
        {
            string message = serialController.ReadSerialMessage();
        
            if(message == null)
            {
                return;
            }

            if(message == "up" || message == "right" || message == "down" || message == "left")
            {
                playerInput.input = message;
            }

        }
    }
}
