void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);
  image(equalization(img), 256, 0);
}

PImage equalization(PImage I) {
  PImage out = I.copy();
  float[] h = histogram(out);

  for (int i = 1; i < 256; ++i) {
    h[i] = h[i]+h[i-1];
  }

  out.loadPixels();

  for (int i = 0; i < out.pixels.length; ++i) {
    out.pixels[i] = color(255*h[int(red(out.pixels[i]))]);
  }

  out.updatePixels();

  return out;
}

float[] histogram(PImage I) {
  float[] h = new float[256];
  for (int i = 0; i< 256; ++i) { 
    h[i] = 0;
  }

  I.loadPixels();

  for (int i = 0; i < I.pixels.length; ++i) {
    h[int(red(I.pixels[i]))]++;
  }

  for (int i = 0; i < 256; ++i) {
    h[i] = h[i] / I.pixels.length;
  }

  I.updatePixels();

  return h;
}
