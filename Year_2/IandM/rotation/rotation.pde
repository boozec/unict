void setup() {
  size(768, 256);
}

float th = 0;

void draw() {
  PImage img = loadImage("lena.png");
  img.resize(256, 256);

  image(img, 0, 0);
  image(rotate_forward(img, radians(th)), 256, 0);

  image(inverse_rotate(img, radians(th)), 512, 0);
}

void keyPressed() {
  if (key == '+') {
    th++;
  } else if (key == '-') {
    th--;
  }
}

PImage rotate_forward(PImage I, float theta) {
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

      x = u1*cos(theta)-v1*sin(theta);
      y = u1*sin(theta)+v1*cos(theta);

      x+=I.width/2;
      y+=I.height/2;

      out.set(round(x), round(y), I.get(u, v));
    }
  }

  out.updatePixels();

  return out;
}

PImage inverse_rotate(PImage I, float theta) {
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

      u = x1*cos(theta)+y1*sin(theta);
      v = -x1*sin(theta)+y1*cos(theta);

      u+=I.width/2;
      v+=I.height/2;

      out.set(x, y, I.get(round(u), round(v)));
    }
  }

  out.updatePixels();

  return out;
}
