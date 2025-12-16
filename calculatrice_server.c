#include "calculatrice.h"
#include <math.h>

float *add_1_svc(struct operands *args, struct svc_req *rqstp) {
    static float result;
    result = args->operand1 + args->operand2;
    return &result;
}

float *sub_1_svc(struct operands *args, struct svc_req *rqstp) {
    static float result;
    result = args->operand1 - args->operand2;
    return &result;
}

float *mul_1_svc(struct operands *args, struct svc_req *rqstp) {
    static float result;
    result = args->operand1 * args->operand2;
    return &result;
}

float *div_1_svc(struct operands *args, struct svc_req *rqstp) {
    static float result;
    if (args->operand2 != 0) {
        result = args->operand1 / args->operand2;
    } else {
        result = 0.0; // Gérer la division par zéro
    }
    return &result;
}

float *mod_1_svc(struct operands *args, struct svc_req *rqstp) {
    static float result;
    result = fmodf(args->operand1, args->operand2);
    return &result;
}

float *puiss_1_svc(struct operands *args, struct svc_req *rqstp) {
    static float result;
    result = powf(args->operand1, args->operand2);
    return &result;
}

float *max_1_svc(struct operands *args, struct svc_req *rqstp) {
    static float result;
    result = (args->operand1 > args->operand2) ? args->operand1 : args->operand2;
    return &result;
}

float *min_1_svc(struct operands *args, struct svc_req *rqstp) {
    static float result;
    result = (args->operand1 < args->operand2) ? args->operand1 : args->operand2;
    return &result;
}

float *sqrt_1_svc(float *arg, struct svc_req *rqstp) {
    static float result;
    result = sqrtf(*arg);
    return &result;
}

float *fact_1_svc(float *arg, struct svc_req *rqstp) {
    static float result = 1.0;
    result = 1.0;
    int i;
    for (i = 1; i <= (int)*arg; ++i) {
        result *= (float)i;
    }
    return &result;
}
