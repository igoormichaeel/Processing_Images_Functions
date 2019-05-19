#include <iostream>
#include <cstring>
#include <fstream> // para arquivos
#include <locale.h> // para pontuação do teclado brasileiro
#include <stdlib.h> // limpar a tela
#include <cstdlib> // exit()

/*OBS. SUBSTITUIÇÕES PARA LINUX:
- Substituir todos os system("cls") por system("clear");
- Substituir todos os system("PAUSE") por:
                                            cout << " Precione enter para continuar . . . ";
                                            getchar();
*/

using namespace std;

const int MAX = 512;
const int SMAX = 512;

struct Img{
    char tipo[MAX]; // identifica formato .ppm (P3)
    int linhas; //altura
    int colunas; // largura
    int maximo; // valor máximo admissível por cada pixel (255)
    int dados[MAX][MAX][3];
};

//Funções obrigatórias
void abre_img (char nome[], Img& img);
void salva_img (char nome[], Img img);
void corta_img (Img img_in, Img& img_out, int li, int ci, int lf, int cf);
//Funções implementáveis
void equaliza_histograma(Img img_in, Img& img_out);
void reduz_tamanho(Img img_in, Img& img_out);
void inverte (Img img_in, Img& img_out);
void aplica_mascara (Img img_in, Img& img_out);
void binariza_canal (Img img_in, Img& img_out, int limiar);
//Funções de interface
void interface_menu(int& menu, char nome_in[]);
void interface_edicao_concluida(int& opcao);
void interface_erro (int verificador_erro);
void interface_despedida ();

