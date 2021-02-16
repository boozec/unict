void setup() {
  size(512, 256);
  PImage img = loadImage("lena.png");
  img.resize(256, 256);
  img.filter(GRAY);
  PImage img2 = negative(img);
  image(img, 0, 0);
  image(img2, 256, 0);

  print("PSNR: ", psnr(img, img2));
}

float mse(PImage i1, PImage i2) {
  float res = 0;
  i1.loadPixels();
  i2.loadPixels();

  for (int i = 0; i < i1.pixels.length; ++i) {
    res+= pow(red(i1.pixels[i])-red(i2.pixels[i]), 2);
  }
  res = res/i1.pixels.length;
  i1.updatePixels();
  i2.updatePixels();

  return res;
}

float psnr(PImage i1, PImage i2) {
  float mse = mse(i1, i2);
  float res = 10*log(255*255/mse)/log(10);

  return res;
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
