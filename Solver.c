#include <stdio.h>

#define n 4

void imprimeTabuleiro(int tabuleiro[n][n]);
bool resolveTabuleiro(int tabuleiro[n][n], int coluna);
bool calculaPosicao(int tabuleiro[n][n], int linha, int coluna);

void imprimeTabuleiro(int tabuleiro[n][n]) {
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("%d ", tabuleiro[i][j]);
		}
		printf("\n");
	}
}

//approach: percorrendo colunas
bool resolveTabuleiro(int tabuleiro[n][n], int coluna) {

	int i;

	 /*
	* Condição de parada. 
	* Se n excede tamanho do tabuleiro, todas as colunas possuem ao menos uma rainha em posição segura.
	 */
	if(coluna >= n) {
		return true;
	}

	 /*
	* Para cada coluna, varra linhas para inserir uma rainha.
	* Chame a função recursivamente até cada rainha estar inserida numa célula segura. 
	 */
	for(i = 0; i < n; i++) {
		if(calculaPosicao(tabuleiro, i, coluna) == true) { //posição Segura?
			tabuleiro[i][coluna] = 1; //sim. insira rainha. (1 = rainha, 0 = vazio)
			
			if(resolveTabuleiro(tabuleiro, coluna+1) == true) { 
				return true; //assuma coluna atual resolvida. resolva próxima coluna
			}
			tabuleiro[i][coluna] = 0; //configuração levou a uma coluna que não pôde ser preenchida. Remova a rainha (Backtrack).
		} // não. Retorne ao laço
	}
	
	return false; //tratando tabuleiros 2x2 e 3x3 - não possuem solução.
}

//calculo de posição segura dado um tabuleiro [n][n]
bool calculaPosicao(int tabuleiro[n][n], int linha, int coluna) {
	int i, j;

	 /*
	* Como utilizamos um approach de colunas, 
	* precisamos checar apenas linhas da atual coluna
	* e diagonais anteriores a atual coluna.
	 */
	
	//linhas
	for(j = 0; j < coluna; j++) {
		if(tabuleiro[linha][j] == 1) { //encontrou uma rainha na mesma linha?
			return false; //insegura!
		}
	}

	//diagonal ascendente
	for(i = linha, j = coluna; i >= 0 && j >= 0; i--, j--) {
		if(tabuleiro[i][j] == 1) {
			return false;
		}
	}

	//diagonal descendente
	for (i = linha, j = coluna; i < n && j >= 0; i++, j--) {
		if (tabuleiro[r][c] == 1) {
			return false;
		}
	}

	return true;
}

int main(void) {
	
	/*
	* Inicia-se um tabuleiro nxn.
	* 0 = célula vazia
	* 1 = célula contém rainha
	 */
	int tabuleiro[n][n] = {0};

	if(resolveTabuleiro(tabuleiro, 0) == false) {
		printf("Tabuleiro 2x2 ou 3x3 - sem solução\n");
	} else {
		display(tabuleiro);
	}

	return 0;
}
