#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ASSERT(expr,instruction) if (!(expr)) { \
    instruction; \
    return EXIT_FAILURE; \
}

#define FIRST_UPPER 65 // A
#define LAST_UPPER 90  // Z

#define FIRST_LOWER 97 // a
#define LAST_LOWER 122 // z

// Imprimir a usagem correta do programa
void usage(char* program_name)
{
    char msg[1024] = "Usagem:\n\t";
    strcat(msg, program_name);
    strcat(msg, " (encrypt|e|decrypt|d) <text> [--offset <n>]\n");

    strcat(msg, "Commands:\n\tencrypt, e: Encripta \'text\' com um offset de 1, transformando, por exemplo, A em B ou Z em A\n\tdecrypt, d: Decripta \'text\' com um offset de 1, transformando, por exemplo, A em Z ou Z em Y\nOptions:\n\t--offset: Especificar o offset para (de/en)criptar");
//    strcat(msg, "Commands:\n\tencrypt, e: Encripta \'text\' com um offset de 1\n\tdecrypt, d: Decripta \'text\' com um offset de 1\nOptions:\n\t--offset: Especificar o offset para (de/en)criptar assim que o programa for iniciado");

    fprintf(stderr, msg);
}

int encrypt (const char* string, int offset, char* result, size_t str_len)
{
    for (int i = 0; i < str_len; ++i) {
        // Se for uma letra maiúscula e estiver maior que 90 (Z)
        if (string[i] <= LAST_UPPER && string[i]+offset > LAST_UPPER)
            result[i] = (FIRST_UPPER) + ((string[i]+offset) - LAST_UPPER) - 1;
        // Se for uma letra minúscula e estiver maior que 122 (z)
        else if (string[i] <= LAST_LOWER && string[i]+offset > LAST_LOWER)
            result[i] = FIRST_LOWER + ((string[i]+offset) - LAST_LOWER) - 1;
        // Se não for uma letra, deixar como está
        else if (!(string[i] >= FIRST_UPPER && string[i] <= LAST_LOWER))
            result[i] = string[i];
        // Se tudo ocorrer normalmente (não precisar dar a volta)
        else result[i] = string[i]+offset;
    }

    // Termo de encerramento (caractere nulo)
    result[str_len] = '\0';

    return EXIT_SUCCESS;
}

int decrypt (char* string, int offset, char* result, size_t str_len)
{
    for (int i = 0; i < str_len; ++i) {
        // Se for uma letra minúscula (maior ou igual a 97 (a)) e estiver menor que 97 (a)
        if (string[i] >= FIRST_LOWER && string[i]-offset < FIRST_LOWER)
            result[i] = LAST_LOWER - (FIRST_LOWER - (string[i]-offset)) + 1;
        // Se for uma letra maiúscula (maior ou igual a 65 (A) e estiver maior que 65 (A)
        else if (string[i] >= FIRST_UPPER && string[i]-offset < FIRST_UPPER)
            result[i] = LAST_UPPER - (FIRST_UPPER - (string[i]-offset)) + 1;
        // Se não for uma letra, deixar como está
        else if (!(string[i] >= FIRST_UPPER && string[i] <= LAST_LOWER))
            result[i] = string[i];
        // Se tudo ocorrer normalmente (não precisar dar a volta)
        else result[i] = string[i]-offset;
    }

    // Termo de encerramento (caractere nulo)
    result[str_len] = '\0';

    return EXIT_SUCCESS;
}

int main (int argc, char* argv[])
{
    ASSERT(argc>2, usage(argv[0])); // Assegurar que há pelo menos dois argumentos (comando e texto)

    // Deixar o offset default como 1
    int offset = 1;
    char* result;

    // Se for especificado --offset
    if (argc>3 && strcmp(argv[3], "--offset") == 0)
    {
        /*
        printf("Offset: ");
        scanf("%d", &offset);
        */
        if (!argv[4]) { usage(argv[0]); return EXIT_FAILURE; } // Se não houver número após '--offset', mostrar uso
        else offset = atoi(argv[4]); // Converter o argumento de string para int
    }

    // Comando de encriptar
    if (strcmp(argv[1], "encrypt") == 0 || strcmp(argv[1], "e") == 0)
    {
        encrypt(argv[2], offset, result, strlen(argv[2]));
    }
    // Comando de decriptar
    else if (strcmp(argv[1], "decrypt") == 0 || strcmp(argv[1], "d") == 0)
    {
        decrypt(argv[2], offset, result, strlen(argv[2]));
    }
    // Caso o comando não exista
    else {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Imprimir as informações na tela
    printf("Input: %s\n", argv[2]);
    printf("Offset: %d\n", offset);
    printf("Resultado: %s\n", result);

    return EXIT_SUCCESS;
}