int main (){
    setlocale (LC_ALL, "Portuguese");
    int menu, opcao, limiar, li, ci, lf, cf;
    char nome_in[SMAX], nome_out[SMAX], resposta1[SMAX], resposta2[SMAX]="y", resposta3[SMAX]="Y", resposta4[SMAX]="n", resposta5[SMAX]="N";
    Img img_in, img_out, mascara;

    interface_menu(menu, nome_in);

    while (menu != 0){
        switch(menu){
            case 5:
                cout << " -> Informe o nome do arquivo que deseja abrir: ";
                cin.ignore();
                cin.getline(nome_in, SMAX);

                abre_img(nome_in, img_in);

                cout << " -> Informe o nome do arquivo que deseja salvar: ";
                cin.getline(nome_out, SMAX);

                while(strcmp(nome_in, nome_out) == 0){
                    cout << " Nomes iguais, deseja substituir o arquivo (Y/N)? ";
                    cin.getline(resposta1, SMAX);

                    while (strcmp(resposta1, resposta2) != 0 && strcmp(resposta1, resposta3) != 0 && strcmp(resposta1, resposta4) != 0 && strcmp(resposta1, resposta5) != 0){
                        cout << " Entrada inválida! Deseja substituir o arquivo (Y/N)? ";
                        cin.getline(resposta1, SMAX);
                    }
                    if (strcmp(resposta1, resposta2) == 0 || strcmp(resposta1, resposta3) == 0){
                        break;
                    }
                    else if (strcmp(resposta1, resposta4) == 0 || strcmp(resposta1, resposta5) == 0){
                        cout << " -> Informe o nome do arquivo que deseja salvar: ";
                        cin.getline(nome_out, SMAX);
                    }
                }

                equaliza_histograma(img_in, img_out);
                salva_img(nome_out, img_out);
                interface_edicao_concluida(opcao);

                if (opcao == 1){
                    interface_menu(menu, nome_in);
                }
                else if (opcao == 0){
                    interface_despedida();
                    return 0;
                }

                break;

            case 4:
                cout << " -> Informe o nome do arquivo que deseja abrir: ";
                cin.ignore();
                cin.getline(nome_in, SMAX);

                abre_img(nome_in, img_in);

                cout << " -> Informe o nome do arquivo que deseja salvar: ";
                cin.getline(nome_out, SMAX);

                while(strcmp(nome_in, nome_out) == 0){
                    cout << " Nomes iguais, deseja substituir o arquivo (Y/N)? ";
                    cin.getline(resposta1, SMAX);

                    while (strcmp(resposta1, resposta2) != 0 && strcmp(resposta1, resposta3) != 0 && strcmp(resposta1, resposta4) != 0 && strcmp(resposta1, resposta5) != 0){
                        cout << " Entrada inválida! Deseja substituir o arquivo (Y/N)? ";
                        cin.getline(resposta1, SMAX);
                    }
                    if (strcmp(resposta1, resposta2) == 0 || strcmp(resposta1, resposta3) == 0){
                        break;
                    }
                    else if (strcmp(resposta1, resposta4) == 0 || strcmp(resposta1, resposta5) == 0){
                        cout << " -> Informe o nome do arquivo que deseja salvar: ";
                        cin.getline(nome_out, SMAX);
                    }
                }

                reduz_tamanho(img_in, img_out);
                salva_img(nome_out, img_out);
                interface_edicao_concluida(opcao);

                if (opcao == 1){
                    interface_menu(menu, nome_in);
                }
                else if (opcao == 0){
                    interface_despedida();
                    return 0;
                }

                break;

            case 3:
                cout << " -> Informe o nome do arquivo que deseja abrir: ";
                cin.ignore();
                cin.getline(nome_in, SMAX);

                abre_img(nome_in, img_in);

                cout << " -> Informe o nome do arquivo que deseja salvar: ";
                cin.getline(nome_out, SMAX);

                while(strcmp(nome_in, nome_out) == 0){
                    cout << " Nomes iguais, deseja substituir o arquivo (Y/N)? ";
                    cin.getline(resposta1, SMAX);

                    while (strcmp(resposta1, resposta2) != 0 && strcmp(resposta1, resposta3) != 0 && strcmp(resposta1, resposta4) != 0 && strcmp(resposta1, resposta5) != 0){
                        cout << " Entrada inválida! Deseja substituir o arquivo (Y/N)? ";
                        cin.getline(resposta1, SMAX);
                    }
                    if (strcmp(resposta1, resposta2) == 0 || strcmp(resposta1, resposta3) == 0){
                        break;
                    }
                    else if (strcmp(resposta1, resposta4) == 0 || strcmp(resposta1, resposta5) == 0){
                        cout << " -> Informe o nome do arquivo que deseja salvar: ";
                        cin.getline(nome_out, SMAX);
                    }
                }

                inverte(img_in, img_out);
                salva_img(nome_out, img_out);
                interface_edicao_concluida(opcao);

                if (opcao == 1){
                    interface_menu(menu, nome_in);
                }
                else if (opcao == 0){
                    interface_despedida();
                    return 0;
                }

                break;

            case 2:
                cout << " -> Informe o nome do arquivo que deseja abrir: ";
                cin.ignore();
                cin.getline(nome_in, SMAX);

                abre_img(nome_in, img_in);

                cout << " -> Informe um valor para o limiar: ";
                cin >> limiar;

                while (limiar < 0 || limiar > 255){
                    cout << " Número inválido! Digite um número entre 0 e 255: ";
                    cin >> limiar;
                }

                binariza_canal(img_in, img_out, limiar);

                cout << " -> Deseja aplicar a mascara à sua edição (Y/N)? ";
                cin.ignore();
                cin.getline(resposta1, SMAX);

                while (strcmp(resposta1, resposta2) != 0 && strcmp(resposta1, resposta3) != 0 && strcmp(resposta1, resposta4) != 0 && strcmp(resposta1, resposta5) != 0){
                    cout << " Entrada inválida! Deseja aplicar a mascara à sua edição (Y/N)? ";
                    cin.getline(resposta1, SMAX);
                }
                if (strcmp(resposta1, resposta2) == 0 || strcmp(resposta1, resposta3) == 0){
                    aplica_mascara(img_in, img_out);
                }

                cout << " -> Informe o nome do arquivo que deseja salvar: ";
                cin.getline(nome_out, SMAX);

                while(strcmp(nome_in, nome_out) == 0){
                    cout << " Nomes iguais, deseja substituir o arquivo (Y/N)? ";
                    cin.getline(resposta1, SMAX);

                    while (strcmp(resposta1, resposta2) != 0 && strcmp(resposta1, resposta3) != 0 && strcmp(resposta1, resposta4) != 0 && strcmp(resposta1, resposta5) != 0){
                        cout << " Entrada inválida! Deseja substituir o arquivo (Y/N)? ";
                        cin.getline(resposta1, SMAX);
                    }
                    if (strcmp(resposta1, resposta2) == 0 || strcmp(resposta1, resposta3) == 0){
                        break;
                    }
                    else if (strcmp(resposta1, resposta4) == 0 || strcmp(resposta1, resposta5) == 0){
                        cout << " -> Informe o nome do arquivo que deseja salvar: ";
                        cin.getline(nome_out, SMAX);
                    }
                }

                salva_img(nome_out, img_out);
                interface_edicao_concluida(opcao);

                if (opcao == 1){
                    interface_menu(menu, nome_in);
                }
                else if (opcao == 0){
                    interface_despedida();
                    return 0;
                }

                break;

            case 1:
                cout << " -> Informe o nome do arquivo que deseja abrir: ";
                cin.ignore();
                cin.getline(nome_in, SMAX);

                abre_img(nome_in, img_in);

                cout << " -> Informe a linha inicial: ";
                cin >> li;

                while (li < 0 || li >= img_in.linhas){
                    cout << " Número inválido! Digite uma linha entre 0 e " << img_in.linhas - 1 << ": ";
                    cin >> li;
                }

                cout << " -> Informe a coluna inicial: ";
                cin >> ci;

                while (ci < 0 || ci >= img_in.colunas){
                    cout << " Número inválido! Digite uma coluna entre 0 e " << img_in.colunas - 1 << ": ";
                    cin >> ci;
                }

                cout << " -> Informe a linha final: ";
                cin >> lf;

                while (lf < li || lf >= img_in.linhas){
                    cout << " Número inválido! Digite uma linha entre " << li << " e " << img_in.linhas - 1 << ": ";
                    cin >> lf;
                }

                cout << " -> Informe a coluna final: ";
                cin >> cf;

                while (cf < ci || cf >= img_in.colunas){
                    cout << " Número inválido! Digite uma coluna entre " << ci << " e " << img_in.colunas - 1 << ": ";
                    cin >> cf;
                }

                cout << " -> Informe o nome do arquivo que deseja salvar: ";
                cin.ignore();
                cin.getline(nome_out, SMAX);

                while(strcmp(nome_in, nome_out) == 0){
                    cout << " Nomes iguais, deseja substituir o arquivo (Y/N)? ";
                    cin.getline(resposta1, SMAX);

                    while (strcmp(resposta1, resposta2) != 0 && strcmp(resposta1, resposta3) != 0 && strcmp(resposta1, resposta4) != 0 && strcmp(resposta1, resposta5) != 0){
                        cout << " Entrada inválida! Deseja substituir o arquivo (Y/N)? ";
                        cin.getline(resposta1, SMAX);
                    }
                    if (strcmp(resposta1, resposta2) == 0 || strcmp(resposta1, resposta3) == 0){
                        break;
                    }
                    else if (strcmp(resposta1, resposta4) == 0 || strcmp(resposta1, resposta5) == 0){
                        cout << " -> Informe o nome do arquivo que deseja salvar: ";
                        cin.getline(nome_out, SMAX);
                    }
                }

                corta_img(img_in, img_out, li, ci, lf, cf);
                salva_img(nome_out, img_out);
                interface_edicao_concluida(opcao);

                if (opcao == 1){
                    interface_menu(menu, nome_in);
                }
                else if (opcao == 0){
                    interface_despedida();
                    return 0;
                }

                break;

            case 0:
                interface_despedida();
                return 0;

                break;
        }
    }

    interface_despedida();

    return 0;
}

