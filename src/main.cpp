////////////////////////////////
/// Inclusóo das bibliotecas ///
////////////////////////////////
#include <string>
#include <iostream>

#include <mysql.h>

///////////////////
/// Protótipos ////
///////////////////
bool conectar();
void exibeMenu();
void desconectar();
void verCompromissos();
void editarCompromisso();
void removerCompromisso();
void adicionarCompromisso();
void mostrarErroDoMysql(MYSQL *mysql);

/////////////////////////////
/// Varióveis globais X<( ///
/////////////////////////////

/**
 * Contem a conexao com o banco de dados
 */
MYSQL *conexao;
bool conectado = false;

//////////////////
/// Constantes ///
//////////////////

const unsigned int ADICIONAR_COMPROMISSO = 0;
const unsigned int REMOVER_COMPROMISSO = 1;
const unsigned int MOSTRAR_COMPROMISSO = 2;
const unsigned int EDITAR_COMPROMISSO = 3;
const unsigned int SAIR = 4;

/**
 * Funcao principal
 */
int main(int argc, char **argv)
{

	// Exibe a mensagem de boas vindas
	std::cout << "Boas vindas da agenda!" << std::endl;

	bool continuarExecutando = true;

	exibeMenu();

	// Guarda a opcao escolhida
	int opcao;

	// Entra em um loop infinito perguntando
	// o que o usuario deseja fazer
	while (continuarExecutando)
	{

		// Pergunta a opcao do usuario
		std::cin >> opcao;

		// Executa a opcao escolhida
		switch (opcao)
		{
			case ADICIONAR_COMPROMISSO:
				adicionarCompromisso();
				break;
			case REMOVER_COMPROMISSO:
				removerCompromisso();
				break;
			case MOSTRAR_COMPROMISSO:
				verCompromissos();
				break;
			case EDITAR_COMPROMISSO:
				editarCompromisso();
				break;
			case SAIR:
				continuarExecutando = false;
		}

		// Exibe o menu novamente
		if (continuarExecutando)
		{
			exibeMenu();
		}
	}

	std::cout << "Saindo... Ate a proxima!" << std::endl;
	desconectar();
	return 0;
}

void editarCompromisso()
{
	// Verifica se a conexao foi realizada com sucesso
	if (!conectar())
	{
		std::cout << "Falha ao conectar ao banco de dados!" << std::endl;
		return;
	}

	std::cout << "Escolha um código de compromisso para editar:" << std::endl;
	verCompromissos();
	std::cout << "Código:";

	int codCompromisso;
	std::cin >> codCompromisso;

	// Variaveis usadas para montar o query
	std::string dia, mes, ano, descricao;

	// Solicita o dia do compromisso
	std::cout << "Informe o dia:";
	std::cin >> dia;

	// Solicita o mós do compromisso
	std::cout << "Informe o mês:";
	std::cin >> mes;

	// Solicita o ano do compromisso
	std::cout << "Informe o ano:";
	std::cin >> ano;

	// Limpa a memoria de qualquer caractere restante
	// Se isso nao for feito getline nao funciona
	std::cin.ignore();

	// Solicita a descricao do compromisso
	std::cout << "Descreva o compromisso:";
	std::getline(std::cin, descricao);

	// Monta a query
	std::string sql = "update Compromisso set data='" + ano + "-" + mes + "-" + dia + "', descricao='" + descricao + "' where cod=" + std::to_string(codCompromisso);

	// Executa a query
	int statusDeExecucao = mysql_query(conexao, sql.data());

	// Verifica se deu tudo certo
	if (statusDeExecucao == 0)
	{
		// Deu certo!
		std::cout << "Compromisso atualizado" << std::endl;
	} else
	{
		// Algo deu errado!
		mostrarErroDoMysql(conexao);
		std::cout << "Falha ao atualizar compromisso!" << std::endl;
	}

}
void removerCompromisso()
{
	std::cout << "Escolha um código de compromisso para remover:" << std::endl;
	verCompromissos();
	std::cout << "Código:";

	int codCompromisso;
	std::cin >> codCompromisso;

	// Monta a query
	std::string sql = "delete from Compromisso where cod=" + std::to_string(codCompromisso);

	// Executa a query
	int statusDeExecucao = mysql_query(conexao, sql.data());

	// Verifica se deu tudo certo
	if (statusDeExecucao == 0)
	{
		// Deu certo!
		std::cout << "Compromisso apagado!" << std::endl;
	} else
	{
		// Algo deu errado!
		mostrarErroDoMysql(conexao);
		std::cout << "Falha ao apagar compromisso!" << std::endl;
	}

}

