void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);

  image(img, 0, 0);
  image(logarithm(img, 100), 256, 0);
}

PImage logarithm(PImage I, int k) {
  PImage out = I.copy();
  out.loadPixels();
  float r, g, b;
  float C = k/log(256);

  for (int i = 0; i < out.pixels.length; ++i) {
    r= C*log(1+red(out.pixels[i]));
    g= C*log(1+green(out.pixels[i]));
    b= C*log(1+blue(out.pixels[i]));

    out.pixels[i] = color(r, g, b);
  }

  out.updatePixels();
  return out;
}
