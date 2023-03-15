#include <bitset>

const int MAXN = 1e5;

typedef bitset<MAXN> BITS;

// TRICK: suma de dos bitsets
void suma(BITS &a, const BITS &b) {
  int carry = 0;
  for (int i = 0; i <= a.size(); i++) {
    if (carry) {
      carry = (a[i] || b[i]);
      a[i] = !(a[i] ^ b[i]);
    }
    else {
      carry = (a[i] && b[i]);
      a[i] = (a[i] ^ b[i]);
    }
  }
}

// TRICK: complemento a dos de un bitset
void complemento_dos(BITS a) {
  bool swapeando = false;
  for (int i = 0; i < a.size(); i++) {
    if (swapeando)
      a[i] = !a[i];
    else if (a[i])
      swapeando = true;
  }
}

// TRICK: resta de dos bitsets. La respuesta esta en complemento a dos
void resta(BITS &a, const BITS &b) {
  BITS comp_b = b;
  complemento_dos(comp_b);
  suma(a, comp_b);
}

int main() {
  // TRICK: __builtin_clz (count leading zeros) contar ceros por delante del
  // binario. Por ej: 00100 tiene 61 leading ceros
  cout << "Leading ceros de 00100: " << __builtin_clz(0x4) << endl;
  // TRICK: __builtin_ctz (count trailing zeros) contar ceros al inicio del
  // binario. Por ej: 010000 tiene cuatro trailing ceros
  cout << "Trailing ceros de 010000: " << __builtin_ctz(0x10) << endl;
  // TRICK: __builtin_popcount cuenta los bits encendidos. Los bitsets tienen
  // un simil llamado bitset::count
  cout << "Bits encendidos de 011010: " << __builtin_popcount(0x1A) << endl;

  // TRICK: for rapido usando __builtin_ctz. Salta de un bit al siguiente en
  // una mascara sin iterar por bits apagados
  int mask = 0xA803FFD5; printf("Mask: %x\tBits encendidos: ", mask);
  for (int c = mask >> __builtin_ctz(mask), pos = __builtin_ctz(mask); c > 0;
      pos += __builtin_ctz(c), c = c >> __builtin_ctz(c)) {
    cout << pos << " "; // pos = indice actual
    pos++;
    c >>= 1;
  }
  cout << endl;

  // TRICK: se puede simular un backtracking sobre un espacio de 2^n
  // posibilidades con un for y una mascara de bits
  int n = 16;
  for (int mask = 0; mask < (1<<n); mask++) {
    // DO SOMETHING
  }

  // TRICK: se pueden representar numeros mayores a LLONG_MAX usando un bitset.
  // Por ej: 2^1000. Se puede programar suma y resta de estas operaciones con
  // complemento a dos y carry. Tambien se pueden comparar
  BITS ABC; ABC[1000] = 1; ABC[1500] = 1;
  BITS CBA; CBA[1000] = 1; CBA[1200] = 1;
  BITS DIFF = resta(ABC, CBA);
}
