// 7 segment display configurator header file
#ifndef ssd
#define ssd

#ifndef Arduino_h
    #include <iostream>
    #define String std::string
#endif
#define segments 7
#define amount 63
#define TM1637 "pgfedcba"

class display {
#if segments == 16
#elif segments == 14
#elif segments == 9
#else
    bool table[amount][8] = {
        // anode values for 0-9, A-Z, a-z
      // a b c d e f g dp
        {0,0,0,0,0,0,1,1}, // 0
        {1,0,0,1,1,1,1,1}, // 1
        {0,0,1,0,0,1,0,1}, // 2
        {0,0,0,0,1,1,0,1}, // 3
        {1,0,0,1,1,0,0,1}, // 4
        {0,1,0,0,1,0,0,1}, // 5
        {0,1,0,0,0,0,0,1}, // 6
        {0,0,0,1,1,1,1,1}, // 7
        {0,0,0,0,0,0,0,1}, // 8
        {0,0,0,0,1,0,0,1}, // 9
        {0,0,0,1,0,0,0,1}, // A
        {0,0,0,0,0,0,0,1}, // B
        {0,1,1,0,0,0,1,1}, // C
        {0,0,0,0,0,1,1,1}, // D
        {0,1,1,0,0,0,0,1}, // E
        {0,1,1,1,0,0,0,1}, // F
        {0,1,0,0,0,0,1,1}, // G
        {1,0,0,1,0,0,0,1}, // H
        {1,1,1,1,0,0,1,1}, // I
        {1,0,0,0,1,1,1,1}, // J
        {1,0,1,0,0,0,0,1}, // K
        {1,1,1,0,0,0,1,1}, // L
        {0,1,0,1,0,1,1,1}, // M
        {1,0,0,1,0,0,0,1}, // N
        {0,0,0,0,0,0,1,1}, // O
        {0,0,1,1,0,0,0,1}, // P
        {0,0,1,0,0,0,1,1}, // Q
        {0,0,1,0,0,0,0,1}, // R
        {0,1,0,0,1,0,0,1}, // S
        {0,1,1,1,0,0,1,1}, // T
        {1,0,0,0,0,0,1,1}, // U
        {1,0,0,0,1,0,1,1}, // V
        {1,0,1,0,1,0,0,1}, // W
        {0,1,1,0,1,1,0,1}, // X
        {1,0,0,0,1,0,0,1}, // Y
        {0,0,1,0,0,1,0,1}, // Z
        {1,1,0,0,1,1,0,1}, // a
        {1,1,0,0,0,0,0,1}, // b
        {1,1,1,0,0,1,0,1}, // c
        {1,0,0,0,0,1,0,1}, // d
        {1,1,1,0,0,1,1,1}, // e
        {0,1,1,1,0,0,0,1}, // f
        {0,1,1,0,1,1,0,1}, // g
        {1,1,0,1,0,0,1,1}, // h
        {1,1,1,1,0,1,1,1}, // i
        {1,0,0,0,1,1,1,1}, // j
        {0,1,1,0,1,0,0,1}, // k
        {1,1,1,1,0,0,1,1}, // l
        {0,1,0,1,0,1,1,1}, // m
        {1,1,0,1,0,1,0,1}, // n
        {1,1,0,0,0,1,0,1}, // o
        {0,0,1,1,0,0,0,1}, // p
        {0,0,0,1,0,0,0,1}, // q
        {1,1,1,1,0,1,0,1}, // r
        {1,1,1,0,1,1,0,1}, // s
        {1,1,1,0,0,0,0,1}, // t
        {1,1,0,0,0,1,1,1}, // u
        {1,1,0,0,1,1,1,1}, // v
        {1,0,1,0,1,0,1,1}, // w
        {1,1,1,0,1,1,0,1}, // x
        {1,0,0,0,1,0,0,1}, // y
        {1,1,1,0,1,1,0,1}, // z
        {1,1,1,1,1,1,1,1}
#endif
    };

    String order, mode; // FixMe, mode should be a char
    short B[amount];

    void calculate();

    public:
        display(String order, String mode = "cathode");
        #ifndef Arduino_h
        display();
        #endif

        short number(short num) { return B[num]; }
        short letter(char c);
        char* message(char msg[]);

        #ifdef Arduino_h
        void send(uint8_t data);
        void send(uint8_t data[], uint8_t sleep = 200);
        #else
        void print_table(short limit = 10, short s = 0, bool mode = 1);
        void dev() {print_table(amount, 0 , 0);};
        #endif
};

/*
#ifdef Arduino_h
class displays {
};
#endif
*/

#endif
