struct operands {
    float operand1;
    float operand2;
};

program CALC_PROG {
    version CALC_VERS {
        float ADD(struct operands) = 1;
        float SUB(struct operands) = 2;
        float MUL(struct operands) = 3;
        float DIV(struct operands) = 4;
        float MOD(struct operands) = 5;
        float PUISS(struct operands) = 6;
        float MAX(struct operands) = 7;
        float MIN(struct operands) = 8;
        float SQRT(float) = 9;
        float FACT(float) = 10;
    } = 1;
} = 0x20000001;
