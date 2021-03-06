#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

float hue = 0;  //Color inicial, de 0 a 255. Float para que lo podamos modificar mas suavemente.

void KnightRiderSetHue(float h) {
  hue = h;
}

void KnightRider(int trail, float rainbow, float rainbowTrail, bool mirrored, uint8_t wait) {
  for (int i = 0; i < NUMLEDS * 2; i++) {
    Trail(i, trail, rainbowTrail, true);

    strip.show();
    delay(wait);
    hue += rainbow;  //Comentar si no quieres que vaya rotando colores.
  }
}

void Trail(int startPos, int trail, float rainbowTrail, bool mirrored) {
  int mirror = 1 + mirrored;
  for (int j = 0; j <= trail; j++) {
    uint32_t color;
    int pos;
    float alpha;
    //Vamos desde 0 hasta el doble del nº de leds
    pos = (startPos + j) % (NUMLEDS * 2 / mirror);
    alpha = (j * 1.0f) / (trail);

    color = Wheel(hue + j * rainbowTrail, alpha);

    if (pos >= NUMLEDS / mirror) {
      //Si pos es mayor al nº de leds, vamos hacia la izq.
      pos = (NUMLEDS - pos % (NUMLEDS)) - 1;
    }

    strip.setPixelColor(pos, color);
    if (mirrored) {
      strip.setPixelColor(NUMLEDS - pos - 1, color);
    }
  }
}