void abre_img (char nome[], Img& img){
    int i, j, k, verificador_erro;
    char teste_tipo[] = "P3";
    fstream arq;

    arq.open(nome);
    arq.getline(img.tipo, SMAX);
    arq >> img.colunas >> img.linhas >> img.maximo;

    if (!arq.is_open()){
        verificador_erro = 0;
    }
    else if(strcmp(img.tipo, teste_tipo) != 0){
        verificador_erro = 1;
    }
    else if (img.linhas < 0 || img.linhas > 512 || img.colunas < 0 || img.colunas > 512){
        verificador_erro = 2;
    }

    if (verificador_erro == 0 || verificador_erro == 1 || verificador_erro == 2){
        interface_erro(verificador_erro);
    }

    for (i=0; i<img.linhas; i++){
        for (j=0; j<img.colunas; j++){
            for (k=0; k<3; k++){
                arq >> img.dados[i][j][k];
            }
        }
    }
}

void salva_img(char nome[], Img img){
    int i, j, k, verificador_erro;
    ofstream arq;

    arq.open(nome);

    if (!arq.is_open()){
        verificador_erro = 3;
    }
    if (verificador_erro == 3){
        interface_erro(verificador_erro);
    }

    arq << "P3" << endl;
    arq << img.colunas << " " << img.linhas << endl;
    arq << 255 << endl;

    for (i=0; i<img.linhas; i++){
        for (j=0; j<img.colunas; j++){
            for (k=0; k<3; k++){
                arq << img.dados[i][j][k] << " ";
            }
        }
        arq << endl;
    }
}

