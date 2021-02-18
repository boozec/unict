float scalex = 1.0, scaley = 1.0;

void setup() {
  size(768, 256);
}

void draw() {
  PImage img = loadImage("lena.png");
  img.resize(256, 256);

  image(img, 0, 0);
  image(scale_forward(img, scalex, scaley), 256, 0);
  image(inverse_scale(img, scalex, scaley), 512, 0);
}

void keyPressed() {
  if (key == '+') {
    scalex+=0.1; 
    scaley+=0.1;
  } else if (key == '-' && (scalex > 0 && scaley > 0)) {
    scalex-=0.1; 
    scaley-=0.1;
  }
}

PImage scale_forward(PImage I, float sx, float sy) {
  PImage out = createImage(I.width, I.height, RGB);

  out.loadPixels();

  for (int i = 0; i < out.pixels.length; ++i) {
    out.pixels[i] = color(0);
  }

  float x, y;
  float u1, v1;

  for (int u = 0; u < I.width; ++u) {
    for (int v = 0; v < I.height; ++v) {
      u1 = u-I.width/2;
      v1 = v-I.height/2;

      x = u1*sx;
      y = v1*sy;

      x+=I.width/2;
      y+=I.height/2;

      out.set(round(x), round(y), I.get(u, v));
    }
  }

  out.updatePixels();

  return out;
}

PImage inverse_scale(PImage I, float sx, float sy) {
  PImage out = createImage(I.width, I.height, RGB);

  out.loadPixels();

  for (int i = 0; i < out.pixels.length; ++i) {
    out.pixels[i] = color(0);
  }

  float u, v;
  float x1, y1;

  for (int x = 0; x < I.width; ++x) {
    for (int y = 0; y < I.height; ++y) {
      x1 = x-I.width/2;
      y1 = y-I.height/2;

      u = x1*1/sx;
      v = y1*1/sy;

      u+=I.width/2;
      v+=I.height/2;

      out.set(x, y, I.get(round(u), round(v)));
    }
  }

  out.updatePixels();

  return out;
}
