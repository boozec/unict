void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  
  image(img, 0, 0);
  image(negative(img), 256, 0);
}

PImage negative(PImage I) {
  PImage out = I.copy();
  out.loadPixels();
  float r, g, b;

  for (int i = 0; i < out.pixels.length; ++i) {
    r= 255-red(out.pixels[i]);
    g= 255-green(out.pixels[i]);
    b= 255-blue(out.pixels[i]);

    out.pixels[i] = color(r, g, b);
  }

  out.updatePixels();
  return out;
}
