#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculatrice.h"

void printMenu() {
    printf("Choisissez une operation:\n");
    printf("0. Sortir du programme\n");
    printf("1. Addition\n");
    printf("2. Soustraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulo\n");
    printf("6. Puissance\n");
    printf("7. Maximum\n");
    printf("8. Minimum\n");
    printf("9. Racine carre\n");
    printf("10. Factorielle\n");
   
}

float readFloatInput(int operation_choice, float previous_result, int operand_number, int operands_required) {
    float input;
    char buffer[256];
     if((operand_number == 1 || operands_required == 2)&& operation_choice !=0 ){    

    printf("Entrer le %d%s chiffre:", operand_number, operand_number == 1 ? "er" : "eme");
    }


     while (1 && operation_choice !=0) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (strcmp(buffer, "resultat\n") == 0) {
               
                return previous_result;
            } else {
                if (sscanf(buffer, "%f", &input) == 1){   
                        return input;
                                
            } else {
                printf("Veuillez entrer un nombre valide : ");
            }
            }
        } else {
            printf("Erreur de saisie. Veuillez rssayer : ");
        }
    }
}

void performOperation(CLIENT *cl) {
    float *result;
    int operation_choice;
    struct operands operands_data;
    int continue_program = 1;
    float previous_result = 0;
    


   

    while (continue_program) {

        printMenu();
        printf("Votre choix:");
       
  operation_choice = readFloatInput(operation_choice,0,0,0);

  if(operation_choice <0 || operation_choice >10 ){
     printf("Choix invalide. Veuillez entrer un nombre entre 0 et 10. \n");
     continue;
   }
       
      operands_data.operand1 = readFloatInput(operation_choice,previous_result, 1, 1);
         
        
        

        if (operation_choice >= 1 && operation_choice <= 5) {
          operands_data.operand2 = readFloatInput(operation_choice,previous_result, 2, 2);
          
        } else {
            operands_data.operand2 = 0;
        }

        switch (operation_choice) {
            case 0:
 
                printf("Sortie du programme...\n");
               
                exit(0);
             
                   break;
            case 1:
                result = add_1(&operands_data, cl);
                break;
            case 2:
                result = sub_1(&operands_data, cl);
                break;
            case 3:
                result = mul_1(&operands_data, cl);
                break;
            case 4:
                if (operands_data.operand2 == 0){
                  printf("Entrer un chiffre different de zero:");
                  operands_data.operand2 = readFloatInput(operation_choice,previous_result,0,0);
                 }
                result = div_1(&operands_data, cl);
                break;
            case 5:
                result = mod_1(&operands_data, cl);
                break;
            case 6:
                  
                 operands_data.operand2 = readFloatInput(operation_choice,previous_result,2,2);
                 result = puiss_1(&operands_data, cl);
                break;
            case 7:
                operands_data.operand2 = readFloatInput(operation_choice,previous_result,2,2);
                result = max_1(&operands_data, cl);
                break;
            case 8:
              
                operands_data.operand2 = readFloatInput(operation_choice,previous_result, 2, 2);
                result = min_1(&operands_data, cl);
                break;
            case 9: {
                float *result_float;
                result_float = sqrt_1(&operands_data.operand1, cl);
                if (result_float == NULL) {
                    clnt_perror(cl, "Erreur d'appel");
                    exit(1);
                }
              
                result = result_float;
                break;
            }
            case 10:
                result = fact_1(&operands_data.operand1, cl);
                break;
            default:
                printf("Operation non supportn");
                continue;
        }

        if (result == NULL) {
            clnt_perror(cl, "Erreur d'appel");
            exit(1);
        }

        printf("\nresultat %.2f\n", *result);
        printf("Voulez-vous effectuer une autre operation ? (1 pour oui / 0 pour non): ");

        previous_result = *result;

        int choice = readFloatInput(operation_choice,0,0,0);
        if (choice != 1) {
            continue_program = 0;
        }         
        
    }
}

int main(int argc, char *argv[]) {
    CLIENT *cl;

    if (argc < 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        exit(1);
    }

    cl = clnt_create(argv[1], CALC_PROG, CALC_VERS, "tcp");
    if (cl == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    performOperation(cl);

    clnt_destroy(cl);
    return 0;
}
