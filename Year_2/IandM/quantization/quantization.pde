void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);
  image(quantization(img, 10), 256, 0);
}

PImage quantization(PImage I, int k) {
  PImage out = I.copy();
  out.loadPixels();
  int r;

  for (int i = 0; i < out.pixels.length; ++i) {
    r = (int) floor((red(out.pixels[i])*k)/256);
    r = int((float(r)/(k-1))*255);

    out.pixels[i] = color(r);
  }

  out.updatePixels();
  return out;
}
