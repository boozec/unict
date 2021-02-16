void setup() {
  size(768, 512);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  image(img, 0, 0);
  image(replication2x(img), 256, 0);
}

PImage replication2x(PImage I) {
  PImage out = createImage(I.width*2, I.height*2, RGB);

  for(int x = 0; x < I.width; ++x) {
    for(int y = 0; y < I.height; ++y) {
      out.set(2*x, 2*y, I.get(x, y));
      out.set(2*x+1, 2*y, I.get(x, y));
      out.set(2*x, 2*y+1, I.get(x, y));
      out.set(2*x+1, 2*y+1, I.get(x, y));
    }
  }

  return out;
}
