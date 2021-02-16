void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);
  image(stretching(img), 256, 0);
}

PImage stretching(PImage I) {
  PImage out = I.copy();
  out.loadPixels();

  float max = red(out.pixels[0]);
  float min = max;

  for (int i = 0; i < out.pixels.length; ++i) {
    float t = red(out.pixels[i]);
    if (t < min)
      min = t;
    if (t > max)
      max = t;
  }

  for (int i = 0; i < out.pixels.length; ++i) {
    out.pixels[i]= color(255*(red(out.pixels[i])-min)/(max-min));
  }

  out.updatePixels();
  return out;
}
