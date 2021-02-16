void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);

  image(img, 0, 0);
  image(gamma(img, 2), 256, 0);
}

PImage gamma(PImage I, float gm) {
  PImage out = I.copy();
  out.loadPixels();
  float r, g, b;
  float C = 1 / pow(255, gm-1);

  for (int i = 0; i < out.pixels.length; ++i) {
    r= C*pow(red(out.pixels[i]), gm);
    g= C*pow(green(out.pixels[i]), gm);
    b= C*pow(blue(out.pixels[i]), gm);

    out.pixels[i] = color(r, g, b);
  }

  out.updatePixels();
  return out;
}
