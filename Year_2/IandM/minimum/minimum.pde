void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);
  image(minimum(img, 11), 256, 0);
}

PImage minimum(PImage I, int n) {
  PImage out = createImage(I.width, I.height, RGB);

  int off = n/2;

  for (int x = 0; x < I.width; ++x) {
    for (int y = 0; y < I.height; ++y) {
      PImage t = I.get(x-off, y-off, n, n);
      float[] tarr = new float[n*n];
      t.loadPixels();
      
      for(int i = 0; i < t.pixels.length; ++i) {
        tarr[i] = red(t.pixels[i]);
      }
      
      out.set(x, y, color(min(tarr)));
    }
  }

  return out;
}
