//------------------------------------------------------------------------------------
 
 


Pontuacoes *ordenar(Pontuacoes *lista){
    Pontuacoes swap;
    for (int i=0;i<16;i++) {
        for (int j=0;j<15-i;j++){
            if (lista[j].pontuacao < lista[j+1].pontuacao) {
                swap = lista[j+1];
                lista[j+1] = lista[j];
                lista[j] = swap; 
            }
        }
    }
    return lista;
}

Pontuacoes *ler_arquivo(FILE *arq) {
    Pontuacoes *lista;
    lista = (Pontuacoes *) malloc(16*sizeof(Pontuacoes));
    for (int i=0;i<15;i++) {
        fread(lista[i].nome,sizeof(char),4,arq);
        fread(&lista[i].pontuacao,sizeof(long int),1,arq);
    }
    return lista;
}

void highscore(Pontuacoes player){
    FILE *arq = fopen("highscore.bin","a+b");
    Pontuacoes *lista;
    if(arq != NULL) {
        // Escrevendo no final do arquivo
        fwrite(player.nome,sizeof(char),4,arq);
        fwrite(&player.pontuacao,sizeof(long int),1,arq);
      
        // Lendo os arquivo de pontuação
        fseek(arq,SEEK_SET,0);
        lista = ler_arquivo(arq);
        lista[16] = player;
        // Ordenando a lista
        lista = ordenar(lista);
        // Reallocando so 15
        Pontuacoes aux = lista;
        lista = (Pontuacoes *) realloc(lista,15*sizeof(Pontuacoes));
        if (lista == NULL){
            printf("Erro de alocacao\n");
            free(aux);
            exit(1);
        }

        for (int i=0;i<15;i++) {
            fwrite(lista[i].nome,sizeof(char),4,arq);
            fwrite(&lista[i].pontuacao,sizeof(long int),1,arq);
        }
        fclose(arq);
    }
}

//------------------------------------------------------------------------------------