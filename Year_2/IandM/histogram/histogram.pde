void setup() {
  size(256, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);

  image(img, 0, 0);
  float[] hist = histogram(img);
  for(int i = 0; i < 256; ++i) {
    println(i, hist[i]);
  }
}

float[] histogram(PImage I) {
  float[] h = new float[256];
  for (int i = 0; i< 256; ++i) { 
    h[i] = 0;
  }
  
  I.loadPixels();
  
  for(int i = 0; i < I.pixels.length; ++i) {
    h[int(red(I.pixels[i]))]++;
  }
  
  for(int i = 0; i < 256; ++i) {
    h[i] = h[i] / I.pixels.length;
  }
  
  I.updatePixels();

  return h;
}
