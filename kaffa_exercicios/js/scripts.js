function validarCNPJ() {
    var form = document.forms["formcnpj"];
    var cnpj = form.cnpjbox.value;

    //Elimina os caracteres não numéricos
    cnpj = cnpj.replace(/[^\d]+/g, '');

    if (cnpj == ''){
        alert('CNPJ inválido');
    } 
    //Verifica se a quantidade na string corresponde a 14 digitos
    else if (cnpj.length != 14) {
        alert('CNPJ inválido');
    }
    else
        alert('CNPJ válido');
}

function validarDigtsCNPJ() {
    var form = document.forms["formcnpjdigts"];
    var cnpjdigts = form.cnpjdigtsbox.value;

    cnpjdigts = cnpjdigts.replace(/[^\d]+/g, '');

    /*if (cnpjdigts == '') {
        alert('CNPJ com digitos inválidos');
        return;
    }*/
    
    if (cnpjdigts.length != 14) {
        alert('CNPJ com digitos inválidos');
        return;
    }
    // Elimina os cnpjs conhecidos e que sejam inválidos
    if (cnpjdigts == "00000000000000" ||
        cnpjdigts == "11111111111111" ||
        cnpjdigts == "22222222222222" ||
        cnpjdigts == "33333333333333" ||
        cnpjdigts == "44444444444444" ||
        cnpjdigts == "55555555555555" ||
        cnpjdigts == "66666666666666" ||
        cnpjdigts == "77777777777777" ||
        cnpjdigts == "88888888888888" ||
        cnpjdigts == "99999999999999") {
        alert('CNPJ com digitos inválidos');
        return;
    }
    // Verifica se a string possui todos os valores iguais
    tam = cnpjdigts.length - 2
    num = cnpjdigts.substring(0, tam);
    digitos = cnpjdigts.substring(tam);
    total = 0;
    posicao = tam - 7;
    for (i = tam; i >= 1; i--) {
        total += num.charAt(tam - i) * posicao--;
        if (posicao < 2)
            posicao = 9;
    }
    resultado = total % 11 < 2 ? 0 : 11 - total % 11;
    if (resultado != digitos.charAt(0)) {
        alert('CNPJ com digitos inválidos');
        return;
    }
    tam = tam + 1;
    num = cnpjdigts.substring(0, tam);
    total = 0;
    posicao = tam - 7;
    for (i = tam; i >= 1; i--) {
        total += num.charAt(tam - i) * posicao--;
        if (posicao < 2)
            posicao = 9;
    }
    resultado = total % 11 < 2 ? 0 : 11 - total % 11;
    if (resultado != digitos.charAt(1)) {
        alert('CNPJ com digitos inválidos');
        return;
    }

        alert('CNPJ com digitos validos segundo a Receita Federal');
        return;
}
    