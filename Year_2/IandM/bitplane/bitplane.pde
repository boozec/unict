int nb = 0;

void setup() {
  size(512, 256);
}

void draw() {
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);
  image(bitplane(img, nb), 256, 0);
}

void keyPressed() {
  if(key == '+' && nb < 7) {
    nb++;
  } else if(key == '-' && nb > 1) {
    nb--;
  }
}

PImage bitplane(PImage I, int nb) {
  PImage out = I.copy();
  out.loadPixels();

  int x, r;

  for (int i = 0; i < out.pixels.length; ++i) {
    x = int(red(out.pixels[i]));
    r = (x >> nb) & 1;
    out.pixels[i] = color(255*r);
  }

  out.updatePixels();

  return out;
}