void corta_img (Img img_in, Img& img_out, int li, int ci, int lf, int cf){
    int i, j, k;

    img_out.linhas = lf - li + 1;
    img_out.colunas = cf - ci + 1;

    for (i=0; i<img_out.linhas; i++){
        for (j=0; j<=img_out.colunas; j++){
            for (k=0; k<3; k++){
                img_out.dados [i][j][k] = img_in.dados[i+li][j+ci][k];
            }
        }
    }
}

void equaliza_histograma(Img img_in, Img& img_out){
    int i, j, k, r, vR[256]={}, vG[256]={}, vB[256]={}, sR=0, sG=0, sB=0;

    img_out.linhas = img_in.linhas;
    img_out.colunas = img_in.colunas;

    for (i=0; i<img_in.linhas; i++){
        for (j=0; j<img_in.colunas; j++){
            for (k=0; k<3; k++){
                if (k==0){
                    vR[img_in.dados[i][j][k]]++;
                }
                else if (k==1){
                    vG[img_in.dados[i][j][k]]++;
                }
                else{
                    vB[img_in.dados[i][j][k]]++;
                }

            }
        }
    }

    for (i=0; i<img_in.linhas; i++){
        for (j=0; j<img_out.colunas; j++){
            for (k=0; k<3; k++){
                for(r=0; r<=img_in.dados[i][j][k]; r++){
                    sR += vR[r];
                    sG += vG[r];
                    sB += vB[r];
                }

                if (k==0){
                    img_out.dados[i][j][k] = sR*255/(img_in.linhas*img_in.colunas);
                }
                else if (k==1){
                    img_out.dados[i][j][k] = sG*255/(img_in.linhas*img_in.colunas);
                }
                else{
                    img_out.dados[i][j][k] = sB*255/(img_in.linhas*img_in.colunas);
                }
                sR=0;
                sG=0;
                sB=0;
            }
        }
    }
}

void aplica_mascara (Img img_in, Img& img_out){
    int i, j, k;
    Img mascara;

    mascara.linhas = img_in.linhas;
    mascara.colunas = img_in.colunas;

    for (i=0; i<img_in.linhas; i++){
        for (j=0; j<img_in.colunas; j++){
            for (k=0; k<3; k++){
                if (j<img_in.colunas/2){
                    mascara.dados[i][j][k] = 0;
                }
                else{
                    mascara.dados[i][j][k] = 255;
                }
            }
        }
    }

    for (i=0; i<img_in.linhas; i++){
        for (j=0; j<img_in.colunas; j++){
            for (k=0; k<3; k++){
                if (mascara.dados[i][j][k]==0){
                    img_out.dados[i][j][k] = img_in.dados[i][j][k];
                }
            }
        }
    }
}

void binariza_canal (Img img_in, Img& img_out, int limiar){
    int i, j, k;

    img_out.colunas = img_in.colunas;
    img_out.linhas = img_in.linhas;


    for (i=0; i<img_in.linhas; i++){
        for (j=0; j<img_in.colunas; j++){
            for (k=0; k<3; k++){
                if (img_in.dados[i][j][k] >= limiar){
                    img_out.dados[i][j][k] = 255;
                }
                else{
                    img_out.dados[i][j][k] = 0;
                }
            }
        }
    }
}

