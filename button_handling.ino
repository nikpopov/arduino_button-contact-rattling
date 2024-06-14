// Define button pin
#define buttonPin 2

// Variables to store the current and last button state
int buttonState = HIGH;         // Current state of the button
int lastButtonState = HIGH;     // Previous state of the button

// Variables to track timing
unsigned long lastDebounceTime = 0; // Time the button was last toggled
unsigned long debounceDelay = 50;   // Debounce time, increase if needed

// Variables to detect press types
unsigned long pressStartTime;
const unsigned long longPressDuration = 1000; // Duration for a long press (in ms)

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
}

void loop() {
  int reading = digitalRead(buttonPin); // Read the state of the button

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reset the debouncing timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed
      if (buttonState == LOW) {
        pressStartTime = millis(); // Record the time when the button is pressed
      } else {
        unsigned long pressDuration = millis() - pressStartTime;

        if (pressDuration < longPressDuration) {
          Serial.println("Tick");
        } else {
          Serial.println("Press");
        }
      }
    }
  }

  lastButtonState = reading;
}
