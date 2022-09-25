String utf8rus(String source)
{
  bool up = false;
  if (up == true) source.toUpperCase();
  int i, k;
  String target;
  unsigned char n;
  k = source.length(); i = 0;
  while (i < k) {
    n = source[i]; i++;
    switch (n) {
      case 208: {
          n = source[i]; i++;
          if (n == 134) { n = 143; break; }  // І
          if (n == 129) { n = 168; break; }
          if (n >= 144 && n <= 191) n = n + 48;
          if (n >= 224 && up == true) n = n - 32;
          break;
        }
      case 209: {
          n = source[i]; i++;
          if (n == 150) { n = 144; break; }  // і
          if (n == 145) { n = 184; break; }
          if (n >= 128 && n <= 143) n = n + 112;
          if (n >= 224 && up == true) n = n - 32;
          break;
        }
      case 210: {
          n = source[i]; i++;
          switch (n) {
            case 146: n = 129; break; // Ғ
            case 147: n = 130; break; // ғ
            case 154: n = 131; break; // Қ
            case 155: n = 132; break; // қ
            case 162: n = 133; break; // Ң
            case 163: n = 134; break; // ң
            case 176: n = 137; break; // Ұ
            case 177: n = 138; break; // ұ
            case 174: n = 139; break; // Ү
            case 175: n = 140; break; // ү
            case 186: n = 141; break; // Һ
            case 187: n = 142; break; // h
            break;
          }
          break;
        }
      case 211: {
          n = source[i]; i++;
          switch (n) {
            case 152: n = 127; break; // Ә
            case 153: n = 128; break; // ә
            case 168: n = 135; break; // Ө
            case 169: n = 136; break; // ө
            break;
          }
          break;
        }
        break;
      case 226: {
        n = source[i]; i++;
          switch (n) {
            case 132:{
              n = source[i]; i++;
                switch (n) {
                  case 150: {
                    n = 35; break; // №
                  }
                }
            }
          }
      }
    }
    target += char(n);
  }
  return target;
}
