int validaData(int dia, int mes, int ano) {
    int quantDias;

    if (mes < 1 || mes > 12)
        return 0;

    if (mes == 2) {
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
            quantDias = 29;
        else
            quantDias = 28;
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        quantDias = 30;
    else
        quantDias = 31;

    if (dia < 1 || dia > quantDias)
        return 0;

    return 1;
}
