void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);
  image(median(img, 11), 256, 0);
}

PImage median(PImage I, int n) {
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
      
      tarr = sort(tarr);
      float med = tarr[(n*n)/2];
      if((n*n)%2 == 0) {
        med = (med+tarr[(n*n)/2-1])/2;
      }
      
      out.set(x, y, color(med));
    }
  }

  return out;
}
