uint8_t GrayToBin(uint8_t gray) {
  // Case table
  switch (gray) {
    case 0b00000: return 0;
    case 0b00001: return 1;
    case 0b00101: return 2;
    case 0b00100: return 3;
    case 0b00110: return 4;
    case 0b00111: return 5;
    case 0b10111: return 6;
    case 0b10110: return 7;
    case 0b10100: return 8;
    case 0b10101: return 9;
    case 0b10001: return 10;
    case 0b10000: return 11;
    case 0b10010: return 12;
    case 0b10011: return 13;
    case 0b11011: return 14;
    case 0b11010: return 15;
    case 0b11000: return 16;
    case 0b11001: return 17;
    case 0b11101: return 18;
    case 0b11100: return 19;
    case 0b11110: return 20;
    case 0b11111: return 21;
    case 0b01111: return 22;
    case 0b01110: return 23;
    case 0b01100: return 24;
    case 0b01101: return 25;
    case 0b01001: return 26;
    case 0b01000: return 27;
    case 0b01010: return 28;
    case 0b01011: return 29;
    case 0b00011: return 30;
    case 0b00010: return 31;
  }
}