void reduz_tamanho(Img img_in, Img& img_out){
    int i, j, k, l, c;

    img_out.linhas = img_in.linhas/2;
    img_out.colunas = (img_in.colunas/2);

    for (i=0, l=0; i<img_in.linhas; i+=2, l++){
        for (j=0, c=0; j<img_in.colunas; j+=2, c++){
            for (k=0; k<3; k++){
                img_out.dados[l][c][k] = img_in.dados [i][j][k];
            }
        }
    }
}

void inverte (Img img_in, Img& img_out){
    int i, j, k;

    img_out.linhas = img_in.linhas;
    img_out.colunas = img_in.colunas;

    for (i=0; i<img_in.linhas; i++){
        for (j=0; j<img_in.colunas; j++){
            for (k=0; k<3; k++){
                img_out.dados[i][j][k] = img_in.dados[img_in.linhas - 1 - i][j][k];
            }
        }
    }
}

void interface_menu(int& menu, char nome_in[]){
    system("cls");
    //system("clear")

    int i;

    cout << " ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n               P H O T O S H O P \n ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n                 Menu principal\n ";

    for (i=0; i<45; i++){
        cout << "-";
    }

    cout << "\n\n  5 - Equalizar histograma da imagem\n";
    cout << "  4 - Reduzir tamanho da imagem\n";
    cout << "  3 - Inverter imagem verticalmente\n";
    cout << "  2 - Binarizar imagem por canal\n";
    cout << "  1 - Cortar imagem\n";
    cout << "  0 - Sair\n\n ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n -> Digite sua opção: ";
    cin >> menu;

    while (menu<0 || menu>5){
            cout << " Opção inválida! Digite uma nova opção: ";
            cin >> menu;
    }
}

void interface_edicao_concluida(int& opcao){
    system("cls");
    //system("clear")

    int i;

    cout << " ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n               P H O T O S H O P \n ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n   Edição feita e imagem salva com sucesso!\n ";

    for (i=0; i<45; i++){
        cout << "-";
    }

    cout << "\n\n         Deseja editar uma nova imagem?\n\n";
    cout << "                    1 - Sim" << endl << "                    0 - Não" << "\n\n ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n -> Digite sua opção: ";
    cin >> opcao;

    while (opcao!=0 && opcao!=1){
        cout << " Opção inválida! Digite uma nova opção: ";
        cin >> opcao;
    }
}

void interface_erro (int verificador_erro){
    system("cls");
    //system("clear")

    int i;

    cout << " ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n               P H O T O S H O P \n ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n            Erro ao abrir arquivo!\n ";

    for (i=0; i<45; i++){
        cout << "-";
    }
    if (verificador_erro == 0){
        cout << "\n\n\n\n            ARQUIVO NÃO ENCONTRADO!\n\n\n\n ";
    }
    else if (verificador_erro == 1){
        cout << "\n\n\n\n            FORMATO NÃO SUPORTADO!\n\n\n\n ";
    }
    else if (verificador_erro == 2){
        cout << "\n\n\n\n          TAMANHO DO ARQUIVO EXCEDIDO!\n\n\n\n ";
    }
    else if (verificador_erro == 3){
        cout << "\n\n\n\n       DISCO CHEIO OU FALTA DE PERMISSÃO!\n\n\n\n ";
    }

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n ";

    system("PAUSE");
    //cout << " Precione enter para continuar . . . ";
    //getchar();
    interface_despedida();
    exit(0);
}

void interface_despedida(){
    system("cls");
    //system("clear")

    int i;

    cout << " ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n               P H O T O S H O P \n ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n            Finalizado com sucesso!\n ";

    for (i=0; i<45; i++){
        cout << "-";
    }

    cout <<  "\n\n\n   Desenvolvido por: Beatriz Moura\n                     Daniel Cardoso\n                     Igor Michael\n\n\n ";

    for (i=0; i<22; i++){
        cout << "=-";
    }

    cout << "=\n ";

    system("PAUSE");
    //cout << " Precione enter para continuar . . . ";
    //getchar();
}
