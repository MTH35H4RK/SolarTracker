#include <Servo.h>

const int LDR_TOP_LEFT = A0;
const int LDR_TOP_RIGHT = A1;
const int LDR_BOTTOM_LEFT = A2;
const int LDR_BOTTOM_RIGHT = A3;

Servo servo_horizontal;
Servo servo_vertical;

const int SEUIL_HORIZONTAL = 50;
const int SEUIL_VERTICAL = 50;

void setup() {
  Serial.begin(9600);
  servo_horizontal.attach(9); // Servomoteur horizontal
  servo_vertical.attach(10); // Servomoteur vertical
  pinMode(LDR_TOP_LEFT, INPUT);
  pinMode(LDR_TOP_RIGHT, INPUT);
  pinMode(LDR_BOTTOM_LEFT, INPUT);
  pinMode(LDR_BOTTOM_RIGHT, INPUT);
}

void loop() {
  int valeur_top_left = analogRead(LDR_TOP_LEFT);
  int valeur_top_right = analogRead(LDR_TOP_RIGHT);
  int valeur_bottom_left = analogRead(LDR_BOTTOM_LEFT);
  int valeur_bottom_right = analogRead(LDR_BOTTOM_RIGHT);
  int difference_horizontale = valeur_top_left - valeur_top_right;
  int difference_verticale = valeur_top_left - valeur_bottom_left;

  // Print sensor values and differences
  Serial.print("Top Left: ");
  Serial.print(valeur_top_left);
  Serial.print(" Top Right: ");
  Serial.print(valeur_top_right);
  Serial.print(" Bottom Left: ");
  Serial.print(valeur_bottom_left);
  Serial.print(" Bottom Right: ");
  Serial.println(valeur_bottom_right);
  
  Serial.print("Difference Horizontale: ");
  Serial.println(difference_horizontale);
  Serial.print("Difference Verticale: ");
  Serial.println(difference_verticale);

  controlerServomoteurs(difference_horizontale, difference_verticale);

  delay(100);
}

void controlerServomoteurs(int difference_horizontale, int difference_verticale) {
  // Debug current servo positions
  int current_horizontal_position = servo_horizontal.read();
  int current_vertical_position = servo_vertical.read();
  
  Serial.print("Current Horizontal Position: ");
  Serial.println(current_horizontal_position);
  Serial.print("Current Vertical Position: ");
  Serial.println(current_vertical_position);

  if (abs(difference_horizontale) > SEUIL_HORIZONTAL) {
    if (difference_horizontale > 0 && current_horizontal_position < 180) {
      servo_horizontal.write(current_horizontal_position + 1); // Tourner à gauche
      Serial.println("Turning Left");
    } else if (difference_horizontale < 0 && current_horizontal_position > 0) {
      servo_horizontal.write(current_horizontal_position - 1); // Tourner à droite
      Serial.println("Turning Right");
    }
  }

  if (abs(difference_verticale) > SEUIL_VERTICAL) {
    if (difference_verticale > 0 && current_vertical_position < 180) {
      servo_vertical.write(current_vertical_position + 1); // Monter
      Serial.println("Moving Up");
    } else if (difference_verticale < 0 && current_vertical_position > 0) {
      servo_vertical.write(current_vertical_position - 1); // Descendre
      Serial.println("Moving Down");
    }
  }
}