/**
 * Exibe um menu para o usuório
 */
void exibeMenu()
{
	std::cout << "Escolha uma opção:" << std::endl;
	std::cout << ADICIONAR_COMPROMISSO << " - Adicionar compromisso" << std::endl;
	std::cout << REMOVER_COMPROMISSO << " - Remover compromisso" << std::endl;
	std::cout << MOSTRAR_COMPROMISSO << " - Mostrar compromisso" << std::endl;
	std::cout << EDITAR_COMPROMISSO << " - Editar compromisso" << std::endl;
	std::cout << SAIR << " - SAIR" << std::endl;
}

/**
 * Mostra os erros que podem ocorrer na conexóo
 * @param mysql
 */
void mostrarErroDoMysql(MYSQL *mysql)
{
	printf("Erro: (%d) [%s] \"%s\"", mysql_errno(mysql), mysql_sqlstate(mysql), mysql_error(mysql));
	mysql_close(mysql);
	exit(-1);
}

/**
 * Conecta no banco de dados
 * @return - true: Conectou, false: Falha ao conectar
 */
bool conectar()
{

	if (conectado) return true;

	conexao = mysql_init(NULL);
	if (!mysql_real_connect(conexao, "127.0.0.1", "root", "1234", "Agenda", 3306, NULL, 0))
	{
		mostrarErroDoMysql(conexao);

		conectado = false;
		return false;
	}

	conectado = true;
	return true;
}

/**
 * Desconecta do banco de dados
 */
void desconectar()
{
	mysql_close(conexao);
	conectado = false;
}

/**
 * Adiciona um compromisso
 */
void adicionarCompromisso()
{

	// Verifica se a conexao foi realizada com sucesso
	if (!conectar())
	{
		std::cout << "Falha ao conectar ao banco de dados!" << std::endl;
		return;
	}

	// VariÃ¡veis usadas para montar o query
	std::string dia, mes, ano, descricao;

	// Solicita o dia do compromisso
	std::cout << "Informe o dia:";
	std::cin >> dia;

	// Solicita o mós do compromisso
	std::cout << "Informe o mós:";
	std::cin >> mes;

	// Solicita o ano do compromisso
	std::cout << "Informe o ano:";
	std::cin >> ano;

	// Limpa a memória de qualquer caractere restante
	// Se isso nóo for feito getline nóo funciona
	std::cin.ignore();

	// Solicita a descricao do compromisso
	std::cout << "Descreva o compromisso:";
	std::getline(std::cin, descricao);

	// Monta a query
	std::string sql = "insert into Compromisso (data, descricao)values('" + ano + "-" + mes + "-" + dia + "','" + descricao + "')";

	// Executa a query
	int statusDeExecucao = mysql_query(conexao, sql.data());

	// Verifica se deu tudo certo
	if (statusDeExecucao == 0)
	{
		// Deu certo!
		std::cout << "Compromisso inserido" << std::endl;
	} else
	{
		// Algo deu errado!
		mostrarErroDoMysql(conexao);
		std::cout << "Falha ao inserir compromisso!" << std::endl;
	}

}

void verCompromissos()
{

	// Verifica se a conexóo foi realizada com sucesso
	if (!conectar())
	{
		std::cout << "Falha ao conectar ao banco de dados!" << std::endl;
		return;
	}

	// Guarda um registro
	MYSQL_ROW registro;

	// Guarda todos os registros retornados
	MYSQL_RES *resultados;

	// Executa a query
	int statusDeExecucao = mysql_query(conexao, "SELECT cod, data, descricao FROM Compromisso");

	// Verifica se deu tudo certo
	if (statusDeExecucao == 0)
	{

		// Deu certo! Recupera os registros retornados;
		resultados = mysql_store_result(conexao);

		// Mostra os registros retornados
		while ((registro = mysql_fetch_row(resultados)))
		{
			std::cout << registro[0] << "\t" << registro[1] << "\t" << registro[2] << std::endl;
		}
	} else
	{
		// Algo deu errado!
		mostrarErroDoMysql(conexao);
		std::cout << "Falha ao recuperar os registros!" << std::endl;
	}
}
